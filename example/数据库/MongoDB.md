## MongoDB 介绍
`MongoDB` 是一个基于**分布式** **文件存储**的`NoSQL`数据库。由 `C++` 语言编写。旨在为 `WEB`应用提供可扩展的高性能数据存储解决方案。

`MongoDB` 是一个介于关系数据库和非关系数据库之间的产品，是非关系数据库当中功能最丰富，最像关系数据库的。

同时 `MongoDB` 的特点如下:
- 模式自由 :**可以把不同结构的文档存储在同一个数据库里**
- **面向集合**的存储：适合存储 `JSON`风格文件的形式，
- **完整的索引支持**：对任何属性可索引，
- **复制和高可用性**：**支持服务器之间的数据复制，支持主-从模式及服务器之间的相互复制。复制的主要目的是提供冗余及自动故障转移。
- 自动分片：**支持云级别的伸缩性**：自动分片功能支持水平的数据库集群，可动态添加额外的机器。
- 丰富的查询：**支持丰富的查询表达方式，查询指令使用JSON形式的标记，可轻易查询文档中的内嵌的对象及数组。**
- 快速就地更新：**查询优化器会分析查询表达式，并生成一个高效的查询计划。**
- **高效的传统存储方式：支持二进制数据及大型对象（如照片或图片）。**

同时 `MangoDB` 适用于如下的场景

- 网站数据：适合实时的插入，更新与查询，并具备网站实时数据存储所需的复制及高度伸缩性。
- 缓存：由于性能很高，也适合作为信息基础设施的缓存层。在系统重启之后，搭建的持久化缓存可以避免下层的数据源过载。
- 大尺寸、低价值的数据：使用传统的关系数据库存储一些数据时可能会比较贵，在此之前，很多程序员往往会选择传统的文件进行存储。
- 高伸缩性的场景：非常适合由数十或者数百台服务器组成的数据库。
- 用于对象及JSON数据的存储：`MongoDB`的`BSON`数据格式非常适合文档格式化的存储及查询。(比如可以存储聊天消息)

`MongoDB` 是一个文档型的数据库,数据以类似于 `JSON` 文档的形式存储,使用了 集合(`Collections` 来组织文档 `Documents` , 每一个文档都是由键值对的方式组成的),各种概念如下:
- **数据库** 存储数据的容器,类似于关系型数据库中的数据库
- **集合** 数据库中的一个集合,类似于关系数据库中的表
- **文档**  集合中的一个数据记录,类似于关系型数据库中的行,使用 `BSON` 的格式进行存储
`MongoDB` 将数据存储为一个文档，数据结构由键值(`key=>value`)对组成，文档类似于 `JSON` 对象，字段值可以包含其他文档，数组及文档数组：

## MongoDB 基础
### MongoDB 部署
所有中间件或者数据库统一都使用 `Docker` 容器部署,便于管理
```shell
# 拉取最新的 mongoDB 镜像
sudo docker pull mongo 

# 启动 mongoDB 容器
sudo docker run -p 27017:27017 \   
-v /home/loser/data/mongo/data:/data/db \
--name my-mongo \
-d mongo
```
在容器中可以使用 `mongosh` 命令启动 `mongoDB` 的命令行 
### MongoDB 基本使用
#### 基本概念
`MongoDB`中的各种基本概念:
- `database` --> 数据库
- `connection` -->  相当于数据库表
- `document` --> 相当于数据库表中的一条记录 
- `column` -->  数据字段/域
- `index` --> 字段索引???

- `BSON`: `Binary JSON` , 是 `MongoDB` 用于存储和传输二进制形式的 `JSON`
- 主键 --> `mongoDB`提供了 `key` 为 `_id`

`MongoDB`中的数据类型:
- `String`
- `Integer`
- `Boolean`
- `Double`
- `Min/Max keys`
- `Array`
- `Timestamp`
- `Object`: 用于内嵌文档(实现多表关系)
- `Null`
- `Sysmbol`
- `Date`
- `Object ID`: 对象 `ID`,用于创建文档的 `ID`
- `Code`: 代码类型,用于存储`js`代码
- `Regular expression`: 正则表达式类型
#### 用户管理
- 连接到 `mongoDB` , 使用 `mongosh` 连接到 `MongoDB` 服务器:
```shell
mongosh --host <hostname> --port <port>
```
- 切换到目标数据库
```shell
use <database_name>
```
- 创建用户(感觉 `mongoDB`中的命令类似于编程语言)
```shell
db.createUser({
  user: "testuser",
  pwd: "password123",
  # 表示赋予用户在某一个数据库的读写权限
  roles: [
    { role: "readWrite", db: "<database_name>" },
    { role: "dbAdmin", db: "<database_name>" }
  ]
})
```
- 验证用户
```shell
db.auth("testUser" , "123456")
```
- 使用用户身份登录
```shell
mongosh --host <hostname> --port <port> -u "testUser" -p <port> "password123" --authenticationDatabase "<database_name>"
```
#### MongoDB 连接
- `url`写法如下,感觉和 `mysql` 差不多
```shell
mongodb://[username:password@]host1[:port1][,...hostN[:portN]][/[defaultauthdb][?options]]
```
- `example`:
```MongoDB
mongodb://username:password@localhost:27017/mydatabase?authSource=admin&ssl=true
```
#### CURD
##### 数据库操作
###### 创建数据库
使用 `use` 命令,如果一个数据库不存在,那么就会创建者一个数据库,创建数据库的语法如下:
```MongoDB
use DATABASE_NAME
```
###### 查看数据库
查看数据库列表,使用 **`show dbs`** 命令
```shell
show dbs
```
查看当前数据库
```shell
db
```
###### 删除数据库
使用 **`db.dropDatabase()`** 方法即可
```shell
use myDatabase
db.dropDatabase()
```
###### 删除集合
使用如下语句删除集合
```shell
db.<collection_name>.drop()
```
##### 集合操作
###### 创建集合
`MongoDB` 中使用 `createCollection()` 来创建集合,语法格式如下:
```shell
db.createCollection(name , options)
```
后面的选项参考: https://www.runoob.com/mongodb/mongodb-create-collection.html
- `example`:
```shell
db.createCollection("myComplexCollection", {
  capped: true,
  size: 10485760,
  max: 5000,
  validator: { $jsonSchema: {
    bsonType: "object",
    required: ["name", "email"],
    properties: {
      name: {
        bsonType: "string",
        description: "必须为字符串且为必填项"
      },
      email: {
        bsonType: "string",
        pattern: "^.+@.+$",
        description: "必须为有效的电子邮件地址"
      }
    }
  }},
  validationLevel: "strict",
  validationAction: "error",
  storageEngine: {
    wiredTiger: { configString: "block_compressor=zstd" }
  },
  collation: { locale: "en", strength: 2 }
});
```
注意到这里的集合类型相当于 `mysql` 中的表,所以这里的 `validator` 的作用是对于每一个字段进行操作
###### 查看已有集合
使用如下命令查看已经有的集合
```shell
show collections
show tables
```
甚至在 `MongoDB` 中,不需要手动创建集合,在向集合中插入数据的时候 , `MongoDB` 会自动创建集合,插入数据的语法:
```shell
db.<collection_name>.insert({"name":"sanzhang"})
```
###### 更新集合名称
更新集合名称需要 `dbAdmin` 或者 `dbOwner` 权限(这里表示使用到某一个集合的时候就需要验证用户了)
```shell
db.adminCommand({
  renameCollection: "sourceDb.sourceCollection",
  to: "targetDb.targetCollection",
  dropTarget: <boolean>
})
```
- `example`:
```shell
runoob> db.adminCommand({
	renameCollection: "runoob.mycol",
	to: "runoob.mycoll"
})
```





