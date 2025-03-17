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



