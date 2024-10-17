>可以参考: [[Mysql数据库基础篇]]
## 查询方式
- 无论对于那一种多表关系,都可以使用`inner join`,`left join`,`right join`的方式对于多表中的关联数据进行查询,同时可以配合不同的条件对于各种情况进行查询,可以得到`A`,`B`之间的差集,交集,并集等(可以使用`union`关键字)
## 一对一关系
- 建表语句如下:
```sql
create table sin_a (  
    aid int primary key  auto_increment,  
    name varchar(20) not null,  
    age int not null  
) comment "tablea";  
  
create table sin_b (  
    bid int primary key auto_increment,  
    password varchar(30) not null,  
    birthday date  
) comment 'tableb';  
  
alter table sin_b add a_id int;  
-- 添加外键盘约束  
alter table sin_b add constraint fore_a_id foreign key (a_id) references sin_a(aid);  
-- 开始添加数据  
insert into sin_a values (null , 'jim' , 12),(null,'bob',20),(null,'judy',30);  
insert into sin_b values (null , '12345' , '2005-10-16' , 1), (null , '23456' , '2007-10-14' , 2) , (null , '3333' , '2008-10-12' , 3);
```
- 查询方式(分别利用`inner join`,`left join`,`right join`进行查询)
```sql
-- inner join  
select a.* , b.* from sin_a a inner join sin_b b on a.aid = b.a_id;  
-- left join  
select a.* , b.* from sin_a a left join sin_b b on a.aid = b.a_id;  
-- right join  
select a.* , b.* from sin_a a right join sin_b b on a.aid = b.a_id;
```
## 一对多关系
- 建表语句如下:
```sql
create table many_a (  
  aid int primary key auto_increment,  
  name varchar(20) not  null,  
  age int not null  
) comment 'one to many one';  
  
create table many_b (  
    bid int primary key auto_increment,  
    classname varchar(20) not null,  
    a_id int,  
    foreign key (a_id) references many_a(aid)  
) comment 'one to many many';  
  
-- 添加数据  
  
insert into many_a values (null , '张三' , 20) , (null , '李四' , 21) , (null , '王五' , 25);  
  
insert into many_b values (null , '高等数学' , 1),(null,'电路理论',1),(null,'模拟电路',2),(null,'数字电路',2),(null,'操作系统',3),(null,'计算机网络' , 3);
```
- 查询语句:
```sql
-- 开始查询  
-- inner join  
select a.* , b.* from many_a a inner join many_b b on a.aid = b.a_id where a.name = '张三';  
-- left join  
select a.* , b.* from many_a a left join many_b b on a.aid = b.a_id where a.name = '李四';  
-- right join  
select a.* , b.* from many_a a right join many_b b on a.aid = b.a_id where a.name = '王五';
```
## 多对多关系
- 建表语句:
```sql
-- 多对多关系  
-- 建立数据库表  
create table mm_a (  
    aid int primary key auto_increment,  
    name varchar(30) not null,  
    age int not null  
) comment 'many to many mm_a';  
  
create table mm_b (  
    bid int primary key auto_increment,  
    classname varchar(30) not null  
);  
  
create table many2many (  
    cid int primary key auto_increment,  
    a_id int,  
    b_id int,  
    foreign key (a_id) references mm_a(aid),  
    foreign key (b_id) references mm_b(bid)  
) comment '中间表';  
  
insert into mm_a values (null , 'z1' , 10) , (null , 'z2' , 20) , (null , 'z3' , 30) , (null , 'z4' , 40) , (null , 'z5' , 50);  
insert into mm_b values (null , 'c1') , (null , 'c2') , (null , 'c3') , (null , 'c4') , (null , 'c5') , (null , 'c6');  
  
insert into many2many values (null , 1 , 2) , (null , 1 , 3) , (null , 2 , 5) , (null , 2 , 6) , (null , 3 , 3 ) , (null , 3 , 4) , (null , 4 , 4) , (null  , 4 , 6) , (null , 5 , 5);
```
- 查询语句
```sql
-- 利用 inner join,看成了两个一对多  
select a.*,b.* from mm_a a inner join many2many c on a.aid = c.a_id inner join mm_b b on b.bid = c.b_id;  
-- 利用 left join
select a.*,b.* from mm_a a left join many2many c on c.a_id = a.aid left join mm_b b on c.b_id = b.bid;  
-- 利用 right
select a.*,b.* from mm_a a right join many2many c on c.a_id = a.aid right join mm_b b on c.b_id = b.bid;
```
- 最后注意在删除或者更新数据的时候,关联这一个数据库表的数据库表的更新或者删除行为由外键约束规定,默认是`NO ACTION`,当然可以改变,比如:
```sql
alter table table_name add constraint fore_key_name foreign key(外键字段) reference main_table(main_column) on update cascade on delete resirict
```