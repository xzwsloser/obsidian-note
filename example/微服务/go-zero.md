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

### 搭建rpc服务
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
