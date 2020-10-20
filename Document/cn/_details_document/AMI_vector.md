# Amachi-STL Readme

## AMI_std::vector

### ���

AMI_std::vector��һ����̬����ģ�壬�����ڶ�̬�洢��˳��ʽ���Ա��������������ļ�`AMI_vector`�У���������std::vector��

### �ⲿ����

AMI_std::vector��Ҫһ��������`value_type* allocate(unsigned int)`��`void deallocate(value_type*, unsigned int)`�ӿڵĿռ�����������Ϊ�ڶ�ģ��������룬Ĭ��ʹ�ð����ļ�`AMI_allocate`�ж������Ĭ��ģ�������`base_allocator`��

��Ҳ��Ҫ����-�����Լ��������δ��ʼ���ռ�Ķ����췽������Щ�����̶��ڰ����ļ�`AMI_base/AMI_construct.h`��`AMI_base/AMI_uninit.h`�С�

ͬʱ�����C++11֮���`initializer_list`��ʼ����׼������Ҫ����`initializer_list`���`begin()`��`end()`�������˴�δ��������C++��׼���жϣ�����ʹ��C++11�����ϵı������׼���ȷ��`initializer_list`�ļ����Է��ʡ�

### public��Ա����

**һ����ʵ���ṹ����**

#### `vector()` 

Ĭ�Ϲ��캯��������һ���յ�vectorʵ����

#### `vector(size_type length)`

���캯����

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

��׼����������

#### `vector<value_type>& operator=(const vector<value_type> &other_v)`

��׼��ֵ�������ء�

����ʵ���滻ΪĿ��ʵ���ĸ��������е�����Ԫ�ؾ����临�ƹ��캯�����졣

�������ȶ����Ż����������Ҹ�ֵ��������Ч�ʿ���ƫ�͡�

**���������ݽṹ����**

## �ļ�`AMI_vector`

### ������