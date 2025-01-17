# 1. 理解模板类型推导
> 理解下列几种情况下的模板类型推导方式

考虑如下模板:
```c++
template<typename T>
void f(ParamType param);
f(expr);
```
## 1. ParamType 是一个指针或者引用,但是不是通用引用
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

## 2. ParamType 是一个通用引用
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
## 3. ParamType既不是指针也不是引用
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
## 4. 数组实参和函数实参
- 记住规律即可:
	- `T`为值,那么推导得到的类型就是指针(对于数组来说就是 `const T *`),对于函数而言就是函数指针
	- `T`为引用`T&` , 那么就会推导得到 `const int& []` 和 `(...)(&)(...)`
# 2. 理解auto类型推导
> 理解`auto`类型推导和模板类型推导基本一样即可,另外注意不同之处再与多与初始化列表的推导
- 利用模板推导的方法来进行`auto`类型推导,此时 `auto` 可以看成 `T`, 类型说明符可以看成`PType` ,也就是如下等效方法:
```c++
auto x = 10;

// 可以等效为
template<typename T>
void func(T x);

const auto& a = x;

// 可以等效为:
template<typename T>
void func(const T& a);  // const int&
```
举例如下:
```c++
auto x = 27;                    //情景三（x既不是指针也不是引用）
const auto cx = x;              //情景三（cx也一样）
const auto & rx=cx;             //情景一（rx是非通用引用）

auto&& uref1 = x;               //x是int左值，
                                //所以uref1类型为int&
auto&& uref2 = cx;              //cx是const int左值，
                                //所以uref2类型为const int&
auto&& uref3 = 27;              //27是int右值，
                                //所以uref3类型为int&&

```
对于数组或者函数也是一样的:
```c++
const char name[] =             //name的类型是const char[13]
 "R. N. Briggs";

auto arr1 = name;               //arr1的类型是const char*
auto& arr2 = name;              //arr2的类型是const char (&)[13]

void someFunc(int, double);     //someFunc是一个函数，
                                //类型为void(int, double)

auto func1 = someFunc;          //func1的类型是void (*)(int, double)
auto& func2 = someFunc;         //func2的类型是void (&)(int, double)
```
- 但是不同之处在与对于初始化列表的推导,对于`auto`而言,推导方式如下:
```c++
auto x1 = 27;                   //类型是int，值是27
auto x2(27);                    //同上
auto x3 = { 27 };               //类型是std::initializer_list<int>，
                                //值是{ 27 }
auto x4{ 27 };                  //同上
```
- 但是对于模板而言:
```c++
auto x = { 11, 23, 9 };         //x的类型是std::initializer_list<int>

template<typename T>            //带有与x的声明等价的
void f(T param);                //形参声明的模板

f({ 11, 23, 9 });               //错误！不能推导出T

template<typename T>
void f(std::initializer_list<T> initList);

f({ 11, 23, 9 });               //T被推导为int，initList的类型为
                                //std::initializer_list<int>

```
- 最后一点,在`C++14` 中允许使用 `auto` 作为函数的返回值,但是类型推导的方式不是根据`auto`而是根据模板的规则来的,所以如下的例子是错误的:
```c++
auto createInitList()
{
    return { 1, 2, 3 };         //错误！不能推导{ 1, 2, 3 }的类型
}

std::vector<int> v;
…
auto resetV = 
    [&v](const auto& newValue){ v = newValue; };        //C++14
…
resetV({ 1, 2, 3 });            //错误！不能推导{ 1, 2, 3 }的类型
```
# 3. 理解 decltype
> 把`decltype`的作用理解为得到变量的类型即可

- 首先关注 `decltype` 的默认作用,举例如下:
```c++
const int i = 0;                //decltype(i)是const int

bool f(const Widget& w);        //decltype(w)是const Widget&
                                //decltype(f)是bool(const Widget&)

struct Point{
    int x,y;                    //decltype(Point::x)是int
};                              //decltype(Point::y)是int

Widget w;                       //decltype(w)是Widget

if (f(w))…                      //decltype(f(w))是bool

template<typename T>            //std::vector的简化版本
class vector{
public:
    …
    T& operator[](std::size_t index);
    …
};

vector<int> v;                  //decltype(v)是vector<int>
…
if (v[0] == 0)…                 //decltype(v[0])是int&
```
- 同时`delctype`的一个比较重要的作用就是当函数模板的返回值与形式参数有关的时候可以利用 `delctype` 进行返回值的类型推导:
```c++
template<typename Container, typename Index>    //可以工作，
auto authAndAccess(Container& c, Index i)       //但是需要改良
    ->decltype(c[i])
{
    authenticateUser();
    return c[i];
}
```
同时对于`lambda`表达式也可以进行相应的推导
- 同时在`C++14`中,由于直接使用`auto` 进行推导会去除引用(第三种情况),所以需要使用`delctype`进行类型推导,也就是可以使用  `decltype(auto)` 进行类型推导,表示进行类型推导但是使用`delctype`的方式进行推导
- 对于需要使用右值引用的情况,还是需要使用`decltype(auto)` 进行推导:
```c++
template<typename Container, typename Index>    //最终的C++14版本
decltype(auto)
authAndAccess(Container&& c, Index i)
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}
```
- 总结:
	- `decltype` 总是不加修改的产生变量或者表达式的类型
	- 对于`T`类型的不是单纯的变量名的左值表达时,`dectype`总是推导为`T&`(比如`c[index]`等)
	- `C++14`中的`decltype(auto)` , 就像`auto`一样,推导出类型,但是它使用`decltype`的规则进行推导

# 4. 学会查看类型推导的结果
1. 利用`IDE`编辑器查看
2. 编译器诊断(报错)
3. 利用`std::typeid().name` 查看变量类型名称(之可以显示类型,没有修改修饰符号)
4. 使用第三方库






