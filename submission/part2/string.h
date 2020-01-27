#ifndef STRING_H
#define STRING_H

#include "object.h"

/**
 * String : This class represents a list of characters.
 *
 * Auther: resnik.n@husky.neu.edu & wang.yifei3@husky.neu.edu
 */
class String : public Object {
public:

    /** Constructs a new string containing the same array as c.
     *
     * A copy of the char array is stored.
     */
  String(const char *c) : _str(nullptr), _len(0) {
        if(c){
            while(c[_len] != '\0') ++_len; // find length assuming null termination
            this->_str = new char[this->_len + 1];
            for(size_t i = 0; i < this->_len; ++i){
                this->_str[i] = c[i];
            }
            this->_str[this->_len] = '\0';
        }
  };

    /** Copy Constructor - creates a new string object representing the same
     * char array as s
     *
     * @arg s - The string to construct a seperate object copy of.
     */
    String(String *s): _str(nullptr), _len(s->_len){
        if(s->_str){
            _str = new char[_len + 1];
            for(size_t i = 0; i < _len; ++i){
                _str[i] = s->_str[i];
            }
            _str[_len] = '\0';
        }
    };

    /** Destructor - deletes the internal character array */
    ~String(){
        if(_str){
            delete[] _str;
        }
    };

    /** Returns a unique numerical value for each string reprsentation (but not object). */
    size_t hash(){
        size_t h = 0;
        for(size_t i = 0; i < this->_len; ++i){
            h += _str[i]; // chars are really ints
        }
        return h;
    };

    /** Returns true if o is also a string object representing the same character array,
     * false otherwise.
     *
     * @arg o - The object to compare.
     *
     * @returns True is o is also a string object representing the same character array, false otherwise.
     */
    bool equals(Object *o){
        if(!o) return false;
        String *oStr = dynamic_cast<String *>(o);
        if(oStr != nullptr){
            return this->compare(oStr) == 0;
        }
        return false;
    }

    /** Compares the two strings alphanumerically.
     *
     * @arg s - The string to compare to this one.
     *
     * @returns - A negative value if this string has a lower alphanumerical value. 0 if they are the same.
     * A positive number if this string has a higher alphanumerical value.
     */
    int compare(String *s){
        if(!s) return -1;
        if(this->_str == s->_str) return 0;

        for(size_t i = 0; i < this->_len; ++i){
            int val = this->_str[i] - s->_str[i];
            if(val != 0){
                return val;
            }
        }
        if(this->_len < s->_len){
            return this->_str[this->_len] - s->_str[this->_len];
        }
        return 0;
    }

    /** Creates a new string object concatenating this string with s.
     *
     * @arg s - The string to concatenate to this one.
     *
     * @returns A pointer to a new string object containing the the character array
     * of the concatenated strings.
     */
    String *concat(String *s){
        if(!s){
            return this; 
        } else if(!s->_str){
            return this;
        } else if(!this->_str){
            return s;
        }

        char *buf = new char[this->_len + s->_len + 1];
        for(size_t i = 0; i < this->_len; ++i){
            buf[i] = this->_str[i];
        }

        for(size_t i = 0; i < s->_len; ++i){
            buf[this->_len + i] = s->_str[i];
        }
        buf[this->_len + s->_len] = '\0';
        String *c = new String(buf);
        delete[] buf;
        return c;
    }


    char *_str;
    size_t _len;

};

#endif
