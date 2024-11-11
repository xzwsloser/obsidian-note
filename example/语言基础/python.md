# python虚拟环境管理
- 虚拟环境用于防止不同的`python`项目之间发生依赖冲突的问题
```shell
$ python3 -m venv myenv  // 创建虚拟环境

$ source myenv/bin/activate  // 激活虚拟环境

(myenv) $ deactivate   // 退出虚拟环境

python -m venv --clear path/to/venv  // 删除虚拟环境
```
- 虚拟环境中创建了`python`解释器的副本还有各种库
