// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <iostream> 

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;
using namespace std;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// MyDeque
// -------

template < typename T, typename A = std::allocator<T> >
class MyDeque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        // need allocator_type rebinded for a pointer of pointers (point to outer array)
        typedef typename allocator_type::template rebind<T*>::other oa_allocator_type;  // oa - outer array
        typedef typename oa_allocator_type::pointer                 oa_pointer; // pointer to oa

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation> DONE
         bool returns true if lhs == rhs
         */
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code> DONE
            // you must use std::equal()
            // like vector in the class examples?
            return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation> DONE
         bool returns true if lhs < rhs
         */
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code> DONE
            // you must use std::lexicographical_compare()
            // again, like vector example in class
            return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----

        // <your data> DONE

        allocator_type _a; // inner array allocator
        pointer _dFront; // pointer to very front of deque
        pointer _dBack; // pointer to very back of deque + 1
        pointer _b; // pointer to beginning of actual data
        pointer _e; // pointer to end of actual data + 1
        pointer _thisBack; // pointer to back of current inner array
        pointer dF_e; // pointer to _b + s NOTE could be out of bounds!! only used to determine _e
    
        oa_allocator_type _oa; // outer array allocator
        oa_pointer _oaFront; // pointer to front of outer array
        oa_pointer _oaBack; // pointer to back of outer array + 1

        size_type dSize; // number of elements
        size_type numArray; // number of inner arrays
        size_type sizeArray; // size of inner arrays
 
    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code> DONE
            return (!_dFront && !_dBack && !_b && !_e && !_oaFront && !_oaBack) || ((_dFront <= _b) && (_b <= _e) && (_e <= _dBack));}

        // returns the size of the outer array
        size_type oaSize () const {
            return _oaBack - _oaFront;
            }  

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename MyDeque::value_type      value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::pointer         pointer;
                typedef typename MyDeque::reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation> DONE
                 bool return true if iterators are '=='
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    // <your code> DONE
                    return (lhs._d == rhs._d) &&(lhs._i == rhs._i);}

                /**
                 * <your documentation> DONE
                 bool return true is iterators are '!='
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation> DONE
                 returns iterator + rhs
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation> DONE
                 returns iterator - rhs
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data> DONE
                MyDeque* _d;
                size_t _i; // index
                pointer _p;


            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code> DONE
                    return _i >= 0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation> DONE
                 constructor
                 */
                iterator (MyDeque* d, size_t i) :
                        _d (d),
                        _i (i)  {
                    // <your code> DONE 
                    _p = (*_d)._b + _i;
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation> DONE
                 deferenced pointer
                 */
                reference operator * () const {
                    // <your code> DONE
                    // dummy is just to be able to compile the skeleton, remove it
                    // static value_type dummy;
                    return (*_p);}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation> DONE
                 member access
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation> DONE
                 pre-increment ++
                 */
                iterator& operator ++ () {
                    // <your code> DONE
                    ++_p;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation> DONE
                 post-increment ++
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation> DONE
                 pre-increment --
                 */
                iterator& operator -- () {
                    // <your code> DONE
                    --_p;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation> DONE
                 post-increment --
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation> DONE
                move iterator + d steps
                 */
                iterator& operator += (difference_type d) {
                    // <your code> DONE
                    _p += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation> DONE
                 move iterator - d steps
                 */
                iterator& operator -= (difference_type d) {
                    // <your code> DONE
                    _p -= d;
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename MyDeque::value_type      value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::const_pointer   pointer;
                typedef typename MyDeque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation> DONE
                 bool return true if iterators are '=='
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code> DONE
                    return (lhs._d == rhs._d) &&(lhs._i == rhs._i);}

                /**
                 * <your documentation> DONE
                 bool return true is iterators are '!='
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation> DONE
                 returns iterator + rhs
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation> DONE
                 returns iterator - rhs
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data> DONE
                const MyDeque* _d;
                size_t _i; // index
                pointer _p;


            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code> DONE
                    return _i >= 0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation> DONE
                 constructor
                 */
                const_iterator (/* <your arguments> DONE */ const MyDeque* d, size_t i) : 
                        _d (d),
                        _i (i),
                        _p ((*_d)._b + _i)  
                        {
                    // <your code> DONE 
                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation> DONE
                 deferenced pointer
                 */
                reference operator * () const {
                    // <your code> DONE
                    // dummy is just to be able to compile the skeleton, remove it
                    // static value_type dummy;
                    return *_p;}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation> DONE
                 member acces
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation> DONE
                 pre-increment ++
                 */
                const_iterator& operator ++ () {
                    // <your code> DONE

                    // THIS KILLS TWO OF MY DEQUE == TESTS???  SHOULD BE ++_p;
                    ++_i;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation> DONE
                 post-increment ++
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation> DONE
                 pre-increment --
                 */
                const_iterator& operator -- () {
                    // <your code> DONE
                    --_p;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation> DONE
                 post increment --
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation> DONE
                 move iterator + d steps
                 */
                const_iterator& operator += (difference_type d) {
                    // <your code> DONE
                    _p += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation> DONE
                 move iterator - d steps
                 */
                const_iterator& operator -= (difference_type d) {
                    // <your code>
                    _p -= d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation> DONE
         constructs a deque given an allocator (basic constructor)
         */
        explicit MyDeque (const allocator_type& a = allocator_type()) :
                _a(a),
                _oa() {
            // <your code> DONE
            _oaFront = _oaBack = 0; 
            _dFront = _dBack = _b = _e = 0;
            dSize = numArray = sizeArray = 0;
            assert(valid());
        }

        /**
         * <your documentation> DONE
         constructs a deque given an allocator, size and value
         */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) :
                _a(a),
                _oa() {
            // <your code>
            // determine number of inner arrays required

            // if size == 0, like the above constructor
            if(s == 0) {
                _oaFront = _oaBack = 0; 
                _dFront = _dBack = _b = _e = 0;
                dSize = 0;
            }
            else {
                // determine number of inner arrays 
                _oaFront = _oaBack = 0; 
                _dFront = _dBack = _b = _e = 0;
                size_type carry = 0;
                sizeArray = 10;

                if(s%sizeArray > 0)
                    carry = 1;
                numArray = s/sizeArray + carry; 
                assert(numArray >= 1);

                // allocate outer array
                _oaFront = _oa.allocate(numArray);
                _oaBack = _oaFront + numArray;

                // construct outer array
                _oa.construct(_oaFront);

                // set pointer to beginning of allocated space
                _dFront = _a.allocate(sizeArray*numArray);

                // allocate inner arrays
                for (size_type i = 0; i < numArray; ++i) {
                    _oaFront[i] = &(_dFront[i*sizeArray]);
                }

                // set pointer to end of the allocated space
                _dBack = _oaFront[numArray - 1] + sizeArray; 

                // pointer to the end of current array
                _thisBack = _oaFront[0] + sizeArray;

                // pointers to the beginning and end of data
                _b = _dFront;
                _e = _b + s;

                // construct inner arrays
                if (s <= sizeArray)
                    uninitialized_fill(_a, _b, _e, v);
                else {
                    pointer t_b = _b;
                    size_type array = 0;
                    while (_b != _e) {
                        if (_b == _thisBack) {
                            ++array;
                            _b = _oaFront[array];
                            _thisBack = _oaFront[array] + sizeArray;
                        } 
                        else {
                            _a.construct(&*_b, v);
                            ++_b;
                        }
                    }
                    _b = t_b;
                }
            }

            // size varible
            dSize = s;
            assert(valid());
        }

        /**
         * <your documentation> DONE
         copy constructor
         */
        MyDeque (const MyDeque& that) :
                _a(that._a),
                _oa() {
            // <your code>

            // size data
            numArray = that.numArray;
            dSize = that.dSize;
            sizeArray = that.sizeArray;

            // allocate outer array
            _oaFront = _oa.allocate(numArray); 
            _oaBack = _oaFront + numArray;

            // construct outer array
            _oa.construct(_oaFront);

            // pointer to front of allocated space
            _dFront = _a.allocate(sizeArray*numArray);

            //allocate inner arrays
            for (size_type i = 0; i < numArray; ++i) {
                _oaFront[i] = &(_dFront[i*sizeArray]);
            }       

            // pointers to end of allocated space 
            _dBack = _oaFront[numArray - 1] + sizeArray;

            _thisBack = _oaFront[0] + sizeArray;

            // data pointers
            _b = _dFront;
            _e = _b + dSize;

            // construct inner arrays
            if(dSize <= sizeArray) 
                uninitialized_copy(_a, that._b, that._e, _b);
            else {
                pointer t_b = _b;
                size_type array = 0;
                size_type otherB = 0;
                while (_b != _e) {
                    if (_b == _thisBack) {
                        ++array;
                        _b = _oaFront[array];
                        _thisBack = _oaFront[array] + sizeArray;
                    }
                    else {
                        _a.construct(&*_b, *(that._b + otherB));
                        ++_b;
                        ++otherB;
                    }
                }
                _b = t_b;
            }
            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation> DONE
         destructor
         */
        ~MyDeque () {
            // <your code> DONE
            if(_dFront) {
                clear();
                // _dBack = &*destroy(_a, _dFront, _dBack);
                _a.deallocate(_dFront, _dBack - _dFront);
            }
            _oaBack = &*destroy(_oa, _oaFront, _oaBack);
            _oa.deallocate(_oaFront, _oaBack - _oaFront);
            assert(valid());
        }

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation> DONE
         returns ref to this deque after copying rhs deque to this deque
         */
        MyDeque& operator = (const MyDeque& rhs) {
            // <your code> DONE
            if(this == &rhs) 
                return *this;
            if(rhs.size() == size())
                copy(rhs.begin(), rhs.end(), begin());
            else if(rhs.size() < size()) {
                copy(rhs.begin(), rhs.end(), begin());
                resize(rhs.size());
            }
            else if(rhs.size() <= (unsigned)(_dBack - _dFront)) {
                copy(rhs.begin(), rhs.begin() + size(), begin());
                _e = &*uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());
            }
            else {
                clear();
                MyDeque lhs(rhs);
                swap(lhs);
            }
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation> DONE
         returns ref to index-th element
         */
        reference operator [] (size_type index) {
            // <your code> DONE
            // dummy is just to be able to compile the skeleton, remove it
            // static value_type dummy;
            return *(_dFront + index);
        }

        /**
         * <your documentation> DONE
         returns const ref to index-th element
         */
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation> DONE
         returns ref to index-th element
         */
        reference at (size_type index) throw (out_of_range) {
            // <your code> DONE
            // dummy is just to be able to compile the skeleton, remove it
            // static value_type dummy;
            return (*this)[index];
        }

        /**
         * <your documentation> DONE
         returns const ref to the index-th element
         */
        const_reference at (size_type index) const {
            return const_cast<MyDeque*>(this)->at(index);
        }

        // ----
        // back
        // ----

        /**
         * <your documentation> DONE
         returns ref to last element
         */
        reference back () {
            // <your code> DONE
            // dummy is just to be able to compile the skeleton, remove it
            // static value_type dummy;
            assert(!empty());
            return *(_e - 1);
        }

        /**
         * <your documentation> DONE
         returns const ref to last element 
         */
        const_reference back () const {
            return const_cast<MyDeque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation> DONE
         returns iterator of 1st element
         */
        iterator begin () {
            // <your code> DONE
            return iterator(this, 0);
        }

        /**
         * <your documentation> DONE
         returns const iterator of 1st element
         */
        const_iterator begin () const {
            // <your code> DONE
            return const_iterator(this, 0);
        }

        // -----
        // clear
        // -----

        /**
         * <your documentation> DONE
         clears all elements from deque/empties deque 
         */
        void clear () {
            // <your code> DONE
            resize(0);
            assert(valid());
        }

        // -----
        // empty
        // -----

        /**
         * <your documentation> DONE
         bool returns true if deque is empty
         */
        bool empty () const {
            return size() == 0;
        }

        // ---
        // end
        // ---

        /**
         * <your documentation> DONE
         returns iterator of the last element + 1
         */
        iterator end () {
            // <your code> DONE
            return iterator(this, size());
        }

        /**
         * <your documentation> DONE
         returns const iterator of the last element + 
         */
        const_iterator end () const {
            // <your code> DONE
            return const_iterator(this, size());
        }

        // -----
        // erase
        // -----

        /**
         * <your documentation> DONE
         removes element at i, returns i
         */
        iterator erase (iterator i) {
            // <your code> DONE
            assert(!empty());
            if(i + 1 == end())
                pop_back();
            else if (i == begin())
                pop_front();
            else {
                copy(i + 1, end(), i);
                resize(size() - 1);
            }
            assert(valid());
            return iterator(this, 0);
        }

        // -----
        // front
        // -----

        /**
         * <your documentation> DONE
         returns ref to 1st element
         */
        reference front () {
            // <your code> DONE
            // dummy is just to be able to compile the skeleton, remove it
            // static value_type dummy;
            assert(!empty());
            return *_dFront;
        }

        /**
         * <your documentation> DONE
         returns const ref to 1st element
         */
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation> DONE
         inserts single element of value v, at i, returns i
         */
        iterator insert (iterator i, const_reference v) {
            // <your code> DONE
            if (i == end()) 
                push_back(v);
            else if (i == begin())
                push_front(v);
            else {
                resize(size() + 1);
                copy(i, end(), i + 1);
                *i = v;
            }
            assert(valid());
            return iterator(this, 0);
        }

        // ---
        // pop
        // ---

        /**
         * <your documentation> DONE
         removes last element from deque
         */
        void pop_back () {
            // <your code> DONE
            assert(!empty());
            resize(size() - 1);
            assert(valid());
        }

        /**
         * <your documentation> DONE
         removes first element from deque
         */
        void pop_front () {
            // <your code> DONE
            assert(!empty());
            destroy(_a, begin(), begin() + 1);
            ++_b;
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation> DONE
         adds element of value v to back of deque
         */
        void push_back (const_reference v) {
            // <your code> DONE
            resize(size() + 1, v);
            assert(valid());}

        /**
         * <your documentation> DONE
         adds element of value v to front of deque
         */
        void push_front (const_reference v) {
            // <your code>
            if (_b != _dFront) {
                _b = &*uninitialized_fill(_a, _b - 1, _b, v);
                --_b;
            }
            else {
                MyDeque x(size() + sizeArray);
                // NOTE: dFront index is at -sizeArray NOT zero..  
                uninitialized_copy(x._a, _b, _e, x._b + sizeArray);
                x._b = x._b + sizeArray;
                swap(x);
                push_front(v);
            }
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            if (s == size())
                return;
            else if (s < size()){
                _e = &*destroy(_a, _b + s, _e);
                // size() = _e - _b;
            }
            else if (s > size() && s <= (unsigned)(_dBack - _dFront)) {
                _e = uninitialized_fill(_a, _e, _b + s, v); // space has already been allocated
            }
            else {
                MyDeque x(s, v);
                uninitialized_copy(x._a, _b, _e, x._b);
                swap(x);
                resize(s, v);
            }
            assert(valid());
        }

        // ----
        // size
        // ----

        /**
         * <your documentation> DONE
         returns number of elements
         */
        size_type size () const {
            // <your code> DONE
            return _e - _b;}

        // ----
        // swap
        // ----

        /**
         * <your documentation> DONE
         swaps elements in this deque with elements in that deque
         */
        void swap (MyDeque& that) {
            // <your code> DONE
            if (_a == that._a) {
                std::swap(_oaFront, that._oaFront);
                std::swap(_oaBack, that._oaBack);
                std::swap(_dFront, that._dFront);
                std::swap(_dBack, that._dBack);
                std::swap(_b, that._b);
                std::swap(_e, that._e);
                std::swap(dSize, that.dSize);
                std::swap(numArray, that.numArray);
                std::swap(sizeArray, that.sizeArray);
            }
            else {
                MyDeque x(*this);
                *this = that;
                that = x;
            }
            assert(valid());}};

#endif // Deque_h
