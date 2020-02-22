#ifndef GITCS4500_SIMPLEROWER_H
#define GITCS4500_SIMPLEROWER_H

#include "../part1/row.h"
#include "../part1/rower.h"
#include "../part1/array.h"


/**
 * This is a simple rower.
 */

class SimpleRower : public Rower {
public:

    String* _output_description;
    float _distance_in_km;
    bool _poi;
    int _sev_plus_one;
    int _sofar;

    SimpleRower() : _output_description(0), _distance_in_km(0.0), _poi((bool)0), _sev_plus_one(1), _sofar(0){}

    bool accept(Row& r){
        int Severity = r.get_int(4);
        float distance = r.get_float(11);
        String* des = r.get_string(12);
        bool amenity = r.get_bool(42);

       _output_description = des;
        if(amenity  == 0){
            this->_poi = 0;
            /* std::cout <<"There is not a POI amenity record." <<std::endl; */
        } else{
            this->_poi = 1;
            /* std::cout <<"There is a POI amenityrecord." <<std::endl; */
        }
        this->_sev_plus_one = Severity + 1;
        /* std::cout <<"Severity plus one is:"<< _sev_plus_one <<std::endl; */
        this->_distance_in_km = distance * 1.609;
        /* std::cout <<"Distance in km is" << _distance_in_km<<std::endl; */
        _sofar++;

        return true;
    }


    void join_delete(Rower* other) {
        if(!other || other == this) return;
        SimpleRower *osr = dynamic_cast<SimpleRower*>(other);
        if(osr){
           _sofar += osr->get_sofar();
        }
        delete other;
    }

     int get_sofar(){
        return this->_sofar;
    }

    void reset(){
        _output_description = 0;
        _distance_in_km = 0;
        _poi = 0;
        _sev_plus_one = 1;
        _sofar = 0;
    }

    Object *clone(){
        return new SimpleRower();
    }
};



#endif //GITCS4500_SIMPLEROWER_H
