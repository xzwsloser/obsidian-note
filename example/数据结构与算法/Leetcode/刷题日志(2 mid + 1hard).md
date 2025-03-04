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
