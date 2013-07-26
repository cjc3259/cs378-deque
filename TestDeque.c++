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

#include <cassert>
#include <iterator>
#include <memory>
#include <utility>
#include <cstdlib>

#include "Deque.h"
// includes from Deque.h

#define class struct
#define protected public
#define private public


// ---------
// TestDeque
// ---------

typedef testing::Types<std::deque<int>, MyDeque<int> > Containers;


// TYPED_TEST_CASE(DequeTest, MyDeques);
template <typename C>
class Tests : public testing::Test {
	protected:
    	C x;
    	C y;
    // typedef typename C::size_type size_type;
    // const size_type s;
    // DequeTest() : 
    	Tests() : x(), y() {}
};

TYPED_TEST_CASE(Tests, Containers);

TYPED_TEST (Tests, allocator) {
    // const C x;
    EXPECT_EQ(0, this->x.size());

}



// *** DEFAULT CONSTRUCTOR ***
TEST (Constructor, def_constructor_1) {
    MyDeque<int> x;
    ASSERT_TRUE(x.size() == 0);
}



// *** CONSTRUCTOR WITH SIZE AND VALUE ***
TEST (Constructor, size_constructor_1) {
    MyDeque<int> x(5);
    ASSERT_TRUE(x.size() == 5);
}

TEST (Constructor, size_constructor_2) {
    MyDeque<int> x(5, 10);
    ASSERT_TRUE(x.size() == 5);
    ASSERT_TRUE(x[0] == 10);
    ASSERT_TRUE(x[4] == 10);
}

TEST (Constructor, size_constructor_3) {
    MyDeque<int> x(15);
    ASSERT_TRUE(x.size() == 15);
    ASSERT_TRUE(x[14] == 0);
}

TEST (Constructor, size_constructor_4) {
    MyDeque<int> x(25, 100);
    ASSERT_TRUE(x.size() == 25);
    ASSERT_TRUE(x[0] == 100);
    ASSERT_TRUE(x[24] == 100);
}



// *** COPY CONSTRUCTOR ***
TEST (Constructor, copy_constructor_1) {
    MyDeque<int> x(5);
    MyDeque<int> y(x);
    ASSERT_TRUE(y.size() == 5);
}

TEST (Constructor, copy_constructor_2) {
    MyDeque<int> x(15, 100);
    MyDeque<int> y(x);
    ASSERT_TRUE(y.size() == 15);
    ASSERT_TRUE(y[0] == 100);
    ASSERT_TRUE(y[14] == 100);
}

TEST (Constructor, copy_constructor_3) {
    MyDeque<int> x(10, 1);
    MyDeque<int> y(x);
    ASSERT_TRUE(y.size() == 10);
    ASSERT_TRUE(y[0] == 1);
    ASSERT_TRUE(y[9] == 1);
}



// *** RESIZE ***
TEST (Resize, resize_1) {
    MyDeque<int> x(5);
    x.resize(5);
    ASSERT_TRUE(x.size() == 5);
}

TEST (Resize, resize_2) {
    MyDeque<int> x(5);
    x.resize(0);
    ASSERT_TRUE(x.size() == 0);
}

TEST (Resize, resize_3) {
    MyDeque<int> x(5);
    x.resize(10, 1);
    ASSERT_TRUE(x.size() == 10);
    ASSERT_TRUE(x[9] == 1);
}

TEST (Resize, resize_4) {
    MyDeque<int> x(5);
    x.resize(11, 1);
    ASSERT_TRUE(x.size() == 11);
    ASSERT_TRUE(x[4] == 0);
    ASSERT_TRUE(x[10] == 1);
}

TEST (Resize, resize_5) {
    MyDeque<int> x(5);
    x.resize(20, 1);
    ASSERT_TRUE(x.size() == 20);
    ASSERT_TRUE(x[4] == 0);
    ASSERT_TRUE(x[19] == 1);
}



// *** SIZE ***
TEST (Size, size_1) {
    MyDeque<int> x(5);
    x.resize(20, 1);
    ASSERT_TRUE(x.size() == 20);
}

TEST (Size, size_2) {
    MyDeque<int> x(5);
    x.resize(20, 1);
    x.push_back(1);
    x.pop_front();
    ASSERT_TRUE(x.size() == 20);
}

TEST (Size, size_3) {
    MyDeque<int> x(1, 1);
	MyDeque<int> y(5, 2);
	x.swap(y);
	ASSERT_TRUE(x.size() == 5);
    ASSERT_TRUE(y.size() == 1);
}



// *** SWAP ***
TEST (SWAP, swap_1) {
	MyDeque<int> x(1, 1);
	MyDeque<int> y(5, 2);
	x.swap(y);
	ASSERT_TRUE(x.size() == 5);
    ASSERT_TRUE(x[4] == 2);
    ASSERT_TRUE(y.size() == 1);
    ASSERT_TRUE(y[0] == 1);
}

TEST (SWAP, swap_2) {
	MyDeque<int> x(1, 1);
	MyDeque<int> y(15, 2);
	x.swap(y);
	ASSERT_TRUE(x.size() == 15);
    ASSERT_TRUE(x[14] == 2);
    ASSERT_TRUE(y.size() == 1);
    ASSERT_TRUE(y[0] == 1);
}

TEST (SWAP, swap_3) {
	MyDeque<int> x;
	MyDeque<int> y(15, 2);
	x.swap(y);
	ASSERT_TRUE(x.size() == 15);
    ASSERT_TRUE(x[14] == 2);
    ASSERT_TRUE(y.size() == 0);
}



// *** PUSH_FRONT ***
TEST (PushFront, push_front_1) {
    MyDeque<int> x(5);
    x.pop_front();
    x.push_front(1);
    ASSERT_TRUE(x.size() == 5);
    ASSERT_TRUE(x[0] == 1);
    ASSERT_TRUE(x[1] == 0);
}

TEST (PushFront, push_front_2) {
    MyDeque<int> x(1, 1000);
    x.push_front(1);
    ASSERT_TRUE(x.size() == 2);
    ASSERT_TRUE(x[9] == 1);
    ASSERT_TRUE(x[10] == 1000);
}

TEST (PushFront, push_front_3) {
    MyDeque<int> x(10, 1000);
    x.push_front(1);
    ASSERT_TRUE(x.size() == 11);
    ASSERT_TRUE(x[9] == 1);
    ASSERT_TRUE(x[10] == 1000);
}



// *** PUSH_BACK ***
TEST (PushBack, push_back_1) {
    MyDeque<int> x(5);
    x.push_back(1);
    ASSERT_TRUE(x.size() == 6);
    ASSERT_TRUE(x[4] == 0);
    ASSERT_TRUE(x[5] == 1);
}

TEST (PushBack, push_back_2) {
    MyDeque<int> x(16, 2);
    x.push_back(1);
    ASSERT_TRUE(x.size() == 17);
    ASSERT_TRUE(x[15] == 2);
    ASSERT_TRUE(x[16] == 1);
}

TEST (PushBack, push_back_3) {
    MyDeque<int> x(10);
    x.push_back(1);
    ASSERT_TRUE(x.size() == 11);
    ASSERT_TRUE(x[9] == 0);
    ASSERT_TRUE(x[10] == 1);
}



// *** POP_FRONT ***
TEST (PopFront, pop_front_1) {
    MyDeque<int> x(5);
    x.pop_front();
    ASSERT_TRUE(x.size() == 4);
    ASSERT_TRUE(x[1] == 0);
}

TEST (PopFront, pop_front_2) {
    MyDeque<int> x(15, 1000);
    x.pop_front();
    ASSERT_TRUE(x.size() == 14);
    ASSERT_TRUE(x[1] == 1000);
}

TEST (PopFront, pop_front_3) {
    MyDeque<int> x(15, 1000);
    x.pop_front(); 
    x.pop_front(); 
    x.pop_front(); 
    x.pop_front();
    ASSERT_TRUE(x.size() == 11);
    ASSERT_TRUE(x[4] == 1000);
}



// *** POP_BACK ***
TEST (PopBack, pop_back_1) {
    MyDeque<int> x(5);
    x.pop_back();
    ASSERT_TRUE(x.size() == 4);
    ASSERT_TRUE(x[4] == 0);
}

TEST (PopBack, pop_back_2) {
    MyDeque<int> x(1);
    x.pop_back();
    ASSERT_TRUE(x.size() == 0);
}

TEST (PopBack, pop_back_3) {
    MyDeque<int> x(11, 100);
    x.pop_back();
    ASSERT_TRUE(x.size() == 10);
    ASSERT_TRUE(x[10] == 100);
}



// *** INSERT ***



// *** FRONT ***
TEST (Front, front_1) {
    MyDeque<int> x(1, 100);
    ASSERT_TRUE(x.front() == 100);
}

TEST (Front, front_2) {
    MyDeque<int> x(1);
    ASSERT_TRUE(x.front() == 0);
}

TEST (Front, front_3) {
    MyDeque<int> x(1, 0);
    ASSERT_TRUE(x.front() == 0);
}



// *** ERASE ***
TEST (Erase, erase_1) {
	MyDeque<int> x(1, 100);
	MyDeque<int>::iterator i(&x, 0);
	x.erase(i);
	ASSERT_TRUE(x.size() == 0);
}



// *** CONST END ***



// *** END ***
TEST (End, end_1) {
    MyDeque<int> x(1, 100);
    MyDeque<int>::iterator i = x.end() - 1;
	ASSERT_TRUE(*i == 100);
}

TEST (End, end_2) {
    MyDeque<int> x(11, 100);
    MyDeque<int>::iterator i = x.end() - 1;
	ASSERT_TRUE(*i == 100);
}

TEST (End, end_3) {
    MyDeque<int> x(110);
    MyDeque<int>::iterator i = x.end() - 1;
	ASSERT_TRUE(*i == 0);
}



// *** CLEAR ***
TEST (Clear, clear_1) {
    MyDeque<int> x(1, 100);
    x.clear();
    ASSERT_TRUE(x.size() == 0);
}

TEST (Clear, clear_2) {
    MyDeque<int> x;
    x.clear();
    ASSERT_TRUE(x.size() == 0);
}

TEST (Clear, clear_3) {
    MyDeque<int> x(10, 10);
    x.clear();
    ASSERT_TRUE(x.size() == 0);
}



// *** CONST BEGIN ***



// *** BEGIN ***
TEST (Begin, begin_1) {
    MyDeque<int> x(1, 100);
    MyDeque<int>::iterator i = x.begin();
	ASSERT_TRUE(*i == 100);
}

TEST (Begin, begin_2) {
    MyDeque<int> x(1);
    MyDeque<int>::iterator i = x.begin();
	ASSERT_TRUE(*i == 0);
}

TEST (Begin, begin_3) {
    MyDeque<int> x(1);
    x.push_back(2);
    MyDeque<int>::iterator i = x.begin() + 1;
	ASSERT_TRUE(*i == 2);
}



// *** BACK ***
TEST (Back, back_1) {
    MyDeque<int> x(1, 100);
    ASSERT_TRUE(x.back() == 100);
}

TEST (Back, back_2) {
    MyDeque<int> x(10, 10);
    ASSERT_TRUE(x.back() == 10);
}

TEST (Back, back_3) {
    MyDeque<int> x(1, 3);
    ASSERT_TRUE(x.back() == 3);
}



// *** AT ***
TEST (At, at_1) {
    MyDeque<int> x;
    x.push_back(1);
    ASSERT_TRUE(x.at(0) == 1);
}

TEST (At, at_2) {
    MyDeque<int> x;
    x.push_back(1);
    x.push_back(2);
    ASSERT_TRUE(x.at(0) == 1);
    ASSERT_TRUE(x.at(1) == 2);
}

TEST (At, at_3) {
    MyDeque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_front(3);
    ASSERT_TRUE(x.at(10) == 1);
    ASSERT_TRUE(x.at(11) == 2);
    ASSERT_TRUE(x.at(9) == 3);
}



// *** [] ***
TEST (Brackets, brackets_1) {
    MyDeque<int> x;
    x.push_back(1);
    ASSERT_TRUE(x[0] == 1);
}

TEST (Brackets, brackets_2) {
    MyDeque<int> x;
    x.push_back(1);
    x.push_back(2);
    ASSERT_TRUE(x[0] == 1);
    ASSERT_TRUE(x[1] == 2);
}

TEST (Brackets, brackets_3) {
    MyDeque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_front(3);
    ASSERT_TRUE(x[10] == 1);
    ASSERT_TRUE(x[11] == 2);
    ASSERT_TRUE(x[9] == 3);
}



// *** CONST ITERATOR -= ***



// *** CONST ITERATOR += ***



// *** CONST ITERATOR PRE-INCREMENT -- ***



// *** CONST ITERATOR PRE-INCREMENT ++ ***



// *** CONST ITERATOR * ***
// TEST (ConstIteratorStar, const_iterator_star_1) {
// 	MyDeque<int> x(1, 1);
// 	MyDeque<int>::const_iterator i = x.begin();
// 	ASSERT_TRUE(*i == 1);
// }

// TEST (ConstIteratorStar, const_iterator_star_2) {
// 	MyDeque<int> x(10, 1);
// 	MyDeque<int>::const_iterator i = x.end() - 1;
// 	ASSERT_TRUE(*i == 1);
// }

// TEST (ConstIteratorStar, const_iterator_star_3) {
// 	MyDeque<int> x(10, 1);
// 	MyDeque<int>::const_iterator i = x.end() - 5;
// 	ASSERT_TRUE(*i == 1);
// }




// *** ITERATOR -= ***
TEST (IteratorMinusEqual, iterator_minus_equal_1) {
	MyDeque<int> x(2, 1);
	MyDeque<int>::iterator i = x.end();
	i -= 1;
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorMinusEqual, iterator_minus_equal_2) {
	MyDeque<int> x(2, 1);
	x.push_front(2);
	MyDeque<int>::iterator i = x.end();
	i -= 3;
	ASSERT_TRUE(*i == 2);
}

TEST (IteratorMinusEqual, iterator_minus_equal_3) {
	MyDeque<int> x(12, 1);
	x.push_front(2);
	MyDeque<int>::iterator i = x.end();
	i -= 12;
	ASSERT_TRUE(*i == 1);
}



// *** ITERATOR += ***
TEST (IteratorPlusEqual, iterator_plus_equal_1) {
	MyDeque<int> x(2, 1);
	MyDeque<int>::iterator i = x.begin();
	i += 1;
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorPlusEqual, iterator_plus_equal_2) {
	MyDeque<int> x(2, 1);
	x.push_back(2);
	MyDeque<int>::iterator i = x.begin();
	i += 2;
	ASSERT_TRUE(*i == 2);
}

TEST (IteratorPlusEqual, iterator_plus_equal_3) {
	MyDeque<int> x(10, 1);
	x.push_back(5);
	MyDeque<int>::iterator i = x.begin();
	i += 10;
	ASSERT_TRUE(*i == 5);
}



// *** ITERATOR PRE-INCREMENT -- ***
TEST (IteratorPostIncr, iterator_post_incr_1) {
	MyDeque<int> x(2, 1);
	MyDeque<int>::iterator i = x.end();
	--i;
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorPostIncr, iterator_post_incr_2) {
	MyDeque<int> x(2, 1);
	x.push_back(2);
	MyDeque<int>::iterator i = x.end();
	--i;
	ASSERT_TRUE(*i == 2);
}

TEST (IteratorPostIncr, iterator_post_incr_3) {
	MyDeque<int> x(2, 1);
	x.push_front(2);
	MyDeque<int>::iterator i = x.end();
	--i;
	ASSERT_TRUE(*i == 1);
}



// *** ITERATOR PRE-INCREMENT ++ ***
TEST (IteratorPreIncr, iterator_pre_incr_1) {
	MyDeque<int> x(2, 1);
	MyDeque<int>::iterator i = x.begin();
	++i;
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorPreIncr, iterator_pre_incr_2) {
	MyDeque<int> x(2, 1);
	MyDeque<int>::iterator i = x.begin() - 1;
	++i;
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorPreIncr, iterator_pre_incr_3) {
	MyDeque<int> x(1, 1);
	x.push_front(2);
	MyDeque<int>::iterator i = x.begin();
	++i;
	ASSERT_TRUE(*i == 1);
}



// *** ITERATOR * ***
TEST (IteratorStar, iterator_star_1) {
	MyDeque<int> x(1, 1);
	MyDeque<int>::iterator i = x.begin();
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorStar, iterator_star_2) {
	MyDeque<int> x(10, 1);
	MyDeque<int>::iterator i = x.end() - 1;
	ASSERT_TRUE(*i == 1);
}

TEST (IteratorStar, iterator_star_3) {
	MyDeque<int> x(10, 1);
	MyDeque<int>::iterator i = x.end();
	--i;
	ASSERT_TRUE(*i == 1);
}



// *** Deque < ***
TEST (DequeLessThan, deque_less_than_1) {
    MyDeque<int> x(1);
    MyDeque<int> y(1, 1);
    ASSERT_TRUE(x < y);
}

TEST (DequeLessThan, deque_less_than_2) {
    MyDeque<int> x(2);
    MyDeque<int> y(1, 1);
    ASSERT_TRUE(x < y);
}

TEST (DequeLessThan, deque_less_than_3) {
    MyDeque<int> x;
    MyDeque<int> y(1);
    ASSERT_TRUE(x < y);
}



// *** Deque == ***
TEST (DequeEqualEqual, deque_equal_equal_1) {
    MyDeque<int> x;
    MyDeque<int> y;
    ASSERT_TRUE(x == y);
}

TEST (DequeEqualEqual, deque_equal_equal_2) {
    MyDeque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_front(3);
    MyDeque<int> y;
    y.push_back(1);
    y.push_back(2);
    y.push_front(3);
    ASSERT_TRUE(x == y);
}

TEST (DequeEqualEqual, deque_equal_equal_3) {
    MyDeque<int> x(10, 0);
    MyDeque<int> y(10);
    ASSERT_TRUE(x == y);
}
