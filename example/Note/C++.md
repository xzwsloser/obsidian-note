> 记录在 `C++` 使用过程中需要注意的点
# 1. C++ 中时间对象和日期对象的转换
利用 `std::chrono::system_clock::now()` 获取到现在的时间戳,利用 `std::chrono::system_clock::to_time_t()` 转换为 `time_t` 类型,利用 `std::localtime`转换为`std::tm` 类型,最后利用 `put_time` 转换为字符串,或者利用 `get_time`解析:
```c++
// C++ 中时间对象和日期字符串之间的相互转换方式
#include <chrono>
#include<iostream>
#include<ctime>
#include <sstream>
#include<iomanip>
using namespace std;
int main() {
    // 1. 时间对象转换为日期字符串
    tm time{}; 
    auto now = chrono::system_clock::now();
    time_t tim = chrono::system_clock::to_time_t(now);
    time = *localtime(&tim);
    ostringstream oss;
    oss << put_time(&time , "%Y-%m-%d %H:%M:%S"); 
    std::string time_str = oss.str();
    cout << time_str << endl;

    // 2. 时间字符串转换为时间对象
    istringstream is(time_str);
    tm time1{};
    is >> get_time(&time1 , "%Y-%m-%d %H:%M:%S");
    cout << time1.tm_year << endl;
}
```
其中`ostringstream` 用于存储输出的字符串 , 其中 `istringstream` 用于存储输入的字符串并且输出到输出流中

# 2. 实现 C++20 新特性 std::latch
可以利用条件变量和互斥锁来实现 `std::latch` , 实现方法如下:
```c++
// @Author: loser
#include "CountDownLatch.h"
#include <mutex>

CountDownLatch::CountDownLatch(int count): 
    count_(count) {}
   
void CountDownLatch::wait()
{
    std::unique_lock<std::mutex> lock { mutex_ };
    // condition_variable wait the condition true
    // so this -> count_ <= 0 is OK
    condition_.wait(lock , [this]() -> bool { return this -> count_ <= 0; });
}

void CountDownLatch::countDown()
{
    std::lock_guard<std::mutex> lock { mutex_ };
    count_--;
    if(count_ == 0) condition_.notify_all();
}
```

# 3. 定位new(placement new) 和 完美转发
`placement new` 的语法结构如下:
```c++
new(p) T(...)
```
含义就是一个已经分配的地址的指针`p` , 并且在这一个空间的位置构造一个对象 `T`,同时也可以和完美转发结合,例子如下:
```c++
tempate<typename T,typename... Args>
T* newElement(Args&&... args) {
	T* p = static_cast<T*>(::operator new(sizeof(T)));
	new(p) T(std::forward<Args>(args)...));
	return p;
}
```

# 4. 可变模板参数: typename... Args
`C++11` 新特性,也就是模板函数中的可变参数,举例如下:
```c++
#include<iostream>
#include<memory>
#include<utility>
using namespace std;

class Person {
public:
    int age_;
    string name_;
    Person(int age , string name): age_(age),name_(name) {}
};

template<typename T, typename... Args>
T* newElement(Args&&... args)
{
    void* p = ::operator new(sizeof(T));
    new(p) T(std::forward<Args>(args)...);
    return static_cast<T*>(p);
}


int main() {
    Person* p = newElement<Person>(10,"zhangsan");
    cout << p -> age_ << " " << p -> name_ << endl;
    return 0;
}
```

# 5. 可以接受任意函数作为参数并且返回 std::future 的函数模板写法

一定需要注意,模板函数的实现需要写在头文件中,编译时期就需要确定了,写法如下:
```c++
template<typename F,typename... Args>
auto AddTask(F&& f , Args&&... args) 
-> std::future<typename std::result_of<F(Args...)>::type>
```




















