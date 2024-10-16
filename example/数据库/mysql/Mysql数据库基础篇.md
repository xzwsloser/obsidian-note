## mysql的启动
1. 命令行输入 `services.msc`
2. 命令行输入 `net start mysql 80` 启动数据库,输入 `net stop mysql80 `关闭数据库
3. 利用`docker`进行部署:
```shell
sudo docker run --name mysql-test -p 3306:3306 -e MYSQL_ROOT_PASSWORD=123456 mysql
```

## mysql的客户端连接
1. 直接利用客户端软件连接
2. 命令行输入 `mysql [ -h 服务器的IP地址] [-P 3306] -u root -p`

## SQL-DDL数据库操作语句
### 查询
1. 查询所有数据库 `show databases`
2. 查询当前数据库 `select database()`

### 创建数据库
1. `createa database [ if not exists ] 数据库名称 [ default charest 字符集] [collect 排序规则 ]`

### 删除数据库
1. `drop databases [ if exists ]  数据库名称`

### 使用/切换数据库
1. `use 数据库名称`

## 对数据库中的表进行操作
### 查询数据库中的所有表结构
1. `show tables`

### 查询表的结构
1.` desc 表名`

### 查询指定的建表语句
```plain
create table 表名 (
  字段1 字段1类型 [comment 字段1注释],
  字段2 字段2类型 [comment 字段2注释],
  字段3 字段3类型 [comment 字段3注释],
  字段4  字段4类型 [comment 字段4注释],
      ... ...
) [comment 表注释]
```

### DDL- 表操作中的数据类型
1. 数值型： 常用的就是 int,其他的还有int的各种变式（tinyint,smallint,mediumint等),还有浮点数类型(float,double,decimal)
2. 字符串类型: 常用的char和varchar(),但是注意都要指定长度(char(10)),另外还有blob二进制文本(应该可以用于存储图片),还有text(文本数据,应该可以存储简历等信息)
3. 日期类型: 常用的就是Date(只表示年月日)，time(只表示时分秒),datatime(都可以表示),timestamp(表示混合日期和时间戳)

### DDL-表操作-修改表中数据
#### 添加字段
+ `alter table 表名 add 字段名 字段类型 [ comment 字段注释]`

#### 修改字段类型
+ `alter table 表名 modify 字段名称 新数据类型(长度)`

#### 修改字段名和类型
+ `alter table 表名 change 旧字段名称 新字段名称 类型(长度) [ comment 字段注释 ]`

#### 删除字段
+` alter table 表名 drop 字段名称`

#### 修改表名称
+ `alter table 表名 rename to 新的表名<font style="background-color:#E7E9E8;"></font>`

#### 删除表
+ `drop table [ if exists ] 表名 (其实就是完全删除表)`
+ `truncate table 表名 （删除指定表并且重新创建该表,其实就是清空数据)`

## SQL-DML数据操作语句
### 添加数据(insert into 关键字和 values 关键字的使用)
#### 给指定字段添加数据
+ insert into 表名 (字段1,字段2,字段3 ... ...) values (值1,值2,值3  ... ... )  (其实就是变量的初始化)

#### 给表中全部字段添加数据
+ insert into 表名 values (值1,值2 ... ....) 

#### 批量添加数据
+ insert into 表名 (字段名1,字段名2 ... ...) values (值1,值2 ... .... ) (值1,值2  ... ...) .... ...
+ insert into 表名 values (值1,值2 ... ...) (值1,值2 ... ...)

#### 注意事项简述：
字符串类型和日期类型在单引号中间

### <font style="color:#000000;background-color:#FAFAFA;">修改数据(update 关键字和 set关键字的使用)</font>
#### 修改数据
+ update  表名 set 字段名1= 值1字段名2= 值2 ... ... [where 条件判断]

#### 注意事项:
+ 后面的条件没有表示修改所有数据,要修改特定的数据必须带上条件

### 删除数据(delete from 关键字的使用)
+ delete from 表名 where 条件

#### 注意事项
+ delete相当于删除某一个数据(其实就是一行数据，但是不可以删除某一个字段的值,where条件不写表示删除所有的值

## SQL-DQL数据库查询语句基础
:::warning
+ 使用数据库查询语句其实就是对于关键字select的使用
+ DQL中使用的语法结构(各种关键字)如下:



:::

```plain
select 字段列表
from 表名列表
where 条件列表
group by 分组字段列表
having 分组之后条件列表
order by 排序字段列表
limit 分页参数
```

### 基础查询
#### 查询多个字段
+ select 字段名1,字段名2,字段名3 ... from 表名
+ select * from 表名

#### 设置别名
+ select 字段名1 [as 别名] ,字段名2 [as 别名] ... ... from 表名

#### 去除重复记录
+ select distinct 字段列表 from 表名

### 条件查询
+ select 字段名1,字段名2 ...... from 表名 where 条件

#### 条件种类的总结如下
1. 常见的比较运算符号: 除了常用的 大于小于等,比较重要的还有 between ... and ... (最大值和最小值之间)  in (列表) 在in后面的列表中选择一个 like 占位符号(非常重要,其实是模糊匹配,_匹配单个字符,%匹配多个字符),isnull 表示为null
2. 逻辑运算符号：都知道的

### 聚合函数
+ 作用: 把一列数据作为一个整体,进行纵向计算
+ 常见的聚合函数如下



| 函数 | 功能 |
| --- | --- |
| count | 统计数量 |
| max | 最大值 |
| min | 最小值 |
| avg | 平均值 |
| sum  | 求和 |


+ 语法：select 聚合函数(字段 列表) from 表名 [ where 条件]

### 分组查询
#### 语法
1. select 字段列表 from 表名 [ where 条件] group by 分组字段名称 [ having 分组之后的过滤条件]

#### 作用
+ 一般是统计不同类别的人的一个情况,比如不同性别的人的人数 ,不同性别人的年龄的平均值

#### where 和 having的区别
1. 执行时机不同: where是分组之后进行过滤,不满足where条件就不可参加分组,但是having在分组执行之后进行的
2. 判断条件不同,where不可以对聚合函数进行操作,但是having可以

### 排序查询
#### 语法
+ select 字段列表 from 表名 order by 字段 排序方式1,字段2 排序方式2(可以进行多字段排序)

#### 排序方式
+ asc 升序(默认)
+ desc 降序

#### 注意事项
+ 多字段排序时,只有当第一个字段相同时,才会根据第二个字段排序

### <font style="color:rgb(31, 35, 40);">分页查询</font>
1. <font style="color:rgb(31, 35, 40);">语法</font>
    1. <font style="color:rgb(31, 35, 40);">SELECT 字段列表 FROM 表名 LIMIT 起始索引,查询记录数;</font>
2. <font style="color:rgb(31, 35, 40);">注意:</font>
    1. <font style="color:rgb(31, 35, 40);">起始索引从0开始,起始索引=(查询页码-1)*每页显示记录数</font>
    2. <font style="color:rgb(31, 35, 40);">分页查询是数据库的方言,不同数据库实现不同,mysql中是LIMIT</font>
    3. <font style="color:rgb(31, 35, 40);">如果查询的是第一页数据,起始索引可以省略,直接简写为limit 10;(与数组相同)</font>



```plain
select * from employee limit 10;
select * from employee limit 10 ,10;
```

1. <font style="color:rgb(31, 35, 40);">实例</font>



```plain
select * from employee where age between 20 and 23;
select * from employee where age between 20 and 40 && name like '___' && gender='男'; -- ___就是匹配字符的符号
select gender ,count(*) from employee where age<60 group by  gender;  -- 注意逗号分割
select name,age,entrydate from employee where age<=35 order by age ,entrydate desc;
select * from employee where gender='男' && age between 20 and 40 order by age,entrydate limit 5;
```

### <font style="color:rgb(31, 35, 40);">DQL语句的执行顺序</font>
1. <font style="color:rgb(31, 35, 40);">上面的是编写顺序</font>
2. <font style="color:rgb(31, 35, 40);">DQL语句的执行顺序 1. from 2. where 3. group by 4. having 5. select 6. order by 7. limit</font>

## <font style="color:rgb(31, 35, 40);">DCL语言</font>
1. <font style="color:rgb(31, 35, 40);">用于管理数据库用户,控制数据库的访问权限</font>
2. <font style="color:rgb(31, 35, 40);">管理用户的语法:</font>
    1. <font style="color:rgb(31, 35, 40);">查询用户</font>
        1. <font style="color:rgb(31, 35, 40);">USE mysql;(访问系统数据库mysql,查询表结构user得到用户)</font>
        2. <font style="color:rgb(31, 35, 40);">SELECT * FROM user;</font>
    2. <font style="color:rgb(31, 35, 40);">创建用户</font>
        1. <font style="color:rgb(31, 35, 40);">CREATE USER '用户名'@'主机名' IDENTIFIED BY '密码';</font>
    3. <font style="color:rgb(31, 35, 40);">修改用户密码:</font>
        1. <font style="color:rgb(31, 35, 40);">ALTER USER '用户名'@'主机名' IDENTIFIED WITH mysql_native_password BY '新密码';</font>
    4. <font style="color:rgb(31, 35, 40);">删除用户:</font>
        1. <font style="color:rgb(31, 35, 40);">DROP USER '用户名'@'主机名';</font>
3. <font style="color:rgb(31, 35, 40);">注意事项</font>
    1. <font style="color:rgb(31, 35, 40);">主机名可以利用% 匹配</font>
    2. <font style="color:rgb(31, 35, 40);">这类SQL语句开发人员利用的少,主要是DBA(数据库管理人员)使用</font>

#### <font style="color:rgb(31, 35, 40);">权限控制</font>
1. <font style="color:rgb(31, 35, 40);">权限的种类</font>

| <font style="color:rgb(31, 35, 40);">权限</font> | <font style="color:rgb(31, 35, 40);">说明</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">ALL,ALL PRIVILEGES</font> | <font style="color:rgb(31, 35, 40);">所有权限</font> |
| <font style="color:rgb(31, 35, 40);">SELECT</font> | <font style="color:rgb(31, 35, 40);">查询数据</font> |
| <font style="color:rgb(31, 35, 40);">INSERT</font> | <font style="color:rgb(31, 35, 40);">插入数据</font> |
| <font style="color:rgb(31, 35, 40);">UPDATE</font> | <font style="color:rgb(31, 35, 40);">修改数据</font> |
| <font style="color:rgb(31, 35, 40);">DELETE</font> | <font style="color:rgb(31, 35, 40);">删除数据</font> |
| <font style="color:rgb(31, 35, 40);">ALTER</font> | <font style="color:rgb(31, 35, 40);">修改表</font> |
| <font style="color:rgb(31, 35, 40);">DROP</font> | <font style="color:rgb(31, 35, 40);">删除表/数据库/视图</font> |
| <font style="color:rgb(31, 35, 40);">CREATE</font> | <font style="color:rgb(31, 35, 40);">创建数据库/表</font> |


1. <font style="color:rgb(31, 35, 40);">权限控制语句的语法</font>
    1. <font style="color:rgb(31, 35, 40);">查询权限:</font>
        1. <font style="color:rgb(31, 35, 40);">SHOW GRANTS FOR '用户名'@'主机名';</font>
    2. <font style="color:rgb(31, 35, 40);">授予权限</font>
        1. <font style="color:rgb(31, 35, 40);">GRANTS 权限列表 ON 数据库名.表名(可以使用通配符) TO '用户名'@'主机名';</font>
    3. <font style="color:rgb(31, 35, 40);">撤销权限</font>
        1. <font style="color:rgb(31, 35, 40);">REVOKE 权限列表 ON 数据库名.表名 FROM '用户名'@'主机名';</font>

## <font style="color:rgb(31, 35, 40);">函数</font>
1. <font style="color:rgb(31, 35, 40);">函数是指一段可以直接被另一端程序调用的程序或者代码</font>
2. <font style="color:rgb(31, 35, 40);">常用的字符串函数:</font>

| <font style="color:rgb(31, 35, 40);">函数</font> | <font style="color:rgb(31, 35, 40);">功能</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">CONCAT(S1,S2..Sn)</font> | <font style="color:rgb(31, 35, 40);">字符串拼接,将s1,s2...sn拼接成一个字符串</font> |
| <font style="color:rgb(31, 35, 40);">LOWER(str)</font> | <font style="color:rgb(31, 35, 40);">把字符串str全部转为小写</font> |
| <font style="color:rgb(31, 35, 40);">UPPER(str)</font> | <font style="color:rgb(31, 35, 40);">把字符串str全部转为大写</font> |
| <font style="color:rgb(31, 35, 40);">LPAD(str,n,pad)</font> | <font style="color:rgb(31, 35, 40);">左填充,用字符串pad对str的左边进行填充,达到n个字符串长度</font> |
| <font style="color:rgb(31, 35, 40);">RPAD(str,n,pad)</font> | <font style="color:rgb(31, 35, 40);">右填充,用字符串pad对str的右边进行填充,达到n个字符串长度</font> |
| <font style="color:rgb(31, 35, 40);">TRIM(str)</font> | <font style="color:rgb(31, 35, 40);">去掉字符串头部和尾部的空格</font> |
| <font style="color:rgb(31, 35, 40);">SUBSTRING(str,start,len)</font> | <font style="color:rgb(31, 35, 40);">返回字符串str从start位置起的len个长度的字符串</font> |


### <font style="color:rgb(31, 35, 40);">数值函数</font>
1. <font style="color:rgb(31, 35, 40);">常见的数值函数:</font>

| <font style="color:rgb(31, 35, 40);">函数</font> | <font style="color:rgb(31, 35, 40);">功能</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">CEIL(X)</font> | <font style="color:rgb(31, 35, 40);">向上取整</font> |
| <font style="color:rgb(31, 35, 40);">FLOOR(X)</font> | <font style="color:rgb(31, 35, 40);">向下取整</font> |
| <font style="color:rgb(31, 35, 40);">MOD(x,y)</font> | <font style="color:rgb(31, 35, 40);">返回x/y的模</font> |
| <font style="color:rgb(31, 35, 40);">RAND()</font> | <font style="color:rgb(31, 35, 40);">返回0-1之间的随机数</font> |
| <font style="color:rgb(31, 35, 40);">ROUND(x,y)</font> | <font style="color:rgb(31, 35, 40);">求参数x的四舍五入值,保留y位小数</font> |


### <font style="color:rgb(31, 35, 40);">日期函数</font>
1. <font style="color:rgb(31, 35, 40);">常见的日期函数</font>

| <font style="color:rgb(31, 35, 40);">函数</font> | <font style="color:rgb(31, 35, 40);">功能</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">CURDATE()</font> | <font style="color:rgb(31, 35, 40);">返回当前日期值</font> |
| <font style="color:rgb(31, 35, 40);">CURTIME()</font> | <font style="color:rgb(31, 35, 40);">返回当前时间</font> |
| <font style="color:rgb(31, 35, 40);">NOW()</font> | <font style="color:rgb(31, 35, 40);">返回当前日期和时间</font> |
| <font style="color:rgb(31, 35, 40);">YEAR(date)</font> | <font style="color:rgb(31, 35, 40);">获取指定date的年份</font> |
| <font style="color:rgb(31, 35, 40);">MONTH(date)</font> | <font style="color:rgb(31, 35, 40);">获取指定date的日期</font> |
| <font style="color:rgb(31, 35, 40);">DAY(date)</font> | <font style="color:rgb(31, 35, 40);">获取指定date的日期</font> |
| <font style="color:rgb(31, 35, 40);">DATE_ADD(date,INTERVAL expr type)</font> | <font style="color:rgb(31, 35, 40);">返回一个日期/时间值加上一个时间间隔expr后的时间值</font> |
| <font style="color:rgb(31, 35, 40);">DATEDEFF(date1,date2)</font> | <font style="color:rgb(31, 35, 40);">返回起始时间date1和结束时间date2之间的天数</font> |


### <font style="color:rgb(31, 35, 40);">流程控制函数</font>
1. <font style="color:rgb(31, 35, 40);">流程控制函数可以实现条件筛选,从而提高语句的效率</font>
2. <font style="color:rgb(31, 35, 40);">常见的流程函数</font>

| <font style="color:rgb(31, 35, 40);">函数</font> | <font style="color:rgb(31, 35, 40);">功能</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">IF(value,t,f)</font> | <font style="color:rgb(31, 35, 40);">如果value为true,则返回t,否则返回f</font> |
| <font style="color:rgb(31, 35, 40);">IFNULL(value1,value2)</font> | <font style="color:rgb(31, 35, 40);">如果value1不为空,返回value1,否则返回value2</font> |
| <font style="color:rgb(31, 35, 40);">CASE WHEN[val1] THEN[res1] ...ELSE[default] END</font> | <font style="color:rgb(31, 35, 40);">如果val1为true,返回res1,... 否则返回default默认值</font> |
| <font style="color:rgb(31, 35, 40);">CASE [expr] WHEN[val1] THEN[res1]...ELSE[default] END</font> | <font style="color:rgb(31, 35, 40);">如果expr的值等于val1,返回res1,... 否则返回default默认值(expr的值就是表达式)</font> |


## <font style="color:rgb(31, 35, 40);">约束</font>
1. <font style="color:rgb(31, 35, 40);">概念:约束是作用于表中字段上的规则,用于限制存储在表中的数据</font>
2. <font style="color:rgb(31, 35, 40);">目的: 保证数据库中的数据的正确性,有效性和完整性</font>
3. <font style="color:rgb(31, 35, 40);">分类：</font>

| <font style="color:rgb(31, 35, 40);">约束</font> | <font style="color:rgb(31, 35, 40);">描述</font> | <font style="color:rgb(31, 35, 40);">关键字</font> |
| --- | --- | --- |
| <font style="color:rgb(31, 35, 40);">非空约束</font> | <font style="color:rgb(31, 35, 40);">限制字段的数据不能为null</font> | <font style="color:rgb(31, 35, 40);">NOT NULL</font> |
| <font style="color:rgb(31, 35, 40);">唯一约束</font> | <font style="color:rgb(31, 35, 40);">保证该字段的所有数据都是唯一的,不重复的</font> | <font style="color:rgb(31, 35, 40);">UNIQUE</font> |
| <font style="color:rgb(31, 35, 40);">主键约束</font> | <font style="color:rgb(31, 35, 40);">主键是一行数据的唯一标识(比如用于区分每一个数据的id和区分每一个人的身份证号),要求非空且唯一</font> | <font style="color:rgb(31, 35, 40);">PRIMARY KEY(后面加上关键字AUTO_INCREMENT使得主键自动增长)</font> |
| <font style="color:rgb(31, 35, 40);">默认约束</font> | <font style="color:rgb(31, 35, 40);">保存数据时,如果没有指定该字段的值,则采用默认值</font> | <font style="color:rgb(31, 35, 40);">DEFAULT</font> |
| <font style="color:rgb(31, 35, 40);">检查约束</font> | <font style="color:rgb(31, 35, 40);">保证字段值满足某一个规则</font> | <font style="color:rgb(31, 35, 40);">CHECK</font> |
| <font style="color:rgb(31, 35, 40);">外键约束</font> | <font style="color:rgb(31, 35, 40);">用来让两张表之间建立联系,保证数据的一致性和完整性</font> | <font style="color:rgb(31, 35, 40);">FOREIGN KEY</font> |


### <font style="color:rgb(31, 35, 40);">约束的使用</font>


```plain
create table user1(
    id int  primary key auto_increment comment '表中的主键,自动增长' ,
    name varchar(10) not null unique comment '姓名,不为空并且唯一',
    age int check(age>=0&&age<=120) comment '年龄',
    status char(1) default 1 comment '状态,默认为1',
    gender char(1) comment '性别'
) comment '用户表';
```

1. <font style="color:rgb(31, 35, 40);">细节: 约束的建立在评论之前,可以利用图形化界面常见约束</font>

### <font style="color:rgb(31, 35, 40);">外键约束</font>
1. <font style="color:rgb(31, 35, 40);">概念:外键用来让两张表的数据之间建立联系,从而保证数据的一致性和完整性</font>
2. <font style="color:rgb(31, 35, 40);">比如一张表之中的外键就是另外一张表中的主键取值,有外键的表称为子表,被关联主键的表被称为主表</font>
3. <font style="color:rgb(31, 35, 40);">语法格式：</font>



```plain
CREATE TABLE 表名(
    字段名 数据类型, 
    ...
    [CONSTRAINT][外键名称] FOREIGN KEY(外键字段名) REFERENCES 主表 (主表列表)
);
-- 添加字段时添加外键约束 
ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY(外键字段名) REFRENCES 主表(主表列名)
```

1. <font style="color:rgb(31, 35, 40);">删除外键: ALTER TABLE 表名 DROP FOREIGN KEY 外键名称;</font>

#### <font style="color:rgb(31, 35, 40);">外键约束中的删除和更新行为</font>
1. <font style="color:rgb(31, 35, 40);">删除/更新行为</font>

| <font style="color:rgb(31, 35, 40);">行为</font> | <font style="color:rgb(31, 35, 40);">说明</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">NO ACTION</font> | <font style="color:rgb(31, 35, 40);">当在父表中删除或者更新对应数据时,首先检查是否有对应外键,如果有对应外键就不允许删除或者更新(于RESIRICT一致)</font> |
| <font style="color:rgb(31, 35, 40);">RESIRICT</font> | <font style="color:rgb(31, 35, 40);">同上</font> |
| <font style="color:rgb(31, 35, 40);">CASCADE(cascade)</font> | <font style="color:rgb(31, 35, 40);">当在父表中删除数据时,首先检查是否有对应外键,如果有,就也删除对应外键,更新就同步更新</font> |
| <font style="color:rgb(31, 35, 40);">SET NULL</font> | <font style="color:rgb(31, 35, 40);">当在父表中删除对应记录时,首先检查该记录是否有对应值,如果有则设置子表中该外键的值为null(这就要求外键允许取值为null)</font> |
| <font style="color:rgb(31, 35, 40);">SET DEFAULT</font> | <font style="color:rgb(31, 35, 40);">父表中有变更时,子表将外键列设置成一个默认的值(Innodb不支持)</font> |


1. <font style="color:rgb(31, 35, 40);">使用以上行为的语法: ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键字段) REFERENCES 主表名(主表字段名) ON UPDATE CASCADE ON DELETE RESIRICT;</font>

## <font style="color:rgb(31, 35, 40);">多表查询</font>
### <font style="color:rgb(31, 35, 40);">多表关系</font>
1. <font style="color:rgb(31, 35, 40);">项目开发中,在进行数据库表结构设计时,会根据业务需求以及业务模块之间的关系,分析并设计表结构,由于业务之间相互关联,所以各个表结构之间也存在着各种联系,基本分为三种: 一对多 多对多 一对一</font>
2. <font style="color:rgb(31, 35, 40);">一对多: 比如部门于员工之间的关系,一个部门不只有一个员工,一个员工归属于一个部门,实现: 在多的一方(员工)建立外键,指向的一方的主键</font>
3. <font style="color:rgb(31, 35, 40);">多对多: 比如学生与课程之间的关系,一个学生可以选择多个课程,每个课程可以有多个学生 实现方式: 建立第三张中间表,中间表中至少包含两个外键,分别关联两方主键(从而反应出两个表中数据之间的关系)</font><font style="color:rgb(31, 35, 40);"> </font>![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-07-22-07-51.png)
4. <font style="color:rgb(31, 35, 40);">一对一的关系: 多用于单表拆分,将一张表的基础字段放在一张表中,其他字段放在另外一张表中,以提高操作效率 实现: 在任意一方加入外键(userid),关联另外一方的主键,并且设置外键为唯一的unique</font>

### <font style="color:rgb(31, 35, 40);">多表查询</font>
1. <font style="color:rgb(31, 35, 40);">对于具有多表关系的两张表,利用原来的查询语句就可以这样写 select * from 子表,父表; 但是得到的结果会产生笛卡尔积的现象(就是在数学中,两个集合A和B集合的所有组合情况(多表查询中要消除无效的笛卡尔积)),利用where条件使得互相连接的键值相同就可以消除笛卡尔积</font>
2. <font style="color:rgb(31, 35, 40);">多表查询中的连接查询:</font>
    1. <font style="color:rgb(31, 35, 40);">内连接: 相当于查询A,B交集部分的数据</font>
    2. <font style="color:rgb(31, 35, 40);">外连接:</font>
        1. <font style="color:rgb(31, 35, 40);">左外连接: 相当于查询左表中的所有数据,以及两表交集部分的数据</font>
        2. <font style="color:rgb(31, 35, 40);">右外连接: 查询右表中的所有数据,以及两张表交集部分的数据</font>
    3. <font style="color:rgb(31, 35, 40);">自连接: 当前表与自身的连接查询,自连接必须使用表别名</font>

#### <font style="color:rgb(31, 35, 40);">内连接</font>
1. <font style="color:rgb(31, 35, 40);">查询交集部分</font>
2. <font style="color:rgb(31, 35, 40);">查询语法:</font>
    1. <font style="color:rgb(31, 35, 40);">隐式内连接: SELECT 字段列表 FROM 表1,表2 WHERE 条件...;(条件中一般时外键与主键之间的关系)</font>
    2. <font style="color:rgb(31, 35, 40);">显式内连接: SELECT 字段列表 FROM 表1 [INNER] JOIN 表2 ON 连接条件(连接条件基本和上面一致)...;</font>

#### <font style="color:rgb(31, 35, 40);">外连接</font>
1. <font style="color:rgb(31, 35, 40);">查询语法(可以通过取别名的方式完成简化):</font>
    1. <font style="color:rgb(31, 35, 40);">左外连接: SELECT 字段列表 FROM 表1 LEFT [OUTER] JOIN 表2 ON 条件...;(注意相当于查询左表中的所有数据,包含两表中的交集数据)</font>
    2. <font style="color:rgb(31, 35, 40);">右外连接: SELECT 字段列表 FROM 表1 RIGHT [ OUTER] JOIN 表2 ON 条件...;(查询右表中的数据)</font>
2. <font style="color:rgb(31, 35, 40);">代码实现：</font>

![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-08-11-53-22.png)

#### <font style="color:rgb(31, 35, 40);">自连接</font>
1. <font style="color:rgb(31, 35, 40);">自连接查询语法 SELECT 字段列表 FROM 表A 别名 表A 别名B ON 条件 ...;</font>
2. <font style="color:rgb(31, 35, 40);">自连接查询可以式内连接也可以是外连接</font>
3. <font style="color:rgb(31, 35, 40);">应用场景: 查询的数据都在一张表中,并且表中的某些字段有对应关系(就是一张表中的两个字段之间的关系为关联关系)</font>
4. <font style="color:rgb(31, 35, 40);">查询时,把这一张表看成两张表</font>

#### <font style="color:rgb(31, 35, 40);">联合查询</font>
1. <font style="color:rgb(31, 35, 40);">对于union查询，就是把多次查询的结果合并起来,形成一个新的查询结果集</font>
2. <font style="color:rgb(31, 35, 40);">语法:</font>



```plain
SELECT 字段列表 FROM 表A ...
UNION [ALL]
SELECT 字段列表 FROM 表B ...;
```

1. <font style="color:rgb(31, 35, 40);">上面满足结果A,下面结果满足结果B(去掉all可以去重)</font>
2. <font style="color:rgb(31, 35, 40);">注意点: 对于联合查询,多张表的列数必须保持一致,字段类型也要一致 union all 会将全部的数据直接合并在一起,union 会对和合并之后的数据去重</font>

### <font style="color:rgb(31, 35, 40);">子查询</font>
1. <font style="color:rgb(31, 35, 40);">概念: SQL语句中嵌套的SELECT语句,称为嵌套查询,又称为子查询</font>
2. <font style="color:rgb(31, 35, 40);">比如 SELECT * FROM t1 WHERE column1=(SELECT column1 FROM t2);</font>
3. <font style="color:rgb(31, 35, 40);">子查询外部的语句可以是: INSERT/UPDATE/DELETE/SELECT中的任意一个</font>
4. <font style="color:rgb(31, 35, 40);">根据子查询的结果不同可以分为:</font>
    1. <font style="color:rgb(31, 35, 40);">标量子查询:子查询的结果返回一个值</font>
    2. <font style="color:rgb(31, 35, 40);">标子查询: 子查询的结果是一列</font>
    3. <font style="color:rgb(31, 35, 40);">行子查询: 子查询的结果是一行</font>
    4. <font style="color:rgb(31, 35, 40);">表子查询: 子查询的结果为多行多列</font>
5. <font style="color:rgb(31, 35, 40);">根据子查询的位置可以分为: WHERE之后的,FROM之后的,SELECT之后的</font>

#### <font style="color:rgb(31, 35, 40);">标量子查询</font>
1. <font style="color:rgb(31, 35, 40);">返回的是单个值,最为简单</font>
2. <font style="color:rgb(31, 35, 40);">常用的运算符: 就是各种算数运算符号</font>
3. <font style="color:rgb(31, 35, 40);">引用场景: 就是要查询的数据要经过几步才可以查到的情况就可以考虑使用标量子查询</font>
4. <font style="color:rgb(31, 35, 40);">代码实现:  
</font>![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-08-14-46-21.png)
5. <font style="color:rgb(31, 35, 40);">注意子查询中的代码要包裹在小括号里面(括号中的才叫子查询)</font>

#### <font style="color:rgb(31, 35, 40);">列子查询(其实子查询返回的就是列,可以时多列)</font>
1. <font style="color:rgb(31, 35, 40);">就是指子查询的结果返回的是列</font>
2. <font style="color:rgb(31, 35, 40);">常用的操作符:IN,NOT IN,ANY,SOME,ALL</font>

| <font style="color:rgb(31, 35, 40);">操作符</font> | <font style="color:rgb(31, 35, 40);">描述</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">IN</font> | <font style="color:rgb(31, 35, 40);">在指定的集合范围中,多选一</font> |
| <font style="color:rgb(31, 35, 40);">NOT IN</font> | <font style="color:rgb(31, 35, 40);">不在指定的集合范围中</font> |
| <font style="color:rgb(31, 35, 40);">ANY</font> | <font style="color:rgb(31, 35, 40);">子查询返回列表中,有任意一个满足条件即可</font> |
| <font style="color:rgb(31, 35, 40);">SOME</font> | <font style="color:rgb(31, 35, 40);">与ANY等同,使用SOME的地方可以使用ANY</font> |
| <font style="color:rgb(31, 35, 40);">ALL</font> | <font style="color:rgb(31, 35, 40);">子查询返回列表的所有值多必须满足</font> |


1. <font style="color:rgb(31, 35, 40);">引用场景</font><font style="color:rgb(31, 35, 40);"> </font>![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-08-15-03-28.png)

#### <font style="color:rgb(31, 35, 40);">行子查询(其实就是某一个数据,最后的格式就是  行=行)</font>
1. <font style="color:rgb(31, 35, 40);">行子查询中子查询的结果子查询返回的是一行数据</font>
2. 常用的操作符号: =,<>,IN,NOT IN;
3. 代码实现

![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-08-15-11-03.png)

#### <font style="color:rgb(31, 35, 40);">表子查询</font>
1. <font style="color:rgb(31, 35, 40);">子查询返回的结果是多行多列</font>
2. <font style="color:rgb(31, 35, 40);">常用的操作符: IN</font>
3. <font style="color:rgb(31, 35, 40);">就是把待查询字段组成一个列表,再在子查询得到的列表中查询(表子查询就相当于是多个行子查询的综合)</font>
4. <font style="color:rgb(31, 35, 40);">应用场景: 就是多个行子查询的综合,并且子查询查到的结果包含多个字段和多行,子查询的结果可以作为一张新的表，再次进行多表查询</font>
5. <font style="color:rgb(31, 35, 40);">代码实现:</font><font style="color:rgb(31, 35, 40);"> </font>![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-08-20-41-43.png)

## <font style="color:rgb(31, 35, 40);">刷题总结</font>
1. <font style="color:rgb(31, 35, 40);">对于多表查询,一定要清除每一个表的连接关系,搞清楚每一张表通过内连接外连接或者子查询得到的新表中的字段名和数据值是多少</font>
2. <font style="color:rgb(31, 35, 40);">对于select函数,多表查询得到的可能是一张表,或者一个数据,或者一列数据,一定要根据得到数据的不同做相应的处理,比如得到数字就用它比较大小,得到一列就用来求品均值,得到一行就用来比较多个字段中数据的大小,得到一张表就用来做多表查询或者分组查询</font>
3. <font style="color:rgb(31, 35, 40);">还是子查询结果的运用,注意子查询中的变量与外部还是有关系的,可以把外部变量中有的性质作为得到子表的一个条件,从而得到想要的数据</font>
4. <font style="color:rgb(31, 35, 40);">子查询出现的位置可以是任意的,要根据子查询得到的结果确定</font>

## <font style="color:rgb(31, 35, 40);">事务</font>
1. <font style="color:rgb(31, 35, 40);">事务是一组操作的集合,是一个不可分割的单位,事务会把所有的操作作为一个整体一起向系统提交或者撤销操作请求，就是这些请求要么同时成功,要么同时失败(比如银行转账)</font>
2. <font style="color:rgb(31, 35, 40);">进行事物处理的过程: 首先处理事务之前要开启事务,之后进行回滚事务(就是进行相应的操作),操作完成之后再提交事务</font>
3. <font style="color:rgb(31, 35, 40);">默认mysql的事务是自动提交的,也就是说,当执行一条DML语句时,mysql会立即隐式的提交事务</font>

### <font style="color:rgb(31, 35, 40);">事务的操作</font>
1. <font style="color:rgb(31, 35, 40);">查看/设置事务的提交</font>
    1. <font style="color:rgb(31, 35, 40);">SELECT @@autocommit;(查看事务提交的方式,如果是1的话就是自动提交,如果不是1的话就是非自动提交)</font>
    2. <font style="color:rgb(31, 35, 40);">SET @@autocommit=0;// 设置提交方式为自动提交</font>
2. <font style="color:rgb(31, 35, 40);">提交事务</font>
    1. <font style="color:rgb(31, 35, 40);">COMMIT;</font>
3. <font style="color:rgb(31, 35, 40);">回滚事务</font>
    1. <font style="color:rgb(31, 35, 40);">ROLLBACK;</font>
4. <font style="color:rgb(31, 35, 40);">代码实现：</font>
    1. <font style="color:rgb(31, 35, 40);">方式1:</font><font style="color:rgb(31, 35, 40);"> </font>![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-10-11-44-17.png)

#### <font style="color:rgb(31, 35, 40);">第二种提交事务的方式</font>
1. <font style="color:rgb(31, 35, 40);">开启事务:</font>
    1. <font style="color:rgb(31, 35, 40);">START TRANSACTION 或者 BEGIN;</font>
2. <font style="color:rgb(31, 35, 40);">提交事务:</font>
    1. <font style="color:rgb(31, 35, 40);">COMMIT;</font>
3. <font style="color:rgb(31, 35, 40);">回滚事务:</font>
    1. <font style="color:rgb(31, 35, 40);">ROLLBACK;</font>
4. <font style="color:rgb(31, 35, 40);">代码实现:</font><font style="color:rgb(31, 35, 40);"> </font>![](https://github.com/xzwsloser/mysql-study/raw/master/Mysql%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80%E7%AF%87%E7%AC%94%E8%AE%B0/2024-02-10-11-52-26.png)

### <font style="color:rgb(31, 35, 40);">事务的四大特性(ACID)</font>
1. <font style="color:rgb(31, 35, 40);">原子性(Atomicity): 事务是不可分割的最小操作单元,要么全部成功,要么全部失败</font>
2. <font style="color:rgb(31, 35, 40);">一致性(Consistency): 事务完成时,必须使得所有的数据保持一致的状态(使得数据库中的变量满足原来的条件)</font>
3. <font style="color:rgb(31, 35, 40);">隔离性(Isolation):数据库系统提供的隔离机制,保证事务在不受外部并发操作影响的独立环境下运行(不同事物,互相不影响)</font>
4. <font style="color:rgb(31, 35, 40);">持久性(Durability):事务一旦提交或者回滚,他对数据库中数据的改变就是永久的(变化就会持久化在磁盘中)</font>

### <font style="color:rgb(31, 35, 40);">并发事务引发的问题</font>
1. <font style="color:rgb(31, 35, 40);">并发事务中的问题(就是两个事务同时进行时的问题)</font>

| <font style="color:rgb(31, 35, 40);">问题</font> | <font style="color:rgb(31, 35, 40);">描述</font> |
| --- | --- |
| <font style="color:rgb(31, 35, 40);">脏读</font> | <font style="color:rgb(31, 35, 40);">一个事务读到另外一个事务还没有提交的数据(结果就是读取事务读取的数据还没有更新就会被读取到)(就是一个事务读取到了第二个事务的没有提交的操作)</font> |
| <font style="color:rgb(31, 35, 40);">不可重复读</font> | <font style="color:rgb(31, 35, 40);">一个事务先后读取到同一条记录,但两次读取到的数据不一样(原因就是两次查询之间有另一个事务又提交了修改操作)(就是同一条sql语句在一个事务中的结果不一样)</font> |
| <font style="color:rgb(31, 35, 40);">幻读</font> | <font style="color:rgb(31, 35, 40);">一个事务按照条件查询数据时,没有对应的数据行,但是在插入数据时,有发现这行数据已经存在了,好像出现了"幻影";(发生原因就是查询和插入数据的间隙时间中,又另外一个事务由提交了插入数据行的操作,所以在插入数据时会失败(本质就是主键冲突的问题))(就是会出现查数据时没有要插入的主键但是插入时会由报错,就是因为使用的事务隔离级别中不可重复读会失效但是幻读会产生)(串行化解决问题的关键就是阻塞一个事务的进行)</font> |


### <font style="color:rgb(31, 35, 40);">解决并发事务重复读取的方法--事务的隔离级别</font>
1. <font style="color:rgb(31, 35, 40);">事务的四种隔离级别:</font>
    1. <font style="color:rgb(31, 35, 40);">Read uncommited: 可能出现脏读,不可重复读和幻读</font>
    2. <font style="color:rgb(31, 35, 40);">Read committed: 可能出现不可重复读和幻读</font>
    3. <font style="color:rgb(31, 35, 40);">Repeatable Read(默认): 可能出现幻读</font>
    4. <font style="color:rgb(31, 35, 40);">Serializable: 都可能会出现</font>
2. <font style="color:rgb(31, 35, 40);">从上向下,数据安全性降低,但是级别会逐渐升高</font>
3. <font style="color:rgb(31, 35, 40);">操作语法:</font>
    1. <font style="color:rgb(31, 35, 40);">查看事务的隔离级别: SELECT @@TRANSACTION_ISOLATION</font>
    2. <font style="color:rgb(31, 35, 40);">设置事务隔离级别: SET [SESSION(只有当前窗口可以使用)|GLOBAL(所有操作窗口多可以使用)] TRANSACTION ISOLATION LEVEL {READ UNCOMMITED READ COMMIT REPEATABLE READ SERIALIZABLE};</font>

