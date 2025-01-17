# 1. 对于独占资源所使用std::unique_ptr
- 使用智能指针,如果是独占资源首选`std::unique_ptr` ,优点如下:
	- 可以自定义删除器
	- 可以很容易转换为 `shared_ptr` 
	- 存在两种形式: `std::unique_ptr<T>`和`std::unique_ptr<T[]>` 
- 补充一个小知识点: 子类需要初始化父类,也就是必须要调用父类的构造函数
# 2. 对于共享资源使用std::shared_ptr
