>注意参考: [[Mysql多表查询总结]]
>[`gorm`官方文档](https://gorm.io/zh_CN/docs/models.html)
>特别需要注意的是注意关联模式和预加载模式,这一部分需要查看官方文档
## 关联模式
- 关联模式一般就是指的各种不同对象在数据库表之间的关系,包含一对一,一对多和多对多的关系,一般来说利用`Create`方法插入对象的时候就会自动插入和这一个对象关联的对象到数据库表中,同时`gorm`中提供了各种更新关联,删除关联数据还有查询关联数据的方法(依赖于`Association`方法),这里讨论的关联模式主要是通过外键实现的
## 预加载
- `Preload`: 主要用于预先加载关联的数据
- `Joins`: 利用`left join`来关联数据
- 但是这两者都只可以用于一对一关系的情况下
## 一对一
- `go`数据库表实例对象的定义:
```go
type Sin_a struct {  
    Aid  int    `gorm:"primary_key;AUTO_INCREMENT;column:aid"`  
    Name string `gorm:"column:name"`  
    Age  int    `gorm:"column:age"`  
    Sb   Sin_b  `gorm:"foreignkey:A_id"`  
}  
  
type Sin_b struct {  
    Bid      int    `gorm:"primary_key;AUTO_INCREMENT;column:bid"`  
    Password string `gorm:"column:password"`  
    Birthday string `gorm:"column:birthday"`  
    A_id     int    `gorm:"column:a_id"`  
}  
  
func (s Sin_a) TableName() string {  
    return "sin_a"  
}  
  
func (s Sin_b) TableName() string {  
    return "sin_b"  
}
```
- 相关的`CURD`操作
```go
func Add() {  
    // 添加数据  
    sa := Sin_a{  
       Name: "Andy",  
       Age:  30,  
       Sb: Sin_b{  
          Password: "12345",  
          Birthday: "1990-10-10",  
       },  
    }  
    err := DB.Create(&sa).Error  
    if err != nil {  
       fmt.Println("create failed !")  
    }  
}  
  
func Update() {  
    // 更新数据,只可分开更新  
    sa := Sin_a{  
       Aid:  4,  
       Name: "Andkkk",  
       Age:  50,  
    }  
    // 首先更新 sa    err := DB.Updates(&sa).Error  
    if err != nil {  
       fmt.Println("update failed !")  
    }  
    // 之后可以更新 sb    err = DB.Model(&Sin_b{}).Where("a_id = ?", sa.Aid).Updates(map[string]interface{}{  
       "password": "2222",  
       "birthday": "1990-10-21",  
    }).Error  
    if err != nil {  
       fmt.Println("update failed !")  
    }  
}  
  
func Query() {  
    var sa Sin_a  
    // Preload中写结构体关联字段的名称  
    err := DB.Debug().Preload("Sb").Find(&sa, "aid = ?", 2)  
    if err != nil {  
       fmt.Println(err.Error)  
    }  
    fmt.Println(sa)  
}  
  
// 利用 Query2 进行查询  
func Query2() {  
    var sa Sin_a  
    err := DB.Debug().Joins("Sb").Find(&sa, "aid = ?", 3).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
    fmt.Println(sa)  
}  
  
// 删除数据  
func Delete() {  
    err := DB.Debug().Delete(&Sin_a{}, "aid = ?", 4)  
    if err != nil {  
       fmt.Println(err)  
    }  
}
```
- 注意使用预加载模式的时候,`Preload`和`Joins`的参数是被关联的结构体的对象名称,这里就是`Sb`一定要注意这一点!,另外更新操作可以直接对于另外一张表进行操作,也可以使用`Association`关联模式进行操作
## 一对多
