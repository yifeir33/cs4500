#include <chrono>

#include <gtest/gtest.h>
#include <stdlib.h>

#include "modified_dataframe.h"

#define SEED 10232314

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


bool initalized = false;

void init() {
    srand(SEED);
    initalized = true;

}

int generate_int(){
    return rand() % 10000 * (rand() % 2 == 1 ? 1 : -1);
}

bool generate_bool(){
    return rand() % 2;
}

float generate_float(){
    return generate_int() * 100.0 / ((rand() % 50) * 1.0);
}

String *generate_string(){
    size_t length = rand() % 10;
    char* str = new char[length];
    for(size_t i = 0; i < length; ++i) {
        bool upper = rand() % 2;
        str[i] = (rand() % 26) + (upper ? 65 : 97);
    }
    String *s = new String(str);
    delete[] str;
    return s;
}

bool generate_large_dataframe(DataFrame& df, size_t nrows, StringArray *arr){
    if(!initalized) init();
    Schema& scm = df.get_schema();

    for(size_t i = 0; i < nrows; ++i){
        Row r(scm);
        for(size_t j = 0; j < scm.width(); ++j){
            switch(scm.col_type(i)) {
                case 'I':
                    {
                        r.set(j, generate_int());
                        break;
                    } 
                case 'F':
                    {
                        r.set(j, generate_float());
                        break;
                    }
                case 'B':
                    {
                        r.set(j, generate_bool());
                        break;
                    }
                case 'S':
                    {
                        String *s = generate_string();
                        r.set(j, s);
                        if(arr)
                            arr->push(s);
                        break;
                    }
                default:
                    return false;
            }
        }
        df.add_row(r);
    }
    return true;
}

class IntSumRower : public Rower {
public:
    class IntSumFielder : public Fielder {
    public:
        size_t _sum;

        IntSumFielder() : _sum(0) {}

        void accept(int i) {
            _sum += i;
        }

        size_t get_sum(){
            return _sum;
        }
    };
    size_t _sum;

    IntSumRower() : _sum(0) {}

    virtual bool accept(Row& r){
        IntSumFielder isf;
        r.visit(r.get_index(), isf);
        _sum += isf.get_sum();
        return true;
    }

    Object *clone() {
        return new IntSumRower();
    }

    virtual void join_delete(Rower* other) {
        if(!other) return;
        IntSumRower *isr = dynamic_cast<IntSumRower*>(other);
        if(isr){
            _sum += isr->get_sum();
        }
        delete other;
    }

    size_t get_sum(){
        return _sum;
    }
};

void test() {
  Schema s("IIIII");
  ModifiedDataFrame mdf(s);
  GT_TRUE(generate_large_dataframe(mdf, 1000000000, nullptr));
  size_t single_thread_result;
  size_t multi_thread_result;

  IntSumRower isr;

  auto single_thread_start = std::chrono::high_resolution_clock::now();
  mdf.map(isr);
  auto single_thread_end = std::chrono::high_resolution_clock::now();

  auto multi_thread_start = std::chrono::high_resolution_clock::now();
  mdf.pmap(isr);
  auto multi_thread_end = std::chrono::high_resolution_clock::now();

  // TODO
  exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
