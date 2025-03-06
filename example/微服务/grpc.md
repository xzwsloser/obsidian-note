
# rpc 基本介绍
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

- 首先需要按照需求自定义 `.proto` 文件,注意到 `proto` 文件相当于一个接口文档,在服务器端需要自定义服务并且这一个接口文档中的方法,客户端中可以按照这一个接口文档中的方法来调用服务,一个简单的 `proto` 文件如下:
```go
// 指定 proto 版本
syntax = "proto3";

// 对应的编译指令为:
// 指定生成的 grpc 代码和 protobuf 代码(转换为 golang)的位置
// protoc --go-grpc_out=require_unimplemented_servers=false:. --go_out=. ./user.proto

// 指定生成文件所在的包名
// 指定包名
package user;

// 包名
// 指定包的导入路径
option go_package = "./user";

// 定义服务名称
service User {
  rpc GetUser(GetUserReq) returns (GetUserResp);
}

// 定义消息
message GetUserReq {
  // 属性类型 属性名称 = 标识符
  string id = 1;
}

message GetUserResp {
  string id = 1;
  string name = 2;
  string phone = 3;
}
```
需要注意自定义 `proto` 的方式以及服务定义的方式和消息定义的方式等等
- 之后需要使用到 `protoc` 工具来生成对应的 `grpc` 和 `protobuf` 代码,命令如下:
```shell
protoc --go-grpc_out=require_unimplemented_servers=false:. --go_out=. ./user.proto
```
其中 `--go-grpc_out` 表示指定的 `grpc` 代码的生成位置,`--go_out` 表示指定的 `protobuf` 对应代码生成的位置,最终会生成两个文件: `xxx.pb.go` 和 `XXX_grpc.pb.go` 前面的 `XXX` 也就是你指定的包名 **生成的 xxx.pb.go 文件中定义类proto文件中定义的消息类型,并且为消息类型添加了各种默认方法,同时 xxx_grpc.pb.go中定义了两个接口,第一个是 xxxClient 作用于客户端,客户端可以创建这一个接口的对象并且调用远程的方法,同时定义了xxxServer接口,服务器端需要实现其中的方法,同时还定义了注册服务的方法**

- 之后可以编写服务器端代码,服务器端代码如下:
```go
package main

import (
	"context"
	"errors"
	"google.golang.org/grpc"
	"grpc_test/proto/user"
	"log"
	"net"
)

// 需要实现的服务器端接口,在 user_grpc.pb.go 下
/*
	type UserServer interface {
		GetUser(context.Context, *GetUserReq) (*GetUserResp, error)
	}
*/

type UserServer struct {
}

func (*UserServer) GetUser(ctx context.Context, req *user.GetUserReq) (*user.GetUserResp, error) {
	if u, ok := users[req.Id]; ok {
		return &user.GetUserResp{
			Id:    u.Id,
			Name:  u.Name,
			Phone: u.Phone,
		}, nil
	}
	return nil, errors.New("没有找到用户信息...")
}

func main() {
	listen, err := net.Listen("tcp", ":9999")
	if err != nil {
		log.Fatal("监听失败...", err.Error())
	}

	s := grpc.NewServer()

	user.RegisterUserServer(s, new(UserServer))
	log.Println("服务已经启动 ...")

	s.Serve(listen)
}
```
服务器端需要实现`xxx_grpc.pb.go` 中定义的接口中的所有方法并且并且调用服务区中的 `RegisterUserServer` 方法,同时启动服务器,这里利用 `Goland`写代码的好处就是可以看到自己是否真的实现了这一个接口
- 最后编写客户端:
```go
package main

import (
	"context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"grpc_test/proto/user"
	"log"
)

func main() {
	// 连接 grpc 服务器
	client, err := grpc.Dial("localhost:9999",
		grpc.WithTransportCredentials(insecure.NewCredentials()))

	if err != nil {
		log.Fatal("连接 grpc 服务器失败...")
	}

	defer client.Close()
	// 创建一个新的客户端
	c := user.NewUserClient(client)

	r, err := c.GetUser(context.Background(), &user.GetUserReq{Id: "1"})
	if err != nil {
		log.Fatal("请求失败 ", err.Error())
	}
	log.Println(r)
}
```
客户端需要首先连接到服务器端,并且创建一个新的客户端连接,之后调用前面的 `xxx_grpc.pb.go` 中生成的 `NewxxxClient` 方法生成 `xxxClient` 对象之后就可以调用这一个对象中的其他方法了,以上就是编写一个简单的 `grpc` 服务的全部过程

## protobuf的协议原理
注意到 `protobuf` 本来不是用于解决`rpc`通信的问题的,就比如 `GPU` 一开始也不是用来跑`AI`的,主要解决引入新的字段以及使得接口更具有自我描述性的问题

### protobuf 语句
- 首先需要使用 `synatx` 来指定使用的版本,类似于 `CMAKE`
- 之后需要定义`serivce`也就是服务,和`message`也就是消息语法,`service`定义方式如下:
```protobuf
service XXXServer {
	rpc MethodName(参数) returns (返回值)
}
```
- `message` 的数据格式如下:
```protobuf
message 消息名称 {
	限定修饰符 数据类型 字段名称 = 字段表示符号 [字段默认值]
}
```
其中限定修饰符号的种类如下,不是必须的:
- required：该规则规定，消息体中该字段的值是必须要设置的
- optional：消息体中该规则的字段的值可以存在，也可以为空，optional的字 段可以根据defalut设置默认值。
- repeated：消息体中该规则字段可以存在多个（包括0个），该规则对应java 的数组或者go语言的slice。  

注意到类型转换关系如下:
![[Pasted image 20250306174449.png]]

### protobuf序列化

`protobuf`做的第一个优化就是使用表示符代替了`Json`中的`key`
#### varInt 和 TLV 的存储格式
- `varInt`: 对于整数的存储使用了`varInt`进行优化,比如 `2` 的存储可以存储为:
```text
1 0 1 0 0 0 0 0
```
也就是四个一组,最前面的一个 `1` 表示后面依然由数据,这样本来需要使用`4`个字节,现在只需要两个字节了
- `TLV`格式: `Key + Value + Len` 的方式,并且整形数据不需要 `Len`,参考前面的`varInt`理解原理即可,只需要找到最后一个 `1` 即可
## grpc请求协议http2
### http1 的缺点
- 低效的`TCP`利用: 短连接
- 臃肿的消息首部
- 明文传输(当然可以使用 `SSL` 连接)
- 传输效率低下
- 不支持服务器端推送
### http2中的优化
- 数据分帧,根据数据包的类型进行分帧,注意是对于一个数据的拆分,优化了输出的传输方式
- 对于请求头的优化: 有状态的,客户端记录已经存在的信息,每一次只需要发送不同的请求路径即可
- 多路复用: 请求的过程中建立一次连接,并且在这一个连接中基于流或者帧进行连接
- 服务端可以推送到客户端: 类似于`WebSocket` , 主要是使用长连接,同时注意到 `Http1.1` 中使用了`Connection: keep alive` 字段来保持长连接
## grpc的服务端连接调度实现分析
### grpc上层服务的注册和加载

建议自己打断点跟一下,这一个流程很简单,首先调用了 `xxx_grpc.pb.go`中的 `RegisterXxxServer`方法,在这一个方法中调用了`grpc.ServiceRegister`对象的`RegisterService`方法,入参就是 对于服务的描述以及具体的服务对象,该方法的实现如下:
```go
func (s *Server) RegisterService(sd *ServiceDesc, ss any) {  
    if ss != nil {  
       ht := reflect.TypeOf(sd.HandlerType).Elem()  
       st := reflect.TypeOf(ss)  
       if !st.Implements(ht) {  
          logger.Fatalf("grpc: Server.RegisterService found the handler of type %v that does not satisfy %v", st, ht)  
       }  
    }  
    s.register(sd, ss)  
}
```
也就是获取到服务信息中实现的接口对象,判断实现关系,并且继续调用`register`方法,注意到`ServiceRegister`应该是一个接口,`Server`实现了这一个接口(`GoLand`中使用`ctrl + F12`可以显示所有接口和方法),最后调用`register`方法,该方法的内部实现如下:
```go
func (s *Server) register(sd *ServiceDesc, ss any) {  
    s.mu.Lock()  
    defer s.mu.Unlock()  
    s.printf("RegisterService(%q)", sd.ServiceName)  
    if s.serve {  
       logger.Fatalf("grpc: Server.RegisterService after Server.Serve for %q", sd.ServiceName)  
    }  
    if _, ok := s.services[sd.ServiceName]; ok {  
       logger.Fatalf("grpc: Server.RegisterService found duplicate service registration for %q", sd.ServiceName)  
    }  
    info := &serviceInfo{  
       serviceImpl: ss,  
       methods:     make(map[string]*MethodDesc),  
       streams:     make(map[string]*StreamDesc),  
       mdata:       sd.Metadata,  
    }  
    for i := range sd.Methods {  
       d := &sd.Methods[i]  
       info.methods[d.MethodName] = d  
    }  
    for i := range sd.Streams {  
       d := &sd.Streams[i]  
       info.streams[d.StreamName] = d  
    }  
    s.services[sd.ServiceName] = info  
}
```
这里的实现比较简单,其中的`services`也就是一个`map`记录着服务名称到服务信息的映射关系,其实底层调用的方法如下:
```go
func _User_GetUser_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetUserReq)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(UserServer).GetUser(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: User_GetUser_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(UserServer).GetUser(ctx, req.(*GetUserReq))
	}
	return interceptor(ctx, in, info, handler)
}
```
可以看到底层其实存在一个拦截器,会首先调用拦截之后才会调用封装的`handler`

