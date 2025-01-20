# 1. 对于独占资源所使用std::unique_ptr
- 使用智能指针,如果是独占资源首选`std::unique_ptr` ,优点如下:
	- 可以自定义删除器
	- 可以很容易转换为 `shared_ptr` 
	- 存在两种形式: `std::unique_ptr<T>`和`std::unique_ptr<T[]>` 
- 补充一个小知识点: 子类需要初始化父类,也就是必须要调用父类的构造函数
# 2. 对于共享资源使用std::shared_ptr
- 首先对于`shared_ptr` 内存布局如下:
![[Pasted image 20250117145205.png]]
- 所以不要时用同一个原始对象创建 `shared_ptr` 会导致内存重复释放,最好使用拷贝构造,赋值运算等方式创建`shared_ptr`
- `reset`方法的作用:
	- 释放`shared_ptr`
	- 重新设置管理对象
- `make_shared`: 可以创建一个控制块,不用担心调用对象的时候存在其他控制块
- 如果想要在类中返回包装了`this`指针的`shared_ptr`,需要继承模板了`enable_shared_from_this`,调用其中的`shared_from_this`
```c++
class Person: public enable_shared_from_this<Person> {
public:
    int* age;
    Person(int age): age(new int(age)) {}
    Person() {}
    Person(const Person& p) {
        /*this -> age = p.age;*/
        this -> age = new int(*(p.age));
    } 
    ~Person() {
        cout << "person析构函数执行了" << endl;
        if(age != nullptr) {
            delete age;
            age = nullptr;
        }
    }

    shared_ptr<Person> get_this() {
        return shared_from_this();
    }
};
```
# 3. 当std::shared_ptr可能悬空的时候使用std::weak_ptr
- 这里介绍了`weak_ptr`的两个作用:
	- 管理`shared_ptr`,根据`shared_ptr`是否悬空创建对象(其中的`lock`方法是并发安全的)
	- 解决`shared_ptr`的循环引用问题
- 解决循环引用问题的方法如下:
![[Pasted image 20250117161020.png]]
指针使用`weak_ptr`即可
- 总结:
	- 用`std::weak_ptr`替代可能会悬空的`std::shared_ptr`。
	- `std::weak_ptr`的潜在使用场景包括：缓存、观察者列表、打破`std::shared_ptr`环状结构。

# 4. 优先考虑使用std::make_unique和std::make_shared,而非直接使用new
- `make_shared`是`C++11`的特性,`make_unique`是`C++14`的特性
- 实现方法都是利用完美转发把参数转发给构造函数使用,比如`make_unique`的一种实现方式如下:
```c++
template<typename T,typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params) 
{
	return unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
```
## 使用 make 函数减少重复代码片段
- 比如使用`make`和`new` 创建智能指针的代码片段如下:
```c++
auto upw1(std::make_unique<Widget>());      //使用make函数
std::unique_ptr<Widget> upw2(new Widget);   //不使用make函数
auto spw1(std::make_shared<Widget>());      //使用make函数
std::shared_ptr<Widget> spw2(new Widget);   //不使用make函数
```
减少了泛型的书写次数
## 保证了异常安全
- 对于如下代码:
```c++
processWidget(std::shared_ptr<Widget>(new Widget),  //潜在的资源泄漏！
              computePriority());
```
- 执行顺序如下:
	- 分配内存空间
	- 智能指针指向内存空间
	- 执行计算权重的函数
- 这三个步骤可能顺序不确定,所以可能造成内存泄漏
## 减少了内存分配次数
- 利用 `new`首先分配堆区内存,之后分配控制块内存
- 利用 `make` 控制块内存和堆区内存同时分配
## make的缺点
- 不可以自定义删除器
- 花括号无法使用完美转发
- 创建的对象比较大的时候,由于`weak_ptr`的存在,可能导致释放对象和释放控制块的事件出现延迟(但是利用`make`同时释放对象和控制块)

- 总结:
	- 和直接使用`new`相比，`make`函数消除了代码重复，提高了异常安全性。对于`std::make_shared`和`std::allocate_shared`，生成的代码更小更快。
	-  不适合使用`make`函数的情况包括需要指定自定义删除器和希望用花括号初始化。
	- 对于`std::shared_ptr`s，其他不建议使用`make`函数的情况包括(1)有自定义内存管理的类；(2)特别关注内存的系统，非常大的对象，以及`std::weak_ptr`s比对应的`std::shared_ptr`s活得更久。

# 5. 当使用 Pimpl惯用法,请实现文件中定义特殊成员函数
## Pimpl惯用法
- 为了降低源代码之间的依赖关系,可以使用`Pimpl`惯用法,这一种方法类似于接口,使用方法如下:
```c++
class Widget                        //仍然在“widget.h”中
{
public:
    Widget();
    ~Widget();                      //析构函数在后面会分析
    …

private:
    struct Impl;                    //声明一个 实现结构体
    Impl *pImpl;                    //以及指向它的指针
};


#include "widget.h"             //以下代码均在实现文件“widget.cpp”里
#include "gadget.h"
#include <string>
#include <vector>

struct Widget::Impl {           //含有之前在Widget中的数据成员的
    std::string name;           //Widget::Impl类型的定义
    std::vector<double> data;
    Gadget g1,g2,g3;
};

Widget::Widget()                //为此Widget对象分配数据成员
: pImpl(new Impl)
{}

Widget::~Widget()               //销毁数据成员
{ delete pImpl; }

```
但是在使用的时候一定需要注意，如果使用`unique_ptr` 来管理对象的时候一定需要定义类中的各种特殊成员函数,否则就会导致不完成的数据类型(声明但是没有定义)
- 总结:
	- Pimpl惯用法通过减少在类实现和类使用者之间的编译依赖来减少编译时间。
	- 对于`std::unique_ptr`类型的`pImpl`指针，需要在头文件的类里声明特殊的成员函数，但是在实现文件里面来实现他们。即使是编译器自动生成的代码可以工作，也要这么做。
	- 以上的建议只适用于`std::unique_ptr`，不适用于`std::shared_ptr`

