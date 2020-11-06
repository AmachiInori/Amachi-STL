# Amachi-STL Readme

## 这是什么？

这是一份简易版的STL标准库，正处于开发阶段。依赖于C++11的特性，C++11以上的编译器可以支持它。  

由于水平有限，本STL的效率和稳定性一定比那些著名的库(如SGI STL)差，但是我保证了编码的直观可读，适合初学者学习STL的基本操作和构建。  

因此，我在编码风格和可读性方面做了些许优化，但为了保证简洁性，注释中只注明了用户可见方法及函数的英文说明，其余说明或中文说明还请参照文档。

## 如何使用

### 包含

在`Amachi_STL`下的所有`.hpp`文件均为面向用户的文件，直接包含即可。

### 严格模式

你可以在包含文件之前使用预编译指令`# define AMI_STRICT_MODE_ON`来启用`Amachi_STL`的严格模式。

在严格模式下：

1. 所有容器的泛型构造和泛型赋值将被禁用
2. 对于容器的访问，边界检查将被启用
3. 一些仅仅提供方便的非STL标准的方法及接口将被禁用

严格模式保证了对标准STL的兼容性，如果你希望将`Amachi_STL`与其他符合STL标准的类结合使用，那么请务必开启严格模式。

## STL库文件

### 核心部分

|文件|文档|简述|
|:----:|:----:|:----:|
|[AMI_allocate](../../Amachi_STL/AMI_allocate)|[AMI_allocate的文档](/Document/cn/_details_document/AMI_allocate.md)|空间配置器的外层封装|
|[AMI_array](../../Amachi_STL/AMI_array)|[AMI_array的文档](/Document/cn/_details_document/AMI_array.md)|静态数组封装类array|
|[AMI_vector](../../Amachi_STL/AMI_vector)|[AMI_vector的文档](/Document/cn/_details_document/AMI_vector.md)|动态数组类vector|

