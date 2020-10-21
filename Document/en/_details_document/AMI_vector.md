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

����һ������Ϊ`length`��vectorʵ�������е�Ԫ�ؾ�������Ĭ�Ϲ��캯�����죬���`value_type`��ӵ��Ĭ�Ϲ��캯����������벻ͨ����

#### `vector(iterator __begin, iterator __end)`

���캯����

����һ��vectorʵ���������ӵ�����`__begin`��`__end`֮�������Ԫ�ظ��ƽ�������

#### `vector(size_type length, const value_type &value)`

���캯����

����һ������Ϊ`length`��vectorʵ�������е�Ԫ�ؾ������临�ƹ��캯�����죬����Ϊ`value`�����`value_type`��ӵ�и��ƹ��캯����������벻ͨ����

#### `vector(int length, const value_type &value)`

���캯����

����һ������Ϊ`length`��vectorʵ�������е�Ԫ�ؾ������临�ƹ��캯�����죬����Ϊ`value`�����`value_type`��ӵ�и��ƹ��캯����������벻ͨ����

#### `vector(long length, const value_type &value)`

���캯����

����һ������Ϊ`length`��vectorʵ�������е�Ԫ�ؾ������临�ƹ��캯�����죬����Ϊ`value`�����`value_type`��ӵ�и��ƹ��캯����������벻ͨ����

#### `vector(const vector<value_type> &other_v)`

���ƹ��캯����

���ƹ���`other_v`�ĸ���������ÿһ������Ԫ�ؾ����临�ƹ��캯�����졣

#### `vector(const std::initializer_list<value_type> &i_list)`

���`std::initializer_list`�Ľӿڣ�ί��`vector(iterator __begin, iterator __end)`����ʵ����

#### `~vector()`

��׼������������Ĭ�����������������е�����Ԫ�ز��ͷſռ䡣

#### `vector<value_type>& operator=(const vector<value_type> &other_v)`

��׼��ֵ�������ء�

����ʵ���滻ΪĿ��ʵ���ĸ��������е�����Ԫ�ؾ����临�ƹ��캯�����졣

�������ȶ����Ż����������Ҹ�ֵ��������Ч�ʿ���ƫ�͡�

**�� �����ݽṹ����**

#### `reference at(size_type loca)`

�����±�λ��`loca`��ȡ��vectorԪ�ص����á�

#### `iterator begin()`

��ȡvector�Ŀ�ʼ������

#### `iterator end()`

��ȡvector����ֹ������

#### `size_type size()`

��ȡvector����ռ�õĴ�С

#### `size_type capacity()`

��ȡvector��ǰӵ�е��ڴ�ռ��С

#### `size_type max_size()`

���ݵ���`capacity()`�õ��ڴ�ռ��С

#### `bool empty()`

�ж�vector�Ƿ�ǿգ������򷵻�true���ǿ��򷵻�false

#### `reference front()`

��������ĵ�һ��Ԫ��(0��Ԫ��)������

#### `reference back()`

������������һ��Ԫ��(`size() - 1`��Ԫ��)������

#### `reference operator[](size_type loca)`

�����±�λ��`loca`��ȡ��vectorԪ�ص����á�

#### `void push_back(const value_type &value)`

��vector����β�˼���һ��Ԫ�أ���Ԫ��ʹ���临�ƹ��캯�����죬����Ϊ`value`

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `void pop_back()`

ɾ��vector����β�˵�һ��Ԫ�أ���ʹ��Ĭ��������������֮��

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator erase(iterator pos)`

ɾ���ɵ�����`pos`ָ���Ԫ�ز����������Ԫ��ǰ��һλ��������ָ���λ�õ��µ�����(������ɵĵ�������ͬ)���˹��̵�������Ԫ��ʵ���ı�׼�����ͱ�׼��ֵ�������

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator erase(size_type pos)`

ɾ�����±�`pos`ָ���Ԫ�ز����������Ԫ��ǰ��һλ��������ָ���λ�õ��µ��������˹��̵�������Ԫ��ʵ���ı�׼�����ͱ�׼��ֵ�������

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator erase(iterator _begin, iterator _end)`

ɾ��������ָ��`_begin`��`_end`֮�������Ԫ�ز����������Ԫ��ǰ������λ��������ָ��ʼλ�õ��µ�����(������ɵĵ�������ͬ)���˹��̵�������Ԫ��ʵ���ı�׼�����ͱ�׼��ֵ�������

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator erase(size_type _begin, size_type _end)`

ɾ���±�`_begin`��`_end`֮�������Ԫ�ز����������Ԫ��ǰ������λ��������ָ��ʼλ�õ��µ��������˹��̵�������Ԫ��ʵ���ı�׼�����ͱ�׼��ֵ�������

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator insert(iterator pos, size_type length, const value_type& value)`

�ڵ�����ָ���λ��`pos`����`length`��Ԫ�أ��������Ԫ�����������λ����ЩԪ�ؾ�ʹ���临�ƹ��캯�����죬����Ϊ`value`���������µĿ�ʼλ��

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator insert(size_type pos, size_type length, const value_type& value)`

���±�ָ���λ��`pos`����`length`��Ԫ�أ��������Ԫ�����������λ����ЩԪ�ؾ�ʹ���临�ƹ��캯�����죬����Ϊ`value`���������µĿ�ʼλ��

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator insert(size_type pos, const value_type& value)`

���±�ָ���λ��`pos`����1��Ԫ�أ��������Ԫ�������1λ�����Ԫ�ؾ�ʹ���临�ƹ��캯�����죬����Ϊ`value`���������µĿ�ʼλ��

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `iterator insert(iterator pos, const value_type& value)`

�ڵ�����ָ���λ��`pos`����1��Ԫ�أ��������Ԫ�������1λ�����Ԫ�ؾ�ʹ���临�ƹ��캯�����죬����Ϊ`value`���������µĿ�ʼλ��

**ע��** �������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `vector& reverse()`

��ת�����������������������á�

�˹�����Ҫ��������Ԫ�صĸ�ֵ�������

#### `iterator clear()`

ɾ��ȫ��Ԫ�ء�

�˹�����Ҫ��������Ԫ�صı�׼������

**ע��** ���������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `void resize(size_type _size, const value_type& value)`

�Դ�С`_size`���������ռ䡣���´�С���ھɴ�С������`value`��������ռ�(���ø��ƹ��캯��)�������´�СС�ھɴ�С�������Ĭ��������

**ע��** ���������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

#### `void resize(size_type _size)`

�Դ�С`_size`���������ռ䡣���´�С���ھɴ�С������Ĭ��ʵ����������ռ�(����Ĭ�Ϲ��캯��)�������´�СС�ھɴ�С�������Ĭ��������

**ע��** ���������п��ܻᴥ�������ռ����䣬�ռ�����ᵼ�����б��ݴ��ָ��ʽ������ʧЧ��������ʹ����һ��������ȷ��ʹ�������±���ģ��ָ��ʽ��������

**�� �����㷨����**

#### `iterator find_first_not_of(const value_type &_target)`

������˳����ҵ�һ����`_target`����ȵ�ʵ����������ʵ��ָ�룬����ʱ�临�Ӷȡ�

�������ʵ�����������������`!=`

#### `iterator find_first_of(const value_type &_target)`

������˳����ҵ�һ����`_target`��ȵ�ʵ����������ʵ��ָ�룬����ʱ�临�Ӷȡ�

�������ʵ����������������`==`

#### `iterator find_last_of(const value_type &_target)`

���ҵ���˳����ҵ�һ����`_target`��ȵ�ʵ����������ʵ��ָ�룬����ʱ�临�Ӷȡ�

�������ʵ����������������`==`

#### `iterator find_last_not_of(const value_type &_target)`

���ҵ���˳����ҵ�һ����`_target`����ȵ�ʵ����������ʵ��ָ�룬����ʱ�临�Ӷȡ�

�������ʵ����������������`!=`

#### `void print (const char* _div = ", ")`

˳���������Ԫ�أ�������Ԫ��֮����`_div`�ָ����������ӻ��з�`\n`��

��Ҫ����`std::cout`������ʵ������������������`<<`

## �ļ�`AMI_vector`

### include��

|�ļ�|����|
|:----:|:----:|
|AMI_allocate|���ڷ���Ĭ�Ͽռ�������|
|initializer_list|��������C++11������initializer_list|
|iostream|������stdout���Ԫ��|

### ���ⲿ����

#### `std::ostream &operator<<(std::ostream& os, vector<T> &_v)`

˳���������Ԫ�أ�������Ԫ��֮����`", "`�ָ���

��Ҫ����`std::cout`������ʵ������������������`<<`
