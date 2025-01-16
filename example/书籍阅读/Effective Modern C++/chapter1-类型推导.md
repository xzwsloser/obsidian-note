## 1. 理解模板类型推导
> 理解下列几种情况下的模板类型推导方式

考虑如下模板:
```c++
template<typename T>
void f(ParamType param);
f(expr);
```
### 1. ParamType 是一个指针或者引用,但是不是通用引用
- 此时,模板类型推导的具体规则如下:
	- 如果`expr`类型是一个引用类型,忽略引用部分
	- 然后使用 `expr`的类型与`ParamType`进行匹配来决定 `T`
具体例子交换如下:
```c++
template<typename T>
void f(const T& param);

int x = 29;
const int cx = x;
const int& rx = x; 

f(x);  // T -> int  PType -> const int&
f(cx); // T -> int PType -> const int&
f(rx); // T -> int PType -> const int& (忽略 rx 的引用性质)
```
指针也是一样的:
```c++
template<typename T>
void f(T* param);

int x = 27;
const int* px = &x;

f(x);  // T -> int PType -> int*
f(px); // 忽略指针: T -> const int PType -> const int*
```

### 2. ParamType 是一个通用引用
> 通用引用也就是 `T&&` 

- 判断规则如下:
	- 如果`expr`为左值,`T`和`ParamType`都会被推导为左值引用(唯一一种被推导成引用的)
	- 如果`expr`为右值,使用正常的推导规则(规则一,忽略引用直接推导)

举例如下:
```c++
template<typename T>
void f(T&& param);

int x = 27;
const int cx = x;
const int& rx = cx;

f(x); // x 为左值 , T -> int&  PType -> int&
f(cx); // cx 为左值, T -> const int& , PType -> const int&
f(rx);  // rx为左值 , T -> const int& , PType -> const int& 

f(27); // 右值 , T -> int , PType -> int&&
```
### 3. ParamType既不是指针也不是引用
> 也就是传递值的形式处理,模板如下:
```c++
template<typename T>
void f(T param);
```
- 推导规则:
	- 如果`expr`的类型为一个引用,就忽略引用部分
	- 如果忽略 `expr`的引用性之后,`expr`是一个`const`,那么就需要再次忽略`const` 
- 例子如下:
```c++
int x=27;                       //如之前一样
const int cx=x;                 //如之前一样
const int & rx=cx;              //如之前一样

f(x);                           //T和param的类型都是int
f(cx);                          //T和param的类型都是int
f(rx);                          //T和param的类型都是int
```
总是记住使用值传递的时候传递的都是拷贝值,如果传递一个指针传递的也就是指针指向的地址(可以把指针看作一个记录地址的变量),所以对于如下推导:
```c++
template<typename T>
void f(T param);                //仍然以传值的方式处理param

const char* const ptr =         //ptr是一个常量指针，指向常量对象 
    "Fun with pointers";

f(ptr);                         //传递const char * const类型的实参
```
拷贝的是 `ptr` 指向的地址,这一个地址指向的数字是不可以变化的,但是拷贝之后的变量本身可以变化,所以推导得到的类型为 `const int*`
### 4. 数组实参和函数实参
- 记住规律即可:
	- `T`为值,那么推导得到的类型就是指针(对于数组来说就是 `const T *`),对于函数而言就是函数指针
	- `T`为引用`T&` , 那么就会推导得到 `const int& []` 和 `(...)(&)(...)`
	