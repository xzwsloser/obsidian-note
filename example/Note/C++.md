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








