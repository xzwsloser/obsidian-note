c> 记录`git`中的常用命令和一些情况的解决方案
## git branch
- 查看所有分支:
```
git branch -a
```
- 查看远程分支:
```
git branch -r
```
- 设置上游分支:
```
git branch --set-upstream-to=origin/feature-branch
```
- 删除分支,或者删除已经合并的分支:
```
git branch -D <branch-name>  // 删除已经合并的分支
git branch -d <branch-name>  // 强制删除分支
```
- 重命名分支:
```
git branch -m <new-branch-name>
```
- 重新设置上游分支:
```
git branch --unset-upstream
git branch -u origin/<new-branch-name>
```
## git checkout
- 创建并且切换分支:
```
git checkout -b new-branch
git checkout -b feature-branch origin/feature-branch # 拉取远程分支,并且创建本地分支
```
## git push
- 创建远程分支并且`push`:
```
git push -u branch-name origin/branch-name
```
- 删除远程分支:
```
git push --delete <branch-name>
```
## git stash
- 首先需要提交
```
git stash
```
- 重新恢复修改
```
git  stash pop
```

## git log和git reflog
- 查询没有删除的分支的提交:(结合 `git reset --hard`) 使用
```
git log
```
- 查询已经删除的分支的提交:(结合`git cherry-pick`) 使用
```
git reflog
```
## git cherry-pick
- 挑选特定的提交融合到本地分支(不会融合整个分支,只会融合特定的代码):
```
git cherry-pick <commit-hash>
```
## git show
- 展示某一次提交的代码:
```
git show <commit-hash>
```
## 记录
### p1: 切换到新的分支提交之后,切换到原来的分支并且删除之前的分支导致代码丢失
- 解决方法如下:
```
git reflog # 查看已经删除的分支的提交
git show <commit-hash> # 查看已经提交的代码
git cherry-pick <commit-hash> # 融合到本地分支
```
