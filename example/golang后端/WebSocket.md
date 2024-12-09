> 介绍 `WebSocket` 协议以及,`WebSocket`协议在`golang` 中的使用方法

由于传统的 `HTTP1.1` 虽然支持长连接,但是连接只能由客户端发起,如果客户端需要实时接受到客户端发送过来的数据就需要建立一条比较长的 `http` 连接,之后不断轮询这一条 `http` 连接从而获取消息,这很大程度上消费了带宽资源

`WebSocket` 协议基于 `Http`协议,是由 `HTTP` 协议进行等级提升得到的,进行提升交换的报文也是使用 `HTTP` 报文, `WebSocket`报文的结构如下:
```text
0 1 2 3 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 +-+-+-+-+-------+-+-------------+-------------------------------+ |F|R|R|R| opcode|M| Payload len | Extended payload length | |I|S|S|S| (4) |A| (7) | (16/64) | |N|V|V|V| |S| | (if payload len==126/127) | | |1|2|3| |K| | | +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - + | Extended payload length continued, if payload len == 127 | + - - - - - - - - - - - - - - - +-------------------------------+ | |Masking-key, if MASK set to 1 | +-------------------------------+-------------------------------+ | Masking-key (continued) | Payload Data | +-------------------------------- - - - - - - - - - - - - - - - + : Payload Data continued ... : + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - + | Payload Data continued ... | +---------------------------------------------------------------+
```
# go 中使用 WebSocket
> 这里需要使用第三方库:  github.com/gorilla/websocket 

- `WebSocket` 的使用方法(实际上`websocket`就是 `http`协议的升级,只是用到协议的提升):
1. 首先利用 `websocekt.Upgrader`得到升级连接的需要使用的对象,注意可以设置同源可以访问也就是解决跨域问题
2. 之后通过这一个对象的 `Upgrade`方法获取连接对象
3. 循环从连接对象中读取连接
```go
package main  
  
import (  
    "fmt"  
    "github.com/gin-gonic/gin"    "github.com/gorilla/websocket"    "net/http"    "time")  
  
type User struct {  
    Name        string `json:"name"`  
    Age         int    `json:"age"`  
    Description string `json:"description"`  
}  
  
func WebSocketJson(g *gin.Context) {  
    wsUpgrader := websocket.Upgrader{  
       HandshakeTimeout: time.Second * 10,  
       ReadBufferSize:   1024,  
       WriteBufferSize:  1024,  
       CheckOrigin: func(r *http.Request) bool {  
          return true  
       },  
    }  
  
    ws, err := wsUpgrader.Upgrade(g.Writer, g.Request, nil)  
  
    if err != nil {  
       fmt.Println("[Error] failed to get a connection!")  
       panic(err)  
    }  
  
    for {  
       messageType, p, err := ws.ReadMessage()  
  
       if err != nil {  
          break  
       }  
  
       if messageType == websocket.TextMessage {  
          err = ws.WriteJSON(User{  
             Name:        string(p),  
             Age:         18,  
             Description: string(p) + "很厉害!!!!",  
          })  
          if err != nil {  
             fmt.Println("Json handler failed!")  
             panic(err)  
          }  
       }  
    }  
}  
  
func main() {  
    r := gin.Default()  
  
    r.GET("/json", WebSocketJson)  
  
    r.Run(":8080")  
}
``` 