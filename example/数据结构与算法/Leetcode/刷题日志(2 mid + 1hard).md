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
3. []()