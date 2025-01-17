# 1. 优先考虑 auto而不是非显示类型声明
> 使用 `auto` 的优点有如下几点
## 1. 防止没有初始化的变量
- `auto`声明的变量必须要初始化,否则就会报错,避免了不明确行为:
```c++
int x1;                         //潜在的未初始化的变量
    
auto x2;                        //错误！必须要初始化

auto x3 = 0;                    //没问题，x已经定义了
```
## 2. 替代复杂类型名称
- 比如对于闭包类型的书写,如果没有 `auto` 就会十分复杂:
```c++
// 没有 auto 
std::function<bool(const std::unique_ptr<Widget> &,
                   const std::unique_ptr<Widget> &)>
derefUPLess = [](const std::unique_ptr<Widget> &p1,
                 const std::unique_ptr<Widget> &p2)
                { return *p1 < *p2; };

// C++ 11 中使用 auto 
auto derefUPLess = [](const std::unique_ptr<Widget> &p1,
                 const std::unique_ptr<Widget> &p2)
                { return *p1 < *p2; };

// C++ 14 中使用 auto
auto derefLess =                                //C++14版本
    [](const auto& p1,                          //被任何像指针一样的东西
       const auto& p2)                          //指向的值的比较函数
    { return *p1 < *p2; };
```
## 3. 不确定的类型可以使用 auto 推导
- 比如各种容器的迭代器或者函数的返回值可以使用 `auto` 推导,例子如下:
```c++
std::unordered_map<std::string, int> m;
…
// X 错误, 元素类型为 std::pair<const std::string , int>
for(const std::pair<std::string, int>& p : m)
{
    …                                   //用p做一些事
}

// 使用 auto 
for(const auto& p : m)
{
    …                                   //如之前一样
}
```
# 2. auto推导若非己愿,使用显式类型初始化惯用方法
> 主要是两种情况: 不要使用`auto`推导代理类的类型,显式链类型推导强制使用`auto` 推导出想要的结果
## 1. 不要使用auto推导代理类型
- 考虑如下代码:
```c++
// 不使用 auto 
Widget w;
…
bool highPriority = features(w)[5];     //w高优先级吗？
…
processWidget(w, highPriority);         //根据它的优先级处理w


// 使用 auto 
Widget w;
…
auto highPriority = features(w)[5];     //w高优先级吗？
…
processWidget(w, highPriority);         //根据它的优先级处理w
```
- 实际上对于`vector<bool>`类型,`operator[]`并不会返回一个`T&`类型,而是返回一个内部类的类型 `std::vector<bool>reference` , 这一个对象中包含指向`word`的指针,但是在临时对象被销毁的时候空间会被释放,造成为定义行为,所以不可以使用 `auto`
## 2. 使用显式类型转换和auto来推导类型
- 利用显式类型转换和 `auto` 可以清晰表现自己想要什么,如下:
```c++
auto ep = static_cast<float>(calEpsilon());
```
