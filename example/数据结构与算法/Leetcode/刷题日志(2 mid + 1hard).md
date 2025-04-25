> 记录刷题日志

# 2.19
1. [Z变化](https://leetcode.cn/problems/zigzag-conversion/description/) 利用一个字符串数组存储,简单模拟即可
2. [整数的反转](https://leetcode.cn/problems/reverse-integer/description/) 看似简单但是并非如此,注意到反转的基本操作: `res = res * 10 + x % 10` ,并且需要每一次都检测 `res < INT_MIN || res > INT_MAX`是否为 `false` , 推导过程可以参考官方的题解(注意力惊人!!!)
3. [正则匹配](https://leetcode.cn/problems/regular-expression-matching/description/) 恭喜成功入选 [[Hard]] , 有意思的一道题目,感觉和编辑距离问题类似

# 2.20
1. [字符串转换整数(atoi)](https://leetcode.cn/problems/string-to-integer-atoi/description/)  模拟题目,没什么意思
2. [最接近的三数之和](https://leetcode.cn/problems/3sum-closest/description/) 排序 + 三指针,和三数之和一模一样,甚至更简单
3. [两数相除](https://leetcode.cn/problems/divide-two-integers/description/) 算是思路惊奇的一道题目,类似于不断二分,核心代码如下:
```c++
long div(long a , long b) {
	if(a < b) return 0;
	long tb = b;
	long count = 1;
	while((tb + tb) <= a) {
		count = count + count;
		tb = tb + tb;_	
	}
	return count + div(a - tb , b);
}
```
注意到最后一句话等效于:
$$
k + \frac{a - kb}{b} = \frac{a}{b}
$$
# 2.21 
1. [有效的数独](https://leetcode.cn/problems/valid-sudoku/description/) 简单模拟 + 哈希 , 没有什么好说的
2. [外观数列](https://leetcode.cn/problems/count-and-say/description/) 简单,没有什么好说的
3. [串联字符串所有单词的子串](https://leetcode.cn/problems/substring-with-concatenation-of-all-words/description/) 入选 [[Hard]]  
# 2.22
1. [字符串相乘](https://leetcode.cn/problems/multiply-strings/) 比较有意思的一个题目,本质上就是对于竖式的一个优化,只需要维护一个数组,并且把结构的每一个位存储在数组中即可,但是注意到一个结论, `num1[i]` 和 `num2[j]` 相乘的结构总共有两位,一个在 `res[i + j]` 的位置上面(这里就是进位) , 另外一个在 `res[i + j + 1]` 上面,可以这样理解(比如对于`num2` , 索引的位置也就是表示开始的位置,对于 `num1` 只是加上了一个偏移即可):
![[Pasted image 20250222154041.png]]


2. [Power(x,n)](https://leetcode.cn/problems/powx-n/) 快速幂,可以使用二进制的方法理解或者使用分治法来理解
$$
n = 2^0 b_1 + 2 ^ 1 b_2 + 2^2 b_3 + ... + 2^nb_{n + 1}
$$
$$
x^n = x^{2^0 b_1 + 2 ^ 1 b_2 + 2^2 b_3 + ... + 2^nb_{n + 1}}= x^{2^0b_1}x^{2^1b_2}x^{2^2b_3}...x^{2^nb_{n + 1}}
$$
所以每一次只需要不断取得 `n` 的二进制位置并且把 `x` 平方即可,核心代码如下:
```c++
while(n != 0) {
	if((n & 1) == 1) res *= x;
	x *= x;
	n >>= 1;	
}
```
当然也可以使用分治的方法:
![[Pasted image 20250222154755.png]]




3 . [通配符匹配](https://leetcode.cn/problems/wildcard-matching/description/) 和正则表达式类似,但是更加简单,使用 `dp` 即可,但是注意到通佩符('*')在最后并且匹配 `0` 个字符的情况即可

# 2.23 
写了一天的 `CURD` , 没有刷题 ...
# 2.24
1. [插入区间](https://leetcode.cn/problems/insert-interval/) 个人感觉自己的写法`corner case`太多了,也就是分区间和最后一个区间交叉,和区间在最后一个区间前面两种情况,利用一个变量记录是否插入即可
2. [旋转链表](https://leetcode.cn/problems/rotate-list/description/) 倒数第 `K` 个节点 + 链表操作,比旋转数组还简单
3. [排列序列](https://leetcode.cn/problems/permutation-sequence/) 我的做法是和`HOT100` 中最后一个排列有关的,代码随想录里面真是写的依托 , 还让找规律,不抓住事物的本质,官方题解中的答案感觉比较困难,也就是无法每一次找到哪一个元素为排列的第一个元素,可以看一下官方题解中的题目,技巧太多了,之后可以看一下吧
# 2.25 
1. [合并有序数组](https://leetcode.cn/problems/merge-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150) 利用三个指针,三个指针分别为 `i = m - 1 , j = n - 1 k = m + n - 1` , 也就是 `k` 指向了新数组的最后一个位置
2. [反转链表 II](https://leetcode.cn/problems/reverse-linked-list-ii/description/) 注意使用虚拟头节点,避免对于是否头节点的讨论即可
# 2.26
实验报告,课太多了...
# 2.27
开始刷 面试经典 150 题目了,大部分原题,刷了 11 道题目
1. [删除数组中的重复项II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/description/?envType=study-plan-v2&envId=top-interview-150)  我的方法是利用一个 `curCount` 来记录出现的次数,题解中的方法是利用 `nums[r] != nums[l - x]` 来进行求解,其实都差不多,最终返回 `l`
2. [H指数](https://leetcode.cn/problems/h-index/description/?envType=study-plan-v2&envId=top-interview-150) 我的方法是利用哈希表进行统计,从后面向前面统计,每一次累积加上 `hash[i]` , 直到`cnt >= i` 就可以返回 `i` 了,类似于灵神的方法,但是注意到大于 `n` 的可以作为 `n` 计算,所以空间就是 `n + 1` 就可以了,但是当`n` 比较大的时候还是我的方法比较好

# 3.3 
中间时间写了项目,没有时间做 ......

1. [反转字符串中的单词](https://leetcode.cn/problems/reverse-words-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150) 自我认为最好的方法就是双指针 + 后序遍历即可,也就是让 `i` 从 `s.size() - 1` 开始向前面遍历,另外一个指针记录着结尾位置,遍历的指针记录头的位置
2. [分割回文子串III](https://leetcode.cn/problems/palindrome-partitioning-iii/?envType=daily-question&envId=2025-03-03) 缝合怪,感觉有一点找回文子串的味道以及编辑距离的味道,入选 [[Hard]] 
# 3.4 
1. [分割回文子串IV](https://leetcode.cn/problems/palindrome-partitioning-iv/description/?envType=daily-question&envId=2025-03-04) 参考上面一道题目,感觉上面一道题目才是最难的,并且注意到可以使用`dp` 判断区间内的回文串
2. [文本对齐](https://leetcode.cn/problems/text-justification/solutions/987057/gong-shui-san-xie-zi-fu-chuan-mo-ni-by-a-s3v7/?envType=study-plan-v2&envId=top-interview-150)情况很多的模拟题目,纯纯恶心人,`40min AC` ,`corner case` 太多了,难点在于空格的分配
3. [字符匹配](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150) [[KMP算法]] 没什么好说的
# 3.5
主要复习了一下滑动窗口的题目,以及做了每日一题(比前面几天的简单不少)

滑动窗口分为三类问题,遇到具体问题需要具体考虑:
- 求解 "最小,最短": 参考面试经典滑动窗口中的 1 4 题目
- 求解满足特定条件的位置: 3 
- 求解 "最长"

下面总结三种题目的解题方法:
- 最小,最短类题目,参考如下模板即可:
```c++
int left = 0;
for(int right = 0 ; right < s.size() ; right ++) {
	 把 right 位置对应的元素加入到滑动窗口中
	 while(题目中的条件) {
		 记录最大值 比如 ans = max(ans , right - left + 1)
		left 位置的值离开滑动窗口
		left ++
	 }
}
```
- 最长类题目: 一般是判断条件是否满足,如果条件不满足移动指针让条件满足即可
```c++
int left = 0;
for(int right = 0 ; right < s.size() ; right ++) {
	if(满足条件) {
		加入元素
	} else {
		while(!条件) {
			移除 left 元素
			left ++
		}
	}
	收集结果
}
```
- 定长窗口类问题: 感觉没有什么固定的解法,和上面差不多,只是需要注意到每一次移除的元素和加入的元素个数一样即可,参考 [串联所有单词的子串](https://leetcode.cn/problems/minimum-window-substring/description/?envType=study-plan-v2&envId=top-interview-150)
# 3.6 
1. [统计美丽子数组树目](https://leetcode.cn/problems/count-the-number-of-beautiful-subarrays/?envType=daily-question&envId=2025-03-06) 很考察直觉的一个题目,注意到其实就是求解子数组中的所有数组异或为 `0` 即可,看到了子数组,所以想到前缀表的做法,进行数学推导,可以发现 `a ^ b ^ c ^ d = e` 并且 `a ^ b = f` , 则有 `a ^ b ^ c ^ d ^ (a ^ b) = 0 ^ c ^ d = e ^ f` , 所以只需要 `prefix[i] ^ prefix[j] == 0` ,那么 `i - j` 之间的数组就是满足要求的位置,同时注意到如果两个数组异或为 `0` ,那么说明两个数字相等,所以想到使用哈希表来查询,时间复杂度为 `O(N)` 
# 3.7
1. [美丽数组的个数](https://leetcode.cn/problems/the-number-of-beautiful-subsets/description/?envType=daily-question&envId=2025-03-07) 如果使用回溯是一道 `middle` , 如果利用回溯算法,就是 `hard`
之后刷了一下面试经典 `150`题中的矩阵题目
# 3.10
1. [生命游戏](https://leetcode.cn/problems/game-of-life/description/?envType=study-plan-v2&envId=top-interview-150) 对于数组进行标记即可,比如死细胞可以标记为负数,或者使用 `int` 的倒数第二个字节存储死亡或者存活信息即可
2. [单词规律](https://leetcode.cn/problems/word-pattern/description/?envType=study-plan-v2&envId=top-interview-150) 简单题搞半天,实际上就是一个双射关系,分为两个单射即可,遍历两次即可,当然也可以遍历一次
刷了原题  ......
# 3.11
1. [数组美丽值求和](https://leetcode.cn/problems/sum-of-beauty-in-the-array/description/?envType=daily-question&envId=2025-03-11) 也就是右边没有比当前元素小的元素,左边没有比当前元素大的元素,找到后面元素的最小值即可,同时可以在记录答案的同时寻找前面元素的最大值,也可使用单调栈
2. [寻找目标值](https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/description/) 从右上角开始即可
3. [锯齿状遍历](https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/) 层序遍历变种,不用多说了

# 3.12 
1. [元音辅音字符串计数 I](https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/)  很有意思的一个滑动窗口问题,看下面一个引导(灵神yyds)
```text
问：某班有 10 个人至少 20 岁，3 个人至少 21 岁，那么恰好 20 岁的人有多少个？

答：「至少 20 岁」可以分成「恰好 20 岁」和「至少 21 岁」，所以「至少 20 岁」的人数减去「至少 21 岁」的人数，就是「恰好 20 岁」的人数，即 10−3=7。

作者：灵茶山艾府
链接：https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/solutions/2934309/liang-ci-hua-chuang-pythonjavacgo-by-end-2lpz/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


所以这一个题目只需要分为至少 `k`个辅音 和 至少 `k + 1` 个辅音,最终的结果就是:
```c++
count(word , k) - count(word , k + 1);
```
这就是恰好类题目的解法
2. [简化路径](https://leetcode.cn/problems/simplify-path/description/?envType=study-plan-v2&envId=top-interview-150) 利用两个指针 `left` 和 `right` 分别控制字符的开始和结束位置即可,如果是 `..` 弹出之前的,如果是 `.` 直接跳过即可
3. [IPO](https://leetcode.cn/problems/ipo/solutions/985099/gong-shui-san-xie-noxiang-xin-ke-xue-xi-fk1ra/?envType=study-plan-v2&envId=top-interview-150)思路比较简单,也就是每一次只需要把需要的利润小于 `w` 对应的利润加入到堆中,每一次取堆中最的元素即可,但是写出来还是比较难的,这里可以首先把成本以及利润进行排序操作 
# 3.13
1. 每日一题: 和昨天一样
2. [分隔链表](https://leetcode.cn/problems/partition-list/description/?envType=study-plan-v2&envId=top-interview-150) 需要一次遍历并且使用原地算法 , 使用双指针,但是注意首先需要把 pre 移动到第一个满足 pre -> next -> val < x 的位置,cur移动到 pre -> next 的位置,并且注意循环中使用 while 防止 cur 移动之后忽略当前节点
3. [二叉树中序遍历迭代器](https://leetcode.cn/problems/binary-search-tree-iterator/description/?envType=study-plan-v2&envId=top-interview-150) 就是把遍历的过程拆分为 `next` 和 `hasnext` 两个函数,也就是分别使用 `while` 中的条件替代 `hasnext` , 使用 `next` 中的代码替换 循环体里面的代码即可,中序遍历的过程如下:
![[Pasted image 20250313194259.png]]
代码实现: https://leetcode.cn/problems/binary-tree-inorder-traversal/
# 3.14
1. 每日一题: `easy` 不用说了
2. [被围绕的区域](https://leetcode.cn/problems/surrounded-regions/description/?envType=study-plan-v2&envId=top-interview-150) 从边界开始遍历遍历到的位置标记为 `*` 即可
3. [克隆图](https://leetcode.cn/problems/clone-graph/description/?envType=study-plan-v2&envId=top-interview-150) 类似于随机链表的复制,只需要在遍历的时候不断构建链表即可,注意在构建子节点之后需要把子结点加入到原来的父节点下面的集合中
4. [基本计算器](https://leetcode.cn/problems/basic-calculator/description/?envType=study-plan-v2&envId=top-interview-150) `corner case`太多了,没有考虑清楚
# 3.17
中间打了周赛
1. [使字符串平衡](https://leetcode.cn/problems/minimum-number-of-swaps-to-make-the-string-balanced/?envType=daily-question&envId=2025-03-17) 贪心问题的关键在与问题的转换,需要考虑局部到整体的关系,比如最小糖果数量这一道题目,只需要考虑一个孩子两边的孩子即可,也就是首先需要转换问题,之后在拆解的问题中从局部到整体考虑,比如本体中把可以这样思考:  在平衡字符串中的前缀中,左括号的数量一定大于或者等于右括号的数量  ---> 交换的时候需要把左括号尽量交换到前缀的位置 ---> 需要把最后的左括号交换到前面不匹配的右括号的位置 , 解法如下,代码很短但是比较难想:
```c++
int c = 0 , ans = 0;
for(char b : s) {
	if(b == '[') {
		c ++;	
	} else if(c > 0) {
		c --;
	} else {
		ans ++;	
		c ++;
	}
	return ans // 也可以是 c / 2
}
```
这里可以返回 `c / 2` 表示本来需要 `-1` , 但是最后 `+ 1` , 所以最后每交换一次增加了 `2` , 所以可以返回 `c / 2`

2. [基本计算器](https://leetcode.cn/problems/basic-calculator/?envType=study-plan-v2&envId=top-interview-150) 可能是编译原理课程上面的课程设计水平吧,但是这一道题目 `LeetCode` 中的 `corner case` 太多了,感觉是一道 顶级`hard` , 参考 [[Hard]] 
3. [除法求值](https://leetcode.cn/problems/evaluate-division/solutions/3078710/bi-jiao-jian-duan-de-dfszuo-fa-yong-shi-r5wmf/?envType=study-plan-v2&envId=top-interview-150) 进行分解即可 
$$
\frac{a}{c} = \frac{a}{b} * \frac{b}{c}
$$
记录 `a -> b` 以及 `b -> a` 的映射关系即可,可以使用 `pair` 存储 分母和值

# 3.18
破 `300` 题目 !!!
![[Pasted image 20250318190314.png]]
1. [对角线上的质数](https://leetcode.cn/problems/prime-in-diagonal/description/?envType=daily-question&envId=2025-03-18) 注意这里判断质数的方式,最后只需要遍历到 $\sqrt x$  即可
2. [课程表II](https://leetcode.cn/problems/course-schedule-ii/description/?envType=study-plan-v2&envId=top-interview-150) 简单的拓扑排序,入度为 `0` 的点进入到队列中即可
3. [蛇形棋](https://leetcode.cn/problems/snakes-and-ladders/description/?envType=study-plan-v2&envId=top-interview-150) 求解最短路径统一使用 `bfs` , 并且 `queue` 的结构可以定义为 `queue<pair<int,int>>` , 前面一个元素表示遍历到的位置,后面一个元素表示当前步数,但是注意去重
4. [最小基因变化](https://leetcode.cn/problems/minimum-genetic-mutation/description/?envType=study-plan-v2&envId=top-interview-150) 和上面一样,下面总计这一类题目的模板:
```c++
void bfs(容器, 当前位置) {
	queue<pair<dataType , int>> que;
	que.emplace(当前位置 , 0);
	unordered_set<dataType> 去重集合;

	while(!que.empty()) {
		auto p = que.front(); que.pop();	
		for(选择关联元素) {
			if(满足条件) {
				return cur.second + 1;	
			}
			if(没有浏览过) {
				que.push(遍历到的元素 , cur.second + 1);	
				去重集合.insert(遍历到的元素);
			}	
		}
	}
}
```
# 3.19
1. [转换二维数组](https://leetcode.cn/problems/convert-an-array-into-a-2d-array-with-conditions/?envType=daily-question&envId=2025-03-19)  看到题目中的元素大小限制容易想到哈希表 , 直接使用哈希表记录元素即可,同时也可使用 `less` 记录种类数量,之后遍历的过程中找到不同种类数量的数字为 `0` 即可,应该是一道 `easy` 题
2. [添加和搜索单词](https://leetcode.cn/problems/design-add-and-search-words-data-structure/description/?envType=study-plan-v2&envId=top-interview-150) 容易想到 `Trie` 前缀树,但是这里的难点在于 `.` 的处理,并且注意一个问题:  **开始的一个节点要对应开始的第一个字符**  这里使用递归函数进行搜索: 
	- 遇到非 `.`  直接下一步,正常搜索
	- 遇到 `.`  如果是最后一个字符,那么就需要看下面是否还有一个字符,如果没有字符了,返回 `false` , 否则返回 `true`,如果不是最后一个字符,开始遍历下面非空的节点,并且传入非空节点和截取的子字符串
3. [单词搜索II](https://leetcode.cn/problems/word-search-ii/description/?envType=study-plan-v2&envId=top-interview-150) 自己做出来的 `Hard` + 1 !!! , 使用 `Trie + dfs` , 由于这里涉及到的子字符串太多了,所以可以首先使用 `Trie` 来插入各种子字符串,之后在`dfs` 遍历的过程中像结果集合中加入元素即可, 注意递归函数的入参和当前遍历位置的关系,注意 `dfs`  的处理和外层的处理一定需要一致
# 3.20
1. [最少翻转操作数](https://leetcode.cn/problems/minimum-reverse-operations/description/?envType=daily-question&envId=2025-03-20) 感觉是一道顶级 `Hard` 了 , 具体思路就是可以观察对于任意的下标 `i` , 可以发现每一次翻转之后的位置变成  `L + R - i` , 并且当滑动窗口开始移动的时候, `i` 的下标可以增加 `2` 或者减少 `2` , 所以可以发现下标是奇数和下标是偶数的可以经过一次翻转得到(**注意这里表示`bfs`的下一层** )  , 有一点类似于 `Hot100` 的最后一道题目,这里可以把所有可以翻着得到的位置连接一条边,从而形成一个图,为了找到最近距离使用 `bfs` 即可 , 还是看灵神的题解吧,比较清晰(注意边界的区分)    
2. [建立四叉树](https://leetcode.cn/problems/construct-quad-tree/solutions/1457069/by-ac_oier-maul/?envType=study-plan-v2&envId=top-interview-150) 很简单的一道递归题,注意到可以使用开始下标和边长来表示矩阵即可
3. [环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/?envType=study-plan-v2&envId=top-interview-150) 我使用了滑动窗口, 击败 百分之五 。。。 , 灵神强,记录最大子数组值和最小子数组值,最后的答案为 `max(max_s , sum - min_s)` 分为横跨和没有横跨两种情况,最后注意为了防止结果集为空 , 需要讨论 `sum` 和 `min_s` 的关系,如果相等,相当于不存在 `sum - min_s)` 项,很好的一道题目
# 3.21
1. [最大或值](https://leetcode.cn/problems/maximum-or/?envType=daily-question&envId=2025-03-21) 第一种思路使用前后缀分解 ,  `suf[i] = nums[i + 1] | ... | nums[n - 1]`  , 同时在遍历的过程中记录前缀,同时注意只需要一个数字移动 `k` 位即可 , 也就是最终可以得到的答案为: `pre | (long long)nums[i] << k | suf[i]` , 至于方法二,没有看懂为什么那一个等式成立
2. [查找峰值](https://leetcode.cn/problems/find-peak-element/?envType=study-plan-v2&envId=top-interview-150)  经典的二分查找题目,思路还是比较清晰的, **注意二分查找的本质就是缩小查找区间,不断根据中间值来确定答案所在的位置**  , 这里我与原来的做法是判断中点的状态,从而决定两端的移动,其实不需要只需要判断当前元素和下面一个元素的大小关系即可,注意 `right` 从 `n - 2` 开始防止索引超过边界

3. [查找和最小的 `K` 对数](https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/description/?envType=study-plan-v2&envId=top-interview-150)  注意到如果 $(i , j)$ 为当前最小值,那么下一个最小值就是 $(i + 1 , j)$ 或者 $(i , j + 1)$ ,所以可以模仿 `bfs` 的原理,把当前值加入到堆中,并且每一次出堆的时候就把这两个元素加入到堆中并且把当前元素加入到集合中 , 感觉类似于  堆 + `bfs`  + 动态规划 , 状态转移方式如下(注意到每一次只是把 $(i , 0)$入堆,这样可以防止重复),每一次只需要把 $(i , j + 1)$ 入堆即可!!!
![[Pasted image 20250321151238.png]]
# 3.22
1. 每日一题: 很简单不用说了
2. [只出现一次的数字II](https://leetcode.cn/problems/single-number-ii/description/?envType=study-plan-v2&envId=top-interview-150) 核心思路就是下面这一句话:
 
**如下图所示，考虑数字的二进制形式，对于出现三次的数字，各 二进制位 出现的次数都是 3 的倍数。**
**因此，统计所有数字的各二进制位中 1 的出现次数，并对 3 求余，结果则为只出现一次的数字。**

第一种方法状态机,这里之需要一个累积输入了三次相同的输入就会回到原来状态的状态机,所以可以抽象出原来的状态机模型:
![[Pasted image 20250322193507.png]]
当然可以使用卡诺图来确定逻辑表达式,但是考虑到 `x ^ 0 = x` , `x ^ 1 = ~x` , 所以可以发现如果使用 `one` 表示第一个位置 , `two` 表示第二个位置,那么就可以得到递推关系如下:
```shell
one = one ^ num & (~two) 
two = two ^ num & (~one)
```
或者一种比较好理解的方法就是统计数位,并且最后把每一个位置上面 `1` 的个数 模 `3` 最后进行拼接即可
3. [数字范围按位与](https://leetcode.cn/problems/bitwise-and-of-numbers-range/description/?envType=study-plan-v2&envId=top-interview-150)  假设 `m` 和 `n` 的公共前缀未 `prefix` , 那么 `prefix` 的下一个位置一定是 `0 or 1` , 所以`m` 可以表示为  `prefix0abcdefs....` , 并且 `n` 可以表示为 `prefix1hijklmn...` , 所以两者之后的位置一定会经过 `prefix10000...` , 所以最终的结果就是 `prefix0000...`,所以之需要找到不同的最高位即可,同时可以使用一个变量来不断记录取出的数字
```c++
class Solution {
public:
	int rangeBitwiseAnd(int m , int n) {
		int mask = 1 << 30;
		int anw = 0;
		
		while(mask > 0 && (m & mask) == (n & mask)) {
		anw |= m & mask;
		mask >>= 1;
		}
		
		return anw;
	}

};
```

# 3.23 
1. [判断一个数字字符是否有效](https://leetcode.cn/problems/check-if-a-parentheses-string-can-be-valid/description/?envType=daily-question&envId=2025-03-23) 如果利用 `dp` 的话,子状态依赖于之后的状态做不出来,可以这样思考,每一次把 `locked[i] == 0` 的位置的括号记录为 `?` , 可以不断变化,所以这个时候只需要不断记录 `c(没有匹配的左括号数量)` 的取值范围即可,最后只需要判断 `c` 的取值范围 `= 0` 即可,并且注意在这一个过程中 , `c` 取值范围只可以时连续的奇数 or 偶数(距离每一次增加 `2` , 并且无法修改时同步)
2. [属性图](https://leetcode.cn/problems/properties-graph/description/?slug=find-the-minimum-amount-of-time-to-brew-potions&region=local_v2) 思路还是简单的, 并查集 即可 , 把所有满足条件的位置加入到并查集中,并且统计 `0 - n` 范围内 `i == father[i]` 的个数即可(使用并查集的压缩存储)
3. [酿造药水需要的最少总时间](https://leetcode.cn/problems/find-the-minimum-amount-of-time-to-brew-potions/?slug=find-the-minimum-amount-of-time-to-brew-potions&region=local_v2) **思路大概是正确的,一层一层递推,正推: `min_time[i] = max(sum_t , min_time[i - 1]) + skill[i] * m` , 反推: `min_time[i] = sum_t - skill[i + 1] * m` , 正推一遍,反推一遍即可,比较好的一道题目**
```c++
class Solution {
public:
long long minTime(vector<int>& skill, vector<int>& mana) {
	int n = skill.size();
	vector<long long> last_finish(n);
	for(int m : mana) {
		long long sum_t;
		for (int i = 0 ; i < n ; i ++) {
			sum_t = max(sum_t , last_finish[i]) + skill[i] * m;
		}
	
		last_finish[n - 1] = sum_t;
	
		for (int i = n - 2 ; i >= 0 ; i --) {
			sum_t -= skill[i + 1] * m;
			last_finish[i] = sum_t;
		}
	
	}
	return last_finish[n - 1];
}
};
```
# 3.24
1. 每日一题: `easy`
2. [阶乘之后的 0](https://leetcode.cn/problems/factorial-trailing-zeroes/description/?envType=study-plan-v2&envId=top-interview-150) 质因子分解,一道数学题,考虑到 `10 = 2 x 5` , 所以只需要求解 `n!` 中质因子`2`的个数和质因子 `5` 的个数之中的较小值即可,但是考虑到质因子 `5` 的个数总是小于或者等于 `2` , 所以之需要考虑质因子 `5` 的个数,代码实现如下
```c++
class Solution { 
public: 
	int trailingZeroes(int n) { 
	int ans = 0; 
	while (n) { n /= 5; ans += n; } 
		 return ans; 
	} 
};
```
2. [三角形最小路径和](https://leetcode.cn/problems/triangle/description/?envType=study-plan-v2&envId=top-interview-150) 设置同样形状的 `dp` 数组, `dp[i][j]` 表示遍历到 `(i , j)` 位置的最小路径,自顶向下或者自下向上都可以
3. [交错字符串](https://leetcode.cn/problems/interleaving-string/description/?envType=study-plan-v2&envId=top-interview-150)  `dp` 思路还是比较明显的 , `dp[i][j]` 表示长度为 `i` 的子字符串 `s1` 和长度为 `j` 的子字符串 `s2`  交错之后是否形成长度为 `i + j` 的 `s3` 的子字符串,递推公式还是可以理解成选 or 不选的问题
# 3.25
1. [对角线上不同值的数量差](https://leetcode.cn/problems/difference-of-number-of-distinct-values-on-diagonals/) 看了一下题目,一定是前后缀分解,我的解法很笨,定义两个数组 `prefix` 和 `suffix` 分别进行填充操作,灵神的方法很厉害,就是太吃操作了,利用这些方法确定对角线(感觉自己的改一下也可以,计算前缀的时候直接使用 `ans` , 之后减去后缀即可)
```c++
class Solution {
public:
vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
	int m = grid.size() , n = grid[0].size();
	vector<vector<int>> ans(m , vector<int>(n , 0));
	unordered_set<int> st;

	for(int k = 1 ; k < m + n ; k ++) {
		int min_j = max(n - k , 0);
		int max_j = min(m + n - 1 - k , n - 1);
	  
		st.clear();
	for(int j = min_j ; j <= max_j ; j ++) {
		int i = k + j - n;
		ans[i][j] = st.size();
		st.insert(grid[i][j]);
	}

	st.clear();
	for(int j = max_j ; j >= min_j ; j --) {
		int i = k + j - n;
		ans[i][j] = abs(ans[i][j] - (int)st.size());
		st.insert(grid[i][j]);
	}
}
	return ans;
}
};
```
2. [最大正方形](https://leetcode.cn/problems/maximal-square/description/?envType=study-plan-v2&envId=top-interview-150) 边长 `dp` , 还是比较好想的,递推公式为: 
$$
dp[i][j] = min(dp[i - 1][j - 1] , dp[i - 1][j] , dp[i][j - 1]) + 1
$$
所以最终答案的求解为: `ans = max(ans , cur * cur)`
3. [直线上的最多点数](https://leetcode.cn/problems/max-points-on-a-line/description/?envType=study-plan-v2&envId=top-interview-150) 想法还是比较直接的,采取枚举直线的方式,但是问题就是如何保存直线? , 这里采用了求解 `x1 - x2` 和 `y1 - y2` 的最小公约数,并且进行求解,推导如下:
$$
\frac{x_1}{a} + \frac{y_1}{b} = 1
$$

$$
\frac{x_2}{a} + \frac{y_2}{b} = 1
$$
两个式子相减可以得到:
$$
\frac{x_1 - x_2}{a} + \frac{y_1 - y_2}{b} = 0 
$$
从而可以得到:
$$
\frac{a}{b} = -\frac{x1 - x2}{y1 - y2}
$$
所以如果得到 `a` 和 `b` 的最小公约是,那么就可以得到
$$
\frac{a}{b} = \frac{mk}{nk} = \frac{m}{n}
$$
其中 `m` 和 `n`互为质数,并且比值固定,所以可以得到只需要 `m` 和 `n` 就可以确定直线了,并且 `m` 和 `n` 为整数,同时注意 `C++` 中的解法,注意求解最大公约数的函数的写法:
```c++
int gcd(int a , int b) {
	return b == 0 ? a : gcd(b , a % b);
}
```
# 3.26
1. [k-avoiding数组的最小总和](https://leetcode.cn/problems/determine-the-minimum-sum-of-a-k-avoiding-array/description/?envType=daily-question&envId=2025-03-26) 如果不要求 `O(1)` 化,基本可以说是一道 `easy` , 和两数之和一个样
2. [岛屿的最大面积](https://leetcode.cn/problems/max-area-of-island/) 图论基本题目
3. 排序数组,重新复习一下十一种排序算法
![[Pasted image 20250326163339.png]]
# 3.27
1. [使所有字符相等的最小成本](https://leetcode.cn/problems/minimum-cost-to-make-all-characters-equal/description/?envType=daily-question&envId=2025-03-27)  注意到只需要相邻的字符相等即可(这就是局部最优),之后可以发现,如果 `s[i] != s[i - 1]` , 那么必须相等,只可以这样翻转: `s[0] - s[i - 1]` 或者 `s[i] - s[n - 1]` , 对于相等的字符翻转之后依然相等,但是对于不相等的字符依然不相等,所以这就由局部最优推出了全局最优,所以每一次翻转的最小的值为 `min(i , n - i)`
2. [衣橱整理](https://leetcode.cn/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/description/) 直接使用 `dfs` 或者 `bfs` 即可,注意题目的意思,看一条大佬的评论
3. [路径总和II](https://leetcode.cn/problems/path-sum-ii/description/) 回溯算法,注意最终的节点为叶子节点即可
4. [望远镜中的最高海拔](https://leetcode.cn/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/description/) 单调队列,注意使用 `deque` 容器维护,这里的单调队列我的理解就是  单调栈入栈的特点 + 队列 `FIFO` 的特点,单调栈和队列的杂合体
# 3.28
1. 每日一题: 字符串去重,使用二进制位统计即可
2. [解码方法](https://leetcode.cn/problems/decode-ways/description/) 使用回溯超时了 !!! , 所以这里使用动态规划即可,但是注意到初始化 `dp[0] = 1` 才可以!
3. [字符串的排列](https://leetcode.cn/problems/permutation-in-string/description/) 比较容易想到滑动窗口,但是注意到窗口移动的条件 `store[c] < 0` 或者 `!store.count(c)`(但是注意到此时需要恢复前面的值)
4. [交易逆序对](https://leetcode.cn/problems/shu-zu-zhong-de-ni-xu-dui-lcof/description/) 很难想到的一道题目,暴力超时,这里使用到归并排序,并且在归并排序合并数组的时候统计即可,参考 `K` 神的题解
# 3.29
1. [图中的最长环](https://leetcode.cn/problems/longest-cycle-in-a-graph/description/?envType=daily-question&envId=2025-03-29) 虽然是一道 `Hard` , 但是感觉思路还是比较直接的,我一开始的思路就是利用并查集找环,最终并查集中满足 `i == father[i]` 的节点加入到查找集合中即可,之后就可以使用链表找环的方法找环,但是看了灵神的题解,这里可以使用到时间来记录,每一次都需要遍历没有走过的节点(也就是 `vis_time[x] == 0` ,这是由于环中的一个节点只可以属于一个环形,每一次分别遍历即可)
2. [解密数字](https://leetcode.cn/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/description/) 和昨天的接码方法一样,不说了
3. [推理二叉树](https://leetcode.cn/problems/zhong-jian-er-cha-shu-lcof/description/) 利用前序遍历和中序遍历确定二叉树,原题了

# 3.30
1. 每日一题: 你就拿这样的中等题来考验面试者,哪一个面试者经不起这样的考验?
2. [子结构判断](https://leetcode.cn/problems/shu-de-zi-jie-gou-lcof/description/) 思路还是比较自然的,当需要判断的节点和当前根节点的值相同的时候是一中情况,不同的时候需要继续在左子数和右子树上面搜索,注意搜索方式即可
```c++
class Solution {
public:
bool isSubStructure(TreeNode* A, TreeNode* B) {
	if(A == nullptr || B == nullptr) return false;
	return isRootSame(A , B) ||
	isSubStructure(A -> left , B) ||
	isSubStructure(A -> right , B);
}

//@brief: 判断 A 是否和 B 结构相似
bool isRootSame(TreeNode* A , TreeNode* B) {
	if(A == nullptr && B == nullptr) return true;
	if(B == nullptr) return true;
	if(A == nullptr) return false;
	if(A -> val != B -> val) return false;
	return isRootSame(A -> left , B -> left) && isRootSame(A -> right , B -> right);
}

};
```
3. [彩灯装饰记录III](https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/description/) 之前的原题
4. [地下城游戏](https://leetcode.cn/problems/dungeon-game/description/) `dfs` 超时了,这里使用反向 `dp` , 由于正向 `dp` 无法确定后面的情况,所以对于一个位置 `(i , j)` , 可以由 `(i + 1 , j) or (i , j + 1)` 到达,所以每一次只需要从累积值小的位置移动过来即可,同样,确定初始值的题目一般都可以往反向 `dp` 思考

# 3.31 
1. 每日一题 
2. [省份数量](https://leetcode.cn/problems/number-of-provinces/) 并查集经典题目
3. [砍竹子I](https://leetcode.cn/problems/jian-sheng-zi-lcof/description/) 动态规划 , `dp[i] = max({dp[i] , j * (i - j) , j * dp[i - j]})`
4. [二叉树的序列化与反序列化](https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/description/) 很有意思的一道题目,使用层序遍历当 `nullptr` 过多的时候会存储很多 `nullptr` 超时,使用 `dfs` + 先序遍历即可,同时注意反序列化的时候时用一个队列存储节点的值,每一次弹出一个节点即可,可以看一下 `笨猪爆破组` 的题解,非常清晰
![[Pasted image 20250331112227.png]]

# 4.1
1. [解决智力问题](https://leetcode.cn/problems/solving-questions-with-brainpower/description/?envType=daily-question&envId=2025-04-01)  注意到 `dp` 中,对于一个位置需要考虑所有情况,也就是选 `or` 不选择的两种情况 , 另外注意到 `dp` 都可以使用 `dfs + 记忆化搜索来求解` , 这一道题目中由于需要知道 `f[i]` 选或者不选两种情况,所以只需要知道 `f[i + questions[i][1]]` 和 `f[i + 1]` 即可,同时分解为子问题进行 `dp` 也可以,把 `dp` 看成搜索即可,`dfs + 记忆化搜索` 的模板如下:
```c++
class Solution { 
public: 
	long long mostPoints(vector<vector<int>>& questions) { 
	int n = questions.size(); 
	vector<long long> memo(n); 
	auto dfs = [&](this auto&& dfs, int i) -> long long { 
	if (i >= n) { return 0; } 
	long long& res = memo[i];
	if(res) return res;
	return res = max(dfs(i + 1) , dfs(i + questions[i][1] + 1) + questions[i][0]);
	};

	return dfs(0);
```

2. [珠宝的最高价值](https://leetcode.cn/problems/li-wu-de-zui-da-jie-zhi-lcof/) 常规 `dp` , 但是注意到可以使用一维数组对于空间进行优化, `dp[i] --> 本层` , `dp[i - 1] --> 上一层` ,同时可以设置数组长度为 `n` 可以避免初始化
3. [旋转数组最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/solutions/9474/154-find-minimum-in-rotated-sorted-array-ii-by-jyd/) 二分查找真的难度大,一般的通解就是标记中间位置的状态,根据中间位置的状态来决定移动方式即可,直接看`K` 神仙的题解吧

# 4.2
1. [有序三元组中的最大值II](https://leetcode.cn/problems/maximum-value-of-an-ordered-triplet-i/description/?envType=daily-question&envId=2025-04-02) 前后缀分解,太明显了,枚举右,维护左即可
2. [删除链表中的节点](https://leetcode.cn/problems/delete-node-in-a-linked-list/description/) 什么 `sb` 题目,没营养
3. 做了其他的几个题目,都是原题没有什么好说的 ...
# 4.3
1. [有序三元组中的最大值II](https://leetcode.cn/problems/maximum-value-of-an-ordered-triplet-ii/description/?envType=daily-question&envId=2025-04-03) 估计是想到昨天有人使用暴力解法可以过,这里使用了前后缀分解 or 枚举 `k` 直即可,维护两个变量`max_diff 和 pre_max` 分别表示最大差值和前面的最大值即可
2. [奇偶链表](https://leetcode.cn/problems/odd-even-linked-list/description/) 直接不断删除偶数节点并且插入到新的链表,最终合并到原来的链表即可
3. [航班预订统计](https://leetcode.cn/problems/corporate-flight-bookings/description/)  差分的思想,差分可以理解为前缀和逆运算
> 差分的抽象:  已经知道每一次公交车上人数的变化,求解每一站车上的人数, 其中 `diff[i]` 表示在 `i` 站下车和上车的人数差值,所以相当于每一个站点车中人数的增长量为`diff[i]` , 所以最终答案的求解过程为: `ans[i] = ans[i - 1] + diff[i]` , 结合公交车的例子很容易理解

在这一道题目中可以这样理解 , `bookings` 中的每一个元素表示 `[first , last]` 的区间上面有 `seats` 个人数,并且注意到 `first` 上车,在 `last + 1` 下车即可,注意差分的模板即可
```c++
class Solution {
public:
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
vector<int> diff(n + 1 , 0);
for (vector<int>& vec : bookings) {
	int first = vec[0];
	int last = vec[1];
	int seats = vec[2];
	diff[first - 1] += seats;
	diff[last] -= seats;
}

vector<int> ans(n , 0);
ans[0] = diff[0];

for (int i = 1 ; i < n ; i ++) {
	ans[i] = ans[i - 1] + diff[i];
}

return ans;
}

};
```
# 4.4
1. [最深叶节点的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/?envType=daily-question&envId=2025-04-04) 还是模仿最先祖先节点的例子,首先需要计算左边子树的最大高度和右边子树的最大高度,确定最深叶子节点的位置,之后递归到最深的叶子节点如果两边的深度一样,那么返回自己即可
2. [二叉搜索树 --> 双向链表](https://leetcode.cn/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/description/) 正常思路转换即可
3. [验证后序遍历](https://leetcode.cn/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/description/) 我自己的思路还是利用后序遍历的性质,左右根 , 所以只需要找到一个位置左边的数字全部小于根节点并且右边的节点全部大于根节点即可,所以这里使用前后缀分解 + 递归的方式即可求解,另外一个大佬使用了单调栈的方法,逆序遍历数组 `root -> right -> left` , 所以遇到第一个小于根节点的元素表示遇到了左子树的根节点,继续递归,并且对于右子树,业绩是一样递归的
> 对于根节点,首先进入到右子树,在右子树中,还是同样的遍历顺序,所以一定会递归到右子树的左子树,此时会更新根节点的值,之后继续遍历保留根节点的值,同时只留下 `root` , 遍历到左子树一是一样的逻辑，当出现不满足大小关系的元素直接退出即可
```c++
class Solution { 
public: 
bool verifyTreeOrder(vector<int>& postorder) { 
	stack<int> stk; 
	int root = INT_MAX;
	for(int i = postorder.size() - 1; i >= 0; i--) {
		if(postorder[i] > root) return false; 
		while(!stk.empty() && stk.top() > postorder[i]) { 
			root = stk.top(); 
			stk.pop(); 
		}
		stk.push(postorder[i]); 
	} 
	return true; 
} 
};
```
# 4.5
1. [找出所有子集的异或总和](https://leetcode.cn/problems/sum-of-all-subset-xor-totals/description/?envType=daily-question&envId=2025-04-05) 看着就是一道数学题,但是还是想不到数学解法,果断回溯直接过了,看了一下灵神解法,可以这样理解:
> 特殊情况: 全部都是 `0 , 1` , 那么就可以发现至少有一个 `1` 的情况下,总的异或和总和为 $2^{n - 1}$ , 所以只需要对于每一个比特位求解总和即可,可以发现最终的结果就是 `2 ^ {所有为 1 的比特位} * 2 ^{n - 1}` ,同时注意到求解前者只需要对于所有的位进行异或即可!

2. [搜索旋转排序数组II](https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/solutions/3058425/ji-yu-33-ti-de-jian-ji-xie-fa-zhi-xu-zen-uayi/) **这里总结三道搜索旋转数组题目的解题方式(注意二分查找的核心就是判断当前的中间位置在目标值的左边 or 右边):**
- 没有重复元素,并且只是搜索 `target` :
![[Pasted image 20250405153607.png]]
所以此时对于中间值: `nums[mid]` , `nums[mid] > end` 的情况下,说明 `mid` 在第一段中,否则说明 `mid` 在第二段中,接下来讨论 `x = nums[mid]` 在 `target` 右边的情况,如果 `x` 在第一段中,那么 `target` 必须在第一段中并且小于或者等于 `x` , 如果 `x` 在第二段中,那么 `target` 可以在第一段中或者在第二段中并且小于等于 `x`即可,判断条件的定义如下:
```c++
int end = nums.back();
auto check = [&](int i) -> bool {
	int x = nums[i];
	// x 在第一段中
	if(x > end) {
		return target > end && target <= x;
	}

	// x 在第二段中
	return target > end || target <= x;
}
```
这里可以使用开区间或者闭区间
- 有重复元素只需要搜索是否存在 `target`: 
![[Pasted image 20250405161559.png]]

注意到这里的判断第一or第二段的方法类似但是注意到如果遇到 `nums[right] == mid` 的情况,需要注意此时让 `right = mid` 即可,这里采用左闭右开的集合 `[begin , end)` , 最终返回 `nums[right] == mid` (这里主要是 `right` 作为一个基准而已,如果此时使用 `[,]` , 那么当 `mid == target` 的时候,`right` 的位置会错过这一个新的位置,从而在一个新的区间里面进行搜索,也就是需要保持 `x` 在区间里面即可)

e.g:  [搜索排序数字中的最小值II](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/submissions/619152550/) 注意类比上面,方法都是一样的,
- 没有重复元素: 和搜索排序数组没有重复元素一样,最终返回 `nums[left]` 即可,相当于没有判断左右的操作
- 有重复元素: 和搜索排序数组有重复元素一样,最终返回 `nums[left] or nums[right]` , 相当于没有判断左右的操作

3. [商品排列顺序](https://leetcode.cn/problems/zi-fu-chuan-de-pai-lie-lcof/description/) 全排列,首先排序,之后注意去重即可,注意同一个数层和同一个树枝的关系:
```c++
// 注意排序
void dfs(vector<int>& nums , vector<bool>& used) {
	if(path.size() == nums.size()) {
		ans.push_back(path);	
		return ;
	}

	for(int i = 0 ; i < nums.size() ; i ++) {
		if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
			continue;	
		}	

		if(!used[i]) {
			used[i] = true;	
			path.push_back(nums[i]);
			dfs(nums , used);
			path.pop_back();
			used[i] = false;
		}
	}
}
```
# 4.6
1. [最大整除子集](https://leetcode.cn/problems/largest-divisible-subset/solutions/3641565/san-chong-fang-fa-ji-yi-hua-sou-suo-di-t-pift/?envType=daily-question&envId=2025-04-06) 很有意思的一个题目 , `dp` 数组记录最大符合要求的子集的长度,并且使用一个 `from` 数组记录上面一个元素即可,记录答案的时候往前面递推,不断递推就可以找到最终的答案,回溯超时了(或者可以使用记忆化搜索),记忆化搜索都可以使用动态规划解决,所以这里就不做说明了,但是注意在 `C++` 中使用 `lambda` 表达时写递归函数的写法:
```c++
auto dfs = [&](this auto&& dfs , int param) -> returnType {
	// ...
	dfs(param);
	// ...
};
```
但是 `C++20` 新特性
2. [有效数字](https://leetcode.cn/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/description/) 好恶心的题目,提交了六次终于过了,感觉这一中解析数字的题目都可以使用状态机来进行解析,比如解析 `Redis` 的命令
3. [最大矩形](https://leetcode.cn/problems/maximal-rectangle/submissions/619534574/) 类比一维的最大矩形题目,可以发现,只需要一行一行的寻找最大高度即可,图解如下:
![[Pasted image 20250406215110.png]]
也就是遍历到每一层之后记录从这一层向上的高度(如果遇到 `0`, 高度归 `0` 即可,之后对于每一次层得到的 `height` 进行一维大的最大矩形操作即可)
# 4.7
1. [分隔等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/description/?envType=daily-question&envId=2025-04-07) 一维背包问题,首先遍历物品,之后逆序遍历背包即可
2. [拼车](https://leetcode.cn/problems/car-pooling/submissions/619643437/) `md` 思路错了,以为是合并区间的做法,但是这里的思想就是简单的差分,利用 `map` 存储站点的人数变量量即可(注意到求解的过程中使用 `map` 从而使得数据有序)  **差分的思想: 记录每一个位置的变化量**
3. [单词搜索II](https://leetcode.cn/problems/word-break-ii/solutions/468624/shou-hua-tu-jie-dan-ci-chai-fen-ii-cong-di-gui-dao/) 看样子可以使用回溯,但是我的第一个想法就是使用 `dp` 判断是否有解,使用回溯判断解的内容,好像直接使用回溯就可以过 ?

# 4.8
1. [使得数组元素不同的最大操作次数](https://leetcode.cn/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/solutions/3027035/on-yi-ci-bian-li-jian-ji-xie-fa-pythonja-jgox/?envType=daily-question&envId=2025-04-08) 翻译题目条件(找到最大没有重复元素的后缀),最终返回 `i / 3 + 1` 即可
2. [最大数字](https://leetcode.cn/problems/largest-number/description/) 注意比较两个比较大的数字可以使用转换为 `string` 类型之后在进行判断的方式进行大小判断
3. [两数相加II](https://leetcode.cn/problems/add-two-numbers-ii/)  链表翻转 + 两数相加可以做出来
4. 有效数字: 和昨天的题目一个样,但是解法是一样的
5.  [矩阵中的最大递增路径](https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/submissions/619999483/)  `dfs` + 记忆化搜索,感觉难度不大,虽然是一道 `hard`
# 4.9
1. 每日一题: EZ
2. [验证图书取出的顺序](https://leetcode.cn/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/description/) 栈的简单应用
3. [撞色搭配](https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/description/) 很有意思,一个数组中有两个元素不一样,如何利用异或求解:

首先考虑一个数组中只有一个元素的情况,比如 `[4,2,4,5,5]` , 那么只需要把所有元素进行异或并且返回即可,但是对于两个元素的情况就不一样了,我们需要分别把这两个元素放入一个数组中,并且在这一个数组中执行异或操作即可,如何确定分类依据? , 如果 `a ^ b != 0` , 那么一定有一个位置 `a(n) ^ b(n) == 1` , 所以这一个位置一定有一个数组这一个位置为 `0` , 另外一个为 `1` ,所以自然可以把这一个作为分类依据,对于相同的数字一定分到一个组合中,所以不不需要担心影响

4. [最长递增子序列长度](https://leetcode.cn/problems/longest-increasing-subsequence/solutions/24173/zui-chang-shang-sheng-zi-xu-lie-dong-tai-gui-hua-2/) 舍弃 `dp` , 使用二分查找 + 贪心算法 ,操作步骤如下:

首先定义一个 `tails` 数组,数组中元素的含义如下:
```c++
tails[k] 表示长度为 k + 1 的子序列的尾部元素
```

**贪心算法: 我们需要使得 `tails[k]` 尽可能小,这是由于只有 `tails[k]` 尽可能小才可能使得后面遍历到的元素大于 `tails[k]` 的概率尽可能大,这样才可以更加容易找到大于 `tails.back()` 的元素从而更新最长长度,比如 `[1,5,3]` 中 `tails[1]` 可以选择 `5 or 3` , 此时我们一定选择 `3`** 

有了上面的条件容易证明 `tails`递增,利用反证法证明: 如果 存在 `k < i` 并且 `tails[k] > tails[i]` , 那么对于长度为 `i + 1` 的子序列,取出前面的 `k + 1` 个数字,这一个子序列的最后一个数字为 `v` , 由于 `v < tails[i]` , 册此时 `v < tails[i] < tails[k]` , 很明显不符合贪心算法,所以 `tails` 一定递增

首先初始化 `tails` 全部都是 `0` , 初始长度为 `res` , 利用二分查找寻找第一个 `tails[i] > num` 的位置,并且更新 `tails[i] = nums` ,如果没有找到这一个位置,说明找到了一个更大的数字,此时需要扩展子数组的长度(一开始后者之后执行都可以,官方题解一开始执行,`K` 神之后判断都可以) , 如果使用 闭区间二分那么可以在 `i == res ---> res ++`  

4. [套娃问题](https://leetcode.cn/problems/russian-doll-envelopes/solutions/19681/zui-chang-di-zeng-zi-xu-lie-kuo-zhan-dao-er-wei-er/) 注意对于信的第二个参数进行降序列排列之后就可以忽略掉 `ev[0]` 相同的情况下选择了,同时对于第二个参数进行 `LIS`即可,**第一个参数升序 并且第二个参数降序排列**即可 

# 4.10
1. [统计强大整数的数量](https://leetcode.cn/problems/count-of-integers/submissions/620901564/) 数位 `dp` 好难 !!! , 这里统一采用第二个版本上下界限 `dp` 的方式进行求解,直接用灵神的模板 `memo` 需要定义为状态参数有关的量,所以需要判断 `!limit_low && !limit_high && memo[i][sum] != -1` , 其实存储的条件和取出的条件是一样的,可以做一个实验,把 `! + ! 改成 ! + 非 !`
# 4.11
系统学习了数位 `DP` , 做了几道数位 `DP` 的 `Hard` ,还是不会 !!!
# 4.12
1. [统计好整数的数量](https://leetcode.cn/problems/find-the-count-of-good-integers/description/?envType=daily-question&envId=2025-04-12)  思路: 枚举所有的回文整数 + 排列组合,高中数学全部忘干净了,对于一个 `n` 位的数字,只需要知道前面的 `(n - 1) / 2` 位置的整数就可以求解整个整数了,所以只需要枚举这一个部分的数字,同时注意取重复(使用排序 + 哈希表的方式),对于满足要求的回文数字,对应的排列数量为:
![[Pasted image 20250412162542.png]]
`cnt_n` 表示 `s` 中 `n` 出现的次数, `s` 中总共有 `n` 位数,第一个位置不可以填 `0` , 所以第一个位置可以填 `n - cnt_0` 个数字,之后的位置总共有 `n - 1` 中填法(`s` 中还有 `n - 1`个数字,全排列即可) , 但是如果 `s` 中有数字出现两次那么就会导致重复,所以对于重复的数字需要除`cnt_i!`(想一想高中相关的题目)
2. [等差数列划分](https://leetcode.cn/problems/arithmetic-slices/description/)   `dp` , 当发现相邻的三个数字构成等差数列的时候就有 `dp[i] = dp[i - 1] + 1` , 表示以 `nums[i]` 结尾的等差数列的数量,就是加上自生的一种,最终对于 `dp` 求和即可
3. 路径总和II 不说了,比较简单
4. [下降路径最小值](https://leetcode.cn/problems/minimum-falling-path-sum/description/)  第一眼被回溯迷惑了,超时了,利用记忆化搜索或者 `dp` 都可以,但是使用 `dp` 需要自下向上,感觉记忆化和 `dp` 的区别就是:

记忆化搜索: 不确定 --> 确定,也就是递归函数的特点
`dp`: 确定 --> 不确定

感觉学了记忆化搜索之后更喜欢记忆化搜索了

# 4.13
1. [好数的数量](https://leetcode.cn/problems/count-good-numbers/submissions/621872757/?envType=daily-question&envId=2025-04-13) 个人感觉很逆天的一个题目,不要直接数位 `dp` , `n` 太大了,并且注意到其实在偶数位置上面可以填 `4` 个数字,在奇数位上可以填写 `5` 个数字,那么最终的答案个数就是 `pow(5,a) * pow(4,b)` , 可以想到使用快速幂进行求解:
```c++
long long pow(long long x , long long n) {
	long long res = 1;
	while(n) {
		if(n & 1) res *= x % MOD;
		x *= x;
		n >>= 1;
	}	
}
```
同时注意到 `a % MOD = d , b % MOD = m , 那么 (a * b) % MOD = d * m % MOD` , 利用余数和乘数就可以进行求解
2. [破解密码](https://leetcode.cn/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/solutions/190476/mian-shi-ti-45-ba-shu-zu-pai-cheng-zui-xiao-de-s-4/) 和前面几天的题目一个样子,在 `C++` 中直接使用 `a + b < b + a` 即可
3. [二分图](https://leetcode.cn/problems/is-graph-bipartite/submissions/621890364/) 在单个连通域中,考虑染色问题即可,也就是相邻的位置染不同的颜色即可
# 4.14
1. [三元组](https://leetcode.cn/problems/count-good-triplets/?envType=daily-question&envId=2025-04-14) 如果不使用暴力解法应该是一道 `mid` , 注意到这一种约束条件比较多的题目,可以才有把这些条件化成一个条件,比如本题中的条件可以转换为求解满足特定范围的 `arr[i]` 的个数,所以此时只有两个自由度了,所以复杂度可以降低到 `O(n^2)` 了,另外一个思想就是使用前缀和,所以总结这一类题目的做法:               减少约束条件(降低自由度) ---> 使用前缀和等手段进行记录数据等操作 , 同时也可以考虑三指针法进行求解 
2. [设计自助结算系统](https://leetcode.cn/problems/dui-lie-de-zui-da-zhi-lcof/description/)  使用 队列 + 优先队列 + 哈希表 或者 队列 + 优先队列都可以,注意利用后者的时候注意,由于加入的时候弹出的元素一定都是前面已经加入的元素,所以不用考虑这些元素了,后面的元素都是比较大的元素,核心就是单调队列!
3. [划分K个相等的子集](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/solutions/) 感觉很好的一道题目,体现了回溯的思想,两种方法理解,第一种是从球的视角来看可以理解为球选择桶,从桶的视角来看可以理解为桶选择球,其实回溯本质上就是一种暴力的模拟,直
4. 接遍历所有情况,同时在本题中可以采用排序以及去重剪枝的方式降低复杂度,比如 `i > 0 && buckets[i] == buckets[i - 1]` 表示当前这一个球选择第 `i - 1` 个桶和选择第 `i` 个桶的情况一样,最后就是遍历到 `i == nums.size()` 的位置说明满足要求直接返回即可,再一次总结回溯的模板(注意到回溯不仅仅针对于一个集合中取出元素,可以针对于各种集合的组合情况等),本质就是选或者不选的问题
```c++
returnType dfs(集合1 , 集合2 ... , 做出选择的元素(可以是集合 1 or 集合2 中的元素)) {
	if(终止条件) {
		return ...
	}

	for(需要选择的元素(和上面的入参互斥)) {
		剪枝操作	
		选择元素
		dfs(... , ... , 另一个集合中的下一个元素 , ... , ...)
		回溯
	}
	
	return ...
}
```
# 4.15
1. [区间和检索](https://leetcode.cn/problems/range-sum-query-mutable/solutions/) 区间和检索可以使用前缀和,线段树或者树状数组来做,今天主要讨论树状数组的解法

树状数组解决的问题主要是前缀和问题,如果利用传统的前后缀分解,在根新数据的时候会产生比较大的时间复杂度,所以使用树状数组来求解前缀和,原理如下:

首先树状数组的表示如下:
![[Pasted image 20250415130945.png]]
	首先介绍树状数组的几个特点(前提 `b` 存储树状数组中的所有元素,并且下标从 `1` 开始):
1. 对于下标为 `i` 的元素表示的序列长度为 `i` 转换为二进制的最低有效位置对应的二进制数字,可以使用 `lowBit` 函数求解,也就是 `i & -i`
2. 对于下标为 `i` 的元素,它正上方的节点(有的地方叫做父节点)的下标为 `i + lowBit(i)` 其实也就是下标 + 区间长度

下面介绍树状数组的几种相关的操作:
1. `prefixSum(i)` 表示求解原来数组中元素的前缀和: `a[0] + a[1] + ... + a[i - 1]` , 这是由于在新的数组中下标从 `1` 开始,所以原来数组中下标 `i` 对应新的数组中下标为 `i + 1` 的元素,求解方式如下,也就是  `i` 所在的区间和 + 前面元素的区间和,求解的具体实现如下:
```c++
int prefixSum(int i) {
	int ans = 0;
	for( ; i > 0 ; i -= lowBit(i)) {
		ans += tree[i];
	}
	return ans;
}
```
2. 更新操作,注意到每一次更新下标为 `i`(原来数组中下标为 `i`) 的元素,就相当于需要更新 `b` 中下标为 `i + 1 --> b.size()` 中的元素,可以求出偏移量之后累加即可:
```c++
void update(int i , int val) {
	int delta = val - nums[i];  // 表示后面元素的更新量
	nums[i] = val;
    for(int j = i + 1 ; j < tree.size() ; j += lowBit(j)) {
		tree[i] += delta; 
    }	
}
```
3. 求解原来数组中 `[left , right]` 中的元素,直接结合前面前缀和的定义即可:
```c++
prefixSum(right + 1) - prefixSum(left);
```
4. 利用一个数组初始化,感觉很类似于归并
```c++
for(int i = 1 ; i <= n ; i ++) {
	tree[i] += nums[i - 1];
	int nxt = i + lowBit(i);
	if(nxt <= n) {
		tree[nxt] += tree[i];
	}
}
```

树状数组的作用: 在不断插入元素的情况下求解前缀和等操作,时间复杂度 `O(logn)` (操作次数可以使用等比级数确定),并且当数组中元素为 `1` 的时候可以求解前面元素出现的次数
#TODO学习线段树  
2. [统计好三元组数量](https://leetcode.cn/problems/count-good-triplets-in-an-array/description/?envType=daily-question&envId=2025-04-15) 很有意思的一道题目,注意到凡是需要枚举多个组合的题目,比如需要枚举 `(A_i , A_j , A_k)` 的题目,都可以转换为枚举中间一个数字也就是`A_j` 的题目,具体的转换方式需要思考,这里的转换方式如下,在 `nums1[i]` 中构建一个映射关系 `nums1[i] -> i` , 也就是 `nums1[i]` 就是 `i` , 这一个操作使得 `nums1` 中的元素有序了,所以只需要在 `nums2` 中进行映射之后找到 `nums2` 中的长度为 `3` 的升序子序列即可,由于这里数据比较多,使用前缀表会超时,所以使用树状数组就可以了(每一次更新元素的时候可以设置 `delta = 1` 即可 , `tree[i]` 表示 `[0 , i - 1]` 内的元素总和 , 每一次只需要 `ans += prefixSum(y) * (n - 1 - y - (i - prefixSum(y))`) 即可
3. [最短无序连续子数组](https://leetcode.cn/problems/shortest-unsorted-continuous-subarray/description/) 思路一开始以为是使用单调栈(其实也可以),但是对于相等元素的情况不好处理,这里应该使用双指针,整个区间如下:
![[Pasted image 20250415144435.png]]

可以发现右边的元素 >= max(中间元素) 并且递增,所以可以发现,其实中间的左边区间的第一个元素是最后一个大于最小值的元素了(右端的元素都大于最小值) , 中间的元素可以更新最小值,但是左边的元素都小于最小值

右边一样的道理,思路还是比较难以想到

`400` 题了 !!!
# 4.16
1. [统计好子数组的个数](https://leetcode.cn/problems/count-the-number-of-good-subarrays/solutions/2062761/shuang-zhi-zhen-by-endlesscheng-lkd9/?envType=daily-question&envId=2025-04-16) 双指针 + 滑动窗口即可,注意到如果当前的窗口满足要求,那么此时满足要求的子数组的个数为 `n - right` 即可
2. [区间检索和](https://leetcode.cn/problems/range-sum-query-2d-immutable/description/) 两个维度的前缀和,注意图形的运算关系即可,注意到如果使用 `prefix[row + 1][col + 1]` 表示 `[0,0] -> [row,col]` 的前缀和如何求解指定区间的前缀和
![[Pasted image 20250416090117.png]]
3. [计算右侧小于当前元素的个数](https://leetcode.cn/problems/count-of-smaller-numbers-after-self/description/) 最直观的想法就是直接使用树状数组直接统计大小(很直观的想法),可以过,同时可以类比之前求解逆序对的题目使用归并排序进行求解,主要注意到在归并排序中分治中的治部分进行答案的统计
# 4.17
1. 每日一题: 哈希表基本题目不用说了
2. [格雷码](https://excalidraw.com/) 想到了卡诺图,其实 `grayCode(n)` 的求解方式就是 `{ grayCode(n - 1) , grayCode(n - 1) 翻转 | 1 << (n - 1) }` 
3. [不同的二叉搜树](https://leetcode.cn/problems/unique-binary-search-trees-ii/submissions/623097372/) 不要一直想回溯,利用递归即可,也就是枚举一个区间 `left -> right` 中数字,同时遍历两个区间中的数字即可,使用动态规划和记忆化搜索即可(记录序列长度和偏移量即可)
# 4.18
1. [统计坏数组的个数](https://leetcode.cn/problems/count-number-of-bad-pairs/description/?envType=daily-question&envId=2025-04-18) 同构,转换为新的数组,并且在新的数组中利用哈希表统计即可
2. [删除并且获得点数](https://leetcode.cn/problems/delete-and-earn/description/) 增强版本打家劫舍问题,但是这里的限制是值域内部的限制,所以直接把值域映射到索引之后利用打家劫舍的方式进行求解即可
3. [根据字符出现频率排序](https://leetcode.cn/problems/sort-characters-by-frequency/description/) 每什么意思,利用排序或者 `muliti_map` 进行拼接也可以
# 4.19
写`CPU` 去了,没有做题
# 4.20
1. [统计公平数对](https://leetcode.cn/problems/count-the-number-of-fair-pairs/submissions/623998423/?envType=daily-question&envId=2025-04-19)  思路还是听普通的,但是,首先利用树状数组(超出内存限制了),所以可以想到就算把两个数字交换顺序也没有什么影响,所以首先排序,之后遍历的过程中利用二分查找寻找某一个区间里面大于或者小于两个区间边界的元素,之后进行相减操作即可
2. [森林中的兔子](https://leetcode.cn/problems/rabbits-in-forest/description/?envType=daily-question&envId=2025-04-20) 贪心算法,首先统计个数,并且注意到相同颜色的兔子一定是说的一样的数量,所以只需要尽可能多的合并相同数量的兔子,同时剩余的兔子如果 `p.second % (p.first + 1) != 0` , 那么剩余的兔子都归入到一一个种类即可 
3. [数据流中的中位数](https://leetcode.cn/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/submissions/624012145/) 一个大顶堆,一个小顶堆,规定大顶堆中的元素个数始终多与小顶堆中的元素个数即可

# 4.21
1. [统计隐藏数组的数目](https://leetcode.cn/problems/count-the-hidden-sequences/description/?envType=daily-question&envId=2025-04-21)  前缀和 + 数学问题,求解偏置量即可(其实可以不用求解数组本身),这里可以采用动态计算最大值和最小值,分别利用 `s , min_s , max_s` 记录当前值
2. [最大连续1的个数](https://leetcode.cn/problems/max-consecutive-ones-iii/solutions/) 对于连续区间可以使用滑动窗口(双指针)
3. [二叉树的反序列化和序列化](https://leetcode.cn/problems/xu-lie-hua-er-cha-shu-lcof/submissions/624147972/) 使用层序遍历或者前序遍历都可以,注意到后者可以使用队列来存储元素
# 4.22
1. [统计理想数组的个数](https://leetcode.cn/problems/count-the-number-of-ideal-arrays/description/?envType=daily-question&envId=2025-04-22) 好难,放过了,数位 `dp` 过不了
2. [恢复二叉树](https://leetcode.cn/problems/recover-binary-search-tree/description/) 本来一个非常简单的题目,中序遍历,由于只是破坏了两个节点,所以只需要找到第一个不满足要求的节点和最后一个不满足要求的节点进行交换即可
3. [链表转换为 BST](https://leetcode.cn/problems/convert-sorted-list-to-binary-search-tree/submissions/624512236/) 找中间节点,和数组转换为 `BST` 差不多,缝合怪而已
# 4.23
1. 每日一题: `Easy` , 不说了
2. [链表插入排序](https://leetcode.cn/problems/insertion-sort-list/description/) 链表插入排序和数组插入排序的区别就是不可以从后面往前面推,从前面往后面推就可以了
3. [最大间距](https://leetcode.cn/problems/maximum-gap/description/) 好逆天,披着 `mid` 外壳的 `Hard`,桶排序 + 逻辑分析
![[Pasted image 20250423092421.png]]

其中总共有 `n` 个元素,所以有 `n - 1` 个区间,所以区间长度的平均值 $d = \frac{M - m}{n - 1}$ , 所以相邻的最大长度  $d >= \frac{M - m}{n - 1}$ , 所以可以这样进行桶的分类,把相差 小于 `d` 的放入到一个桶中即可,但是这一种情况下,相差最大的元素一定不在一个桶中,而在于相邻的不同桶中(分桶的方式: `m , m + d , m + 2 * d , m + 3 * d ...  | m + 1 + d , m + 1 + 2 * d , m + 1 + n * d ....`)  , 所以这只需要维护前面桶中元素的最大值和最小值,同时由于桶中元素的顺序,那么答案的组成方式就是 前面一个桶中的最大值和后面一个桶中的最小值(注意到相邻的桶)相邻的元素一定相邻
# 4.24
1. [统计完全子数组的数量](https://leetcode.cn/problems/count-complete-subarrays-in-an-array/description/?envType=daily-question&envId=2025-04-24)  滑动窗口,经典题目,套模板就可以了
2. [比较版本号](https://leetcode.cn/problems/compare-version-numbers/description/) 没什么营养,不说了
3. [扰乱字符串](https://leetcode.cn/problems/scramble-string/description/) 递归接法比较容易想到,但是超时,判断了字符种类依然超时,所以采用记忆化搜索,注意记忆化搜索主要是要找到相同的状态,也就是每一次匹配的入参是一样的,确定入参的方式就是记录 `s1 的 开始索引 start1` , `s2 的开始索引 start2` , 并且记录匹配的长度即可,作为 `hard` , 难度还行
# 4.25
1. [统计趣味子数组的个数](https://leetcode.cn/problems/count-of-interesting-subarrays/description/?envType=daily-question&envId=2025-04-25) 可以看出使用前缀和,但是不知道如何使用前缀和,看了一下 ys 的题解,可以发现其中利用了前缀和 + 转换的思想,比如利用前缀和 `cnts[i]` 表示 `[0 , i - 1]` 内的满足要求的元素个数,那么对于一个区间 `[i,j]` , 其中满足要求的 `cnt` 的个数为 `cnts[j + 1] - cnts[i]` ,也就是 `(cnts[j + 1] - cnts[i]) % modulo == k % modulo`,所以进行转换,前缀和或者哈希表的思想(类似于两数之和)的思想就是利用后面的数字推出前面的数组,那么上面的式子可以变形为: `(cnts[j + 1] - k) % modulo == (cnts[i] % modulo)` ,所以只需要每一次 `ans += cnts[(s - k) % modulo]` 即可,利用一个 `sum` 统计前缀和,利用一个 `cnts` 统计 `sum[i] % modulo` 即可
2. 重复序列: 定长滑窗,每什么好说的
3. [单词搜索II](https://leetcode.cn/problems/word-ladder-ii/submissions/625421181/) 非常好的一道题目,首先利用 `bfs` 得到答案,之后利用 `dfs` 遍历建立起来的答案图,注意到 `bfs` 使用 `curl -> 当前层  nextl -> 下一个层` , 这样可以批量遍历每一个层














