## rpc 基本介绍
`rpc` 也就是 `remote process call` 也就是远程服务调用,可以让一台机器调用另外一台机器上运行的程序,通信的双方需要规定通信数据的格式,网络协议等,具体的 `RPC`通信过程示意图如下:
![[Pasted image 20250305171745.png]]

示意图中的调度过程如下:

1. 客户端与服务端之间会先约定统一的编码/数据格式，一般都是以服务端定义为主。
2. 客户端在本地代码中发起调度
3. client stub(客户端存根)：实际就是对rpc请求的封装包代码，主要事情是将接收到的调度请求，进行组装为对应的数据结构/编码/并将消息通过网络发送给目标服务器
4. server stub(服务端存根)：实际就是对rpc请求的封装包代码,主要是将接收到的消息按照定义好的编码拆包，获取请求方法与参数，并根据方法名和参数进行本地调用。
5. 服务端处理完请求，将结果通过server stub处理返回给调用的客户端。
6. 调用的客户端中基于client stub获取到请求后解析，最终得到本次rpc调用的结果

通信协议的选择: 一般采用 `TCP` 为主,而不是采用 `http`:
- 效率: `TCP` 面向连接,相对于 `HTTP` ，通信效率高,采用流式传输,保证了数据的完整性和可靠性
- 传输量: `RPC` 用于传递大量数据,`HTTP` 传递大量数据的时候采用了分块存储
- 灵活性: 可以支持各种通信协议,比如 `TCP/UDP/WebSocket`等
- 安全性: `TCP` 不用多少了吧,但是其实 `HTTPS`安全性也可以的

### 为什么使用 rpc 而不是使用 restful
`rpc` 和 `restful` 的区别如下:
- 定义区别：RPC是一种思想是对微服务之间的调度过程的定义，restful是一种http请求协议的标准规范
- 目标不同：RPC主要的调度对象本质对象是service；restful是基于http请求方法，调度的本质对象是controller
- 通信协议：rpc可以自定义协议，而restful是统一的http协议
- 传输协议：在rpc中传输的协议可以用二进制性能消耗低，而restful是json字符串
## net/rpc 实践
这里考虑利用 `net/rpc` 实现 `rpc` 通信,另外注意到 `go mod` 的作用就是依赖管理,并且 `package` 后面的名称不一定就是包名,需要加上路径
- `server`:
```go
package main

import (
	"errors"
	"log"
	"net"
	"net/rpc"
)

type (
	GetUserReq struct {
		Id int `json:"id"`
	}

	GetUserResp struct {
		Id    int    `json:"id"`
		Name  string `json:"name"`
		Phone string `json:"phone"`
		Age   int    `json:"age"`
	}
)

var userMap map[int]*User = map[int]*User{
	1: &User{
		Id:    1,
		Name:  "张三",
		Phone: "110",
		Age:   20,
	},
}

// 定义服务
type UserServer struct {
}

func (*UserServer) GetUserById(req GetUserReq, resp *GetUserResp) error {
	if u, ok := userMap[req.Id]; ok {
		*resp = GetUserResp{
			Id:    u.Id,
			Name:  u.Name,
			Phone: u.Phone,
			Age:   u.Age,
		}
		return nil
	}
	return errors.New("没有找到用户名...")
}

func main() {
	// 创建 rpc 服务
	userServer := new(UserServer)
	// 注册服务到 rpc 中
	rpc.Register(userServer)
	// 监听对应的端口
	listener, err := net.Listen("tcp", ":9999")

	if err != nil {
		log.Fatal("开启 rpc 失败...")
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println("监听失败...")
			continue
		}

		rpc.ServeConn(conn)
	}

}
```

- `client`:
```go
package main

import (
	"log"
	"net/rpc"
)

type (
	GetUserReq struct {
		Id int `json:"id"`
	}

	GetUserResp struct {
		Id    int    `json:"id"`
		Name  string `json:"name"`
		Phone string `json:"phone"`
		Age   int    `json:"age"`
	}
)

func main() {
	// 1. 连接到服务器端
	client, err := rpc.Dial("tcp", "localhost:9999")
	if err != nil {
		log.Fatal("连接服务器端失败...")
	}
	defer client.Close()
	// 2. 调用服务
	req := GetUserReq{
		Id: 2,
	}

	var resp GetUserResp

	err = client.Call("UserServer.GetUserById", req, &resp)
	if err != nil {
		log.Fatal(err.Error())
	}

	log.Println(resp)
}
```
## net/rpc 的底层原理
源代码阅读方法:
- 确定目标(`STL`底层的容器实现等)
- 构思实现
- 源代码分析
![[Pasted image 20250305200205.png]]
感觉注册过程有一点类似于 `gin` 框架中路由注册的过程
## grpc 的介绍
`rpc`通讯的机制下存在的问题:
- 缺乏跨语言支持
- 缺乏错误处理机制
- 缺乏服务发现机制
- 没有清晰的接口定义等 ......

`Grpc`是一种`rpc`框架,

`Grpc`优点:
- 基于 `HTTP2` 的协议传输
- 自动化的服务发现以及负载均衡
- 内置中间件机制

### grpc 下载

不知道这一个课讲的什么鬼东西,安装这么多东西,直接参考官方文档安装 `protoc`(之前安装 `anaconda`的时候居然安装了) 和 `proto-gen` 即可: https://grpc.io/docs/languages/go/quickstart/ 
注意配环境变量
## grpc 的使用
`grpc` 是的使用步骤如下:
1. 编写 `.protoc`描述文件
2. 编译生成 `.pb.go` 文件,这一个过程中需要使用到 `.pb.go` 文件
3. 服务器端实现约定的接口并且提供服务
4. 客户端根据约定的方法请求服务器端
