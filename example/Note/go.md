# 1. go 中的 io 库
`go` 中的 `io` 库分为: `io` , `os` , `ioutil` , `bufio`, `bytes` 和 `strings` 库等,他们分别的作用是:
- `io`: 提供基础的 `io.Reader` 和 `io.Writer` , 也就是最基础的读源和写源,提供相应的 `Read/Write` 方法
- `os`: 与操作系统相关,可以执行各种命令,比如判断文件是否存在,打开文件等
- `bufio`：带有缓冲的 `reader / writer` 
- `bytes`: 提供从 `[]byte` 中读取数据的方法
- `strings`: 提供从 `string` 中读取数据的方法,同时也提供各种 `string` 的操作函数
参考: https://zhuanlan.zhihu.com/p/383198737
同时 `strings` 包的使用可以参考: https://juejin.cn/post/7309761475526557730
# 2. go  reflect 中的 Elem 方法的作用
`reflect.Type.Elem` 方法的作用是获取到底层元素的类型,比如对于指针类型,返回指针指向的类型,对于切片类型返回切片元素的类型,对于映射类型,返回映射值的类型
# 3. goland快捷键
1. 搜索符号: 万能搜索键 `Shift + Shift`
2. 显示所有函数: `ctrl + F12`
