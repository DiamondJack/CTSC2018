{{ self.title() }}


## {{ _('Description') }}

temporaryDO 是一个很菜的 OIer。在 4 月，他在省队选拔赛的考场上见到了《林克卡特树》一题，其中 $k=0$ 的部分分是求树 $T$ 上的最长链。可怜的 temporaryDO 并不会做这道题，他在考场上抓猫耳挠猫腮都想不出一点思路。

这时，善良的板板出现在了空中，他的身上发出璀璨却柔和的光芒，荡漾在考场上。“题目并不难。”板板说。那充满磁性的声音，让 temporaryDO 全身充满了力量。他决定：写一个枚举点对求 LCA 算距离的 $k=0$ 的 $O(n^2\log n)$ 的部分分程序！于是，temporaryDO 选择以 $1$ 为根，建立了求 LCA 的树链剖分结构，然后写了二重 `for` 循环枚举点对。

然而，菜菜的 temporaryDO 不小心开小了数组，于是数组越界到了一片神秘的内存区域。但恰好的是，那片内存区域存储的区域恰好是另一棵树 $T'$。这样一来，程序并没有 RE，但他求 $x$ 和 $y$ 的距离的时候，计算的是 $\text{depth}(x)+\text{depth}(y) - (\text{depth}(\text{LCA}(x,y)) + \text{depth}'(\text{LCA}'(x,y)))$，其中 $\text{depth}(p)$ 和 $\text{depth}'(p)$ 表示两棵树中点 $1$ 到点 $p$ 的距离。最后程序会输出每一对点对 $i,j$（$i\le j$）的如上定义的“距离”的最大值。

temporaryDO 的程序在评测时光荣地爆零了。但他并不服气，他决定花好几天把自己的程序跑出来。请你帮帮可怜的 temporaryDO 求出他程序的输出，你可以得到 $T$ 和 $T'$。

## {{ _('Input Format') }}

{{ self.input_file() }}

第一行包含一个整数 $n$，表示树上的节点个数；

第 $2$ 到第 $n$ 行，每行三个整数 $x$、$y$、$v$，表示 $T$ 中存在一条从 $x$ 到 $y$ 的边，其长度为 $v$；

第 $n+1$ 到第 $2n-1$ 行，每行三个整数 $x$、$y$、$v$，表示 $T'$ 中存在一条从 $x$ 到 $y$ 的边，其长度为 $v$。

## {{ _('Output Format') }}

{{ self.output_file() }}

输出一行一个整数，表示 temporaryDO 的程序的输出。

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}

{{ self.title_sample_description() }}

点对 $(3,4)$ 的距离计算为 $3 + 0 - (0+(-2))=5$。


{% do vars.__setitem__('sample_id', 2) %}
{{ self.sample_file() }}

## {{ _('Subtasks') }}

以下部分分中，描述的“链”均满足该树中每一条边有 $|x-y|=1$。

对于 $10\%$ 的数据，$n\le 366$ 且 $v=1$；

对于 $25\%$ 的数据，$n\le 2,666$ 且 $v$ 非负；

对于 $45\%$ 的数据，$n\le 12,345$；

另有 $10\%$ 数据，$T$ 和 $T'$ 都是链，其中有 $5\%$ 数据满足 $v$ 非负；

另有 $15\%$ 数据，$T$ 是链，其中有 $10\%$ 数据满足 $v$ 非负；

另有 $15\%$ 数据，$T'$ 是链，其中有 $10\%$ 数据满足 $v$ 非负；

对于所有数据，$n\le {{ tl.hn(prob.args['maxn']) }}$，$|v|\le {{ tl.hn(prob.args['maxv']) }}$。

## {{ _('Hint') }}

题目并不难。\color{white}{这题思博题QAQ，好水呀，好水呀～}\color{black}