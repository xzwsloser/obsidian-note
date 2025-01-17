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

