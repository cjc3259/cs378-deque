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
        pointer _iaFront; // pointer to beginning of inner array
        pointer _iaBack; // pointer to end of inner array
        pointer _dFront; // point to very front of deque
        pointer _dBack; // point to very back of deque
        pointer _b; // pointer to beginning of actual data
        pointer _e; // pointer to end of actual data
    
        oa_allocator_type _oa; // outer array allocator
        oa_pointer _oaFront; // point to front of outer array
        oa_pointer _oaBack; // pointer to back of outer array

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code> DONE
            return (!_iaFront && !_iaBack && !_dFront && !_dBack && !_b && !_e && !_oaFront && !_oaBack) || ((_dFront <= _b) && (_dBack >= _e) && (_b < _e));}

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
                iterator (/* <your arguments> DONE */ MyDeque* d, size_t i) :
                        _d (d),
                        _i (i) {
                    // <your code> DONE 
                    // no code
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
                    return (*_d)[_i];}

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
                    ++_i;
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
                    --_i;
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
                    _i += d;
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
                    _i -= d;
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
                MyDeque* _d;
                size_t _i; // index

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
                        _i (i) {
                    // <your code> DONE
                    // no code
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
                    return (*_d)[_i];}

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
                    --_i;
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
                    _i += d;
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
                    _i += d;
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
            _iaFront = _iaBack = _dFront = _dBack = _b = _e = 0;
            assert(valid());
        }

        /**
         * <your documentation> DONE
         constructs a deque given an allocator, size and value
         */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation> DONE
         copy constructor
         */
        MyDeque (const MyDeque& that) :
                _a(that._a) {
            // <your code> DONE
            _oaFront = _oaBack = 0; 
            _iaFront = _iaBack = 0; 
            _b = _dFront = _a.allocate(that.size());
            _e = _dBack = _b + that.size();
            uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

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
                _a.deallocate(_dFront, capacity());
            }
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
            else if(rhs.size < size()) {
                copy(rhs.begin(), rhs.end(), begin());
                resize(rhs.size());
            }
            else if(rhs.size() <= capacity()) {
                copy(rhs.begin(), rhs.begin() + size(), begin());
                _e = uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());
            }
            else {
                clear();
                reserve(rhs.size());
                _e = uninitialized_fill(_a, rhs.begin(), rhs.end(), begin());
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
            return begin()[index];}

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
            if (index >= size())
                throw out_of_range("deque::_M_range_check");
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
            return *(end() - 1);
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
            return iterator(/* <your arguments> DONE */ this, 0);}

        /**
         * <your documentation> DONE
         returns const iterator of 1st element
         */
        const_iterator begin () const {
            // <your code> DONE
            return const_iterator(/* <your arguments> DONE */ this, 0);}

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
         returns iterator of the last element
         */
        iterator end () {
            // <your code> DONE
            return iterator(/* <your arguments> DONE */ this, size());
        }

        /**
         * <your documentation> DONE
         returns const iterator of the last element
         */
        const_iterator end () const {
            // <your code> DONE
            return const_iterator(/* <your arguments> DONE */ this, size());
        }

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();
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
            return *begin();
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
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        size_type capacity () const {
            return _dBack - _dFront;
        }

        void reserve (size_type c) {
            if (c > capacity()) {
                MyDeque x(*this/*, c*/);
                swap(x);
            }
            assert(valid());
        }

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void push_front (const_reference) {
            // <your code>
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            // if (s == size())
            //     return;
            // if (s < size())
            //     _e = my_destroy(_a, begin() + s, end());
            // else if (s <= capacity())
            //     _e = uninitialized_fill(_a, end(), begin() + s, v);
            // else {
            //     reserve(max(2*size(), s));
            //     resize(s, v);
            // }
            // assert(valid());
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
            // like vector in class?
            if (_a == that._a) {
                std::swap(_oaFront, that._oaFront);
                std::swap(_oaBack, that._oaBack);
                // std::swap(_oa, that._oa);
                std::swap(_iaFront, that._iaFront);
                std::swap(_iaBack, that._iaBack);
                std::swap(_dFront, that._dBack);
                std::swap(_dBack, that._dBack);
                std::swap(_b, that._b);
                std::swap(_e, that._e);

            }
            else {
                MyDeque x(*this);
                *this = that;
                that = x;
            }
            assert(valid());}};

#endif // Deque_h
