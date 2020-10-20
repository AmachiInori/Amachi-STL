# Amachi-STL Readme

## 这是什么？

这是一份简易版的STL标准库，正处于开发阶段。依赖于C++11的特性，C++11以上的编译器可以支持它。  

由于水平有限，本STL的效率和稳定性一定比那些著名的库(如SGI STL)差，但是我保证了编码的直观可读，适合初学者学习STL的基本操作和构建。  

因此，我在编码风格和可读性方面做了些许优化，但为了保证简洁性，注释中只注明了用户可见方法及函数的英文说明，其余说明或中文说明还请参照文档。

## STL库文件

### 核心部分

|文件|文档|简述|
|:----:|:----:|:----:|
|[AMI_allocate](../../Amachi_STL/AMI_allocate)|[AMI_allocate的文档](/Document/cn/_details_document/AMI_allocate.md)|空间配置器的外层封装|
|[AMI_array](../../Amachi_STL/AMI_array)|[AMI_array的文档](/Document/cn/_details_document/AMI_array.md)|静态数组封装类array|
|[AMI_vector](../../Amachi_STL/AMI_vector)|[AMI_vector的文档](/Document/cn/_details_document/AMI_vector.md)|动态数组类vector|

