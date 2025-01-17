# 1. 区别使用() 和 {} 创建对象
> 注意 `{}` 的优点和缺点以及使用时机
## 1. {}可以统一初始化方法
- 比如对于自定义对象,初始化和赋值的区别如下:
```c++
Widget w1;              //调用默认构造函数
Widget w2 = w1;         //不是赋值运算，调用拷贝构造函数
w1 = w2;                //是赋值运算，调用拷贝赋值运算符（copy operator=）
```
- 同时注意利用  `{}` 不会造成数据类型的变窄,但是利用  `()` 可能造成类型的变窄
## 2. {}倾向于调用 initializer_list 为参数的初始化函数
- 比如如下代码不可以通过编译:
```c++
class Widget { 
public: 
    Widget(int i, bool b);                      //同之前一样
    Widget(int i, double d);                    //同之前一样
    Widget(std::initializer_list<bool> il);     //现在元素类型为bool
    …                                           //没有隐式转换函数
};

Widget w{10, 5.0};              //错误！要求变窄转换
```

总结: 
- 花括号是使用最广泛的初始化语法,可以防止变窄转换,并且可以防止把初始化解析为函数声明(只要像函数声明一定会别解析为函数声明)
- 在构造函数重载决议中,编译器会尽最大的努力将括号初始化和初始化列表参数匹配即使不正确
- 对于数据类型`std::vector`来说两种初始化方式不太一样
# 2. 优先考虑 nullptr 而不是 0 和 NULL
- 不使用`0` 和 `NULL` 的原因是可能既不是指针类型也不是整型类型,比如如下例子:
```c++
void f(int);        //三个f的重载函数
void f(bool);
void f(void*);
f(0);               //调用f(int)而不是f(void*)
f(NULL);            //可能不会被编译，一般来说调用f(int)，
                    //绝对不会调用f(void*)
```
- 如果没有确定的类型(也就是只是根据`0`或者`NULL`进行类型推导,推导出来的结果一定不是指针),在模板中这种问题比较明显:
```c++
template<typename FuncType,
         typename MuxType,
         typename PtrType>
decltype(auto) lockAndCall(FuncType func,       //C++14
                           MuxType& mutex,
                           PtrType ptr)
{ 
    MuxGuard g(mutex);  
    return func(ptr); 
}

auto result1 = lockAndCall(f1, f1m, 0);         //错误！
auto result2 = lockAndCall(f2, f2m, NULL);      //错误！
auto result3 = lockAndCall(f3, f3m, nullptr);   //没问题
```
# 3. 优先考虑别名声明而非 typedef 
## 1. typedef 不支持模板化,但是别名支持
- 比如同时声明一个复杂类型:
```c++
// 使用别名声明
template<typename T>
using MyAllocList = std::list<T,MyAlloc<T>>;

MyAllocList<Widget> lw;

// 使用 typedef 
template<typename T>
struct MyAllocList {
	typedef std::list<T,MyAlloc<T>> type;  // type 表示类型
};

// 使用模板类
typename MyAllocList<Widget>::type lw;
```
## 2. C++14 中提供了类型转换的别名
- `C++14` 中提供的类型转换的别名与`C++11`中类型转换的别名的对应关系如下:
```c++
std::remove_const<T>::type          //C++11: const T → T 
std::remove_const_t<T>              //C++14 等价形式

std::remove_reference<T>::type      //C++11: T&/T&& → T 
std::remove_reference_t<T>          //C++14 等价形式

std::add_lvalue_reference<T>::type  //C++11: T → T& 
std::add_lvalue_reference_t<T>      //C++14 等价形式
```
# 4. 优先考虑限域enum而非未限域enum
- 非限域枚举:
```c++
enum Color {
	White,
	Red,
	Yellow
};
```
- 限域枚举:
```c++
enum class Color {
	White,
	Red,
	Yellow,
};
```
- 限域枚举的优点:
	- 不会污染命名空间
	- 不会发生类型转换
	- 可以前置声明,枚举改变不需要重新编译整个文件
	- 可以指定类型
```c++
enum class Color : int {
	White,
	Red,
	Yellow
};
```
并且枚举类需要进行类型转换才可以当成整型变量使用
# 5. 优先考虑deleted函数而非使用未定义的私有声明
- 注意`deleted`函数的作用就是代替`C++98`中如果不想要使用某一个函数就需要把这一个函数设置为私有函数并且不做实现(这样外界函数无法调用,并且友元函数由于无实现链接错误页无法调用)
- `deleted` 函数的作用如下:
	- 可以禁止调用某一些类自动生成的函数(比如赋值运算符号和拷贝构造函数)
	- 可以禁止使用某些类型作为重载函数的入参
	- 可以排除模板函数的参数的各种情况
```c++
class Widget {
public:
    …
    template<typename T>
    void processPointer(T* ptr)
    { … }
    …

};

template<>                                          //还是public，
void Widget::processPointer<void>(void*) = delete;  //但是已经被删除了
```
```c++
bool isLucky(int number);       //原始版本
bool isLucky(char) = delete;    //拒绝char
bool isLucky(bool) = delete;    //拒绝bool
bool isLucky(double) = delete;  //拒绝float和double
```
# 6. 使用 override声明重写函数
## 引用限定符号
- 作用: 根据调用这一个函数的`this`指针的类型来判断应该时用那一个函数,是函数重载的条件之一:
```c++
class Widget {
public:
    …
    void doWork() &;    //只有*this为左值的时候才能被调用
    void doWork() &&;   //只有*this为右值的时候才能被调用
}; 
…
Widget makeWidget();    //工厂函数（返回右值）
Widget w;               //普通对象（左值）
…
w.doWork();             //调用被左值引用限定修饰的Widget::doWork版本
                        //（即Widget::doWork &）
makeWidget().doWork();  //调用被右值引用限定修饰的Widget::doWork版本
                        //（即Widget::doWork &&）
```
## final 和 override
- `final`: 修饰函数标识函数不可以被重写,修饰类标识类不可以别继承
- `override`: 可以修饰重写函数,防止不满足重写规则
# 7. 优先考虑 const_iterator而非iterator
- `const_iterator` 相当于指向常量的指针,可以防止容器内的数据被改变,所以推荐使用,但是在`C++11`之前获取到`const_iterator` 比较困难,`C++11` 中引入了成员函数`cbegin , cend`可以直接获取到 `const_iteator`,同时`C++14`中有提供了自由函数`cbegin() 和 cend()` 可以直接对于容器进行操作获取到`const_iterator`
- 总结:
	- 优先考虑`const_iterator`而非`iterator`
	- 最大程度通用的代码中考虑非成员函数版本的`begin , end , cbegin , cend`函数等
# 8. 如果函数不抛出异常请使用noexcept
- 如果确定函数不会抛出异常(前置条件强制满足)那么就可以把函数声明为 `noexcept`,这一个标记的优点如下:
	- 与`non-noexcept`函数相比便于优化
	- 对于移动语义,`swap`和内存释放函数和析构函数非常有用(比如`swap`函数是否抛出异常依赖于自己定义的`swap`是否抛出异常)
- 在`C++98`和`C++11` 中不抛出异常的函数定义如下:
```c++
int f(int x) throw();   //C++98风格，没有来自f的异常
int f(int x) noexcept;  //C++11风格，没有来自f的异常
```
- 另外注意:
	- `noexcept`是函数接口的一部分,意味着调用者可能依赖它
	- 大多数函数是异常中立的
# 9. 尽可能使用constexpr
## constexpr与const的区别
- 对于`constexpr`修饰的变量,它的值都是编译期可知道的,但是`const`修饰的变量可能是运行时期可知的,所以利用`constexpr`可以作为函数模板参数等,举例说明:
```c++
// constexpr 修饰
int sz;                             //non-constexpr变量
…
constexpr auto arraySize1 = sz;     //错误！sz的值在
                                    //编译期不可知
std::array<int, sz> data1;          //错误！一样的问题
constexpr auto arraySize2 = 10;     //没问题，10是
                                    //编译期可知常量
std::array<int, arraySize2> data2;  //没问题, arraySize2是constexpr

// const修饰
int sz;                            //和之前一样
…
const auto arraySize = sz;         //没问题，arraySize是sz的const复制
std::array<int, arraySize> data;   //错误，arraySize值在编译期不可知
```
## constexpr函数
- `constexpr`函数的特点如下:
	- 如果实参是编译时期可确定的,此时`constexpr`的结果就是编译时期计算的
	- 当一个`constexpr`被一个或者多个编译时期不可知的值调用的时候,它就像普通函数一样,运行时计算结果
- `C++11`中利用`constexpr`修饰的函数之可以有不超过一行语句,但是在`C++14`中放开了标准
- 所以根据这一个特性,`constexpr`修饰的函数可以作为编译时期可知道的量处理
- 总结:
	- `constexpr`对象是`const`,被编译时期可知的值初始化
	- 传递编译时期可知的值的时候,`const expr`可以产出编译时期可知的结果
	- `constexpr`对象和函数的使用范围比较广阔
	- `constexpr`是对象和函数接口的一部分
# 10. 让const成员函数线程安全
- `const`成员函数也就只有常对象才可以调用并且可以修改