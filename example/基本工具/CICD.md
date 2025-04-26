## CICD 的含义

- `CI`(持续集成): 持续集成是一种开发实践，要求开发人员将代码频繁地提交到共享代码库中。每次提交代码时，都会通过自动化的流程对代码进行构建和测试，从而快速检测代码中的错误并减少调试时间。同时可以使用 `Github Action` 直接在 `Github` 仓库中创建自定义的 `CI` 流水线,这些流水线可以自动构建代码,运行代码检查工具,执行单元测试或者功能测试等
- `CD`(持续部署): 持续部署是一种自动发布和部署软件更新的实践。它通常与持续集成结合使用。通过自动化流程，代码在部署之前会经过构建和测试。GitHub Actions 允许你设置触发事件（如代码推送到主分支时）来启动持续部署流水线。
## Github Action入门

由于不少的项目构建测试,代码检查的操作都差不多,所以 `github`把这些操作成为一个 `actions` , 并且有一个 `actions` 市场,每一个 `action`可以看作一个脚本,需要使用的时候只需要在自己的 `ci.yaml` 中使用 `uses` 关键字就可以使用了

基本概念如下:
- `workflow`(工作流程): 持续集成一次的过程
- `job`(任务): 一个 `workflow` 由一个或者多个 `jobs` 构成,含义是一次持续集成的运行,可以完成多个任务
- `step`(步骤): 每一个 `job` 由多个 `step` 构建,一步一步完成
- `action`: 每一个 `step` 可以一次执行一次或者多个命令

### workflow
注意 `workflow` 中主要包含如下几个可以设置的字段:
![[Pasted image 20250426195341.png]]
### jobs
需要使用 `jobs` 关键字来声明 `job` , `jobs` 里面定义一个集合,需要把本次需求相关的 `job`都放在这一个集合中,并且在同一个 `workflow` 中的任务一般都是并行的,除非使用 `need` 关键字可以规定先后顺序,`job` 配置如下:
![[Pasted image 20250426195557.png]]

比如单个 `job` 的实现如下:
```yaml
name: learn-github-action   # workflow 名称
on: [push]                  # 设置 workflow 触发时机
jobs:
	checkou-bats-version1: # job_id
		name: checkout-version1-name # job_id.name
		runs-on: unbuntu-latest      # 指定运行的操作系统
		steps:
			- uses: actions/checkout@v2 #使用这一个 actions 脚本
			- uses: actions/setup-node@v3 #安装 nodejs 的脚本 
			  with:
				 node-version: '14'
			- run: npm install -g bats  # 执行命令	
			- run: bats -v
```











