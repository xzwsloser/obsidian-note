# 前言
>参考: [[https://gorm.io/zh_CN/docs/method_chaining.html](https://gorm.io/zh_CN/docs/method_chaining.html)]]

## ORM
+ orm是一种对象关系映射,它解决了对象和关系型数据库之间的数据交互内容,简单来说就是利用一个类来表示一张表,类中的属性表示表中的字段，使用操作对象的方法操作数据库与自己手动编写sql相比,优势更加明显,但是自动生成sql语句还是会对性能有一些影响,一般比较复杂的数据库还是需要自己编写sql语句

## 下载gorm框架并且连接数据库
### 下载gorm框架的依赖
```go
go get gorm.io/driver/mysql   // 下载mysql的驱动
go get gorm.io/gorm   // 下载gorm框架

go get github.com/jinzhu/gorm // 另外一个up主的方法,最好利用上面一个方法导入mysql的驱动
```

+ 下载完成之后的go mod

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712415530769-0bb973c5-1e68-41fe-9800-99d3a596e904.png)

### 连接数据库的操作
1. 具体方法: 利用gorm.Open方法连接数据库
2. 细节: 注意参数的设置 “用户名：密码@tcp(ip:port)数据库名称/charset=utf8&parseTime=True&loc=Local ,还需要导入mysql的驱动 github.com/jinzhu/gorm/dialects/mysql
3. 代码演示如下:

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql" // 加载mysql的驱动,前面加上一个_表示忽略内容
)

func main() {
	// 1. 连接数据库  test_jdbc
	// Open的参数,需要出入两个信息:
	// 参数1: 需要连接的数据库
	// 参数2: 指的是数据库的设置信息,利用键值对的形式传参： 用户名:密码@tcp(ip:port/数据库名称)?charset=utf8&parseTime=True&loc=Local
	// charset指定使用的字符集
	// parseTime表示处理time.Time类型
	// loc = local表示设置本地时区  注意使用的open函数第一个参数为 dialect
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	// db的类型是一个指针,具体作用是之后再说
	if err != nil {
		fmt.Println("数据库连接失败")
		panic(err) // 利用panic可以结合错误终止程序
	}
	defer db.Close()  // 注意利用演示函数释放空间
}

```

## 创建表,删除表,判断表是否存在
+ 利用 db.CreateTable(&结构体{}）方法创建表 利用db.Table(表名).CreateTable(&结构体{}) 创建表
+ 利用db.dropTable(&结构体{})删除默认创建的表 db.dropTable(表名)删除表
+ 利用db.HasTable(&结构体{})查看是否存在利用默认创建的表，利用db.HasTable(表名)通过表名判断是否有删除的表

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql" // 加载mysql的驱动,前面加上一个_表示忽略内容
)

// 定义一个结构体进行映射
type User struct {
	Name string
	Age  int
}

func main() {
	// 1. 连接数据库  test_jdbc
	// Open的参数,需要出入两个信息:
	// 参数1: 需要连接的数据库
	// 参数2: 指的是数据库的设置信息,利用键值对的形式传参： 用户名:密码@tcp(ip:port/数据库名称)?charset=utf8&parseTime=True&loc=Local
	// charset指定使用的字符集
	// parseTime表示处理time.Time类型
	// loc = local表示设置本地时区  注意使用的open函数第一个参数为 dialect
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	// db的类型是一个指针,具体作用是之后再说
	if err != nil {
		fmt.Println("数据库连接失败")
		panic(err) // 利用panic可以结合错误终止程序
	}
	defer db.Close() // 注意利用演示函数释放空间
	// 创建一个表
	// 通常情况下,创建的表名就是结构体的复数形式,但是小写
	db.CreateTable(&User{}) // 利用对象映射出一个表,名称都是默认的
	// 自己指定表的名称,利用Table方法指定表名
	db.Table("myusers").CreateTable(&User{}) // 感觉提供对象用于反射
	// 删除表名
	db.DropTable(&User{}) // 删除一个表,但是只可以删除利用原始名称创建的一张表
	// 通过名称删除表
	db.DropTable("myusers")        // mysql中都是小写的
	flags1 := db.HasTable(&User{}) // 判断是否有第一种方式创建的表
	fmt.Println(flags1)
	flags2 := db.HasTable("myusers") // 通过名称判断
	fmt.Println(flags2)
}

```

## 数据库的增删改查
+ 首先创建一个结构体对象 var myUser User
+ 增加数据   db.Create(&User{Name:"张三",Age:19})
+ 查询数据 db.First(&myUser,"age = ?" ,19)  // 利用占位符提供的条件
+ 修改数据 必须在得到数据之后进行修改: db.Model(&myUser).Update("字段名称",修改之后的值)
+ 删除数据 还是在查询之后 进行: db.Delete(&myUser) // 其实就是删除对应查询到的字段,无论是删除还是更新,首先要得到需要操作的一行数据(其实就是查询这一行记录)

```go
	// 数据库的增删改查方法
	// 增加:
	db.Create(&User{Name: "张三", Age: 18})
	// 查询数据
	var myUser User
	db.First(&myUser, "age = ?", 18)
	fmt.Println(myUser)
	// 更新数据
	// 首先查询之后更新
	db.Model(&myUser).Update("age", 23)
	db.Model(&myUser).Update("name", "李四")
	// 删除数据
	// 还是需要先查询之后删除
	db.Delete(&myUser)
```

## 对于表名的阐述: 
### 模型名和表名的映射规则
#### 模型名和表名的映射规则如下:
1. 如果模型名没有驼峰命名,那么模型名就是 小写+复数形式 （user -> users）
2. 如果模型名有驼峰命名，那么表名就是变成小写之后大写字段前面加上_ (UserInfo -> user_info)
3. 如果有连续的大写和驼峰命名,就会将大写变为小写在驼峰的头部加上 _ (DBUSerInfo -> db_user_info)

### 自定义表名
+ 需要自定义表名只用重写TableName方法就可以了,毕竟go语言中实现接口只用实现其中方法就可以了

```go
type User struct {
	Name string
	Age  int
}

func (user *User) TableName() string {
	return "test_user_name"
}
```

## gorm.Mobel匿名字段
+ 作用: 其实就是默认给自己的表添加另外四个字段，就是添加gorm.model字段之后默认添加了四个字段： ID,CreateAt,UpdatedAt,DeletedAt字段
+ ID : 主键自增长
+ CreateAt: 用于记录存储记录的创建时间
+ UpdatedAt: 用于存储记录的修改时间
+ DeletedAt: 用于记录删除记录的时间

```go
type User struct {
	Name string
	Age  int
	gorm.Model
}

```

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712502125604-e6fbe294-cd82-4ec8-b762-83f6dd178108.png)

## 结构体标签gorm
+ gorm标签的作用: 给表中的字段添加索引和各种约束,以及指定初始值
+ 语法: `gorm:"条件1;条件2;待设置的属性:属性值`
+ 代码演示如下:

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

type Student struct {
    // 其实就是 利用`gorm:"约束1;约束2;约束3;索引:索引名称;长度:长度值"
    // 和gin框架中的json标签的作用类似
	StuID int    `gorm:"primary_key;AUTO_INCREMENT"` // 设置主键,自增
	Name  string `gorm:"not null"`
	Age   int    `gorm:"index:name_index"`     // 创建索引时可以添加一个名字,只用利用 : 指定索引名称即可
	Email string `gorm:"unique_index"`         // 创建唯一索引
	Sex   string `gorm:"unique;column:gender;size:10"` // 添加一个唯一约束,同时利用column:指定列名,利用size设置默认长度
	Desc  string `gorm:"-"`                    // 表示直接在数据库中忽略
	classID string `gorm:"type:int"`  // 定义一个类型
}

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		fmt.Println("数据库连接失败")
		panic(err)
	}
	defer db.Close()
	db.CreateTable(&Student{})
}

```

## gorm框架中各种表之间的映射关系
### 一对一映射
+ 其实就是一个表对应一张表，并且是一一对应的,就是利用外键关联别人的主键，并且这个外键也是唯一的
+ 方式1: 类中指定字段和外键名称,但是需要规范外键名称
+ 方式2： 利用gorm标签 gorm:"ForeignKey:外键字段名;AssociationForeKey:UserId" 后面一个需要规范命名
+ 注意的规范就是: 需要关联的对象实例 需要关联的对象类型名 'gorm:"ForeignKey:需要关联的外键(其实就是需要关联对象中的一个键);AossicationForeignKey:自己的一个字段名称"  // 这样的话 ForeignKey就是关联了AssociationForeignKey了

代码演示

```go
-- 结构体
package main

type User struct {
	id   int `gorm:"primary_key;AUTO_INCREMENT"`
	Name string
	Age  string
	// 关联写下面一个字段,指定关系不在同一个表示包含关系
	IID int
}
type UserInfo struct {
	InfoID  int `gorm:"primary_key;AUTO_INCREMENT"`
	Pic     string
	Address string
	Email   string
	// 关联关系
	User User `gorm:"ForeignKey:IID;AssociationForeignKey:InfoID"` // 注意之后的字段名称的写法
	// 含义就是外键是其他表中关联的键,但是关联的外键就是自己的键
    // 我感觉突然明白了外键名称和外键字段名称之间的关系
	// 指定外键,只用在关联关系之后指定外键
	// UserID int // 相当于创建一个字段作为外键,其实并没有强制加入外键,只是建立了关联关系
	// 如果用上面的方法定义名称一定要是 表名 + 主键名
	
}
-- 建表
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 创建表,注意两个表都要创建并且两个表部分顺序
	db.CreateTable(&User{})
	db.CreateTable(&UserInfo{})
	// 建立关联关系

}

```





### 一对多
+ 一个表对应另外一个表中的多个字段,就是外键不一定有唯一约束或者主键约束
+ 首先创建两个结构体,把作为一的一个结构体的中的一个成员写成另外一个对应多的结构体组成的数组，另外利用gorm标签添加外键约束即可
+ 代码演示如下:

```go
package main

type Author struct {
	AID  int `gorm:"primary_key;AUTO_INCREMENT"`
	Name string
	Age  int
	Sex  string
	// 关联关系
	Article []Article `gorm:"ForeignKey:AuId;AssociationForeignKey:AID"` // 建立外键约束
}

type Article struct {
	ArdId   int
	Title   string
	Content string
	Desc    string // 表示结构
	// 设置外键: 如上
    /**
    创建之后字段不会显示,而是默认就会添加一个外键约束,用于多表查询
    */
    AuId int  // 这就是外键,基本和上面的方法一致,一般外键和主键不一样

}

```



### 多对多
+ 类似学生和课程表之间的关系，需要一张中间表进行操作，中间表的中两个外键分别关联两张表
+ 常见过程基本和一对多类似,但是需要改变后面的gorm标签,把gorm标签改为多表的情况，同时必须添加主键约束作为中间表的字段 （gorm:"many2many:Student2Course)
+ 注意此时创建关联的方式: 直接利用标签进行创建,但是因为中间表中的两个字段都是两个表中的主键,所以应该设置主键自增 gorm:"many2many:Student2Course"
+ 此时查询的操作在学生表中进行可以
+ 代码演示：

```go
package main

// 学生表
type Student struct {
	SId  int `gorm:"primary_key;AUTO_INCREMENT"` // 此时一定需要指定主键,否则就不会生成一个表
	SNo  int
	Name string
	Sex  string
	Age  int
	// 开始关联一个表
	Course []Course `gorm:"many2many:Student2Course"` // 其实就是一对多的外键约束改成了一个标签约束
}

// 课程表
type Course struct {
	CId         int `gorm:"primary_key;AUTO_INCREMENT"`
	CName       string
	TeacherName string
	Room        string
}

```

+ 结果演示

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712586875709-8bb7330b-8dc9-4c06-840c-784dc53debb8.png)

## 与映射关系有关的各种表的操作
### 与一对一关系有关的操作
#### 添加关联操作
+ 总结以下其实就是初始化其中一个实例对象,就是其中有一个成员是两外一个结构体的哪一个对象
+ 总结一下外键创建方法,gorm标签中，外键名称就是另外一个表中你要关联的字段，association后面的就是本表中的字段，其实三种关联方式大同小异
+ 直接初始化一个对象,利用create方法create(&struct)即可得对应效果
+ 代码演示如下

```go
// 结构体创建
package main

type User struct {
	id   int `gorm:"primary_key;AUTO_INCREMENT"`
	Name string
	Age  int
	// 关联写下面一个字段,指定关系不在同一个表示包含关系
	IID int // 最为外键
}
type UserInfo struct {
	InfoID  int `gorm:"primary_key;AUTO_INCREMENT"`
	Pic     string
	Address string
	Email   string
	// 关联关系
	User User `gorm:"ForeignKey:IID;AssociationForeignKey:InfoId"` // 注意之后的字段名称的写法,其实就是给原来的外键起别名	// 我感觉突然明白了外键名称和外键字段名称之间的关系
	// 动一下脑子想一下,外键要关联的对象是什么
	// 指定外键,只用在关联关系之后指定外键
	// UserID int // 相当于创建一个字段作为外键,其实并没有强制加入外键,只是建立了关联关系
	// 如果用上面的方法定义名称一定要是 表名 + 主键名

}
// 具体操作
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 创建表
	db.CreateTable(&User{})
	db.CreateTable(&UserInfo{})
	// 对于一对一映射的操作: 关联添加数据
	userInfo := UserInfo{
		Pic:     "/upload/hello.png",
		Address: "湖北武汉",
		Email:   "111222",
		User: User{
			Age:  18,
			Name: "张三",
		},
	}
	// 开始添加数据
	db.Create(&userInfo) // 创建即可,注意接口的妙用,直接添加一个数据就可以添加数据

}

```

#### 查询数据
+ 其实查询数据的逻辑就是首先利用Id查到主键,之后利用主键作为外键查询数据
+ 注意首先查询主键的操作必不可少，之后查询外键的操作依赖于 查询逐渐的操作
+ 主键： db.First(&myUser,条件,占位符) 外键 db.Model(&userInfo).Asscation("关联的结构体名").Find(&userInof.User) 
+ 利用Debug查看原生sql
+ 代码演示：

```go
package main
/**
 查询方式： 
     1. 	首先查询主键
        db.First(&userinfo,条件)
         db.Model(&userinfo).Association("User").Find(&userinfo.User) 
    2. 利用preload方法进行查询
        db.PreLoad("User").First(&userinfo,"条件")
    3. 利用Related查询
        // 首先查询主键
        db.First(&useinfo,条件)
        db.Model(&userinfo).Relate(&user,"User")
    */
import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 创建表
	/*db.CreateTable(&User{})
	db.CreateTable(&UserInfo{})*/
	//// 对于一对一映射的操作: 关联添加数据
	//userInfo := UserInfo{
	//	Pic:     "/upload/hello.png",
	//	Address: "湖北武汉",
	//	Email:   "111222",
	//	User: User{
	//		Age:  18,
	//		Name: "张三",
	//	},
	//}
	//// 开始添加数据
	//db.Create(&userInfo) // 创建即可,注意接口的妙用,直接添加一个数据就可以添加数据
	// 查询操作
	// 关联关系再UserInfo中，所以查询也要在UserInfo中
	var userInfo UserInfo
	db.Debug().First(&userInfo, "info_id = ?", 1)
	// 如果执行上面操作得不到User信息
	fmt.Println(userInfo)
	// 如果得到User,就要执行下面的信息,注意两个都需要执行,利用Debug可以找到对应的sql语句
	db.Debug().Model(&userInfo).Association("User").Find(&userInfo.User) // 其实就是查询得到的字段应该存储到哪里
	fmt.Println(userInfo)

}

```

 ![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712588701449-026f9fef-5e16-4578-a4b6-b55980da9033.png)

##### 利用preLoad查询
+ 就是利用preLoad提前 加载 db.Debug().preLoad("User").Find(&userInfo,条件,占位符号)
+ 但是原理还是两个sql

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 利用preLoad函数进行一次查询
	var userInfo elemType.UserInfo
	db.Debug().Preload("User").Find(&userInfo, "info_id = ?", 1)
	fmt.Println(userInfo)

}

```

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712589396363-39d07e2c-5016-44a5-ac0a-fb5838133af9.png)

##### 利用Related函数查询
+ 其实就是构建一个新的User把信息 单独存入到这个对象中
+ 首先还是要得到userInfo对象，之后 db.First(&userInfo).Related(&user,"User")
+ 代码演示：

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 利用relate方法进行查询
	var userInfo elemType.UserInfo
	db.First(&userInfo,"info_id = ?",1)
	
	var user elemType.User
	// 其实就是构建一个新的容器
	// 但是可以把这个字段单独存储
	// 通过userInfo模型查出来的User字段信息放入到新的user容器中
	db.Model(&userInfo).Related(&user,"User"); 

}

```

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712589887585-dfe675f1-34b1-4e78-9b59-fd36ad749dce.png)

#### 关联更新
+ 还是利用model指定操作对象,之后利用Update方法进行操作
+ 代码演示

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示关联更新操作
	// 1. 首先查询数据
	var userInfo elemType.UserInfo
	db.Preloads("User").First(&userInfo, "info_id = ?", 1)
	fmt.Println(userInfo)
	// 先查询之后更新
	db.Model(&userInfo.User).Update("age", 12) // 其实就是进行一个关联更新
	fmt.Println(userInfo)

}

```

##### 关联删除操作
+ 首先明白关联的市值就是在一个结构体中定义另外一个变量,这一个变量就可以用于更新删除操作,其实 struct1.struct2就是一个结构体
+ 利用deleted方法删除
+ 代码演示

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示删除操作
	var userinfo elemType.UserInfo
	db.Preload("User").Find(&userinfo, "info_id = ?", 1)
	// 开始删除
	// 可以根据userinfo模型删除User记录
	db.Delete(&userinfo.User) // 但是userinfo中的信息没有被删除
	// 如果要删除全部 就可以之间删除
	db.Delete(&userinfo)

}

```

### 一对多的表的操作
#### 关联添加
+ 前面结构体的创建是错误的
+ 结构体的创建和添加字段的代码如下

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 用于演示关联添加操作
	// 一个作者对象多个关系，操作作者表即可
	author := elemType.Author{
		Name: "张三",
		Age:  30,
		Sex:  "男",
		Article: []elemType.Article{
			{
				Title:   "hello world",
				Content: "你好 世界",
				Desc:    "没有", // 关联外键
			},
			{
				Title:   "hello css",
				Content: "你好 css",
				Desc:    "有", // 关联外键
			},
		},
	}
	db.Create(&author)

}
-- 结构体
package elemType

type Author struct {
	AID  int `gorm:"primary_key;AUTO_INCREMENT"`
	Name string
	Age  int
	Sex  string
	// 关联关系
	Article []Article `gorm:"ForeignKey:AuId;AssociationForeignKey:AID"` // 建立外键约束
}

type Article struct {
	ArId    int
	Title   string
	Content string
	Desc    string // 表示结构
	// 设置外键:
	AuId int
}
```

#### 关联查询
+ 基本和一对多关系一致,至少Assciation方法和PreLoad方法一致，Related方法唯一不同就是关联对象不同,这里关联的就是一个切片

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 用于演示一对多查询操作
	// Association方式
	// 必须操作Author
	//var author elemType.Author
	//db.First(&author,"a_id = ?",1)
	//fmt.Println(author)
	//db.Model(&author).Association("Article").Find(&author.Article)
	//fmt.Println(author)
	// 利用PreLoad方式查询
	//var author elemType.Author
	//db.Preloads("Article").Find(&author,"a_id = ?",1)
	// 利用Related方法进行查询
	var author elemType.Author
	var articles []elemType.Article
	// 首先查询
	db.First(&author, "a_id = ?", 1)
	// 唯一不同点就是这里用一个切片接收信息
	db.Model(&author).Related(&articles, "Article") // 唯一不同就是使用切片接受
	fmt.Println(author)
	fmt.Println(articles)

}
```

#### 关联更新
+ 基本操作和上面一致，但是需要利用where条件限定(db.Model(操作对象).Where(条件).Update(字段名,新的值)
+ 代码演示

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 首先查询之后更新
	var author elemType.Author
	db.Preload("Article").Find(&author,"a_id = ?",1)
	// 如果直接利用update操作,关联操作就会全部显现
	//db.Model(&author.Article).Update("title","java从入门到精通")
	// 必须加上一个更新操作
	// 需要加上一个条件进行限定,利用where限定
	db.Model(&author.Article).Where("ar_id = ?",1).Update("title","python机器学习")
}

```

#### 关联删除
+ 还是基本和上面一致,但是一对多的模型,为了筛选出需要删除的模型,必须利用where函数过滤

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 首先查询之后更新
	var author elemType.Author
	db.Preload("Article").Find(&author, "a_id = ?", 1)
	// 查询之后删除
	db.Where("ar_di = ?", 2).Delete(&author.Article)
}


```

### 多对多
#### 关联添加
+ 还是一样的原- 则,关联关系在哪一个表中,就要创建那一个表的对象，直接创建

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 关联添加操作,关系在哪一个表中就要操作哪一个结构体
	stu := elemType.Student{
		SNo:  1002,
		Name: "张三",
		Sex:  "女",
		Age:  18,
		Course: []elemType.Course{
			{
				CName:       "python",
				TeacherName: "hello",
				Room:        "s111",
			},
			{
				CName:       "java",
				TeacherName: "olleh",
				Room:        "s111",
			},
		},
	}
	db.Create(&stu)
}

```

#### 查询,更新,删除操作
+ 基本和上面一致
+ 代码演示

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 查询操作
	var stu elemType.Student
	// 1. Association方法
	db.First(&stu, "s_id = ?", 1)
	db.Model(&stu).Association("Course").Find(&stu.Course)
	fmt.Println(stu)
	// 2. 利用preLoad方法
	db.Preload("Course").Find(&stu,"s_id = ?",1)
	fmt.Println(stu)
	//// 3. 利用Related方法
	var course elemType.Course
	db.Related(&course,"Course").Find(&stu.Course)
	// 更新操作
	// 1. 查询
	db.Preload("Course").Find(&stu, "s_id = ?", 1)
	db.Model(&stu.Course).Where("c_id = ?", 1).Update("c_name", "golang")
	// 2. 删除
	db.Preload("Course").Find(&stu, "s_id = ?", 1)
	db.Where("c_id = ?", 1).Delete(&stu.Course)
}

```

## gorm中的常见方法
### First,FirstOrCreate,Last,Take,Find方法
+ 都是用于查询的方法但是查询的方式和结果不同,看名字应该知道
+ 细节: golang中结构体中成员的私有或者公有化其实就是通过大小写字母确定的,一定要知道这一点
+ Find可以查询出多个方法
+ 代码演示:

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// First方法 sql  SELECT * FROM `users`  WHERE `users`.`user_id` = 1 AND ((user_id = 1)) ORDER BY `users`.`user_id` ASC LIMIT 1
	var userinfo elemType.UserInfo
	db.Debug().First(&userinfo, 1) // 后面就是主键,前面就是承装的对象
	fmt.Println(userinfo)
	var user elemType.User
	db.Debug().First(&user, 1)
	fmt.Println(user)
	// 利用Where方法
	db.Debug().Where("user_id = ?", 1).First(&user) // 也可以
	// 注意成员的共有和私有化
	// FirstOrCreate  如果有这个记录就会查询否则就会创建
	user1 := elemType.User{
		UserId: 1,
		Age:    19,
		Name:   "小明",
		IID:    1,
	}
	db.FirstOrCreate(&user, user1) // 后面就是一个默认值,前面还是一个容器
	fmt.Println(user)
	// First方法 sql  SELECT * FROM `users`  WHERE `users`.`user_id` = 1 AND ((user_id = 1)) ORDER BY `users`.`user_id` ASC LIMIT 1
	// Last方法,first中查询是升序查询,但是last是降序查询 sql
	db.Debug().Last(&user, 1)
	// Take方法: 没有进行排序  sql   SELECT * FROM `users`  WHERE `users`.`user_id` = 1 AND ((`users`.`user_id` = 1)) LIMIT 1
	db.Debug().Take(&user, 1)
	fmt.Println(user)
	// Find方法 按照条件进行查询,但是可以查询出多个记录,参数可以传递一个切片
	user_id_arr := []int{1, 2} // 后面其实就是一个条件切片

	db.Debug().Find(&user, user_id_arr)
	fmt.Println(user)
}

```

### Where和Select函数
+ Where用法: 其实就是限定条件,可以把条件写在前面,使用占位符,可以使用模糊匹配和区间匹配(Between,like,in)
+ Select用法: 其实就是指定需要查询出来的字段名称
+ 代码演示如下

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示Where方法
	user := []elemType.User{}
	user_arr_id := []int{1, 2}
	db.Where("user_id in (?)", user_arr_id).Find(&user)
	// 演示利用Select方法进行筛选
	// 其实就相当于需要查询出来的条件,其他条件不会被查出来
	db.Select("name,age").Where("user_id in (?)", user_arr_id).Find(&user)
	fmt.Println(user)
}

```

+ 运行结果演示

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712673220961-f5469e96-2314-4c85-a077-811b1f1a533f.png)

### Create和Save方法
+ 作用基本相同,都是用于插入数据,都只可以插入一次数据,不可以批量插入数据

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示create方法,只是可以插入单条记录
	user := elemType.User{
		Name: "李四",
		Age:  24,
		IID:  1,
	}
	db.Create(&user)
	// 演示Save方法,还是完成添加数据的操作
	users := elemType.User{
		Name: "赵六",
		Age:  12,
		IID:  1,
	}
	db.Save(&users)

}

```

### Update函数
+ 查询方式多种多样,可以直接进行链式操作,也可以利用model进行操纵
+ 注意interface{}类型相当于一个泛型,相当于java中的Object,空接口就是一个泛型

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示Update函数
	// 首先查询之后更新
	var user elemType.User
	db.Where("user_id = ?", 1).First(&user)
	// 1. 通过Model进行操作,指定操作对象
	db.Model(&user).Update("age", 22)
	fmt.Println(user) // 注意user也会发生改变
	// 2. 直接在查询之后操作
	db.Where("user_id = ?", 2).First(&user).Update("name", "bob")
	// 3. 还是直接在查询之后操作,但是可以利用结构体传入多个字段
	db.Where("user_id = ?", 1).First(&user).Update(elemType.User{
		Name: "小李",
		Age:  10,
	})
	// 4. 通过插入键值对的方法
	db.Where("user_id = ?", 2).First(&user).Update(map[string]interface{}{
		"age":  21,
		"name": "小花", // 其实后面的一个接口就相当于一个泛型,相当于一个Object对象
	})

}
)
```

### Delete函数
+ 两种方法进行删除操作

```go
package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示Delete函数
	// 1. 首先查询之后删除
	var user elemType.User
	db.Where("user_id = ?",1).First(&user)
	db.Delete(&user) 
	// 2. 直接利用条件删除
	db.Where("user_id = ?",2).Delete(&user)
}

```

### Not,Or,Order函数
+ Not: 用于排除条件
+ Or: 用于条件连接
+ Order: 用于对结果进行排序

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示Not函数  , 其实就是找出不满足条件的记录
	var user elemType.User
	db.Where("user_id = ?", 1).First(&user)
	var users []elemType.User
	db.Not("user_id = ?", 1).Find(&users)
	fmt.Println(users)
	// not中加上多个条件,含义就是找出不满足name=赵六,age=22的全部记录
	db.Not(elemType.User{
		Name: "赵六",
		Age:  22,
	}).Find(&users)
	fmt.Println(users)
	// 演示Or方法,其实就是条件的连接
	db.Where("user_id = ?", 1).Or("user_id = ? ", 3).Find(&users)
	fmt.Println(users)
	// 演示Order方法进行查询,其实就是进行升序后者降序按操作
	db.Not("user_id = ?", 1).Order("age asc").Find(&users)
	fmt.Println(users)
}

```

### Limit,Offset,Scan方法
+ limit和offset用于限定范围，scan用于结构体扫描
+ 代码演示

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 演示limit函数,用于限定查询所得记录的条数
	var users []elemType.User
	db.Not("user_id = ?", 1).Find(&users)
	fmt.Println(users)
	db.Not("user_id = ?", 1).Limit(2).Find(&users)
	fmt.Println(users)
	// 演示Offset函数,需要和limit函数一起使用,用于指定查询起点,从0开始
	db.Not("user_id = ?", 1).Offset(1).Limit(2).Find(&users)
	fmt.Println(users)
	// Scan方法,将结果扫描到另外一个结构 体中,扫描的必须是一致的
	type UserDemo struct {
		Name string
		Age  int
	}
	var userdemo UserDemo
	var user elemType.User
	db.Where("user_id = ?", 1).Find(&user).Scan(&userdemo)
	fmt.Println(user)
	fmt.Println(userdemo)
}

```

+ 结果演示

![](https://cdn.nlark.com/yuque/0/2024/png/40754486/1712675391360-f750e86e-e020-45d8-9ee6-d1cf47ebb725.png)

### Count,GROUP,Having方法
+ 基本和原生sql中的操作一致,含义一致

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 用于演示Count方法,进行计数
	var users []elemType.User
	// 定义一个变量接受结果,好像gorm框架中变量接受都需要定义一个结构体
	var count int
	db.Find(&users).Count(&count)
	fmt.Println(users)
	fmt.Println(count)
	// 一定要学会利用结构体接受数据,但是一定要注意结构体名和筛选出元素和结构体中元素的区别
	type GroupDemo struct {
		Age   int
		Count int
	}
	var group_date GroupDemo
	// 用于演示group函数进行查询,基本和原生sql中的操作一致
	db.Select("age,count(*) as Count").Group("age").Find(&users).Scan(&group_date)
	fmt.Println(users)
	fmt.Println(group_date)
	// Having: 用于分组之后的条件过滤
	db.Select("age,count(*) as Count").Group("age").Having("age > ?", 18).Find(&users).Scan(&group_date)
	fmt.Println(users)
	fmt.Println(group_date)
}

```

### 左连接,右连接
+ 首先回顾一下左连接和右连接的区别: 其实就是关联的两张表中有一些数据没有相互对应关系(其实就是没有在另外一张表中的映射关系),查询时选择性查询数据(有一张表的数据中的记录不全)
+ 利用Joins方法结合原生sql进行操作即可

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 用于演示左连接和右连接
	// 利用Joins方法进行操作
	// 常常利用Select方法和Scan方法定义一个新的结构体用于承装需要查询出来的字段,利用Scan方法进行扫描
	// 其实Joins方法中的条件就是sql中的条件
	var users []elemType.User
	db.Joins("left join user_infos on users.i_id = user_infos.info_id").Find(&users)
	fmt.Println(users)
}

```

### LogMode方法
+ 用于开启debug模式 ,展示 对应的sql语句
+ 代码演示

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 开启打印日志
	db.LogMode(true) // 其实就是默认加上debug模式
	// 用于演示左连接和右连接
	// 利用Joins方法进行操作
	// 常常利用Select方法和Scan方法定义一个新的结构体用于承装需要查询出来的字段,利用Scan方法进行扫描
	// 其实Joins方法中的条件就是sql中的条件
	var users []elemType.User
	db.Joins("left join user_infos on users.i_id = user_infos.info_id").Find(&users)
	fmt.Println(users)
}

```

## 原生sql操作
+ 操作的原生sql利用row函数指定
+ 删除,更新修改的原生sql利用exec演示
+ 代码演示:

```go
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"gomod/elemType"
)

func main() {
	// 连接数据库        "mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open("mysql", "root:808453@tcp(localhost:3306)/test_jdbc?charset=utf8&parseTime=true&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	// 开启打印日志
	db.LogMode(true) // 其实就是默认加上debug模式
	// 演示利用原生sql进行操作,就是利用Raw方法进行操作
	var users []elemType.User
	db.Raw("select* from users").Find(&users)
	fmt.Println(users)
	// 增加,更新,修改操作
	db.Exec("insert into users (age,name) values (?,?)", 23, "小丽")
	db.Exec("delete from users where user_id = ?", 1)
	db.Exec("update users set name = ? where user_id = ?", "明天", 2)
}

```

## 日志操作(之后学完gin框架之后补充)
+ 日志的作用:
    - 记录用户操作的审计日志
    - 快速定位问题的根源
    - 追踪程序执行的过程
    - 追踪数据的变化
    - 追踪数据统计和性能分析
    - 采集运行环境数据
+ 第三方日志框架: logrus 框架

### 引入方式


