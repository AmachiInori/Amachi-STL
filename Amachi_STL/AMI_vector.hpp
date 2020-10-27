# pragma once
# include "AMI_allocate.hpp"
# include "initializer_list"
# include <iostream>

/**
 * This file is the user oriented part of amachi STL
 * Open source by MIT by amachi Inori
 * 
 * Main header file of dynamic array AMI_std::vector
 * The dynamic array AMI_std::vector is declared and defined in this file with namespace AMI_std
 * Some overloaded stream operations are also defined in this file with namespace AMI_std
**/

__ASTL_NAMESPACE_START

/**
 * ordered table container similar to std::vector
 * 
 * compared with std::vector, 
 * this implementation improves the utilization of space by releasing too much free space at any time
 * (So iterators are more likely to fail) Use a relative cursor to store the location
 * some practical methods have been added
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
        uninitialized_fill_n(res, length, value);
        return res;
    }
    iterator __alloc_and_copy(pointer begin, pointer end) {
        iterator res = __vector_alloc::allocate(end - begin);
        uninitialized_copy(begin, end, res);
        return res;
    }
    void __destroy_element() {
        destroy(__map_begin, __map_end);
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
        uninitialized_copy(__map_begin, __map_end, new_begin);
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
        uninitialized_copy(__map_begin, __map_end, new_begin);
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
     * Constructor of vector with two iterator to copy all the elements between __begin and __end 
     * @return no return 
     * @param __begin - iterator - the start point of the copied array
     * @param __end   - iterator - the end point of the copied array
    **/
    vector(iterator __begin, iterator __end) noexcept {
        size_type __length = __end - __begin;
        __map_begin = __alloc_and_copy(&*__begin, &*__end);
        __map_end = __storage_end = __map_begin + __length;
    }

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

    /**
     * Destructor of vector
    **/
    ~vector() noexcept {
        __destroy_element();
        __dealloc();
    }

    /**
     * Standard assignment operator
     * @return returns: vector<value_type> & - lvalue of assignment
     * @param other_v - const vector<value_type> & - the right value of assignment  
    **/
    vector<value_type>& operator=(const vector<value_type> &other_v) {
        vector<value_type> temp(other_v);
        this->__destroy_element();
        this->__dealloc();
        __map_begin = __alloc_and_copy(&*(temp.__map_begin), &*(temp.__map_end));
        __map_end = __storage_end = __map_begin + (temp.__map_end - temp.__map_begin);
        return *this;
    }

    /**
     * Gets the reference of the element according to the subscript
     * @return returns: value_type & - the element according to the subscript
     * @param loca - unsigned int - the subscript 
    **/
    value_type& at(size_type loca) {
        return (*this)[loca];
    }

    /**
     * Gets the begin itreator of vector
     * @return returns: iterator - the begin itreator of vector
     * 
    **/
    iterator begin() { return __map_begin; }

    /**
     * Gets the end itreator of vector
     * @return returns: iterator - the end itreator of vector
     * 
    **/
    iterator end() { return __map_end; }

    /**
     * Gets the occupied size of vector
     * @return returns: unsigned int - occupied size of vector
     * 
    **/
    size_type size() const { return size_type(__map_end - __map_begin); }

    /**
     * Gets the memory size of vector
     * @return returns: unsigned int - memory size of vector
     * 
    **/
    size_type capacity() const { return size_type(__storage_end - __map_begin); }

    /**
     * Gets the memory size of vector
     * @return returns: unsigned int - memory size of vector
     * 
    **/
    size_type max_size() const { return this->capacity(); }

    /**
     * Judge whether vector is empty
     * @return returns: bool
     * 
    **/
    bool empty() const { return __map_begin == __map_end; }

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
        construct(__map_end, value);
        __map_end++;
    }

    /**
     * Remove an element from the end of the vector
     * @return no return 
     * 
    **/
    void pop_back() {
        destroy(__map_end);
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
        size_type relative = pos - __map_begin;
        if (pos + 1 != end()) {
            copy(pos + 1, end(), pos);
        }
        destroy(__map_end--);
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
        copy(_end, end(), _begin);
        destroy(end() - dele_length, end());
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
            uninitialized_copy(end() - length, end(), end());
            copy_backward(new_pos, new_pos + length, new_pos + length);
            fill_n(new_pos, length, value);
            __map_end += length;
        } else {
            iterator fill_end = end() + length - size_type(end() - new_pos);
            uninitialized_fill(end(), fill_end, value);
            uninitialized_copy(new_pos, end(), fill_end);
            fill(new_pos, end(), value);
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
            swap((*this)[i], (*this)[length - i - 1]);
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
    void print (const char* _div = ", ") {
        for (size_type i = 1; i < size(); i++) {
            std::cout << (*this)[i - 1] << _div;
        }
        if (size() > 0) std::cout << back();
        std::cout << "\n";
    }
};

template <class T> 
std::ostream &operator<<(std::ostream& os, vector<T> &_v) {
    for (_AMI_size_t i = 1; i < _v.size(); i++) {
        std::cout << _v[i - 1] << ", ";
    }
    if (_v.size() > 0) std::cout << _v.back();
    return os;
}

__ASTL_NAMESPACE_END 