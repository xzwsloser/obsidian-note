# vimtutor
## 移动光标
- `h`  -> 左
- `j` -> 下
- `k` -> 上
- `l` -> 右
## 删除
- 指定的位置键入 `x` 即可删除对应位置的字符
## 插入
- `i`: 进入插入模式,在指定的字符前面插入内容
- `A`:在文章末尾插入元素
- `o` :在光标所在的一行的下行开启一个新行进入插入模式
- `O`: 在光标所在的上一行开启一个新行并且进入插入模式
- `a`: 在当前光标的后面插入
- `R`: 进入替换模式,可以把当前位置的字符进行替换
### 删除类命令
- 在指定的单词的首部键入`dw`即可删除这一个单词,光标跳转到下一个字母的首部
- `d$`从键入位置删除到行首部
### 更改类命令
- 在需要修改的位置的首字母的位置键入`ce`,输入修改之后的值,即可完成修改 (注意进入了插入模式)
- `c [number] motion`  比如 `c 4 w` 表示从当前位置开始向后面修改四个单词,`c $` 表示修改到行末尾
- 剪切操作可以使用`p`使得删除的内容出现在光标的后面
### 定位和文件状态

- 在某一行键入 `CTRL + G` (长按`ctrl`,之后按`g`) 就会显示当前文件的状态以及所在的行号,之后可以进行任意的跳转,想要回到原来的位置只需要键入原来的行号并且按下`G`即可
- `G`表示到文件末尾
- `gg`表示到文件开头

### 搜索类命令
- `/需要搜索的单词` 按下回车之后就可以进行搜索了,`n`表示搜索下一个,`N`表示搜索上一个
- `?需要搜索的单词` 表示反向搜索
- `ctrl + o` 回退到原来的位置,`ctrl + I`撤销回退
- `:set hs` 可以高亮
- `:set ic` 可以忽略大小写
- `:set noic` 可以取消大小写

### 括号匹配

- 在括号的位置或者括号里面内容的位置键入: `%`即可找到相匹配的括号位置

### 修改匹配字符串
- 修改方式:
    - `/s/old/new` 对于某一个行,把这一行中的第一个`old`修改为`new`
    - `/s/old/new/g` 对于某一行,把这一行中的所有的`old`修改为`new`
    - `#,#/s/old/new/(g)` 表示修改两行之间的内容中的`old`为`new`
    - `%s/old/new/(g)` 对于整个文件中的所有内容进行匹配

### 执行外部命令

- `:!` 即可执行外部命令了,注意所有的`:`都必须使用回车结尾
- 比如`:!rm TEST`可以执行删除命令

### 保存文件
- `:w 文件名` 可以使用特定的文件名保留文件
- 可以按住`v`进入可视模式,之后选择一段文字,按下`:`,之后键入保存文件的命令(比如`w TEST`)即可把这一段文字保存为指定的文件

### 合并文件
- `:r 文件或者其他可以输入标准输出的东西` 就可以把之后显示的内容输出到当前光标的下一行

### 动作与数字结合
- 动作(`operator`): 也就是复制删除等动作,比如`y`,`dd`等操作
- 移动(`motion`): 移动比如利用`h j k l`进行移动
- 动作数字和移动可以结合,比如:
    - `dw`表示删除一个单词
    - `de` 表示删除到单词末尾
    - `d$` 表示删除到行末尾
    - `d2w` 表示删除两个单词
- 注意动作在移动之前
- 但是特殊字符比如`$`等在移动动作之后(比如``)

### 撤销
- 撤销移动: `ctrl + o` 恢复到原来的位置: `ctrl + I`
- 撤销上一步的修改: `u` , 撤销整行的修改: `U`

### 操作符号
- `dd`: 表示删除
- `y`: 表示复制
- `p`: 表示粘贴
- `d + p` 可以完成剪切操作

### 帮助文档
- `:help` 即可
- 自动补全功能: `CRTL + D`

### 备忘录
![[Pasted image 20250113092531.png]]
### 跳转到函数定义处
- `ctrl + ]`即可跳转到函数的定义处,同时利用`crtl + o`就可以回退了

# 基础部分

### 窗口,缓冲区,标签
- 每一个文本都是缓冲区的一个部分,都是在特有的缓冲区打开的
- 窗口是缓冲区上一层的视窗,查看文件的不同位置就需要窗口
- 标签就是窗口的集合,需要不同的窗口布局就需要使用标签
- `:vsplit` 表示水平分割屏幕,`:diffsplit` 表示垂直分割屏幕
- `crtl + w p j k l` 分别表示上下,下,上,右移动,左可以使用`p`(表示跳转)
- `crlt + W c` 关闭当前窗口
- `ctrl + W q`关闭当前窗口
- `:only` 仅仅保留当前分屏
- `:hide` 关闭当前分屏

### 缓冲区的状态
- 利用`vim file`命令启动`vim`,会使得文件的内容加载道缓冲区中,如果有一个已经载入的缓冲区,可以在`vim`中保存文件
- 如果键入`:e file2`就会使得`file2`加入缓冲区,但是`file1`变成隐藏的缓冲区
- `:ls` 可以列出所有缓冲区,`:ls!`可以显示被放入缓冲区列表和没有放入列表的缓冲区,未命名的缓冲区是一种没有关联特定文件的缓冲区,可以使用`:enew`创建,添加一些文本可以保存着一个缓冲区中的内容 `:w /temp/foo`

### 按键映射

- 可以使用`:map` 命令定义自己的快捷键,映射可以是递归的也可以是非递归的,递归的映射表示一个键完全替代了应外一个键,需要执行另外一个键的其他功能
![[Pasted image 20250113092656.png]]
- 除非递归映射是必须的,一般都会使用非递归映射
- 映射前置键: `Leader`是一个按键映射,默认为`\`
## B 站Vim 教程补充
### 移动命令
- `{lineno}gg`: 表示跳转到第 `lineno` 行
- `Ctrl + u / Ctrl + b` 向上翻页
- `Ctrl + d / Ctrl + f` 向下翻页
- `zz/zt/zb`: 光标位置设置为页中/页第一行/页最后一行
### 插入命令
- `s`: 删除当前单词进入插入模式
- `S`: 删除当前行进入插入模式
- `A`: 在行末尾插入
### 移动命令补充
#### 基于单词移动
- `e`: 移动到下一个单词的末尾
- `ge`: 移动到上一个单词的末尾
#### 基于搜索的移动
- `f{char}/t{char}` 跳转到下一个`char` 字符出现的前面和后面
- `;/,`: 表示跳转到下一个 `ft` 搜索的位置,或者上一个
- `F{char}/T{char}` 向前面搜索
- `*` 类似于 `/{pattern}` 但是就是搜索光标下的单词
#### 基于标记的搜索
- `m{mark}` 设置标记,比如 `mm`
-  `撇号{mark}` 跳转到`mark`的位置
- 内置标记:
	- `撇号撇号`: 跳转到上一个跳转的位置
	- `撇号.`: 跳转到上一个修改的位置
	- `撇号.^`: 跳转到上一个插入的位置
### 组合命令
#### Operator + Motion = Action
- 比如操作命令和移动命令可以同时使用,比如:
	- `dw`
	- `yw`
- 同时操作命令重复表示作用于一行,比如:
	- `yy`
	- `dd` 
#### {count}Action
- 利用`Action`前面加上数量就可以实现多次操作,比如:
	- `3dw`
	- `2yw`
### 编辑命令
#### 撤销命令
- `.`: 重复上一次修改
- `u`: 撤销上一个修改
- `Ctrl + r`: 重新进行上一次修改
#### 相对行号
- `:set relativenumber` 开启
- `:set norelativenumber` 关闭
#### 补充编辑命令
- `gu/gU/g~` 大小写转换和反转
- `J` 连接上下两行
- `Ctrl + x / Ctrl - a + number`: 数字的增减  
- `可视模式 g Ctrl - a`: 生成递增序列,非常好用(可以用于编辑行号)
- `</>`: 缩近 
#### 文本对象操作
文本对象就是一个文本片段 `{textobj}`,表示方式如下:
- `i`: 表示内部,不包含匹配符号
- `a`: 表示包含匹配符号
文本对象的类型如下:
- `w` 单词 , `s` 句子 , `p` 段落
- `()` , `[]` , `{}` 匹配符
文本对象的构成方法:  `i / a` + 文本对象类型,比如 `iw , aw` 等
文本对象操作: `{operator}{textobj}` 表示把操作放在文本对象上,比如:
- `yi(`
- `diw`
注意,如果不清楚`{textobj}` 的位置,利用可视觉模式 `v{textobj}` 看是否是自己需要的位置即可
### 寄存器与宏定义
寄存器用于保存各种操作,可以利用 `:reg {register}` 查看寄存器中的内容
#### 寄存器 + Operator
- 利用 `"{register}{Action}` 操作可以把操作的值放入到寄存器中,或者从寄存器中取值,比如:
	- `"add`: 表示删除本行放在 `a` 中
	- `"ap`: 表示把 `a` 中的内容粘贴到这一个位置来
- 默认寄存器如下:
	- `"`: 默认寄存器
	- `%`: 文件名称
	- `.`: 上一次插入的内容
	- `:`: 上一次执行的命令
#### 宏定义(非常好用)
利用 `q{register}` 开始链录制宏,之后执行一系列普遍的的操作,利用 `q` 结束录制,之后利用 `@{register}` 就可以防止宏定义,同时 `@@` 表示放置上一次放置的宏定义

同时可以考虑在宏定义中加入移动命令,从而使用 `{count}@{register}` 连续方式宏定义
### 命令模式
#### 命令基本格式
`Ex`命令: `:[range] {excommand} [args]` 范围 + 命令 + 参数,默认操作行,同时也可以使用 `[x]` 作为寄存器:
- 比如 `print`  , `delete [x]`
#### `address` 组合成为 `range`
- `1,3` 表示文件的 `1 - 3` 行
- `. , .+4` 当前,当前向下四行 , `.` 表示当前行,注意包含当前行
- `$-3,$`: 最后四行,`$` 表示最后一行
- `%` 表示所有行
- `< / >` 表示可视模式下选中范围的开头和结尾
#### 行的复制移动和粘贴
- `:[range] copy {address}` 把 `range` 的内容复制到 `address` 后面
- `:[range] move {address}` 把`range` 中的内容移动到 `address` 后面
- `:[address] pux [x]`  把 `x` 的内容粘贴到 `address` 后面
- `0` 是虚拟的位置
#### 批量操作 normal 命令
- 规则: `:[range] normal {commands}` 对于范围里面的行执行命令
- 技巧:
	- `:range normal .` 执行上一次命令效果拔群
	- `:range normal @{register}` 可以结合宏定义来做
#### 批量操作 global 命令
- 规则: `:[range] global/{pattern}/[cmd]` 可以对于包含 `pattern` 的行执行命令,注意`normal` 命令也可以,比如可以使用 `:[range] global/{pattern}/normal {command}` ,同时比如 `:% global/TODO/delete` 可以删除所有带有 `TODO` 的行
#### 替换命令
- `:[range] s/{pattern}/{string}/[flags]` 把`pattern`替换为`string`
- `flags`:
	- `g`: 替换每一行的所有匹配位置
	- `i`: 忽略大小写
	- `c`: 替换前进行确认
	- `n`: 计数而不是替换
- 比如: `%s/vim//gn`
## neovim配置以及基本使用(基于 LazyVim框架)
- 首先`LazyVim` 相关的配置文件结构如下:
```
├── init.lua
├── lazy-lock.json
├── lazyvim.json
├── LICENSE
├── lua
│   ├── config
│   │   ├── autocmds.lua
│   │   ├── keymaps.lua
│   │   ├── lazy.lua
│   │   └── options.lua
│   └── plugins
│       └── example.lua
├── README.md
└── stylua.toml
```
- 其中 `init.lua` 用于加载各种插件的配置文件
- `lua/config` 中记录着各种配置:
	- `keymaps`: 表示配置键位
	- `options`: 表示配置编辑选项,比如是否开启相对行号
- `plugins` 用于安装各种插件,比如需要安装一个插件就可以在这一个文件夹下新建一个文件并且填入配置信息即可,同时也可以新建一个 `disable.lua` 来记录插件启用情况
## LazyVim 基本使用技巧
> 参考:  https://www.lazyvim.org/keymaps

### 快捷键和命令的设置
- 配置文件目录结构如下:
```txt
├── init.lua
├── lazy-lock.json
├── lazyvim.json
├── LICENSE
├── lua
│   ├── config
│   │   ├── autocmds.lua
│   │   ├── keymaps.lua
│   │   ├── lazy.lua
│   │   └── options.lua
│   └── plugins
│       └── example.lua
├── README.md
└── stylua.toml
```
- 修改键位:  修改 `lua/config/keymaps.lua` 即可
- 修改选项:  修改`lua/config/options.lua`即可
### 安装插件
- 一般来说,`LazyExtra`中的额外插件就够使用了,所以可以使用 `:LazyExtra`命令来安装额外插件
- 另外安装第三方插件需要在 `lua/plugins`文件夹下建立 `*.lua` 文件并且按照 `LazyVim` 要求的方式配置(还需要实践)
### 常用快捷键
- `Ctrl + h , j , k , l` : 移动到上下左右的窗口位置
- `Ctrl + left , right , up  , down`: 增大/减小窗口的长度或者宽度的大小
- `Alt + j , k`: 在任何模式下上下移动行/代码块
- `Shift + h , l`: 左右移动到旁边的标签页
- `<leader>bd`: **删除缓冲区**
- `<leader>bD`: 删除缓冲区和窗口
- `<leader>bo`: 删除其他缓冲区
- `<leader>ur`: 清除高亮标记
- `Ctrl + s`: 保存文件
- `<leader>K`: 比如可以显示系统调用的文档,或者标准 C 库的文档
- `gco , gcO`: 在上面或者下面添加注释
- `<leader>l`: 启动插件管理栏
- 各种 `Toggle` 命令比较有意思,可以参考 文档,比如
- `<leader>ub`: 切换背景
- `<leader>uL`: 切换相对行号的显示
- `<leader>gb`: 显示当前文件提交信息
- `<leader>ft`: 调出终端
- `<leader>-`: 在下面分割出来屏幕
- `<leader>|`: 子右边分割出来屏幕
- `<leader>wd`: (Windows Delete) 删除窗口
- `<leader>uf`: 是否取消保存时候自动不全
- `[e , ]e`: 进行错误的跳转
### 代码跳转
- 利用 `ctags` 工具生成跳转标签,利用 `ctrl + [` 跳转到函数的实现位置
- 如果写对了头文件的路径就可以使用  `gd` 可以进行实现找到定义,定义找到实现
### LSP
- 可以使用 `<leader>cl`进入到 `LSP` 管理界面,或者使用 `:Mason`也可以,找到需要的语言的`LSP`即可
### buffer
- `<leader>bl` 删除左边的缓冲区
- `<leader>bp` 是否钉住缓冲区
- `<leader>bP` 删除没钉住的缓冲区
- `<leader>br` 删除右边的缓冲区
### fzf(很好用的搜索插件)
- `<leader><space>`: 查找文件
- `<leader>/` 类似于 `Grep` 查找关键词
- `<leader>:` 命令历史
- `<leader>fb`: 查找缓冲区
- `<leader>fc`: 寻找配置文件
- `<leader>ff`: 和第一个一样
- `<leader>fF`: 工作目录查找,还是类似
- `<leader>fg`: 查找`git`文件
- `<leader>fr`: 查找最近的文件
- `<leader>gc`: 查看提交
- `<leader>gs`: 查看状态
- `<leader>sg`: 类似于上面的`Grep`,只不过是全局的
- `<leader>sG`: 当前工作目录寻找
- `<leader>ss`: 查找本文件中的符号,比如函数等
- `<leader>sS`: 查找工作空间中的类函数等
- `<leader>sw`: 还是和 `sg` 一样的
- `<leader>uC`: 切换主题,挺好玩的
### grug-far(感觉比较好用)
- `<leader>sr` 匹配搜索到的单词
### Mason
- `<leader>cm`: 用于开启`Mason`,安装各种语言的自动提示
### neo-tree
- `<leader> be` 打开当前文件夹
- `<leader>e` 打开/关闭文件夹
- `<leader>fe` 一样
- `<leader>ge` 打开`Git` 文件夹(没有追踪的)
### noice(不知道有什么用)
- `<c-b>` 向后面滚动
- `<c-f>` 向前面滚动
- `<leader>sn` 添加注意事项
### CopilotChat
- `<leader> aa` 打开聊天框
- `<leader> ap` 指定行为感觉没用
- `<leader> aq` 快速提问
- `<leader> ax` 清除屏幕

搜索当前单词: `*` 搜索下一个 ，`#` 搜索上一个