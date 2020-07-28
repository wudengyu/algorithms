# 石头剪子布
## 题目描述
石头Rock剪子Scissors布Paper。

想哥和叶姐又开始这个有趣的游戏。众所周知，他们俩的游戏不可能公平。他们分别给出自己出的序列（RSP分别代表石头、剪刀、布）。

想哥给出一个长度为n的序列，而叶姐给出长度为m的序列。1≤m<n≤100,000

。叶姐显然有特权，她可以选择跳过想哥序列的一段开头，才开始将RSP序列进行匹配，以寻求从这一位置开始最多获胜次数。

请你帮叶姐求出这一次数，这就是想哥请17级吃饭的次数。显然，R胜S，S胜P，P胜R。
## 输入
第一行为n，m，含义如上。

接下来两行分别为想哥和叶姐的RSP序列。
## 输出

输出一行，最大获胜数
### 输入样例1
```
12 4
RSPPSSSRRPPR
RRRR
```
### 输出样例1
```
3
```
### 输入样例2
```
12 4
PPPRRRRRRRRR
RSSS
```
### 输出样例2
```
2
```
### 输入样例3
```
12 4
RRRRRRRRRSSS
RRRS
```
### 输出样例3
```
3
```
## Hint
对于从哪里开始的匹配规则，请多参照样例2、3。

对于50%的数据，n,m≤4000
.（三方的算法就不要交了）
## 解题思路
朴素的字符串匹配是O(n*m)，肯定会TLE的。但是这题还不能算是字符串匹配问题，所以KMP等方法也用不上。FFT(fast Fourier transform快速傅里叶变换)可以把O(n<sup>2</sup>)的多项式乘法优化到O(nlogn)，可以用来解决字符串匹配问题，因为多项式乘法法则是“系数逐项相乘，再合并同类项”，而字符串匹配问题朴素的方法则是“逐字符比较”，如果把字符转换成数字，就成了“逐项求差”，匹配的话就是连续m项和为0了。进一步的解释和说明还是有点复杂，建议看看“FFT 字符串匹配“相关的文章，总之，可以用FFT来解决字符串匹配问题，甚至本题这种不完全匹配问题（构造文本字符串和匹配字符串，用枚举的办法计算每个字符匹配的次数）。但是FFT要用到“n次单位复数根”，不可避免的要用到浮点运算，所以使用NTT(Number Theoretic Transform快速数论变换)更好。NTT实际上来源于FFT，只不过把“n次单位复数根”用“原根”来代替而已。原根是一个素数，具有ω相同的性质，它的n次方可以用快速幂算法来计算。

思路就这些，剩下的就是“板子”了。因为FFT或NTT有点复杂，要想根据FFT原理、思路重头写代码还是有难度的。所以收集一些“板子”很有必要。这不也是刷题的一种效果么。