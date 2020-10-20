# Amachi-STL Readme

## AMI_std::vector

### 简介

AMI_std::vector是一个动态数组模板，它属于动态存储的顺序式线性表容器，定义于文件`AMI_vector`中，它仿照了std::vector。

### 外部依赖

AMI_std::vector需要一个定义了`value_type* allocate(unsigned int)`和`void deallocate(value_type*, unsigned int)`接口的空间配置器类作为第二模板参数传入，默认使用包含文件`AMI_allocate`中定义的以默认模板参数的`base_allocator`。

它也需要构造-析构以及针对连续未初始化空间的对象构造方法，这些方法固定在包含文件`AMI_base/AMI_construct.h`和`AMI_base/AMI_uninit.h`中。

同时，针对C++11之后的`initializer_list`初始化标准，它需要访问`initializer_list`类的`begin()`和`end()`方法。此处未添加针对于C++标准的判断，故请使用C++11及以上的编译器套件并确保`initializer_list`文件可以访问。

### public成员方法

**一、类实例结构方法**

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

标准析构函数。

#### `vector<value_type>& operator=(const vector<value_type> &other_v)`

标准赋值运算重载。

将本实例替换为目标实例的副本，其中的数组元素均以其复制构造函数构造。

进行了稳定性优化，适配自我赋值情况，因此效率可能偏低。

**二、类数据结构方法**

## 文件`AMI_vector`

### 包含项