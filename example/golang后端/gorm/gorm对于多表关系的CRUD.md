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
- 注意利用`Preload`和`Joins`产生的`sql`语句的区别:
```sql
-- Preload
-- 首先进行预加载,之后进行查询
SELECT * FROM `sin_b` WHERE `sin_b`.`a_id` = 2
SELECT * FROM `sin_a` WHERE aid = 2
-- Joins
-- 只会使用一条sql语句,效率更高
SELECT `sin_a`.`aid`,`sin_a`.`name`,`sin_a`.`age`,`Sb`.`bid` AS `Sb__bid`,`Sb`.`password` AS `Sb__password`,`Sb`.`birthday` AS `Sb__birthday`,`Sb`.`a_id` AS `Sb__a_id` FROM `sin_a` LEFT JOIN `sin_b` `Sb` ON `sin_a`.`aid` = `Sb`.`a_id` WHERE aid = 3
```
- 一对一关系中更新数据,最好还时使用分开更新的方式,也就是首先更新主表中的数据,之后利用`DB.Model(&Sin_b{}).Where("a_id = ?",aid).Updates(数据)` 的方法进行数据的更新,`Association`主要用于一对多关系的更新
## 一对多
- 结构体的建立:
```go
type Many_a struct {  
    Aid  int      `gorm:"column:aid;primaryKey;AutoIncrement"`  
    Name string   `gorm:"column:name"`  
    Age  int      `gorm:"column:age"`  
    Mbs  []Many_b `gorm:"foreignKey:A_id"`  
}  
  
type Many_b struct {  
    Bid       int    `gorm:"column:bid;primaryKey;AutoIncrement"`  
    ClassName string `gorm:"column:classname"`  
    A_id      int    `gorm:"column:a_id;"`  
}  
  
func (ma Many_a) TableName() string {  
    return "many_a"  
}  
  
func (mb Many_b) TableName() string {  
    return "many_b"  
}
```
- 对于一对多关系的增删改查的方式:
```go
func Query_Preload() {  
    // 利用 Preload 进行查询  
    var ma Many_a  
    err := DB.Debug().Preload("Mbs").Where("aid = ?", 1).Find(&ma).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
    fmt.Println(ma)  
}  
  
// 底层通过反射机制拿到结构体,的那是不可以对于切片使用反射  
//  
//  func Query_Joins() {  
//     // 利用 Joins 进行查询  
//     var ma Many_a  
//     err := DB.Debug().Joins("Mbs").Where("aid = ?", 2).Find(&ma).Error  
//     if err != nil {  
//        fmt.Println(err)  
//     }  
//     fmt.Println(ma)  
//  }  
func Create_Many() {  
    // 增加数据  
    // 直接增加即可  
    // 注意此时外键和主键都不用写  
    mb := Many_b{  
       ClassName: "大学物理",  
    }  
    ma := Many_a{  
       Name: "赵六",  
       Age:  22,  
       Mbs:  []Many_b{mb},  
    }  
    err := DB.Debug().Create(&ma).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
}  
  
// 同时更新多个字段使用 Updates , 更新单个字段使用 Update,更新关联值使用Association方法  
func Update_Many() {  
    // 更新数据  
    // 可以使用 Association 进行更新,这里可以演示 Append 操作,当然还有很多其他的操作  
    ma := Many_a{  
       Aid:  4,  
       Name: "赵七",  
    }  
    err := DB.Debug().Updates(&ma).Error  
    err = DB.Debug().Model(&ma).Association("Mbs").Append(&Many_b{  
       ClassName: "复变函数与积分变化",  
    })  
    if err != nil {  
       fmt.Println(err)  
    }  
}  
  
// 删除操作,但是有外键的情况下不允许删除  
func Delete_Many() {  
    err := DB.Debug().Where("aid = ?", 1).Delete(&Many_a{})  
    if err != nil {  
       fmt.Println(err)  
    }  
}
```
- 注意此时由于`Joins`底层使用反射机制获取到结构体中所有的值和标签,所以对于切片来说,无法利用反射获取到所有值,所以不可以使用`Joins`方法进行查询操作
- 更新单个值使用`Update`,更新多个值使用`Updates`,更新关联值使用`Association`(可以进行`Append,Count`等操作),利用`Save`操作表示没有数据就创建数据,有数据就更新数据但是不可以与`Model`一起使用
	- `Associatoin`执行的时候的`SQL`语句:
```sql
UPDATE `many_a` SET `name`='赵七' WHERE `aid` = 4
INSERT INTO `many_b` (`classname`,`a_id`) VALUES ('复变函数与积分变化',4) ON DUPLICATE KEY UPDATE `a_id`=VALU)
```
## 多对多关系
- 建立结构体(注意使用`JoinForeignKey`和`JoinReferenceKey`来指定中间表中的外键名称,否则使用默认的外键名称):
```go
// 注意建立中间表的结构  
// 建立中间表之后 joinForeignKey 表示连接到中间表的外键,JoinReferences 表示参照中间表的参考字段  
type MM_a struct {  
    Aid  int    `gorm:"column:aid;primaryKey;AutoIncrement"`  
    Name string `gorm:"column:name"`  
    Age  int    `gorm:"column:age"`  
    Mbs  []MM_b `gorm:"many2many:many2many;joinForeignKey:A_id;JoinReferences:B_id"`  
}  
  
type MM_b struct {  
    Bid       int    `gorm:"column:bid;primaryKey;AutoIncrement"`  
    ClassName string `gorm:"column:classname"`  
    Mas       []MM_a `gorm:"many2many:many2many;joinForeignKey:B_id;JoinReferences:A_id"`  
}  
  
type M2M struct {  
    Cid  int `gorm:"column:cid;primaryKey;AutoIncrement"`  
    A_id int `gorm:"column:a_id"`  
    B_id int `gorm:"column:b_id"`  
}  
  
func (m2m M2M) TableName() string {  
    return "many2many"  
}  
func (ma MM_a) TableName() string {  
    return "mm_a"  
}  
  
func (mb MM_b) TableName() string {  
    return "mm_b"  
}
```
- `CRUD`方法:
```go
// 还是需要按照需要进行查询  
func Query_Many2Many() {  
    var ma MM_a  
    err := DB.Debug().Preload("Mbs").Find(&ma, 1).Error  
    var mb MM_b  
    err = DB.Debug().Preload("Mas").Find(&mb, 1).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
    fmt.Println(ma)  
    fmt.Println(mb)  
}  
  
// 更新数据,还是需要根据关联进行更新  
func Create_Many2Many() {  
    mb := MM_b{  
       ClassName: "c7",  
    }  
  
    ma := MM_a{  
       Name: "小明",  
       Age:  23,  
       Mbs:  []MM_b{mb},  
    }  
    err := DB.Debug().Create(&ma).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
  
}  
  
func Update_Many2Many() {  
    // 首先更新 MM_a    ma := MM_a{  
       Aid:  2,  
       Name: "z111",  
       Age:  33,  
    }  
    err := DB.Debug().Updates(&ma).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
    // 更新后面的表,直接更新即可  
    // 如果想要更新  
    err = DB.Debug().Model(&MM_b{}).Where("classname = ?", "c5").Update("classname", "c55").Error  
    if err != nil {  
       fmt.Println(err)  
    }  
}  
  
func Update2_Many2Many() {  
    // 利用 Association 进行添加  
    ma := MM_a{Aid: 5}  
    var mb MM_b  
    err := DB.Debug().Model(&MM_b{}).Where("classname = ?", "c4").Find(&mb).Error  
    err = DB.Debug().Model(&ma).Association("Mbs").Append(&mb)  
    if err != nil {  
       fmt.Println(err)  
    }  
}  
  
func Delete_Many2Many() {  
    err := DB.Debug().Delete(&MM_a{Aid: 2}).Error  
    if err != nil {  
       fmt.Println(err)  
    }  
}
```
>总结: 在多表关系的`CURD`中,注意关联模式和预加载:
>`Preload` 首先会把另外一张表的关联值查询得到
>`Joins`底层使用反射机制进行`left joins`进行查询,所以只可以用于一对一的情况
>`Association`用于一对多和多对多的关系,主要用于更新一个结构体中的关联的另外的一个结构体数据(更新,替换或者插入等操作)

- 各种不同情况下的更新策略:
	- 一对一关系: 更新是分别更新两个表的数据,也就是利用`Model`定位不同的表
	- 一对多关系: 首先更新单张表,之后利用`Association`更新关联的表(必要的时候可以首先查询)
	- 多对多关系: 同上(但是注意中间表的定制化!!!)