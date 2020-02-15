#include <gtest/gtest.h>
#include "dataframe.h"

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


//test Rower by creating a new GPA calculator
void test6() {

    // created as follow:
    // Student Name(String)  Course1_Credits(Int) Course1_grade(float) Course2_credits... has_bad_record(bool)
    Schema sch("SIFIFB");
    DataFrame df(sch);
    class GPA_calculator : public Rower {
    public:
        DataFrame* df_;
        GPA_calculator(DataFrame* df) :df_(df){
        }

        bool accept(Row& r ){
            float total = (int)r.get_int(1) * (float) r.get_float(2) +
                    (int)r.get_int(3) * (float)r.get_float(4);
            float GPA = total / ((float) r.get_int(1) + (float) r.get_int(3));
            if(r.get_bool(5)){
                GPA -= 0.3;
            }
            df_->set(6, r.get_index(), GPA);
            return true;
        }


    };

    //student doesnt have bad record
    Row annie(df.get_schema());
    String* annie1 = new String("Annie");
    annie.set(0, annie1);
    annie.set(1, 4);
    annie.set(2, (float)3.3);
    annie.set(3, 4);
    annie.set(4,(float)3.6);
    annie.set(5, 0);

    //student has bad record
    Row bo(df.get_schema());
    String* bo1 = new String("Bo");
    bo.set(0, bo1);
    bo.set(1, 4);
    bo.set(2, (float)2);
    bo.set(3, 4);
    bo.set(4,(float)3);
    bo.set(5, 1);
    df.add_row(bo);

    GPA_calculator gpa_calc(&df);
    df.map(gpa_calc);
    GT_EQUALS(df.get_float(6, 0), (float)3.45);
    GT_EQUALS(df.get_float(6, 1), (float)2.2);

    delete annie1, bo1;

}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test6); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

