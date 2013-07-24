// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
 * TestDeque
 *
 * To compile this, use the command
 * g++ -pedantic -std=c++0x -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread
 *
 * Then it can run with
 * TestDeque
 *
 * It will work on any machine with gtest and the precompiled libraries installed
 */

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"                        // Google Test framework


#include "Deque.h"
// includes from Deque.h
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>

#define class struct
#define protected public
#define private public


// ---------
// TestDeque
// ---------

typedef testing::Types<std::deque<int>, MyDeque<int> > MyDeques;

template <typename C>

// TYPED_TEST_CASE(DequeTest, MyDeques);

class DequeTest : public testing::Test {
    const C x;
    typedef typename C::size_type size_type;
    const size_type s;
    DequeTest() : s(100) {}
    // DequeTest() : s() {}
};

TYPED_TEST_CASE(DequeTest, MyDeques);

TYPED_TEST (DequeTest, allocator) {
    // const C x;
    EXPECT_EQ(0, this->x.size());

}

// TEST (Deque, allocator) {
//     const C x;
// 