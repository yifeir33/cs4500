// lang: CwC
#pragma once

#include "object.h"

/**
 * String : This class represents a list of characters.
 *
 * Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */
class String : public Object {
public:

    /** Constructs a new string containing the same array as c.
     *
     * A copy of the char array is stored.
     */
    String(const char *c);

    /** Copy Constructor - creates a new string object representing the same
     * char array as s
     *
     * @arg s - The string to construct a seperate object copy of.
     */
    String(String * const s);

    /** Destructor - deletes the internal character array */
    ~String();


    /** Compares the two strings alphanumerically.
     *
     * @arg s - The string to compare to this one.
     *
     * @returns - A negative value if this string has a lower alphanumerical value. 0 if they are the same.
     * A positive number if this string has a higher alphanumerical value.
     */
    int cmp(String* const s);

    /** Creates a new string object concatenating this string with s.
     *
     * @arg s - The string to concatenate to this one.
     *
     * @returns A pointer to a new string object containing the the character array
     * of the concatenated strings.
     */
    String *concat(String* const s);

    /**
     * Returns the size of the string.
     *
     * @returns - The length of the string
     */
    size_t size();
};
