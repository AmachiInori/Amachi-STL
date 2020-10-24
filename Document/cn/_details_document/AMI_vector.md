# Amachi-STL Readme

## AMI_std::vector

### 概览

AMI_std::vector是一个动态数组模板，它属于动态存储的顺序式线性表容器，定义于文件`AMI_vector`中，它仿照了std::vector。

### 外部依赖

AMI_std::vector需要一个定义了`value_type* allocate(unsigned int)`和`void deallocate(value_type*, unsigned int)`接口的空间配置器类作为第二模板参数传入，默认使用包含文件`AMI_allocate`中定义的以默认模板参数的`base_allocator`。

它也需要构造-析构以及针对连续未初始化空间的对象构造方法，这些方法固定在包含文件`AMI_base/AMI_construct.h`和`AMI_base/AMI_uninit.h`中。

同时，针对C++11之后的`initializer_list`初始化标准，它需要访问`initializer_list`类的`begin()`和`end()`方法。此处未添加针对于C++标准的判断，故请使用C++11及以上的编译器套件并确保`initializer_list`文件可以访问。

### public成员方法

**一 类实例结构方法**

#### `vector()` 

默认构造函数，构造一个空的vector实例。

#### `vector(size_type length)`

构造函数。

构造一个长度为`length`的vector实例，其中的元素均调用其默认构造函数构造，因此`value_type`须拥有默认构造函数，否则编译不通过。

#### `vector(iterator __begin, iterator __end)`

构造函数。

构造一个vector实例，并将从迭代器`__begin`到`__end`之间的所有元素复制进入其中

#### `vector(size_type length, const value_type &value)`

构造函数。

构造一个长度为`length`的vector实例，其中的元素均调用其复制构造函数构造，参数为`value`，因此`value_type`须拥有复制构造函数，否则编译不通过。

#### `vector(int length, const value_type &value)`

构造函数。

构造一个长度为`length`的vector实例，其中的元素均调用其复制构造函数构造，参数为`value`，因此`value_type`须拥有复制构造函数，否则编译不通过。

#### `vector(long length, const value_type &value)`

构造函数。

构造一个长度为`length`的vector实例，其中的元素均调用其复制构造函数构造，参数为`value`，因此`value_type`须拥有复制构造函数，否则编译不通过。

#### `vector(const vector<value_type> &other_v)`

复制构造函数。

复制构造`other_v`的副本，其中每一个数组元素均由其复制构造函数构造。

#### `vector(const std::initializer_list<value_type> &i_list)`

针对`std::initializer_list`的接口，委托`vector(iterator __begin, iterator __end)`构造实例。

#### `~vector()`

标准析构函数。以默认析构函数析构所有的数组元素并释放空间。

#### `vector<value_type>& operator=(const vector<value_type> &other_v)`

标准赋值运算重载。

将本实例替换为目标实例的副本，其中的数组元素均以其复制构造函数构造。

进行了稳定性优化，适配自我赋值情况，因此效率可能偏低。

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

需调用类实例的重载相异运算符`!=`

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
