
/**
 * This is a Standard C++ Library header.
 * This file is the user oriented part of Amachi STL
 * Open source by MIT by amachi Inori
 * Copyright (C) 2020-2020 Amachi Inori.
 * 
 * Main header file of dynamic array AMI_std::vector
 * The dynamic array AMI_std::vector is declared and defined in this file with namespace AMI_std
 * Some overloaded stream operations are also defined in this file with namespace AMI_std
**/

# pragma once
# include "AMI_allocate.hpp"
# include "initializer_list"

# ifndef AMI_STL_STRICT_MODE
#   include <iostream>
# endif

__ASTL_NAMESPACE_START

/**
 * ordered table container similar to std::vector
 * The first template parameter T refers to the element type
 * The second template parameter alloc refers to the allocator
 * 
 * compared with std::vector, 
 * this implementation improves the utilization of space by releasing too much free space at any time
 * (So iterators are more likely to fail) Use a relative cursor to store the location
 * Some practical methods have been added
**/
template <class T, class alloc = __secondary_allocator> 
class vector {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
    typedef _AMI_ptrdiff_t  difference_type;

protected:
    typedef base_allocator<value_type, alloc> __vector_alloc;

    iterator __map_begin = 0;
    iterator __map_end = 0;
    iterator __storage_end = 0;
    
    iterator __alloc_and_init(size_type length, const value_type &value) {
        iterator res = __vector_alloc::allocate(length);
        AMI_std::uninitialized_fill_n(res, length, value);
        return res;
    }
    template <class inpt_iter>
    iterator __alloc_and_copy(inpt_iter begin, inpt_iter end) {
        iterator res = __vector_alloc::allocate(end - begin);
        AMI_std::uninitialized_copy(begin, end, res);
        return res;
    }
    void __destroy_element() {
        AMI_std::destroy(__map_begin, __map_end);
        __map_end = __map_begin;
    }
    void __dealloc() {
        if (__map_begin) {
            __vector_alloc::deallocate(__map_begin, this->size());
        }
        __map_begin = 0;
        __map_end = 0;
        __storage_end = 0;
    }
    void __enlarge() {
        size_type old_size = capacity();
        size_type used_length = size_type(__map_end - __map_begin);
        size_type new_size;
        if (old_size == 0) new_size = 1;
        else if (old_size <= 512) new_size = old_size * 2;
        else if (old_size <= 4096) new_size = old_size * 1.7;
        else if (old_size <= 65536) new_size = old_size * 1.4;
        else new_size = old_size * 1.1;
        iterator new_begin = __vector_alloc::allocate(new_size);
        AMI_std::uninitialized_copy(__map_begin, __map_end, new_begin);
        __destroy_element();
        __dealloc();
        __map_begin = new_begin;
        __map_end = __map_begin + used_length;
        __storage_end = __map_begin + new_size;
    }
    void __shrink() {
        size_type used_length = size_type(__map_end - __map_begin);
        size_type new_size = capacity() / 2;
        iterator new_begin = __vector_alloc::allocate(new_size);
        AMI_std::uninitialized_copy(__map_begin, __map_end, new_begin);
        __destroy_element();
        __dealloc();
        __map_begin = new_begin;
        __map_end = __map_begin + used_length;
        __storage_end = __map_begin + new_size;
    }
public:
    /** 
     * Default constructor of vector
     * @return no return 
     * 
    **/
    vector() noexcept = default;

    /** 
     * Constructor of vector with a uint length, element uses its default constructor 
     * @return no return 
     * @param length - unsigned int - the length of the array
    **/
    explicit vector(size_type length) noexcept {
        __map_begin = __alloc_and_init(length, value_type());
        __map_end = __storage_end = __map_begin + length;
    }

    /**
     * Move constructor
     * @return no return 
     * @param __move_ori - rvalue of a vector<value_type>
    **/
    vector(vector<value_type>&& __move_ori) noexcept : 
        __map_begin(__move_ori.__map_begin),
        __map_end(__move_ori.__map_end),
        __storage_end(__move_ori.__storage_end) {
        __move_ori.__map_begin = nullptr;
        __move_ori.__map_end = nullptr;
        __move_ori.__storage_end = nullptr;
    }

# ifndef AMI_STL_STRICT_MODE
    /** 
     * Constructor of vector with two iterator to copy all the elements between __begin and __end 
     * @return no return 
     * @param __begin - iterator - the start point of the copied array
     * @param __end   - iterator - the end point of the copied array
    **/
    template <class inpt_iter>
    vector(inpt_iter __begin, inpt_iter __end) noexcept {
        size_type __length = __end - __begin;
        __map_begin = __alloc_and_copy(&*__begin, &*__end);
        __map_end = __storage_end = __map_begin + __length;
    }
# else
    /** 
     * Constructor of vector with two iterator to copy all the elements between __begin and __end 
     * @return no return 
     * @param __begin - iterator - the start point of the copied array
     * @param __end   - iterator - the end point of the copied array
    **/
    vector(iterator __begin, iterator __end) noexcept {
        size_type __length = __end - __begin;
        __map_begin = __alloc_and_copy(__begin, __end);
        __map_end = __storage_end = __map_begin + __length;
    }
# endif
    /** 
     * Constructor of vector with a uint length, element uses its copy constructor 
     * @return no return 
     * @param length - unsigned int        - the length of the array
     * @param value  - const value_type &  - the copied element
    **/
    vector(size_type length, const value_type &value) noexcept {
        __map_begin = __alloc_and_init(length, value);
        __map_end = __storage_end = __map_begin + length;
    }

    /** 
     * Constructor of vector with a int length, element uses its copy constructor 
     * @return no return 
     * @param length - int                 - the length of the array
     * @param value  - const value_type &  - the copied element
    **/
    vector(int length, const value_type &value) noexcept {
        __map_begin = __alloc_and_init(size_type(length), value);
        __map_end = __storage_end = __map_begin + length;
    }

    /** 
     * Constructor of vector with a long int length, element uses its copy constructor 
     * @return no return 
     * @param length - long int            - the length of the array
     * @param value  - const value_type &  - the copied element
    **/
    vector(long length, const value_type &value) noexcept {
        __map_begin = __alloc_and_init(size_type(length), value);
        __map_end = __storage_end = __map_begin + length;
    }

    /** 
     * Copy constructor of vector
     * @return no return 
     * @param other_v - const vector<value_type> & - the copied vector
    **/
    vector(const vector<value_type> &other_v) noexcept {
        __map_begin = __alloc_and_copy(&*(other_v.__map_begin), &*(other_v.__map_end));
        __map_end = __storage_end = __map_begin + (other_v.__map_end - other_v.__map_begin);
    }

    /** 
     * Constructor of vector with a initializer_list
     * @return no return 
     * @param i_list - std::initializer_list<value_type> & - the initializer_list
    **/
    vector(const std::initializer_list<value_type> &i_list) noexcept : 
        vector((pointer)i_list.begin(), (pointer)i_list.end()) {}

# ifndef AMI_STL_STRICT_MODE
    /** 
     * Constructor of vector with any container type
     * @return no return 
     * @param _other - const other& - container with iterator method begin() and end()
    **/
    template <class other>
    vector(const other& _other) noexcept :
        vector(_other.begin(), _other.end()) {}
# endif

    /**
     * Destructor of vector
    **/
    ~vector() noexcept {
        __destroy_element();
        __dealloc();
    }

# ifndef AMI_STL_STRICT_MODE
    /**
     * Generics assignment operator
     * @return returns: vector<value_type> & - lvalue of assignment
     * @param other_v - const other & - the right value of assignment  
    **/
    template <class other>
    vector<value_type>& operator=(const other &other_v) noexcept {
        vector<value_type> temp(other_v);
        this->__destroy_element();
        this->__dealloc();
        __map_begin = __alloc_and_copy(&*(temp.__map_begin), &*(temp.__map_end));
        __map_end = __storage_end = __map_begin + (temp.__map_end - temp.__map_begin);
        return *this;
    }
# endif

    /**
     * Standard assignment operator
     * @return returns: vector<value_type> & - lvalue of assignment
     * @param other_v - const vector<value_type>& - the right value of assignment  
    **/
    vector<value_type>& operator=(const vector<value_type>& other_v) noexcept {
        if (&other_v != this) {
            this->__destroy_element();
            this->__dealloc();
            __map_begin = __alloc_and_copy(&*(other_v.__map_begin), &*(other_v.__map_end));
            __map_end = __storage_end = __map_begin + (other_v.__map_end - other_v.__map_begin);
        } 
        return *this;
    }

    /**
     * Move assignment operator
     * @return returns: vector<value_type> & - lvalue of assignment
     * @param other_v - vector<value_type>&& - the rvalue of assignment  
    **/
    vector<value_type>& operator=(vector<value_type>&& other_v) noexcept {
        if (other_v.__map_begin != this->__map_begin) {
            this->__destroy_element();
            this->__dealloc();
            __map_begin = other_v.__map_begin;
            __map_end = other_v.__map_end;
            __storage_end = other_v.__storage_end;
            other_v.__map_begin = nullptr;
            other_v.__map_end = nullptr;
            other_v.__storage_end = nullptr;
        } 
        return *this;
    }

    /**
     * Gets the reference of the element according to the subscript
     * @return returns: value_type & - the element according to the subscript
     * @param loca - unsigned int - the subscript 
    **/
    value_type& at(size_type loca) {
    # ifdef AMI_STL_STRICT_MODE
        if (loca >= size()) __THROW_OUT_OF_BOUNDS;
    # endif
        return (*this)[loca];
    }

    /**
     * Gets the begin itreator of vector
     * @return returns: iterator - the begin itreator of vector
     * 
    **/
    iterator begin() const noexcept { return __map_begin; }

    /**
     * Gets the end itreator of vector
     * @return returns: iterator - the end itreator of vector
     * 
    **/
    iterator end() const noexcept { return __map_end; }

    /**
     * Gets the occupied size of vector
     * @return returns: unsigned int - occupied size of vector
     * 
    **/
    size_type size() const noexcept { return size_type(__map_end - __map_begin); }

    /**
     * Gets the memory size of vector
     * @return returns: unsigned int - memory size of vector
     * 
    **/
    size_type capacity() const noexcept { return size_type(__storage_end - __map_begin); }

    /**
     * Gets the memory size of vector
     * @return returns: unsigned int - memory size of vector
     * 
    **/
    size_type max_size() const noexcept { return this->capacity(); }

    /**
     * Judge whether vector is empty
     * @return returns: bool
     * 
    **/
    bool empty() const noexcept { return __map_begin == __map_end; }

    /**
     * Gets the first element of vector
     * @return returns: value_type& - the last element of vector
     * 
    **/
    reference front() { return *begin(); }

    /**
     * Gets the last element of vector
     * @return returns: value_type& - the last element of vector
     * 
    **/
    reference back() { return *(end() - 1); }

    /**
     * Gets the reference of the element according to the subscript
     * @return returns: value_type & - the element according to the subscript
     * @param loca - unsigned int - the subscript 
    **/
    reference operator[](size_type loca) {
    # ifdef AMI_STL_STRICT_MODE
        if (loca >= size()) __THROW_OUT_OF_BOUNDS;
    # endif
        return *(__map_begin + loca);
    }

    /**
     * Add an element to the end of the vector
     * @return no return 
     * @param value - const value_type & - elements to be added
    **/
    void push_back(const value_type &value) {
        if (capacity() < size() + 1) {
            this->__enlarge();
        }
        AMI_std::construct(__map_end, value);
        __map_end++;
    }

    /**
     * Remove an element from the end of the vector
     * @return no return 
     * 
    **/
    void pop_back() {
    # ifdef AMI_STL_STRICT_MODE
        if (empty()) __THROW_OUT_OF_BOUNDS;
    # endif
        AMI_std::destroy(__map_end);
        __map_end--;
        if (capacity() > size() * 4) {
            this->__shrink();
        }
    }

    /**
     * Delete the element that iterator pos refers to
     * @return returns: iterator - iterator to deleted position
     * @param pos - iterator - the iterator
    **/
    iterator erase(iterator pos) {
    # ifdef AMI_STL_STRICT_MODE
        if (empty()) __THROW_OUT_OF_BOUNDS;
    # endif
        size_type relative = pos - __map_begin;
        if (pos + 1 != end()) {
            AMI_std::copy(pos + 1, end(), pos);
        }
        AMI_std::destroy(__map_end--);
        if (capacity() > size() * 4) {
            this->__shrink();
        }
        return __map_begin + relative;
    }

    /**
     * Delete the element that subscript pos refers to
     * @return returns: iterator - iterator to deleted position
     * @param pos - unsigned int - the subscript
    **/
    iterator erase(size_type pos) {
        return erase(begin() + pos);
    }

    /**
     * Delete the elements from _begin to _end
     * @return returns: iterator - iterator to the _begin iterator
     * @param _begin - iterator    -  the begin point of deletion
     * @param _end   - iterator    -  the end point of deletion
    **/
    iterator erase(iterator _begin, iterator _end) {
        size_type relative = _begin - __map_begin;
        size_type dele_length = _end - _begin;
    # ifdef AMI_STL_STRICT_MODE
        if (dele_length >= size()) __THROW_OUT_OF_BOUNDS;
    # endif
        AMI_std::copy(_end, end(), _begin);
        AMI_std::destroy(end() - dele_length, end());
        __map_end -= dele_length;
        while (capacity() > size() * 4) {
            this->__shrink();
        }
        return __map_begin + relative;
    }

    /**
     * Delete the elements from _begin to _end
     * @return returns: iterator - iterator to the _begin iterator
     * @param _begin - unsigned int    -  the begin point of deletion
     * @param _end   - unsigned int    -  the end point of deletion
    **/
    iterator erase(size_type _begin, size_type _end) {
        return erase(begin() + _begin, begin() + _end);
    }

    /**
     * Insert a sequence of elements with a given length at a given point
     * @return returns: iterator - iterator to the insert-begin iterator
     * @param pos    - iterator               -  the begin point of insertion
     * @param length - unsigned int           -  the length of the length of insert
     * @param value  - const value_type&      -  the value of the inserted element
    **/
    iterator insert(iterator pos, size_type length, const value_type& value) {
        return insert(pos - begin(), length, value);
    }

    /**
     * Insert a sequence of elements with a given length at a given point
     * @return returns: iterator - iterator to the insert-begin iterator
     * @param pos    - unsigned int           -  the begin point of insertion
     * @param length - unsigned int           -  the length of the length of insert
     * @param value  - const value_type&      -  the value of the inserted element
    **/
    iterator insert(size_type pos, size_type length, const value_type& value) {
        while (capacity() < size() + length) {
            __enlarge();
        }
        iterator new_pos = begin() + pos;
        if (size_type(end() - new_pos) >= length) {
            AMI_std::uninitialized_copy(end() - length, end(), end());
            AMI_std::copy_backward(new_pos, new_pos + length, new_pos + 2 * length);
            AMI_std::fill_n(new_pos, length, value);
            __map_end += length;
        } else {
            iterator fill_end = end() + length - size_type(end() - new_pos);
            AMI_std::uninitialized_fill(end(), fill_end, value);
            AMI_std::uninitialized_copy(new_pos, end(), fill_end);
            AMI_std::fill(new_pos, end(), value);
            __map_end += length;
        }
        return new_pos;
    }

    /**
     * Insert one elements at a given point
     * @return returns: iterator - iterator to the insert-begin iterator
     * @param pos    - unsigned int           -  the point of insertion
     * @param value  - const value_type&      -  the value of the inserted element
    **/
    iterator insert(size_type pos, const value_type& value) {
        return insert(pos, 1, value);
    }

    /**
     * Insert one elements at a given point
     * @return returns: iterator - iterator to the insert-begin iterator
     * @param pos    - iterator               -  the point of insertion
     * @param value  - const value_type&      -  the value of the inserted element
    **/
    iterator insert(iterator pos, const value_type& value) {
        return insert(pos, 1, value);
    }

    /**
     * Reverse vector and return its reference
     * @return returns: Reference to the reversed vector
     * 
    **/
    vector& reverse() {
        size_type length = size();
        for (size_type i = 0; i < length / 2; i++) {
            AMI_std::swap((*this)[i], (*this)[length - i - 1]);
        }
        return (*this);
    }

    /**
     * Clears all elements of the vector without reallocating space
     * @return returns: the first iterator of the cleared vector
     * 
    **/
    iterator clear() { return erase(begin(), end()); }

    /**
     * Resets the size of the vector 
     * discards elements that are out of range OR fill in the new free space
     * @return no returns
     * @param _size    - unsigned int      - the new size
     * @param value    - const value_type& - elements to fill in (if possible)
    **/
    void resize(size_type _size, const value_type& value) { 
        if (_size > size()) {
            insert(end(), _size - size(), value);
        } else {
            erase(begin() + _size, end());
        }
    }

    /**
     * Resets the size of the vector 
     * discards elements that are out of range OR fill in the new free space with its default ctor
     * @return no returns
     * @param _size    - unsigned int      - the new size
    **/
    void resize(size_type _size) {
        resize(_size, value_type());
    }

    /**
     * Find the first element that is not equal to value
     * @return returns: iterator - required iterator
     * @param _target - const value_type & - the target
    **/
    iterator find_first_not_of(const value_type &_target) {
        return ::AMI_std::find_first_not_of(begin(), end(), _target);
    }

    /**
     * Find the first element that is equal to value
     * @return returns: iterator - required iterator
     * @param _target - const value_type & - the target
    **/
    iterator find_first_of(const value_type &_target) {
        return ::AMI_std::find_first_of(begin(), end(), _target);
    }

    /**
     * Find the last element that is equal to value
     * @return returns: iterator - required iterator
     * @param _target - const value_type & - the target
    **/
    iterator find_last_of(const value_type &_target) {
        return ::AMI_std::find_last_of(begin(), end(), _target);
    }

    /**
     * Find the last element that is not equal to value
     * @return returns: iterator - required iterator
     * @param _target - const value_type & - the target
    **/
    iterator find_last_not_of(const value_type &_target) {
        return ::AMI_std::find_last_not_of(begin(), end(), _target);
    }

    /**
     * Output vector elements with fixed separator, Stream operation operators that overload elements are required.
     * @return no returns
     * @param _div - const char* (default: ", ") - the separator
    **/
    void print(const char* _div = ", ") {
        for (iterator i = begin(); i < end() - 1; i++) {
            std::cout << *i << _div;
        }
        if (size() > 0) std::cout << back();
        std::cout << "\n";
    }

# ifndef AMI_STL_STRICT_MODE

    /**
     * Forced transfer to bool
     * @return returns: bool - Is the vector empty
     * 
    **/
    operator bool() { return this->empty(); }
# endif
};

# ifndef AMI_STL_STRICT_MODE
    template <class T> 
    std::ostream &operator<<(std::ostream& os, vector<T> &_v) {
        for (typename vector<T>::iterator i = _v.begin(); i < _v.end() - 1; i++) {
            std::cout << *i << ", ";
        }
        if (_v.size() > 0) std::cout << _v.back();
        return os;
    }
# endif

__ASTL_NAMESPACE_END 