> 移动语义:  **移动语义**使编译器有可能用廉价的移动操作来代替昂贵的拷贝操作。正如拷贝构造函数和拷贝赋值操作符给了你控制拷贝语义的权力，移动构造函数和移动赋值操作符也给了你控制移动语义的权力。移动语义也允许创建只可移动（_move-only_）的类型，例如`std::unique_ptr`，`std::future`和`std::thread`。

> 完美转发:  **完美转发**使接收任意数量实参的函数模板成为可能，它可以将实参转发到其他的函数，使目标函数接收到的实参与被传递给转发函数的实参保持一致。

> 右值引用就是这两个概念之间的联合剂,注意在如下的讨论中,函数的形式参数永远都是左值,即使类型是一个右值引用,比如:
```c++
void f(Widget&& w);
```
其中,`w`的类型虽然是一个右值引用,但是本身是一个左值
# 1. 理解 std::move 和 std::forward
- 首先一定需要明确`std::move`和`std::forward`的作用,两者的作用如下:
	- `std::move`执行到右值的无条件的转换，但就自身而言，它不移动任何东西。
	- `std::forward`只有当它的参数被绑定到一个右值时，才将参数转换为右值。
	- `std::move`和`std::forward`在运行期什么也不做。
- `std::move`的一种简单的实现方式如下:
```c++
template<typename T>                            //在std命名空间
typename remove_reference<T>::type&&
move(T&& param)
{
    using ReturnType =                          //别名声明，见条款9
        typename remove_reference<T>::type&&;

    return static_cast<ReturnType>(param);
}
```
- 使用的注意事项:
	- 不要再希望能移动对象的时候声明他们为`const`,否则对于`const` 对象的移动请求可能会转换为拷贝操作
	- `std::move`不仅可以移动任何东西,还可以保证执行转换的对象可以被移动

- `std::forward`的一种简单的实现方式如下:
```c++
template<typename T>
T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward call");
    return static_cast<T&&>(t);
}
```
从上面的实现可以简单,之后当传入的参数为右值引用类型的时候(依赖于模板参数`T`才会完成右值的转化,其中`std::is_lvalue_reference<T>`判断传入的模板参数是否是左值引用
- 比如一种`std::forward`的使用案例如下:
```c++
void process(const Widget& lvalArg);        //处理左值
void process(Widget&& rvalArg);             //处理右值

template<typename T>                        //用以转发param到process的模板
void logAndProcess(T&& param)
{
    auto now =                              //获取现在时间
        std::chrono::system_clock::now();
    
    makeLogEntry("Calling 'process'", now);
    process(std::forward<T>(param));
}
```

# 2. 区分通用引用和右值引用
- 首先搞清楚通用引用和右值引用之间的关系:
	- 通用引用: 用于类型推导,如果类型为左值,那么就推导为左值引用,如果类型为右值,那么就是右值引用
	- 右值引用: 一种引用类型,标识数据为右值
- 总结:
	- 如果一个函数模板形参的类型为`T&&`，并且`T`需要被推导得知，或者如果一个对象被声明为`auto&&`，这个形参或者对象就是一个通用引用。
	- 如果类型声明的形式不是标准的`type&&`，或者如果类型推导没有发生，那么`type&&`代表一个右值引用。
	- 通用引用，如果它被右值初始化，就会对应地成为右值引用；如果它被左值初始化，就会成为左值引用。
# 3. 对于右值引用使用 std::move,通用引用使用 std::forward

- 最后一次使用的时候,如果是右值引用使用`std::move`,在通用引用上面使用`std::forward`,这是由于对于通用引用来说,可以根据传入的模板参数来确定返回的是一个左值引用还是一个右值引用,从而确定拷贝或者移动操作
- 对于按值返回的函数返回的右值引用和通用引用,执行相同的的操作
- 如果局部对象可以被返回值优化消除(`RVO`),不要使用`std::move`或者`std::forward`,另外不要返回局部对象的引用(利用`std::move`也是一样的)
# 4. 避免在通用引用上重载
- 比较少使用,总结如下:
	- 对通用引用形参的函数进行重载，通用引用函数的调用机会几乎总会比你期望的多得多。
	- 完美转发构造函数是糟糕的实现，因为对于non-`const`左值，它们比拷贝构造函数而更匹配，而且会劫持派生类对于基类的拷贝和移动构造函数的调用。
# 5. 熟悉通用引用重载的替代方法
- 使用情况比较少,可以使用传递值或者使用`tag dispatch`的方法,也就是根据类型进行操作的分发(这里可以使用`std::enable_if`模板进行定义),总结如下:
	- 通用引用和重载的组合替代方案包括使用不同的函数名，通过lvalue-reference-to-`const`传递形参，按值传递形参，使用_tag dispatch_。
	- 通过`std::enable_if`约束模板，允许组合通用引用和重载使用，但它也控制了编译器在哪种条件下才使用通用引用重载。
	- 通用引用参数通常具有高效率的优势，但是可用性就值得斟酌。
# 6. 理解引用折叠
