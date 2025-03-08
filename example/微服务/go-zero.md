> `go-zero`是一款微服务框架
## 微服务框架和Web框架的区别
微服务架构下的问题:
- 服务`rpc`通信
- 服务发现
- 负载均衡
- 链路跟踪
- 熔断降级
微服务框架就是把这一些问题封装好了一套解决方案

`grpc`主要解决`rpc`通信中的问题,其中没有集成链路跟踪,数据读写等功能,所以无法直接基于`grpc` 来开发微服务

微服务框架与`Web`框架的区别:
- 框架功能: 目前的微服务框架基本包含web框架的功能，因此我们也可以通过微服务框架实现web应用开发，而微服务框架在web框架的基础上还有如：服务注册发现、rpcServer与rpcClient、链路跟踪等功能。
- 目的和用途: web框架主要用于构建web应用，它提供处理http请求、模板引擎等功能，是可以让开发人员快速搭建和管理web的项目。而微服务框架更加关注在分布式系统和服务化构建，使每个服务都可以独立开发、部署和扩展，从而提供整个系统的灵活性和可伸缩性。
- 架构模式: Web框架通常基于传统的客户端-服务器架构，其中客户端发出HTTP请求，服务器接收请求并返回相应的HTML、JSON等数据。而微服务框架则是基于微服务架构，它将应用程序划分为一组独立的服务，每个服务都有自己的数据库、业务逻辑和API接口，它们通过网络进行通信，并可以独立部署和扩展。
## go-zero基本使用
`go`中的各种微服务框架: `go-micro` , `tars-go` , `dubbo-go` , `go-kit` , `go-kratos` 和 `go-zero`等

参考官方文档,注意到 `go-zero` 依赖 `grpc , redis , etcd`等,分别对应`rpc`通信,缓存以及服务发现等功能

注意到 `go-zero` 项目中分为 `api` 和 `rpc` 两个部分,可以直接通过 `goctl` 生成 `api/rpc` 项目结构代码,命令如下:
```shell
goctl api new demo  # 生成 api 服务
goctl rpc new demo  # 生成 rpc 服务
```

### go-zero服务搭建
#### 搭建rpc服务
但是一般的开发流程需要自己写好 `xxx.proto` 文件,之后在 `xxx.proto` 命令中执行命令如下:
```shell
goctl rpc protoc user.proto --go_out=. --go-grpc_out=. -zrpc_out=.
```
其中`zrpc_out` 表示生成 `rpc` 服务的位置,最终生成的项目结构如下:
```text
.
├── etc
│   └── user.yaml
├── internal
│   ├── config
│   │   └── config.go
│   ├── logic
│   │   └── getuserlogic.go
│   ├── server
│   │   └── userserver.go
│   └── svc
│       └── servicecontext.go
├── user
│   ├── user_grpc.pb.go
│   └── user.pb.go
├── userclient
│   └── user.go
├── user.go
└── user.proto
```
说明一下目录结果,其中 `user.yaml` 表示配置文件,其中可以配置监听端口信息等,`config` 包下为配置文件,注意到其中的 `Config` 结构体中的成员必须和配置文件中的成员名称一样,类型为 `XxxxConfig`, `logic` 为逻辑层代码,这也是我们唯一一个需要修改的位置,在这一个位置,我们需要实现接口规定的方法的主要业务逻辑, `server`包也就是 `server` 层,其中记录这用户服务信息,调用了 `logic` 层中的方法处理业务, 最后的 `svc` 可以理解为 `context` 包,使用 `context.Context`记录服务信息用于传递各种参数,类似于 `gin.Context`,最后`user.go` 作为入口文件用于启动整个服务

#### 搭建 Api 服务

感觉 `go-zero` 的开箱即用程度甚至高于 `SpringBoot`, 首先编写 `user.api` 文件来规定接口以及传输数据(如果接口过多是否会产生响应的未见过多),注意`api` 文件的语法,一个例子如下:
```go
// 指定语法版本
syntax = "v1"

// 服务接口描述
info (
	title:   "用户api接口"
	desc:    "集成用户服务业务"
	author:  "loser"
	version: "v1"
)

// 请求参数结构
type (
	UserReq {
		Id string `json:"id"`
	}
	UserResp {
		Id    string `json:"id"`
		Name  string `json:"name"`
		Phone string `json:"phone"`
	}
)

// 定义 http 服务
service User {
	// 定义 http.Handler
	@handler user
	get /user (UserReq) returns (UserResp)
}
```
其中需要定义使用的`api` 语法版本,服务接口描述以及请求参数接口和`http` 服务接口,感觉不太方便

之后就可以使用 `goctl` 生成对应的工程文件了,生成命令如下:
```shell
$ goctl api go -api user.api -dir . -style gozero
```

最终生成的工程目录结构如下:
```text
.
├── etc
│   └── user.yaml
├── internal
│   ├── config
│   │   └── config.go
│   ├── handler
│   │   ├── routes.go
│   │   └── userhandler.go
│   ├── logic
│   │   └── userlogic.go
│   ├── svc
│   │   └── servicecontext.go
│   └── types
│       └── types.go
├── user.api
└── user.go
```
其中 `etc` 表示配置文件, `config` 表示配置文件同上,`handler` 定义了接口文件,相当于`controller`层,其中定义了各种接口以及控制层处理逻辑,`logic` 也是一样的,核心逻辑需要放在这里面,`svc`: 同 `rpc` 项目, `types`: 记录各种需要使用到的数据结构

### go-zero中间件与数据库读写
#### go-zero中的数据库配置

首先需要创建一个 `sql` 文件,之后需要利用到 `goctl` 脚手架工具来生成 `mysql` 代码,生成命令如下:
```shell
$ goctl model mysql ddl -src="./*.sql" -dir="." -c
```
最后的 `-c` 选项表示是否使用缓存,最终生成的目录结构如下:
```text
.
├── usermodel_gen.go
├── usermodel.go
├── user.sql
└── vars.go
```
其中 `usermodel`中定义了创建 `UserModel` 对象的方法,也就是用于操作数据库对象的方法,其中包含各种 `CRUD` 的方法,`usermodel`方法中定义了`CRUD` 的接口,这一个接口由`UserModel`实现,实现了 `FindOne , Insert` 等方法

之后如果需要使用到 `Mysql` 和 `Redis` 还是三步走:  编辑配置文件 --> 修改 `Config` 文件 --> 修改 `srv` 文件(也就是在上下文对象中添加需要使用到的对象,比如 `Model`对象,注意到配置文件读取的规则,一般都是时用一个同名的结构体来收集信息) --> 最终使用即可

配置文件的格式如下:
```yaml
Name: user.rpc
ListenOn: 0.0.0.0:8080
Etcd:
  Hosts:
  - 127.0.0.1:2379
  Key: user.rpc

# 配置 Mysql 连接信息
Mysql:
  DataSource: root:123456@tcp(127.0.0.1:3306)/user?charset=utf8mb4


# 配置 Redis 连接信息
Cache:
  - Host: 127.0.0.1:6379
    Type: node
    Pass: "123456"
```

最终就可以在项目中使用了,使用方式如下:
```go
func (l *CreateUserLogic) CreateUser(in *user.UserInfo) (*user.Resp, error) {
	// todo: add your logic here and delete this line
	_, err := l.svcCtx.UserModel.Insert(l.ctx, &model.User{
		Id:       in.Id,
		Name:     sql.NullString{String: in.Name},
		Password: in.PassWord,
	})

	if err != nil {
		return &user.Resp{}, err
	}
	return &user.Resp{}, nil
}
```

#### go-zero中的中间件配置
首先需要在 `service` 中使用 `@server` 指定使用到的中间件信息,语法如下:
```go
// 指定语法版本
syntax = "v1"

// 服务接口描述
info (
	title:   "用户api接口"
	desc:    "集成用户服务业务"
	author:  "loser"
	version: "v1"
)

// 请求参数结构
type (
	UserReq {
		Id string `json:"id"`
	}
	UserResp {
		Id    string `json:"id"`
		Name  string `json:"name"`
		Phone string `json:"phone"`
	}
)

// 定义 http 服务
service User {
	// 定义 http.Handler
	@handler user
	get /user (UserReq) returns (UserResp)
}

// 定义 http 服务并且使用中间件
@server (
	middleware: LoginVerifation
)
service User {
	@handler userinfo
	post /userinfo (UserReq) returns (UserResp)
}
```
之后使用命令生成`api` 代码:
```shell
$ goctl api go -api user.api -dir . -style gozero
```
最后项目结构如下:
```text
.
├── etc
│   └── user.yaml
├── internal
│   ├── config
│   │   └── config.go
│   ├── handler
│   │   ├── routes.go
│   │   ├── userhandler.go
│   │   └── userinfohandler.go
│   ├── logic
│   │   ├── userinfologic.go
│   │   └── userlogic.go
│   ├── middleware
│   │   └── loginverifationmiddleware.go
│   ├── svc
│   │   └── servicecontext.go
│   └── types
│       └── types.go
├── user.api
└── user.go
```
接下来需要在`middleware`中填写对应的逻辑代码,逻辑代码如下:
```go
func (m *LoginVerifationMiddleware) Handle(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		// TODO generate middleware implement function, delete after code implementation
		if r.Header.Get("token") == "123456" {
			next(w, r)
			return
		}
		// Passthrough to next handler if need
		w.Write([]byte("...鉴权失败..."))
		return
	}
}
```
最后需要在 `srv`中配置中间件:
```go
type ServiceContext struct {
	Config          config.Config
	UserClient      userclient.User
	LoginVerifation rest.Middleware
}

func NewServiceContext(c config.Config) *ServiceContext {
	return &ServiceContext{
		Config:     c,
		UserClient: userclient.NewUser(zrpc.MustNewClient(c.UserRPC)),
		// 注意到这里需要传递一个函数,函数参数需要时 http.HandleFunc,相当于 gin.Context
		LoginVerifation: middleware.NewLoginVerifationMiddleware().Handle,
	}
}
```

## go-zero底层逻辑
### go-zero中的 rpc server 启动过程
`rpc server` 部分的入口文件为 `xxx.go`,内容如下:
```go
func main() {
	flag.Parse()

	var c config.Config
	conf.MustLoad(*configFile, &c)
	ctx := svc.NewServiceContext(c)

	s := zrpc.MustNewServer(c.RpcServerConf, func(grpcServer *grpc.Server) {
		user.RegisterUserServer(grpcServer, server.NewUserServer(ctx))

		if c.Mode == service.DevMode || c.Mode == service.TestMode {
			reflection.Register(grpcServer)
		}
	})

	// 添加拦截器
	interceptor := func(ctx context.Context, req any,
		info *grpc.UnaryServerInfo, handler grpc.UnaryHandler) (resp any, err error) {
		fmt.Println("...开启服务...")
		resp, err = handler(ctx, req)
		fmt.Println("...服务结束...")
		return
	}

	s.AddUnaryInterceptors(interceptor)

	defer s.Stop()

	fmt.Printf("Starting rpc server at %s...\n", c.ListenOn)
	s.Start()
}
```
前面的都是用于加载配置文件的,配置文件的逻辑为   填写配置文件 --> 在 `config.go`中配置相应的配置信息 ---> 在 `xxxContext.go`中根据配置信息创建自己需要的对象比如 `mysql` 操作对象或者`redis` 客户端等等 --> 最后在 `xxxMethodLogic.go` 中使用 `xxxContext` 中提供的对象进行各种操作即可

上面代码的核心就是 `zrpc.MustNewServer`,可以看一下这一个函数的实现(这一个函数的底层调用了`NewServer`,所以只需要关注 `NewServer` 的实现,实现方式如下):
```go
func NewServer(c RpcServerConf, register internal.RegisterFn) (*RpcServer, error) {
	var err error
	if err = c.Validate(); err != nil {
		return nil, err
	}

	var server internal.Server
	metrics := stat.NewMetrics(c.ListenOn)
	serverOptions := []internal.ServerOption{
		internal.WithRpcHealth(c.Health),
	}

	if c.HasEtcd() {
		server, err = internal.NewRpcPubServer(c.Etcd, c.ListenOn, serverOptions...)
		if err != nil {
			return nil, err
		}
	} else {
		server = internal.NewRpcServer(c.ListenOn, serverOptions...)
	}

	server.SetName(c.Name)
	metrics.SetName(c.Name)
	setupStreamInterceptors(server, c)
	setupUnaryInterceptors(server, c, metrics)
	if err = setupAuthInterceptors(server, c); err != nil {
		return nil, err
	}

	rpcServer := &RpcServer{
		server:   server,
		register: register,
	}
	if err = c.SetUp(); err != nil {
		return nil, err
	}

	return rpcServer, nil
}
```
前面表示创建监听对象,也就是创建 `Server` 的过程,注意到 `Server` 是一个接口,接口的实现包含 `RpcServer` 和 `KeepAliveServer`,不同之处在于是否使用到 `etcd` 作为注册中心,最后返回一个 `RpcServer` 对象,并且添加各种拦截器
### go-zero中的client调度过程
这里我们抛开`grpc` 本身的逻辑,只看`go-zero` 做的扩展,可以发现`go-zero`生成了 `xxxcilent.go` 文件来提供客户端连接,内容如下:
```go
type (
	GetUserReq  = user.GetUserReq
	GetUserResp = user.GetUserResp
	Resp        = user.Resp
	UserInfo    = user.UserInfo

	User interface {
		GetUser(ctx context.Context, in *GetUserReq, opts ...grpc.CallOption) (*GetUserResp, error)
		CreateUser(ctx context.Context, in *UserInfo, opts ...grpc.CallOption) (*Resp, error)
	}

	defaultUser struct {
		cli zrpc.Client
	}
)

func NewUser(cli zrpc.Client) User {
	return &defaultUser{
		cli: cli,
	}
}

func (m *defaultUser) GetUser(ctx context.Context, in *GetUserReq, opts ...grpc.CallOption) (*GetUserResp, error) {
	client := user.NewUserClient(m.cli.Conn())
	return client.GetUser(ctx, in, opts...)
}

func (m *defaultUser) CreateUser(ctx context.Context, in *UserInfo, opts ...grpc.CallOption) (*Resp, error) {
	client := user.NewUserClient(m.cli.Conn())
	return client.CreateUser(ctx, in, opts...)
}
```
可以发现其实就是把在用户和`grpc`生成的代码之间加了一层中间层,并且实现了接口的方法,具体创建过程需要看客户端,还是本者 配置文件 -> `go` 对象的流程,可以在 `xxxContext.go` 中看到`xxxClient` 的创建过程:
```go
func NewServiceContext(c config.Config) *ServiceContext {
	return &ServiceContext{
		Config:     c,
		UserClient: userclient.NewUser(zrpc.MustNewClient(c.UserRPC)),
		// 注意到这里需要传递一个函数,函数参数需要时 http.HandleFunc,相当于 gin.Context
		LoginVerifation: middleware.NewLoginVerifationMiddleware().Handle,
	}
}
```
可以发现底层其实调用了`userClient.NewUser`(是否会产生耦合??? --- 不会,原因是实际项目开发中,客户端和服务器端都有一份 `proto` 文件,可以生成自己的 `xxxclient`) 方法,并且其中传递的参数为 `zrpc.MustNewClient`,返回了一个 `client` 对象,这一个方法中没有什么核心的业务逻辑,也就是创建各种对象,并且连接到 `grpc`的服务器端
### go-zero中api服务启动过程
`api` 服务启动文件如下:
```go
func main() {
	flag.Parse()

	var c config.Config
	conf.MustLoad(*configFile, &c)

	server := rest.MustNewServer(c.RestConf)
	defer server.Stop()

	ctx := svc.NewServiceContext(c)
	handler.RegisterHandlers(server, ctx)

	fmt.Printf("Starting server at %s:%d...\n", c.Host, c.Port)
	server.Start()
}
```
流程大体没有看懂: 大概是 ---> 创建服务器  ---> 注册路由 ---> 启动服务器,路由使用字典树管理,执行流程如下:
![[Pasted image 20250308105035.png]]


### go-zero语法信息
参考官方网站,中文文档,很友好: https://go-zero.dev/
#### go-zero中集成gorm
两种方法:
1. 在 `srv` 中加入 `gorm.DB`对象,并且利用这一个对象进行业务逻辑处理
2. 在`model`层引入对象进行业务逻辑处理(底层重写相关方法)

我感觉甚至可以不使用生成 `mysql` 代码的形式,直接使用 `gorm` 即可,但是依赖于配置文件




