# Amachi-STL Readme

## AMI_std::vector

### Overview

AMI_std::vector is a dynamic array template. It belongs to a dynamic storage sequential linear table container, which is defined in the file 'AMI_vector', it imitates std::vector.

### External dependence

AMI_std::vector needs a memory allocator which has a `value_type* allocate(unsigned int)` and `void deallocate(value_type*, unsigned int)` function as the second template parameter. The default configuration is the `base_allocator` with default template parameter in the including file `AMI_allocate`.

Construction-destruct and object construction methods for continuous uninitialized space which are defined in the including file `AMI_base/AMI_construct.h` and `AMI_base/AMI_uninit.h` are also needed.

Meanwhile, In order to fit the `initializer_list` which is the new features of C++11, access of the method `begin()` and `end()` of the `initializer_list` is also required. Judgment for the version of C++ is not added here, Therefore, please use C++ 11 and above compiler packages and ensure that the `initializer_list` file can be accessed.

### public member method

**A. class structure method**

#### `vector()` 

The default constructor constructs an empty vector instance.

#### `vector(size_type length)`

Constructor.

Construct a vector with a given length, all elements in the instance will use its default constructor to construct, so `value_type` must have a default constructor, otherwise the compilation fails.

#### `vector(iterator __begin, iterator __end)`

Constructor.

Construct a vector with two iterators, all the elements from `__begin` to `__end` will be copied in the new vector.

#### `vector(size_type length, const value_type &value)`

Constructor.

Construct a vector with a given length, all elements in the instance will use its copy constructor to construct with the parameter `value`, so `value_type` must have a copy constructor, otherwise the compilation fails.


#### `vector(int length, const value_type &value)`

Constructor.

Construct a vector with a given length, all elements in the instance will use its copy constructor to construct with the parameter `value`, so `value_type` must have a copy constructor, otherwise the compilation fails.


#### `vector(long length, const value_type &value)`

Constructor.

Construct a vector with a given length, all elements in the instance will use its copy constructor to construct with the parameter `value`, so `value_type` must have a copy constructor, otherwise the compilation fails.


#### `vector(const vector<value_type> &other_v)`

Copy constructor.

Copy-construct a copy of `other_v`, each of the elements will be constructed with its copy constructor.

#### `vector(const other& _other)`

广义复制构造函数。仅非严格模式。

调用容器`_other`中的复制构造函数复制其中的全部元素。

需要`other`类型有`begin()`和`end()`方法返回一个迭代器。

#### `vector(const std::initializer_list<value_type> &i_list)`

In orded to fit the `std::initializer_list` class, delegate `vector(iterator __begin, iterator __end)` to construct the vector.

#### `~vector()`

Standard destructor. Destructs all array elements with the default destructor and frees up memory.

#### `vector<value_type>& operator=(const vector<value_type> &other_v)`

Standard assignment operation overload.

Replace this instance with a copy of the target instance, where the array elements are constructed with their copy constructors.

Stability optimization is carried out to adapt to the self assignment situation, so the efficiency may be low.

#### `vector<value_type>& operator=(const other &other_v)`

泛型赋值运算符重载。

将本实例中的全部元素通过复制构造替换为目标容器中的所有元素。

需要`other`类型有`begin()`和`end()`方法返回一个迭代器。


**二 类数据结构方法**

#### `reference at(size_type loca)`

按照下标位置`loca`提取出vector元素的引用。

#### `iterator begin()`

获取vector的开始迭代器

#### `iterator end()`

获取vector的终止迭代器

#### `size_type size()`

获取vector中已占用的大小

#### `size_type capacity()`

获取vector当前拥有的内存空间大小

#### `size_type max_size()`

传递调用`capacity()`得到内存空间大小

#### `bool empty()`

判断vector是否非空，若空则返回true，非空则返回false

#### `reference front()`

返回数组的第一个元素(0号元素)的引用

#### `reference back()`

返回数组的最后一个元素(`size() - 1`号元素)的引用

#### `reference operator[](size_type loca)`

按照下标位置`loca`提取出vector元素的引用。

#### `void push_back(const value_type &value)`

在vector容器尾端加入一个元素，该元素使用其复制构造函数构造，参数为`value`

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `void pop_back()`

删除vector容器尾端的一个元素，并使用默认析构函数析构之。

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator erase(iterator pos)`

删除由迭代器`pos`指向的元素并将其后所有元素前移一位，并返回指向此位置的新迭代器(可能与旧的迭代器不同)，此过程调用数组元素实例的标准析构和标准赋值运算符。

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator erase(size_type pos)`

删除由下标`pos`指向的元素并将其后所有元素前移一位，并返回指向此位置的新迭代器，此过程调用数组元素实例的标准析构和标准赋值运算符。

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator erase(iterator _begin, iterator _end)`

删除迭代器指针`_begin`和`_end`之间的所有元素并将其后所有元素前移若干位，并返回指向开始位置的新迭代器(可能与旧的迭代器不同)，此过程调用数组元素实例的标准析构和标准赋值运算符。

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator erase(size_type _begin, size_type _end)`

删除下标`_begin`和`_end`之间的所有元素并将其后所有元素前移若干位，并返回指向开始位置的新迭代器，此过程调用数组元素实例的标准析构和标准赋值运算符。

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator insert(iterator pos, size_type length, const value_type& value)`

在迭代器指向的位置`pos`插入`length`个元素，并将其后元素向后移若干位，这些元素均使用其复制构造函数构造，参数为`value`，并返回新的开始位置

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator insert(size_type pos, size_type length, const value_type& value)`

在下标指向的位置`pos`插入`length`个元素，并将其后元素向后移若干位，这些元素均使用其复制构造函数构造，参数为`value`，并返回新的开始位置

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator insert(size_type pos, const value_type& value)`

在下标指向的位置`pos`插入1个元素，并将其后元素向后移1位，这个元素均使用其复制构造函数构造，参数为`value`，并返回新的开始位置

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `iterator insert(iterator pos, const value_type& value)`

在迭代器指向的位置`pos`插入1个元素，并将其后元素向后移1位，这个元素均使用其复制构造函数构造，参数为`value`，并返回新的开始位置

**注意** 本方法有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `vector& reverse()`

反转整个容器，并返回它的引用。

此过程需要调用容器元素的赋值运算符。

#### `iterator clear()`

删除全部元素。

此过程需要调用容器元素的标准析构。

**注意** 本方法极有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `void resize(size_type _size, const value_type& value)`

以大小`_size`重配容器空间。若新大小大于旧大小，则以`value`填充新增空间(调用复制构造函数)；若若新大小小于旧大小，则调用默认析构。

**注意** 本方法极有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

#### `void resize(size_type _size)`

以大小`_size`重配容器空间。若新大小大于旧大小，则以默认实例填充新增空间(调用默认构造函数)；若若新大小小于旧大小，则调用默认析构。

**注意** 本方法极有可能会触发容器空间重配，空间重配会导致所有被暂存的指针式迭代器失效。故如需使用这一方法，请确保使用数组下标来模拟指针式迭代器。

**三 迭代算法方法**

#### `iterator find_first_not_of(const value_type &_target)`

从左到右顺序查找第一个与`_target`不相等的实例，并返回实例指针，线性时间复杂度。

需调用类实例的重载相异运算符`!=`

#### `iterator find_first_of(const value_type &_target)`

从左到右顺序查找第一个与`_target`相等的实例，并返回实例指针，线性时间复杂度。

需调用类实例的重载相等运算符`==`

#### `iterator find_last_of(const value_type &_target)`

从右到左顺序查找第一个与`_target`相等的实例，并返回实例指针，线性时间复杂度。

需调用类实例的重载相等运算符`==`

#### `iterator find_last_not_of(const value_type &_target)`

从右到左顺序查找第一个与`_target`不相等的实例，并返回实例指针，线性时间复杂度。

需调用类实例的重载相等运算符`!=`

#### `void print (const char* _div = ", ")`

顺序输出容器元素，在两个元素之间以`_div`分隔并在最后添加换行符`\n`。

需要访问`std::cout`和容器实例的重载流输出运算符`<<`

## 文件`AMI_vector`

### include项

|文件|简述|
|:----:|:----:|
|AMI_allocate|用于访问默认空间配置器|
|initializer_list|用于适配C++11新特性initializer_list|
|iostream|用于以stdout输出元素|

### 类外部方法

#### `std::ostream &operator<<(std::ostream& os, vector<T> &_v)`

顺序输出容器元素，在两个元素之间以`", "`分隔。

需要访问`std::cout`和容器实例的重载流输出运算符`<<`
