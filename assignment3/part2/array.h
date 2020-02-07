// lang: CwC
#pragma once
#include <iostream>
#include <cstring>

#include "object.h"
#include "string.h"
#include "assert.h"

/**
 * NOTE: Just use your implementations - our API makes no assumptions about this interface
 * besides basic functionality.
 *
 * Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang.yifei3@husky.neu.edu)
 */


/**
 * An Array class to which elements can be added to and removed from.
 */
class ObjectArray : public Object {};

/**
 * An Array class to which strings can be added to and removed from.
 */
class StringArray : public Object {};

/**
 * An Array class to which booleans can be added to and removed from.
 */
class BoolArray : public Object {};

/**
 * An Array class to which floats can be added to and removed from.
 * author: chasebish */
class FloatArray : public Object {};

/**
 * An Array class to which integers can be added to and removed from.
 * author: chasebish */
class IntArray : public Object {};
