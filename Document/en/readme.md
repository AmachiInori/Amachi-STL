# Amachi-STL Readme

## What is this

This is a simple version of STL standard library, which is in the development stage. Depending on the characteristics of C++11, compilers above C++11 can support it.

Due to my limited programming skills, the efficiency and stability of this STL must be worse than those famous libraries (such as SGI STL), but I ensure that the coding is intuitive and readable, which is suitable for beginners to learn the basic operation and construction of STL.

Therefore, I have made some optimization in coding style and readability. However, in order to ensure brevity, the notes only indicate the English description of user visible methods and functions. For other descriptions or Chinese or Japanese descriptions, please refer to the documents.

## How to use?

### Include

In `Amachi_STL`, all of the `.hpp` files are user oriented and can be included directly.

### Strict mode

You can use precompiling instructions `# define AMI_STRICT_MODE_ON` before including files to enable `Amachi_STL`'s strict mode.

Under strict mode:

1. Generic construction and generic assignment for all containers will be disabled
2. For access to the container, boundary checking is enabled
3. Some non STL standard methods and interfaces that only provide convenience will be disabled

Strict mode ensures compatibility with standard STL. If you want to use it with other STL compliant classes, be sure to turn on strict mode.

## STL Sourse

### Major file

|File|Document|Description|
|:----:|:----:|:----:|
|[AMI_allocate](../../Amachi_STL/AMI_allocate)|[AMI_allocate](/Document/en/_details_document/AMI_allocate.md)|Memory allocator|
|[AMI_array](../../Amachi_STL/AMI_array)|[AMI_array](/Document/en/_details_document/AMI_array.md)|Static array|
|[AMI_vector](../../Amachi_STL/AMI_vector)|[AMI_vector](/Document/en/_details_document/AMI_vector.md)|Dynamic array class `vector`|

