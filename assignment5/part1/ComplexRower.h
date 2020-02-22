#ifndef GITCS4500_COMPLEXROWER_H
#define GITCS4500_COMPLEXROWER_H

#include "../part1/row.h"
#include "../part1/rower.h"
#include "../part1/array.h"
#include "../part1/dataframe.h"

/**
 * This is a simple rower.
 */

class ComplexRower : public Rower {
public:
    class ComplexFielder_1: public Fielder{
    public:
        size_t int_sum;
        size_t float_sum;

        ComplexFielder_1(): int_sum(0), float_sum(0){
        }
        void accept(int i){
            int_sum += i;
        }

        void accept(float f){
            float_sum += f;
        }

        size_t get_int_sum() {
            return int_sum;
        }

        size_t get_float_sum() {
            return float_sum;
        }

    };

    class ComplexFielder_2: public Fielder{
    public:
        size_t _weather_float_num;

        ComplexFielder_2(): _weather_float_num(0){
        }

        void accept(float f){
            _weather_float_num ++;
        }

        size_t get_weather_num() {
            return _weather_float_num;
        }

    };

    class ComplexFielder_3: public Fielder{
    public:
        bool _POI;

        ComplexFielder_3():_POI(0){}
        void accept(bool b){
            _POI = _POI && b;
        }
        bool get_POI(){
            return _POI;
        }
    };



    class ComplexFielder_4: public Fielder{
    public:
        StringArray _output_description;
        ComplexFielder_4():_output_description((size_t)0){
        }
        void accept(String* s){
            _output_description.push(s);
        }
        StringArray get_all_string(){
            return _output_description;
        }
    };

    size_t index;
    int _int_sum;
    float _float_sum;
    int _weather_float_num;
    bool _poi_sum;


    ComplexRower(): index(0), _int_sum(0),_float_sum(0), _weather_float_num(0),_poi_sum(0){}

    bool accept(Row& r){
        ComplexFielder_1 cf1;
        ComplexFielder_2 cf2;
        ComplexFielder_3 cf3;
        ComplexFielder_3 cf4;
        for(size_t i = 0; i < r.width(); i++){
            r.visit(i,cf1);
            r.visit(i,cf2);
            r.visit(i,cf3);
            r.visit(i,cf4);
        }
        index++;
        _int_sum += cf1.get_int_sum();
        _float_sum += cf1.get_float_sum();
        _weather_float_num += cf2.get_weather_num();
        _poi_sum =_poi_sum && cf3.get_POI();

        return true;
    }


    void join_delete(Rower* other) {
        if(!other || other == this) return;
        ComplexRower *osr = dynamic_cast<ComplexRower*>(other);
        if(osr){
            _int_sum += osr->get_int_sum();
            _float_sum += osr->get_float_sum();
            _weather_float_num += osr->get_weather_sum();
            _poi_sum = _poi_sum && osr->get_bool();
        }
        delete other;
    }


    int get_int_sum(){
        return this->_int_sum;
    }
    float get_float_sum(){
        return this->_float_sum;
    }
    int get_weather_sum(){
        return this->_weather_float_num;
    }
    bool get_bool(){
        return this->_poi_sum;
    }
    void reset() {
        _int_sum = 0;
         _float_sum =0;
        _weather_float_num =0;
        _poi_sum = (bool)0;
    }

    Object *clone(){
        return new ComplexRower();
    }

};




#endif //GITCS4500_COMPLEXROWER_H
