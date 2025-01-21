> **闭包**（_enclosure_）是_lambda_创建的运行时对象。依赖捕获模式，闭包持有被捕获数据的副本或者引用。在上面的`std::find_if`调用中，闭包是作为第三个实参在运行时传递给`std::find_if`的对象。
> **闭包类**（_closure class_）是从中实例化闭包的类。每个_lambda_都会使编译器生成唯一的闭包类。_lambda_中的语句成为其闭包类的成员函数中的可执行指令。
- `lambda`表达式的语法形式如下:
```c++
[capture](params) opt -> ret {body;};
```
- 其中:
	- `capture` 表示捕获列表
	- `params` 表示参数列表
	- `opt` 表示函数选项(比如`mutable`表示可以修改按值传递进来的拷贝,`exception`指定函数抛出的异常,可以使用 `throw`)
	- `ret`: 返回值类型
	- `body`: 函数体
## 捕获列表
- 捕获列表使用方法如下:
	- [] - 不捕捉任何变量
	- [`&`]  捕获外部作用域中所有变量, 并作为引用在函数体内使用 (按引用捕获)
	- [`=`] 捕获外部作用域中所有变量, 并作为副本在函数体内使用 (按值捕获)
	- 拷贝的副本在匿名函数体内部是只读的
	- [=, &foo] - 按值捕获外部作用域中所有变量, 并按照引用捕获外部变量 foo
	- [bar] - 按值捕获 bar 变量, 同时不捕获其他变量
	- [&bar] - 按引用捕获 bar 变量, 同时不捕获其他变量
	- [this] - 捕获当前类中的this指针
让lambda表达式拥有和当前类成员函数同样的访问权限
如果已经使用了 & 或者 =, 默认添加此选项

- 其实`lambda`表达时本质上就是一个包含`operator()`方法的类,是一个仿函数

# 1. 避免使用默认捕获模式
- 默认捕获模式表示按照值捕获或者按照引用捕获
- 如果按照引用捕获,比如对于局部变量按照引用捕获,脱离作用域之后就回到时局部变量的空间被释放了,那么此时可能导致悬空引用
- 默认的按照值捕获的对于悬空指针比较敏感(比如`this`指针),并且对于`static`变量可以引用但是无法捕获,会让人误导以为`lambda`是独立的想法
# 2. 使用初始化捕获来移动对象到闭包中
- 初始化捕获的是`C++14`特性,可以对于`lambda`作用域里面的变量进行操作并且移动到生成的闭包类中,但是可以使用`C++11`中的`std::bind`函数模拟初始化捕获
- `C++14`中的实现方式如下:
```c++
auto func = [pw = std::make_unique<Widget>()]   //同之前一样
            { return pw->isValidated()          //在闭包中创建pw
                     && pw->isArchived(); };
```
- `C++11`中利用`std::bind`的实现方式如下:
```c++
auto func = std::bind(
                [](const std::unique_ptr<Widget>& pw)
                { return pw->isValidated()
                         && pw->isArchived(); },
                std::make_unique<Widget>()
            );
```
# 3. 对 auto&& 形参使用 decltype以std::forward它们
- `C++14`新特性: 可以在`lambda`的形参中使用`auto`关键字,例子如下:
```c++
auto f = [](auto x){ return func(normalize(x)); };
```
- 对应的闭包类型如下:
```c++
class SomeCompilerGeneratedClassName {
public:
    template<typename T>                //auto返回类型见条款3
    auto operator()(T x) const
    { return func(normalize(x)); }
    …                                   //其他闭包类功能
};
```
- 从而可以使用 `auto&& + decltype` 来实现完美转发,方式如下:
```c++
auto f =
    [](auto&&... params)
    {
        return
            func(normalize(std::forward<decltype(params)>(params)...));
    };
```
# 4. 考虑lambda而非std::bind
- 利用`lambda`表达式实现一个功能比利用`std::bind`实现一个功能更加简便并且直观,比如同样实现两个数字的大小比较,两种方式的实现方法如下:
```c++
// std::bind 实现
auto betweenB =
    std::bind(std::logical_and<bool>(),         //C++11版本
              std::bind(std::less_equal<int>(), lowVal, _1),
              std::bind(std::less_equal<int>(), _1, highVal));

// lambda表达式实现
auto betweenL =                                 //C++11版本
    [lowVal, highVal]
    (int val)
    { return lowVal <= val && val <= highVal; };
```
- 总结如下:
	- 与使用`std::bind`相比，_lambda_更易读，更具表达力并且可能更高效。
	- 只有在C++11中，`std::bind`可能对实现移动捕获或绑定带有模板化函数调用运算符的对象时会很有用。

