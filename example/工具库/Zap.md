> 一款 `Golang` 下的日志框架: https://github.com/uber-go/zap

安装:
```go
go get -u go.uber.org/zap
```

# 1. 配置 Zap Logger

`Zap` 提供了两种类型的日志记录器  `Sugared Logger` 和 `Logger`  , 前者的性能比较高,但是内存分配的次数更多

使用 `zap.NewProduct` 方法可以获取到一个 `*zap.Logger` 对象,并且对于这一个对象调用 `Sugar` 方法可以得到一个 `*zap.Sugar` 对象,对于这一个对象可以使用 `Printf` 的方式来输出日志

配置方式: