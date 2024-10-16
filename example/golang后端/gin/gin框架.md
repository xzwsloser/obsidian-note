+ gin框架: 是一个golang的一个web开发框架
>参考: https://gin-gonic.com/docs/

# gin框架的引入
+ 代理设置: 可以直接在创建工程中的environment选项中设置: GOPROXY=https://goproxy.cn.direct

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712728476237-5f9d4078-79dd-4e1f-8f5c-8cf4f779a86a.png)

+ 可以利用postman端口调试工具给后端发送请求
+ 下载gin依赖的方法如下:

:::color1
go get -u github.com/gin-gonic/gin   // 直接利用go get下载依赖

:::

## gin框架的展示和基本使用
+ gin框架中的helloworld代码,其实就是演示创建路由使用路由的过程

```go
package main

import (
	"github.com/gin-gonic/gin"
)

func main() {
	// 用于演示gin框架的基本操作
	// 利用gin编写一个接口
	// 创建一个默认路由,路由其实就是相当于一个访问地址,访问这个地址时可以根据请求的对象做出相应的行为

	router := gin.Default()
	// 绑定路由规则和路由函数,就是访问这个路由时就会使用这一个函数进行处理
	router.GET("/index", func(context *gin.Context) {
		context.String(200, "hello world")
	})
	// 其实服务器监听,服务器会把服务运行在 localhost的某一个端口中,还可以利用终端通过curl命令访问这个端口
	// curl http://localhost:8080/index   , 127.0.0.1
	router.Run("localhost:8080") // localhost:8080
	// 也可以使用原生http服务的方式启动
	// http.ListenAndServe("8080", router)
}

```

## gin框架响应数据
### 响应字符串和json格式的字符串
+ 响应字符串使用 string方法
+ 响应json使用JSON方法,
+ json可以响应如下数据
    - 结构体的实例对象: 利用 (*gin context)JSON(状态码,对象名)
    - 响应map集合 利用(*gin context)JSON(状态码,map集合名称)
    - 直接响应数据 : 利用(*gin context).JSON(状态码,gin.H{键值对}
+ 代码演示:

```go
package main

import (
	"github.com/gin-gonic/gin"
)

func _string(c *gin.Context) {
	c.String(200, "hello gin")
}
func _json(c *gin.Context) {
	type UserDemo struct { // 可以利用 json标签指定变成json之后的key值变化
		Name     string `json:"user_name"`
		Age      int    `json:"age"`
		password string `json:"-"` // 用于忽略响应的结果,其实就是忽略转化为json
	}
	user := UserDemo{
		Name:     "zhangsan",
	Age:      12,
		password: "123456",
	}
	// json响应map
	userMap := map[string]string{
		"username":  "hello",
		"passworld": "111",
    }
	c.JSON(200, userMap) // 就是可以把对象变成json格式的字符串,其实后面就是一个对象
	// 直接响应json,相当于可以响应一个结构体,直接利用gin.H方法响应json
	c.JSON(200, gin.H{"username": "张三", "age": 23})
}
func main() {
	// 用于演示响应 json格式的数据
	router := gin.Default()
	//router.GET("/", func(c *gin.Context) {
	//	// 响应一个字符串
	//	// 动态码演示
	//	/*
	//	    200 响应成功  , 还可以利用枚举列出响应状态码
	//		404 找不到资源
	//
	//	 */
	//	// c.String(http.StatusOK, "hello gin")
	//	// 响应一个json
	//
	//})
	router.GET("/", _string)
	router.GET("/json", _json) // 一个页面只可以请求一个数据
	router.Run(":80")
}

```

### 响应xml格式和yaml
+ xml和yaml,json的格式如下:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712731730172-9a7c4b29-5cc9-4764-9fcf-27e29d533ceb.png)

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712731756666-271bc95f-e840-4aa6-927f-a30d12a1ffc2.png)

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712731776339-b35a3b7b-9ced-4c6f-9bae-50a446fe7ce7.png)

+ 代码演示:

```go
func _xml(c *gin.Context) {
	c.XML(200, gin.H{"username": "张三", "age": 23, "httpStatus": http.StatusOK})
}

// 响应yaml格式的代码
func _yaml(c *gin.Context) {
	c.YAML(200, gin.H{"username": "张三", "age": 23, "httpStatus": http.StatusOK})
}
```

### 响应html
+ 响应html,利用HTML方法,但是需要加载资源文件,利用loadHtmlGlobal方法进行文件的加载
+ 但是可以进行类似声明式渲染的功能,利用 {{ .变量名 }}的方法进行声明式渲染
+ 代码演示:

```go
// 响应html文件
func _html(c *gin.Context) {
	// 其实不可以传递一个结构体,但是可以利用gin.H方法传递结构体
	c.HTML(200, "index.html", gin.H{"username": "张三"}) // 响应回去

}
func main() {
	// 用于演示响应 json格式的数据
	router := gin.Default()
	// 注意引入html一定需要引入全局html
	router.LoadHTMLGlob("../template/*") // 加载所有文件
	//router.GET("/", func(c *gin.Context) {
	//	// 响应一个字符串
	//	// 动态码演示
	//	/*
	//	    200 响应成功  , 还可以利用枚举列出响应状态码
	//		404 找不到资源
	//
	//	 */
	//	// c.String(http.StatusOK, "hello gin")
	//	// 响应一个json
	//
	//})
	router.GET("/", _string)
	router.GET("/json", _json) // 一个页面只可以请求一个数据
	router.GET("/xml", _xml)
	router.GET("/yaml", _yaml)
	router.GET("/html", _html)
	router.Run(":80")
}
```

+ html

```go
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>响应html</title>
</head>
<body>
    <h1>响应了html,你好 {{ .username }}</h1>
</body>
</html>
```

+ 结果演示

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712760992729-b70fb561-83cb-42a6-8103-1fa29f5abcb9.png)

### 文件响应
+ 文件只用配置访问时使用的url和文件的路径就可以了,利用StaticFile配置静态资源,利用StaticFs配置打个文件
+ 注意golang中还是有相对路径的(为什么我的结果和视频中的结果不同)（当前路径就是项目所在的路径，其实就是项目的根目录）
+ 代码演示:

```go
package main

import (
	"github.com/gin-gonic/gin"
	"net/http"
)

func main() {
	router := gin.Default()
	// golang中还是有相对路径的,配置单个文件的方式,可以利用这种方法进行访问
    // golang中的相对路径指的就是main包所在的路径,这里main所在的路径要得到相对路径只用
    // 利用  .. 退回上面一级目录
	router.StaticFile("/pic", "../static/img.png") // 前面一个参数就是访问的路径
	router.StaticFS("/static", http.Dir("./static/static/*"))
	router.Run(":80")
}

```

+ 文件目录结构

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712761856198-619ffc10-4a53-43e9-90a6-ae1555b9d405.png)

### 重定向
+ 其实就是访问一个地址时,自动跳转到另外一个地方中

```go
package main

import "github.com/gin-gonic/gin"
// 前面加上_表示 私有方法
func _redict(c *gin.Context) { // 表示一个私有方法
	// 301 表示原来的地址已经迁移了,服务器没有缓存了,一个是永久重定向,一个是临时重定向
	// 可以使用 c.Redirect(201,"/html")
	c.Redirect(201, "https://www.baidu.com")
}
func main() {
	// 用于演示响应重定向
	router := gin.Default()
	router.GET("/baidu", _redict)
	router.Run(":80")
}

```

## 请求
### query参数
+ query参数就表示访问某一个资源时，url之后的一个键值对参数
+ 可以利用query方法获取单个参数,可以利用queryArray方法获取多个参数
+ 代码演示

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func _query(c *gin.Context) {
	// 得到的参数就是请求url之后的键值对参数
	user := c.Query("user")
	// 其实可以利用 c.getquery方法进行操作
	fmt.Println(user)
	// 可以拿到多个同名参数
	fmt.Println(c.QueryArray("user"))
}
func main() {
	router := gin.Default()
	router.GET("/query", _query)
	router.Run(":80")
}

```

### 动态参数(param参数)
+ 什么是动态参数就是同一个请求地址之后带上不同的参数,比如请求的url可以写成 /static/:username/:password,请求时之后的参数就可以通过url之后的参数名称获取到,访问时直接利用变量替代:username和:password即可
+ 代码演示如下:

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func _param(c *gin.Context) {
	// 动态参数,路径可以变化,除了路径参数之外的其他参数都可以
    // 注意先后顺序,如果访问都会走到,谁先走到谁先匹配
	fmt.Println(c.Param("userid"))
	fmt.Println(c.Param("bookid"))
}
func _query(c *gin.Context) {
	// 得到的参数就是请求url之后的键值对参数
	user := c.Query("user")
	// 其实可以利用 c.getquery方法进行操作
	fmt.Println(user)
	// 可以拿到多个同名参数
	fmt.Println(c.QueryArray("user"))
}
func main() {
	router := gin.Default()
	router.GET("/query", _query)
	router.GET("/param/:userid", _param)
	router.GET("/param/:userid/:bookid", _param)
	router.Run(":80")
}

```

### 表单参数
+ 表单就是前端中的表单,其中可以利用postman发送表单信息，其实就是利用postman中的body进行发送,之后就可以利用headers查看发送的参数
+ 注意postForm函数可以接受的参数有很多,比如 <font style="color:#bcbec4;background-color:#1e1f22;">可以接受 www-form-urlencoded 和 form表单参数</font>

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func _form(c *gin.Context) {
	// 表单参数必须利用post请求
	// 可以接受 www-form-urlencoded 和 form表单参数
	fmt.Println(c.PostForm("name"))
	// 接收多个参数的方法
	fmt.Println(c.PostFormArray("username"))
	// 如果用户没有传入尺寸就可以设置一个默认值,query也是有一个默认值的
	fmt.Println(c.DefaultPostForm("addr", "湖北省"))
	forms, err := c.MultipartForm() // 用于接收文件和其他所有参数,最后传出来的就是利用键值对构建的一个数组
	fmt.Println(forms, err)
}
func main() {
	router := gin.Default()

	router.POST("/form", _form)

	router.Run("localhost:80")
}

```

### 原始参数GetRawData
+ 其实就得到各种请求的数据,可以用于处理请求体和请求头
+ 请求体中不同参数的表现形式:
    - json : 直接打印得到的就是一个unicode码值,但是需要利用string进行强转,另外可以利用json库中的uhamral函数 进行强制类型转换,但是需要传一个结构体承装结果，注意postman中发送请求的方式，直接利用body中的raw书写结构体发送请求
    - www参数: 表现形式就是一串 unicode码值
    - 表单参数,string强转之后得到的就是一个表单的具象化
+ 代码演示:

```go
package main

import (
	"encoding/json"
	"fmt"
	"github.com/gin-gonic/gin"
)

func _form(c *gin.Context) {
	// 表单参数必须利用post请求
	// 可以接受 www-form-urlencoded 和 form表单参数
	fmt.Println(c.PostForm("name"))
	// 接收多个参数的方法
	fmt.Println(c.PostFormArray("username"))
	// 如果用户没有传入尺寸就可以设置一个默认值,query也是有一个默认值的
	fmt.Println(c.DefaultPostForm("addr", "湖北省"))
	forms, err := c.MultipartForm() // 用于接收文件和其他所有参数,最后传出来的就是利用键值对构建的一个数组
	fmt.Println(forms, err)
}

// 原始参数
func _raw(c *gin.Context) {
	// 接收到的是请求体中的参数
	// 但是不同的参数的处理方式不同,比如www参数是用unicode编码写出的
	// 表单时直接列出的
	// fmt.Println(c.GetRawData()) // 其实得到的就是参数的一个unicode值
	body, _ := c.GetRawData()
	//fmt.Println(string(body))
	// 获取请求头
	contentType := c.GetHeader("content-Type")
	switch contentType {
	case "application/json":
		// 如果是json数据开始解析数据
		type User struct {
			Name string `json:"name"`
			Age  int    `json:"age"`
		}
		// 相当于一个匿名结构体
		// 解析json字符串的方法利用结构体承装转换之后的对象
		var user User
		err := json.Unmarshal(body, &user)
		if err != nil {
			fmt.Println(err.Error())
		}
		fmt.Println(user)

	}
	fmt.Println(contentType)

}
func main() {
	router := gin.Default()

	router.POST("/form", _form)
	router.POST("/raw", _raw)
	router.Run("localhost:80")
}

```

### 四大请求方式
+ Restful风格是网络应用中就是资源定位和资源操作的风格,不是协议也不是标准

#### GET
+ 其实就是从服务器中取出资源

#### POST
+ 在服务器端创建一个资源

#### PUT
+ 在服务器中更新资源(客户端提供完整资源数据)

#### PATCH
+ 在服务器中更新资源(客户端提供需要修改的资源)

#### DELETE
+ 从服务器中删除资源

#### 各种资源的演示(实例相关)
```go
// 文件资源为例
// GET /articles    返回一个文件列表
// GET /articles/:id  返回一个文章详情
// POST /articles  添加一遍文章
// PUT /articles 修改一篇文章
// DELETE /articles/:id 删除某一篇文章(客户端提供一个删除的id)
```

#### 利用各种请求方式进行文章操作(仅仅正对于restful的操作)
```go
package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"github.com/gin-gonic/gin"
)

type Article struct {
	Title   string `json:"title"`
	Context string `json:"context"` // 其实就是json字符串中的一个键值
}
type Response struct {
	Code int    `json:"code"`
	Data any    `json:"data"`
	Msg  string `json:"msg"`
}

// 提供增删改查的接口
func _getList(c *gin.Context) {
	articleList := []Article{
		{
			Title:   "GO语言入门",
			Context: "go语言圣经",
		},
		{
			Title:   "java语言入门",
			Context: "java从入门到进阶",
		},
		{
			Title:   "cpp语言入门",
			Context: "cpp从入门到放弃",
		},
	}
	//c.JSON(200, articleList)
	c.JSON(200, Response{0, articleList, "传输成功"}) // 注意规范
}

// 文章详情页面
func _getDetail(c *gin.Context) {
	// 获取param的参数
	fmt.Println(c.Param("id"))
	article := Article{
		Title:   "GO语言入门",
		Context: "go语言圣经",
	}
	c.JSON(200, Response{0, article, "传输成功"})
}

// 处理json数据
func _bindJson(c *gin.Context, obj any) error {
	// 首先获取json数据
	data, err := c.GetRawData()
	if err != nil {
		return errors.New("解析失败")
	}
	json.Unmarshal(data, obj)
	return nil
}

// 添加文章,接受前端的json数据
func _create(c *gin.Context) {
	var article Article
	err := _bindJson(c, &article)
	if err != nil {
		fmt.Println(err)
		return
	}

	c.JSON(200, Response{0, article, "添加成功"})
}

// 编辑文章逻辑
func _update(c *gin.Context) {
	fmt.Println(c.Param("id"))
	// 根据id进行修改数据
	var article Article
	err := _bindJson(c, &article)
	if err != nil {
		fmt.Println(err)
		return
	}

	c.JSON(200, Response{0, article, "修改成功"})
}
func _delete(c *gin.Context) {
	// 其实就是找到id,之后删除记录即可
	fmt.Println(c.Param("id"))
	c.JSON(200, Response{0, map[string]string{}, "删除成功"}) // 其中map其实就是一个空的映射
}

func main() {
	router := gin.Default()
	// 注册路由
	router.GET("/articles", _getList)       // 查看文章,其实就是后端向前端响应数据
	router.GET("/articles/:id", _getDetail) // 查看文章详情
	router.POST("/articles", _create)       // 添加文章
	router.PUT("/articles/:id", _update)    // 更新文章
	router.DELETE("/articles/:id", _delete) // 删除文章,都是客户端发送参数,后端接收参数查询数据并且删除数据

	router.Run(":80")
}

```

## 请求头相关
### 请求头参数获取
+ 主要利用GetHeader方法或者c.Request.Header对象中的一个Get方法或者直接利用键值对的形式传递参数
+ 但是GetHeader,Get虽然不区分大小写,但是只可以 取出一个参数
+ 直接利用键值对可以取出多个参数

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"strings"
)

func main() {
	// 请求头参数相关
	router := gin.Default()
	router.GET("/", func(c *gin.Context) {
		// 首先如何拿到请求头
		// 请求头: 首字母大小写不区分,单词和单词之间使用 - 连接
		// 使用Get方法或者是GetHeader方法就可以不用区分大小写,但是只可以获取第一个对象
		// 如果使用map的取值方式,注意大小写即可
		fmt.Println(c.GetHeader("User-Agent"))
		// 获取请求体中的全部数据,返回的参数就是一个键值对
		fmt.Println(c.Request.Header["User-Agent"])     // Header 其实就是一个普通的映射 map[string][]string
		fmt.Println(c.Request.Header.Get("User-Agent")) // 利用这一种方式之可以拿到第一个参数,不可以拿到其他同名参数
		c.JSON(200, gin.H{"msg": "成功"})
		// 自定义请求使用Get方法还是可以不用区分大小写
		fmt.Println(c.Request.Header.Get("Token"))
	})
	// 判断登录用户类型
	router.GET("/index", func(c *gin.Context) {
		userAgent := c.GetHeader("User-Agent")
		// 可以利用正则表达式单独匹配
		// 或者字符串的包含匹配
		if strings.Contains(userAgent, "python") {
			c.JSON(0, gin.H{"data": "这是响应给爬虫的数据"})
			return
		}
		c.JSON(0, gin.H{"data": "这是响应给用户的数据"})
	})
	router.Run(":80")
}

```

### 响应头相关
+ 重点就是利用Header方法设置参数的名称 Header(字段名称,值)，主要利用这个方法设置Content-Type的值,用于指定传输文件的类型
+ 代码演示:

```go
	// 设置响应头
	router.GET("/res", func(c *gin.Context) {
		// 设置响应头
		c.Header("Hello", "发现我了吗")
		// 利用Header方法一般是用于设置Content-type,就是相应的内容
		c.Header("Content-Type", "application/json;charset=utf-8")
		c.JSON(200, gin.H{"Msg": "看一下响应头中有没有token"})
	})
```

## bind参数绑定
+ gin框架中的一个bind可以很方便的把前端传递过来的数据和结构体进行参数绑定,以及参数校验
+ 使用这个功能时,需要为结构体中的成员加上一个Tag: json(之前用于指定一个json中结构体中个字段对应的名称),form,url,xml,yaml(其实就是类似于一个gorm标签)
+ 基本使用Shouldbind

#### 利用shouldbingJson方法绑定参数到结构体中
```go
package main

import "github.com/gin-gonic/gin"

// 结构体
type UserInfo struct {
	Name   string `json:"name" form:"name"`  // 注意之后的字段
	Age    int    `json:"age" form:"age"`
	Gender string `json:"gender" form:"gender"`
}

func _bind(c *gin.Context) {
	var userinfo UserInfo
	err := c.ShouldBindJSON(&userinfo)
	if err != nil {
		c.JSON(200, gin.H{"msg": "错误出现了"})
		return
	}
	// 响应原始数据
	c.JSON(200, userinfo)

}
func main() {
	// 用于参数绑定,绑定查询参数
	router := gin.Default()
	router.POST("/bind", _bind) // 利用post用于添加数据,但是get方法只是可以传递键值对参数
	router.POST("/query", func(c *gin.Context) {
		var userinfo UserInfo
		err := c.ShouldBindQuery(&userinfo)
		if err != nil {
			c.JSON(200, gin.H{"Msg": "出错啦"}) // 注意利用gin.H传递json对象
			return
		}
		c.JSON(200, userinfo)

	})
	router.Run(":80")
}


```

#### 利用shouldBindQuery查询字段是否错误,并加以检验
+ 注意用以检验的字段所在的位置和类型,可以检验字段,此时参数的类型就是键值对参数类型：

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712821149813-f2b42818-e29b-4138-ae23-14aa96f7f975.png)

+ 代码演示,注意添加form表单标签指定相关的属性

```go
router.POST("/query", func(c *gin.Context) {
		var userinfo UserInfo
		err := c.ShouldBindQuery(&userinfo)
		if err != nil {
			c.JSON(200, gin.H{"Msg": "出错啦"}) // 注意利用gin.H传递json对象
			return
		}
		c.JSON(200, userinfo)

	})
```

#### 利用shouldBIndUri进行绑定动态参数
+ 其实上面不同的方法就是针对于不同携带参数请求方式进行参数与结构体之间的绑定,这里演示利用uri携带参数获取参数并且绑定结构体的方法
+ 注意tag为uri
+ uri携带参数的方式(/uri/id/username/age):

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712821848433-d8090229-6615-4102-988f-416940647358.png)

+ 代码演示：

```go
router.POST("/uri/:name/:age/:gender", func(c *gin.Context) {
		var userinfo UserInfo
		err := c.ShouldBindUri(&userinfo)
		if err != nil {
			c.JSON(200, gin.H{"Msg": "出错啦"}) // 注意利用gin.H传递json对象
			return
		}
		c.JSON(200, userinfo)
	})
```



#### 如何绑定formdate或者www-form-urlencode参数
+ 直接利用 shouldbind方法从响应头 开始寻找,找到表单之后开始赋值
+ 代码演示:

```go
router.POST("/form", func(c *gin.Context) {
		var userinfo UserInfo
		// 这个方法回从请求头开始寻找,寻找之后可以可以找到form表单并且获取数据
		// 一定有一个类型限制,必须限制类型
		err := c.ShouldBind(&userinfo)
		if err != nil {
			c.JSON(200, gin.H{"Msg": "出错啦"}) // 注意利用gin.H传递json对象
			return
		}
		c.JSON(200, userinfo)
	})
```

## gin验证器
### 常用验证器
:::info
required : 必填字段 比如 binding:"required"  // 多个条件连接使用 , 分隔开

min： 最小长度： 比如 binding:"min=4"

max: 最大长度

len :指定长度

eq: 等于

ne : 不等于

gt:"大于"

gte:"大于等于"

lt:"小于"

lte:"小于等于"

eqfield:等于其他字段的值 "binding:eqfield=ConfirmPassword",后面是结构体中的字段

nefied:不等于其他字段的值

-:"忽略字段 binding:"-"

:::

+ 通过错误类型就可以直接通过验证器确定错误,采取响应的措施
+ 代码演示：

```go
package main

import "github.com/gin-gonic/gin"

type UserInfo struct {
	Name       string `json:"name" binding:"min=4,max=6,required,"` // 可以通过在后面加上限制条件进行条件过滤,都需要填写在binding字段之后
	Age        int    `json:"age"`
	PassWord   string `json:"password"`
	RePassWord string `json:"re_password" binding:"eqfield=Password"` // 确认密码
}

func main() {
	router := gin.Default()

	router.POST("/", func(c *gin.Context) {
		var user UserInfo
		err := c.ShouldBindJSON(&user)
		if err != nil {
			// 字段不可以为空,但是可以传递
			c.JSON(200, gin.H{"msg": err.Error()})
			return // 可以返回一个error
			// 这里返回结果利用err.Error就可以进行类型校验
		}
		c.JSON(200, gin.H{"msg": "成功", "obj": user})
	})

	router.Run(":80")
}

```

### gin内置验证器
#### 字符串操作
:::info
  
    字符串操作：  
       contains: 包含  
       exclude: 不包含  
       startwith:以什么开头  
       endwith:以什么结尾  


:::

#### 数组操作
:::info
数组操作:

dive 对于数组中每一个元素进行验证

比如 required dive min=1 startwith=like

:::

#### 网络验证
:::info
ip : 表示ip地址

url : 表示url验证

uri: 表示uri验证

注意uri就是url的之后的一部分，类似于访问路径

:::

#### 日期验证
:::info
datetime: 指定日期的格式  datetime=2006 01-02 15:04:05

:::

+ 利用标签进行验证过程演示

```go
package main

import "github.com/gin-gonic/gin"

type SignInfo struct {
	/**
	字符串操作：
		contains: 包含
		exclude: 不包含
		startwith:以什么开头
		endwith:以什么结尾
	*/
	Name     string   `json:"name" binding:"contains=f"` // 用户名 contains验证表示必须包含某一个信息,利用excluede可以表示不包含
	Age      int      `json:"age"`
	Gender   string   `json:"gender" binding:"oneof=man woman"`                 // 一个枚举验证器,列出所有可能的值
	LikeList []string `json:"like_list" binding:"required,dive,startwith=like"` // 之后表示对于每一个对象进行操作
	IP       string   `json:"ip" binding:"ip"`
	Url      string   `json:"url" binding:"url"` // url其实就是指一个地址
	Uri      string   `json:"ur}" binding:"uri"` // url其实就是指一个地址 uri是url的子集
	// 日期验证
	Date string `json:"data" binding:"datetime=2006-01-02 15:04:05"` // 1月2日3时4分5秒
}

func main() {
	router := gin.Default()
	router.POST("/", func(c *gin.Context) {
		var user SignInfo
		err := c.ShouldBindJSON(&user)
		if err != nil {
			c.JSON(200, err.Error())
			return
		}
		c.JSON(200, user)

	})
	router.Run(":80")
}

```

### gin验证器自定义错误信息
+ 基本操作就是利用标签中的属性 msg指定报错信息,但是难点就是根据报错信息获取到msg的一个值,这里需要利用反射进行获取
+ 代码演示如下:

```go
package main

import (
	"github.com/gin-gonic/gin"
	"github.com/go-playground/validator/v10"
	"reflect"
)

func GetValidMsg(err error, obj any) string {
	getObj := reflect.TypeOf(obj)
	// 将error接口断言称具体类型
	if errs, ok := err.(validator.ValidationErrors); ok {
		// 之后err 就是一个切片应为多次有错误
		for _, e := range errs {
			// 循环获取每一错误信息
			// 根据报错字段获取信息
			if f, exits := getObj.Elem().FieldByName(e.Field()); exits {
				msg := f.Tag.Get("msg")
				return msg
			} // 根据报错名获取字段
		}
	}
	return err.Error()
}
func main() {
	// 用于演示自定义错误信息
	router := gin.Default()
	router.POST("/", func(c *gin.Context) {
		type User struct {
			Name string `json:"name" binding:"required" msg:"用户名校正失败"`
			Age  int    `json:"age" binding:"required" msg:"年龄校验失败"`
		}
		var user User
		err := c.ShouldBindJSON(&user)
		if err != nil {
			res := GetValidMsg(err, &user)
			c.JSON(200, res)
			return
		}
		c.JSON(200, user)

	})
	router.Run(":80")
}

```

### 自定义验证器
+ 其实就是自定义一个验证器,代码中使用了Validator方法不知道是什么意思
+ 代码演示:

```go
package main

import (
	"github.com/gin-gonic/gin"
	"github.com/gin-gonic/gin/binding"
	"github.com/go-playground/validator/v10"
	_ "github.com/go-playground/validator/v10"
	"reflect"
	_ "reflect"
)

type User struct {
	Name string `json:"name" binding:"required,sign" msg:"用户名校正失败"`
	Age  int    `json:"age" binding:"required" msg:"年龄校验失败"`
}

func signValid(f1 validator.FieldLevel) bool {
	// 这里就可以用于定义一个验证器了
	nameList := []string{
		"张三", "李四", "王五",
	}
	name := f1.Field().Interface().(string) // 类型断言
	for _, namestr := range nameList {
		if name == namestr {
			return false
		}
	}
	return true
}
func GetValidMsg(err error, obj any) string {
	getObj := reflect.TypeOf(obj)
	// 将error接口断言称具体类型
	if errs, ok := err.(validator.ValidationErrors); ok {
		// 之后err 就是一个切片应为多次有错误
		for _, e := range errs {
			// 循环获取每一错误信息
			// 根据报错字段获取信息
			if f, exits := getObj.Elem().FieldByName(e.Field()); exits {
				msg := f.Tag.Get("msg")
				return msg
			} // 根据报错名获取字段
		}
	}
	return err.Error()
}

func main() {
	// 用于演示自定义错误信息
	router := gin.Default()
	if v, ok := binding.Validator.Engine().(*validator.Validate); ok {
		v.RegisterValidation("sign", signValid)
	}

	router.POST("/", func(c *gin.Context) {

		var user User
		err := c.ShouldBindJSON(&user)
		if err != nil {
			res := GetValidMsg(err, &user)
			c.JSON(200, res)
			return
		}
		c.JSON(200, user)

	})
	router.Run(":80")
}

```

## gin中文件上传和文件下载
+ 利用postman发送请求传递文件的方法,传递文件不可以使用其他格式,之可以使用form表单格式,直接选择上传信息的类型,之后选择文件即可
+ 服务端可以使用 : FormFile方法进行文件的接受
+ 以下是上传文件之后本地保存文件的三种方法

#### 利用SaveUploadedFile方法
+ 代码演示:

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()
	router.POST("/upload", func(c *gin.Context) {
		file, _ := c.FormFile("file")
		// 获取文件之后的操作
		fmt.Println(file.Size / 1024)
		fmt.Println(file.Filename) // 这就是文件名和文件大小
		// 这里的路径就是指的是当前工程的一个路径,这个工程就是upload
		// 演示服务端保存文件的几种方式
		// 1. 直接利用SavaUploadedFile函数保存文件
		c.SaveUploadedFile(file, "./ginDemo1/uploads/hell.jpg") // 指定保存文件的路径,这里保存文件的路径就是这个目录
		c.JSON(200, gin.H{"msg": "上传"})
	})
	// 为什么选择post方法,因为post方法用于向服务器提交文件
	router.Run(":801")
}

```

#### 利用io操作(os和is库进行文件的操作)
+ 代码演示：

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"io"
)

func main() {
	router := gin.Default()
	router.POST("/upload", func(c *gin.Context) {
		file, _ := c.FormFile("file")
		// 第二种方法保存文件
		readerFile, _ := file.Open()
		data, _ := io.ReadAll(readerFile)
		fmt.Println(string(data))
		// 这样的话就和io操作就可以实现对于文件的操作了
		c.JSON(200, gin.H{"msg": "上传"})
	})
	// 为什么选择post方法,因为post方法用于向服务器提交文件
	router.Run(":801")
}

```

#### 还是利用io操作,创建输出流对象,之后利用io中的copy方法进行操作
```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"io"
	"os"
)

func main() {
	router := gin.Default()
	router.POST("/upload", func(c *gin.Context) {
		file, _ := c.FormFile("file")
		// 第三种方式, 直接利用Create和Copy方法
		readFile, _ := file.Open()
		writerFile, _ := os.Create("./uploads/h.png")
		defer writerFile.Close()
		n, _ := io.Copy(writerFile, readFile) // 直接利用输入输出流的方式进行文件的读取
		fmt.Println(n)
		c.JSON(200, gin.H{"msg": "上传"})
	})
	// 为什么选择post方法,因为post方法用于向服务器提交文件
	router.Run(":801")
}

```

### 多文件上传
+ 通过MutipartForm方法获取一个表单,表单中,表单参数中有一个file属性，这个对象中有文件组成的集合,通过操作承装文件的集合就可以操作文件了
+ 代码演示如下:

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"io"
	"os"
)

func main() {
	router := gin.Default()
	router.POST("/upload", func(c *gin.Context) {
		file, _ := c.FormFile("file")
		// 第三种方式, 直接利用Create和Copy方法
		readFile, _ := file.Open()
		writerFile, _ := os.Create("./uploads/h.png")
		defer writerFile.Close()
		n, _ := io.Copy(writerFile, readFile) // 直接利用输入输出流的方式进行文件的读取
		fmt.Println(n)
		c.JSON(200, gin.H{"msg": "上传"})
	})
	router.POST("/uploads", func(c *gin.Context) {
		form, _ := c.MultipartForm()   // 接受多个文件
		files := form.File["upload[]"] // 后去的其实是一个map集合,后面就是请求时表单中key的值
		for _, file := range files {
			c.SaveUploadedFile(file, "./uploads/"+file.Filename)
		}
		c.JSON(200, gin.H{"msg": fmt.Sprintf("成功上传%d个文件", len(files))})
	})
	// 为什么选择post方法,因为post方法用于向服务器提交文件
	router.Run(":801")
}

```

## gin中间件和路由
+ Gin框架允许开发者在处理请求的过程中加入用户自己的钩子函数,这个钩子函数就叫做中间件,中间件适合于访问一些公共的业务逻辑比如登录认证,权限校验等,比如访问一个网页时无论访问什么路径都需要登录,此时就需要为所有的路径的处理函数进行一个统一中间件(用于校验是否登录)
+ Gin中的中间件必须是一个gin.HandlerFunc类型的

### 单个路由中间件
+ 其实每一个请求函数之后的一个函数参数就是一个中间件,中间件的执行顺序就是从前到后,但是遇到Abort函数 之后就会退出了
+ 代码演示如下:

```go
func main() {
	// 用于演示中间件,单个路由中间件
	router := gin.Default()
	// 其实get函数的第二个参数是一个切片可以填写多个函数
	// 只需要参数是一个c *gin.Context就说明可以是一个中间件
	// 顺序就是从前往后
	// 其实就是前面一个函数执行完了之后就可以执行后面一个函数了
	// 可以利用abort函数阻止函数的继续执行
	// abort之后的中间件就不会再走了
	router.GET("/", func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "第1次返回"})
	}, func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "第2次返回"})
	
	}, func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "第3次返回,还想要更多次数的返回吗?"})
		c.Abort() // 停止 函数的执行
	}, func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "应该没有看到我吧"})
	})
	// 演示双路由中间件
	//router.GET("/", f1, index, f2) // 看一下路由的顺序
	router.Run(":80")
}

```

### 多个路由中间件
+ 就是几个中间件的执行顺序和加入next函数之间的关系,代码演示如下：

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func f1(c *gin.Context) {
	fmt.Println("f1 in ......")
	c.Next()
	fmt.Println("f1 out ......")
}
func index(c *gin.Context) {
	fmt.Println("index in ......")
	c.Next()
	fmt.Println("index out ......")
}
func f2(c *gin.Context) {
	fmt.Println("f2 in ......")
	c.Next()
	fmt.Println("f2 out ......")
}
func main() {
	// 用于演示中间件,单个路由中间件
	router := gin.Default()
	// 其实get函数的第二个参数是一个切片可以填写多个函数
	// 只需要参数是一个c *gin.Context就说明可以是一个中间件
	// 顺序就是从前往后
	// 其实就是前面一个函数执行完了之后就可以执行后面一个函数了
	// 可以利用abort函数阻止函数的继续执行
	// abort之后的中间件就不会再走了
	//router.GET("/", func(c *gin.Context) {
	//	c.JSON(200, gin.H{"msg": "第1次返回"})
	//}, func(c *gin.Context) {
	//	c.JSON(200, gin.H{"msg": "第2次返回"})

	//}, func(c *gin.Context) {
	//	c.JSON(200, gin.H{"msg": "第3次返回,还想要更多次数的返回吗?"})
	//	c.Abort() // 停止 函数的执行
	//}, func(c *gin.Context) {
	//	c.JSON(200, gin.H{"msg": "应该没有看到我吧"})
	//})
	// 演示双路由中间件
	router.GET("/", f1, index, f2) // 看一下路由的顺序
	router.Run(":80")
}

```

+ 运行结果:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713020707237-94a1a22c-2db0-43cf-9299-180aaadbb44a.png)

+ 运行结果分析: 首先next函数可以把原来的中间件分为多段,不同中间件的执行顺序就是next之前的首先执行(请求中间件),next函数之后的后执行(响应中间件),拦截函数就是一样(执行顺序: 从前往后执行请求中间件,从后往前执行相应中间件)
+ 细节就是如果c.Abort()函数在第一个中间件的next函数的后面就相当于没有执行什么了(abort函数不会阻止当前中间件的执行),其实相当于递归函数的执行
+ 画图分析:

![](https://cdn.nlark.com/yuque/0/2024/jpeg/40754486/1713021008464-68807708-219b-484c-a78a-eb5b7dcf4696.jpeg)

### 全局注册中间件
+ 只用利用router.User函数就可以完成中间件的全局注册了,并且每一个中间件执行完了之前都会执行一遍全局中间件
+ 全局中间件就相当于普通的中间件,执行顺序有绑定时间决定

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func f3(c *gin.Context) {
	fmt.Println("全局中间件f3执行了")
	c.Next()
	fmt.Println("全局中间件f3执行结束了")
}
func f4(c *gin.Context) {
	fmt.Println("全局中间件f4执行了")
	c.Next()
	fmt.Println("全局中间件f4结束了")
}
func main() {
	// 用于演示全局注册中间件
	router := gin.Default()
	router.Use(f3,f4) // 这样就注册了全局中间件,全局中间就是
	router.GET("/m1", func(c *gin.Context) {
		fmt.Println("m1执行了")
		c.Next()
		fmt.Println("m1执行结束了")
	})
	router.Run(":80")
}

```

+ 结果演示:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713021796456-4abedb8e-6fbf-4833-8761-39966706c1ab.png)

### 中间件传参
+ 相当于一个全局应用域名,可以利用Set方式设置键值对,利用Get方法获得键值对
+ 细节: 需要如果传递的参数不可以直接使用(比如结构体),就可以进行类型断言之后使用
+ 代码演示:

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

type User struct {
	Name string
	Age  int
}

func f5(c *gin.Context) {
	// 用于获取数据
	fmt.Println("%p", c)
	c.Set("user", User{
		Name: "张三",
		Age:  12,
	})
}
func main() {
	// 中间件传递数据
	router := gin.Default()
	router.Use(f5)
	router.GET("/", func(c *gin.Context) {
		// 获取变量
		user, ok := c.Get("user")
		// 类型断言
		realUser, ok := user.(User)
		fmt.Println("%p", c)
		fmt.Println(realUser, ok)
	})
	router.Run(":80")
}

```

+ 运行结果演示：

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713022574681-1cc4899a-2bfe-4e38-96a0-ca45874a657a.png)

### 路由分组
+ 就是根据路由控制的功能给路由分组,每一个组的路由执行的任务不同,分组的方法 api = router.Group,并且api之后还可以继续分组来表示不同的业务逻辑
+ 细节: 用户访问时访问的路径前面还要加上api或者其他数据,利用api.GET（）指定请之后的操作
+ 代码演示: 

```go
package main

import "github.com/gin-gonic/gin"

// 定义需要使用的函数
type UserInfo struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
}
type Article struct {
	Title   string `json:"title"`
	Content string `json:"content"`
}

// 定义一个返回值
type Response struct {
	Code int    `json:"code"`
	Data any    `json:"data"`
	Msg  string `json:"msg"`
}

// 定义路由分组的操作
func UserList(c *gin.Context) {
	c.JSON(200, Response{
		Code: 0,
		Data: []UserInfo{
			{
				Name: "张三",
				Age:  12,
			},
			{
				Name: "李四",
				Age:  18,
			},
		},
		Msg: "响应成功",
	})

}

func ArticleList(c *gin.Context) {
	c.JSON(200, Response{
		Code: 0,
		Data: []Article{
			{
				Title:   "java",
				Content: "java从入门到放弃",
			},
			{
				Title:   "python",
				Content: "python从入门到放弃",
			},
		},
		Msg: "响应成功",
	})
}
func UserControl(api *gin.RouterGroup) {
	// 定义一些操作用户的方法
	usermanager := api.Group("user")
	{
		// 定义一个路由方法
		usermanager.GET("/users", UserList)
	}
}
func ArticleControl(api *gin.RouterGroup) {
	// 定义一个操作文章的方法
	articles := api.Group("article")
	{
		// 定义一个操作文章的方法
		articles.GET("/articles", ArticleList)
	}
}
func main() {
	router := gin.Default()
	api := router.Group("api") // 返回的就是一个路由组
	UserControl(api)
	ArticleControl(api)
	router.Run(":80")
}

```

### 路由分组注册中间件
注意事项如下:

    1. 首先注意注册全局中间件的方法: 直接在注册得到的路由组之后利用use方法就可以得到了想要的一个独属于这一个分组的路由中间件了
    2. 注意注册的中间件只在这一个组中生效,中间件具有传递的作用,只要归属于这个组的其他组都可以使用这一个中间件
    3. 另外 就是带上括号的中间件了,这一类中间件其实必须需要 返回一个gin.Handlefunc,也就是一个不到括号的中间件(匿名函数),好处 时可以使用闭包

代码演示：

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

type Res struct {
	Code int    `json:"code"`
	Data any    `json:"data"`
	Msg  string `json:"msg"`
}

// 用户数据
type Userinfo struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
}

// 返回一个列表,下划线开头的函数表示可以忽略这个函数可以重复定义
func _UserList(c *gin.Context) {
	c.JSON(200, Res{
		Code: 0,
		Data: []Userinfo{
			{
				Name: "张三",
				Age:  12,
			},
			{
				Name: "李四",
				Age:  18,
			},
			{
				Name: "王五",
				Age:  32,
			},
		},
		Msg: "响应成功",
	})
}

// 定义一个函数进行用户管理
func _Usercontrol(router *gin.RouterGroup) {
	usermanager := router.Group("users")
	// 注册全局中间件
	usermanager.Use(Middleware("响应失败啦 ......"))
	{
		usermanager.GET("/user", _UserList)
	}
}
func _TestMiddle(c *gin.Context) {
	fmt.Println("测试中间件执行了")
}

// 开始定义一个全局中间件
func Middleware(msg string) gin.HandlerFunc {
	// 这就是中间件的返回值
	return func(c *gin.Context) {
		// 首先拿到token
		token := c.GetHeader("token") // Header函数的作用时设置响应头
		if token == "1234" {
			// 向后面响应
			c.Next()
			return
		}
		c.JSON(200, gin.H{"msg": msg})
		c.Abort()
	}

}

// 中间件
func main() {
	// 演示给分组之后的路由注册中间件
	// 中间件的注册方式
	// 只需要分组时创建中间件该组中的中间件就可以使用了
	// 另外就是中间件的另外一种写法 直接利用 middleware()  但是需要返回一个 gin.HandlerFunc
	router := gin.Default()
	api := router.Group("api")
	api.Use(_TestMiddle)
	_Usercontrol(api)

	// 另外如果不使用中间件的情况
	api.GET("/not", func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "你居然不回走用户管理"})
	})
	router.Run(":80")
}

```

### gin.Default()函数
+ gin.Default的底层调用了gin.New()函数,同时New函数绑定了Logger()函数和Recovery()函数,分别用于日志的打印和信息回滚,但是如果利用New()函数需要自己设置日志的打印方式
+ 底层代码演示:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713078189194-3df35623-81b6-4976-bdd0-d2e4041979ca.png)

## 日志
+ 使用日志的原因:
    - 记录用户操作,方便猜测用户行为
    - 记录bug的位置

### gin自带的日志系统
#### 首先进行路由的重定向
+ 路由默认是打印在控制台上比如: 

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713079083212-3aa6e3fe-c0d6-4d40-855b-27c0aaf8e984.png)

+ 可以自己创建一个文件,把路由文件的打印方向重定向到新的一个文件中,设置的代码如下(在 gin.Defalut之前加上重定向打印日志的功能)

```go
    file, _ := os.Create("gin.log")
	gin.DefaultWriter = io.MultiWriter(file) // 这就是默认打印的重定向
```

+ 结果演示:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713079193380-4f7fbab4-7c39-4c47-8c73-522f0ee9cd3a.png)

#### 自定义路由打印的格式的方法
+ 直接操作路由打印的方法,是否类似于一个方法重写?,直接重定义另外一个方法,设置打印格式,代码演示如下:

```go
package main

import (
	"github.com/gin-gonic/gin"
	"io"
	"log"
	"os"
)

func main() {
	// 用于演示gin自带的日志系统
	// 自定义路由的格式
	gin.DebugPrintRouteFunc = func(httpMethod, absolutePath, handlerName string, nuHandlers int) {
		log.Printf("[ loser ] %v %v %s %d", httpMethod, absolutePath, handlerName, nuHandlers)
	}
	file, _ := os.Create("gin.log")
	gin.DefaultWriter = io.MultiWriter(file) // 这就是默认打印的重定向
	router := gin.Default()
	// 配置参数打印日志到文件系统
	router.GET("/index", func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "响应成功"})
	}) // 日志会默认打印到控制台中

	router.Run(":80")
}

```

+ 结果演示：

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713079311492-dba1497c-a8bc-4c3c-8de7-c759bc1bf442.png)

#### 自定义打印结果演示
+ 自定义打印结果其实就是重新定义一个一个日志的打印方式，使得日志打印更加直观\
+ 此时需要把原来的Debug模式改为ReleseMode模式从而更好地打印日志
+ 颜色的分析: 首先打印颜色,之后打印状态码,最后打印颜色即可
+ 代码演示如下:

```go
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
)

func main() {
	// 用于演示gin自带的日志系统
	// 自定义路由的格式
	//gin.DebugPrintRouteFunc = func(httpMethod, absolutePath, handlerName string, nuHandlers int) {
	//	log.Printf("[ loser ] %v %v %s %d", httpMethod, absolutePath, handlerName, nuHandlers)
	//}
	//file, _ := os.Create("gin.log")
	//gin.DefaultWriter = io.MultiWriter(file) // 这就是默认打印的重定向
	// 设置模式不为调试模式
	gin.SetMode(gin.ReleaseMode)

	router := gin.New()
	router.Use(gin.LoggerWithFormatter(func(params gin.LogFormatterParams) string {
		// 自定以一个打印日志
		return fmt.Sprintf(
			"[FENG] %s|%s %d %s| %s %s %s %s\n",
			params.TimeStamp.Format("2006-01-02 15:04:05"),
			params.StatusCodeColor(), params.StatusCode, params.ResetColor(),
			params.MethodColor(), params.Method, params.ResetColor(), // 用于输出颜色
			params.Path,
		)
	}))
	// 配置参数打印日志到文件系统
	router.GET("/index", func(c *gin.Context) {
		c.JSON(200, gin.H{"msg": "响应成功"})
	}) // 日志会默认打印到控制台中
	fmt.Println(router.Routes()) // 上面的函数其实就是回调函数
	router.Run(":80")
}

```

+ 结果演示:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713080406619-d5cc9d45-034a-492d-a76d-6818074caa88.png)

#### 查看路由:
+ 就是利用router.routers()函数就可以获取日志组成的集合了

### 日志框架Logrus
#### 引入方式
:::info
 go get github.com/sirupsen/logrus

:::

#### 基本使用
+ 可以打印出来同等级的日志信息 （Error Warnln Infof Debug Println），但是需要注意低于默认等级的日志信息就不会被打印出来
+ 可以利用GetLevel获取日志等级,可以利用SetLevel设置日志等级
+ 代码演示：

```go
package main

import (
	"fmt"
	"github.com/sirupsen/logrus"
)

func main() {
	// 演示Logrus功能
	logrus.SetLevel(logrus.WarnLevel) // 设置打印等级,只有warn等级和error等级的日志才会输出
	// 日志的等级基本和生产环境相似
	logrus.Error("出错信息")
	logrus.Warnln("警告")
	logrus.Infof("信息")
	logrus.Debug("调试信息")
	logrus.Println("打印日志信息")
	// 如果等级比Infof小的话就不会输出了

	fmt.Println(logrus.GetLevel())
}

```

#### 给日志信息设置特定的字段名称（参数）
+ 可以利用Logrus.WithField方法设置参数,同时可以使用Log.WithFields()方法设置参数,但是注意后面一个方法需要的一个参数就是 logrus.fields{}
+ 代码演示：

```go
package main

import (
	"github.com/sirupsen/logrus"
	"time"
)

func main() {
	// 可以指定每一条日志的信息,可以使用键值对表示
	log := logrus.WithField("func", "app").WithField("time", time.Now())
	log.Error("出错啦 ......")
	// 还可以使用创建对象的方法定义一个数据
	log1 := logrus.WithFields(logrus.Fields{
		"user_id": "111",
		"ip":      "192.168.0.233",
	})
	log1.Error("log1出错啦")
}

```

+ 运行结果演示:

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713082571441-b0450c7a-8c26-425d-8f88-0fc19dd01487.png)

#### 显示特定格式
+ 设置格式为json格式,可以直接利用logurs.SetFormatter( logrus.JSONFormatter{})
+ 设置颜色和时间戳使用在TextFormatter中打开 响应的配置信息即可,并且不同的等级的颜色不同
+ 颜色的设置可以使用 ASCI转义字符,如果像颜色这样的顺次定义的概念可以使用枚举 const集合,可以结合枚举结合打印函数进行输出(定义一个函数，传递相应的枚举名称就可以输出对应的颜色即可)
+ 代码演示如下:

```go
package main

import (
	"github.com/sirupsen/logrus"
	"time"
)

func main() {
	// 可以指定每一条日志的信息,可以使用键值对表示
	// 指定格式为json
	logrus.SetFormatter(&logrus.JSONFormatter{}) // 得到的就是一个json格式的数据
	logrus.SetFormatter(&logrus.TextFormatter{
		ForceColors:     true,                  // 设置颜色的方法，每一中等级的颜色可以不一样
		FullTimestamp:   true,                  // 设置时间戳格式
		TimestampFormat: "2006-01-02 15:04:05", // 设置时间输出格式
	})
	log := logrus.WithField("func", "app").WithField("time", time.Now())
	log.Error("出错啦 ......")
	log.Warnln("警告 ......")
	log.Debug("调试 ......")
	log.Infof("重要信息 ......")
	// 还可以使用创建对象的方法定义一个数据
	log1 := logrus.WithFields(logrus.Fields{
		"user_id": "111",
		"ip":      "192.168.0.233",
	})
	log1.Error("log1出错啦")
}

```

+ 结果演示

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713083085440-8a750dae-b601-4ba5-abdb-0873e13b5d46.png)

### 自定义日志格式
#### 输出日志信息到文件中
+ 设置文件输出的位置的方法主要就是使用Setoutput方法,之后的参数就是重定向之后的位置,可以是文件输入流io,也可以是标准输出流 stdout
+ 代码如下:

```go
package main

import (
	"github.com/sirupsen/logrus"
	"io"
	"os"
)

func main() {
	// 日志重定向到文件中,注意路径的选择
	file, _ := os.OpenFile("/info.log", os.O_CREATE|os.O_APPEND, 0666) // 用于指定文件的权限和读写
	//logrus.SetOutput(file)
	// 同时设置日志的方向为文件和控制台
	logrus.SetOutput(io.MultiWriter(file, os.Stdout)) // 标准输出流和文件中都有日志啦,这一支持可变参数
	// 开始输出
	logrus.Error("出错啦")
	logrus.Warnln("警告啦")
	// ln结尾的就是自动换行
	logrus.Infof("重要信息")

}

```

+ 结果演示：

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713084943498-f5ea7e8b-282a-4bf7-8713-7a09cd5986f7.png)

#### 自定义输出格式
+ 看一下前面定义格式的方法,这里需要定义自己的formatter格式,这里就是利用一个结构体定义一个formatter,这一个结构体需要实现Format方法才可以被使用,Format方法中的一个参数就是entry，相当于当前操作的对象,具体操作如下,返回值必须是一个字节数组
+ 显示行号只需要从entry中取出行号对象即可 entry.Caller.File和entry.Caller.Line
+ 另外注意空结构体中可以承装对象,盛装的对象可以用于自定义信息的显示
+ 代码演示 :

```go
package main

import (
	"bytes"
	"fmt"
	"github.com/sirupsen/logrus"
	"path"
)

const (
	CBlack = iota
	CRed
	CGreen
	CYellow
	CBlue
	CPurple
	CCyan
	CGray
)

type MyFormatter struct {
	// 首先设置颜色
	prefix   string
	fomatter string
}

// 重写Formatter方法
func (f MyFormatter) Format(entry *logrus.Entry) ([]byte, error) {
	// 设置颜色,entry表示当前对象
	var color int
	switch entry.Level {
	case logrus.ErrorLevel:
		color = CRed
	case logrus.WarnLevel:
		color = CYellow
	case logrus.InfoLevel:
		color = CGreen
	case logrus.DebugLevel:
		color = CPurple
	default:
		color = CGray
	}
	// 设置缓冲区
	var b *bytes.Buffer
	if entry.Buffer == nil {
		// 初始化
		b = &bytes.Buffer{}
	} else {
		b = entry.Buffer
	}
	// 设置时间格式
	format := entry.Time.Format(f.fomatter)
	// 设置文件的行号等信息
	// entry中的信息挺全的
	finVal := fmt.Sprintf("%s %d", path.Base(entry.Caller.File), entry.Caller.Line) // 设置行号的显示
	// 设置路径
	fmt.Fprintf(b, "[%s] \033[3%dm[%s]\033[0m [%s] %s %s\n", f.prefix, color, entry.Level, format, entry.Message, finVal)
	return b.Bytes(), nil
}
func main() {
	// 还是需要利用setFormatter方法定义格式
	// 开启行号显示
	logrus.SetReportCaller(true)
	logrus.SetLevel(logrus.DebugLevel)
	logrus.SetFormatter(&MyFormatter{prefix: "GORM", fomatter: "2006-01-02 15:04:05"})
	logrus.Error("出错啦")
	logrus.Debug("调试啦")
	logrus.Infof("信息来啦")
	logrus.Warnln("警告")
}

```

+ 结果演示：

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1713086967779-00f63206-4bb8-4fce-800c-f83d5424e83b.png)

### Hook机制
+ Hook机制,通过初始化时为logrus添加hook,logrus可以实现各种拓展功能
+ Hook其实就是一个接口,接口中的属性包含功能覆盖的字段和entry对象
+ 实现的Levels方法返回的就是一个类型切片,这个类型切片中可以定义需要操作的类型,Fire函数就是对已经选择的类型进行操作的函数
+ 代码演示如下:

```go
package main

import (
	"fmt"
	"github.com/sirupsen/logrus"
	"os"
)

type MyHook struct {
}

// 注意事项方法 Levels 和 Fire
func (MyHook) Levels() []logrus.Level {
	// 设置生效范围
	return []logrus.Level{logrus.ErrorLevel}
}
func (MyHook) Fire(entry *logrus.Entry) error {
	// 定义打印信息时的行为
	fmt.Println(entry.Level)
	// 还可以设置属性
	//entry.Data["app"] = "hello"
	// 实现把错误日志写入到文件中
	file, _ := os.OpenFile("error.log", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666)
	line, _ := entry.String()
	file.Write([]byte(line)) // 写入信息到文件中
	return nil
}
func main() {
	logrus.AddHook(&MyHook{})
	logrus.Warnln("警告")
	logrus.Error("错误")
}

```

## 日志分割
### 日志时间分割
待定

## gin框架集成logrus




