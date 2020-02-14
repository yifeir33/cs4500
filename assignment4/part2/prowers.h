#pragma once

#include <math.h>

#include "modified_dataframe.h"
#include "../part1/row.h"
#include "../part1/rower.h"
#include "../part1/fielder.h"

class IntSumRower : public Rower {
public:
    class IntSumFielder : public Fielder {
    public:
        size_t _sum;

        IntSumFielder() : _sum(0) {}

        void accept(int i) {
            _sum += i;
        }

        size_t get_sum() {
            return _sum;
        }

    };

    size_t _sum;

    IntSumRower() : _sum(0) {}

    bool accept(Row& r){
        IntSumFielder isf;
        r.visit(r.get_index(), isf);
        _sum += isf.get_sum();
        return true;
    }

    Object *clone() {
        return new IntSumRower();
    }

    void join_delete(Rower* other) {
        if(!other || other == this) return;
        IntSumRower *isr = dynamic_cast<IntSumRower*>(other);
        if(isr){
            _sum += isr->get_sum();
        }
        delete other;
    }

    size_t get_sum(){
        return _sum;
    }

    void reset() {
        _sum = 0;
    }
};

class AbsoluteValueRower : public Rower {
public:
    DataFrame& _df;

    AbsoluteValueRower(DataFrame& df) : _df(df) {}

    bool accept(Row& r){
        for(size_t c = 0; c < r.width(); ++c) {
            if(r.col_type(c) == 'I'){
                int ni = std::abs(r.get_int(c));
                assert(ni >= 0);
                _df.set(c, r.get_index(), ni);
            } else if(r.col_type(c) == 'F') {
                float of = r.get_float(c);
                float nf = std::abs(of);
                assert(nf >= 0);
                _df.set(c, r.get_index(), nf);
            }
        }
        return true;
    }

    Object *clone() {
        return new AbsoluteValueRower(_df);
    }
};

class NonNegativeRower : public Rower {
public:
    bool _sucess;

    NonNegativeRower() : _sucess(true) {}

    bool accept(Row& r){
        for(size_t c = 0; c < r.width(); ++c) {
            if(r.col_type(c) == 'I'){
                _sucess = _sucess && r.get_int(c) >= 0;
            } else if(r.col_type(c) == 'F') {
                _sucess = _sucess && r.get_float(c) >= 0;
            }
        }
        return true;
    }

    Object *clone() {
        return new NonNegativeRower();
    }

    bool sucessful() {
        return _sucess;
    }

    void reset() {
        _sucess = true;
    }

    void join_delete(Rower *other) {
        if(!other || other == this) return;
        NonNegativeRower *nnr = dynamic_cast<NonNegativeRower*>(other);
        if(nnr) {
            _sucess = _sucess && nnr->_sucess;
        }
        delete other;
    }
};

class StringCleanupRower : public Rower {
public:
    DataFrame& _df;

    StringCleanupRower(DataFrame& df) : _df(df) {}

    bool accept(Row& r) {
        for(size_t c = 0; c < r.width(); ++c) {
            if(r.col_type(c) == 'S'){
                String *s = r.get_string(c);
                _df.set(c, r.get_index(), nullptr);
                if(s) delete s;
            }
        }
        return true;
    }

    Object *clone() {
        return new StringCleanupRower(_df);
    }

};
