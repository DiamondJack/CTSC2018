{{ self.title() }}


## {{ _('Description') }}

temporaryDO 是一个很菜的 OIer。在 4 月，他在省队选拔赛的考场上见到了《林克卡特树》一题，其中 $k=0$ 的部分分是求一条树 $T$ 上最长链。可怜的 temporaryDO 并不会做这道题，他在考场上抓猫耳挠猫腮都想不出一点思路。

这时善良的板板出现在了空中，他的身上发出璀璨的光芒。“这题并不难。”那充满磁性的声音，让 temporaryDO 全身充满了力量。他决定——写一个枚举点对求 LCA 算距离的 $k=0$ 的 $O(n^2\log n)$ 的部分分程序！

然而，菜菜的 temporaryDO 不小心开小了数组，于是数组越界到了一片神秘的内存区域。但恰好的是，那片内存区域存储的区域恰好是另一棵树 $T'$。这样一来，程序并没有 RE，但他求 $x$ 和 $y$ 的距离的时候，计算的是 $\text{depth}(x)+\text{depth}(y) - 2(\text{depth}(\text{LCA}(x,y)) - \text{depth'}(\text'{LCA}(x,y)))$。

temporaryDO 的程序在评测时光荣地爆零了。但他并不服气，他决定花好几天把自己的程序跑出来。请你帮帮可怜的 temporaryDO 求出他程序的输出，你可以得到 $T$ 和 $T'$。

## {{ _('Input Format') }}

{{ self.input_file() }}

上面会根据具体的评测环境说明输入是文件还是标准输入等。

输入第一行包含一个正整数 $n$，保证 $n \le {{ tools.hn(prob.args['n']) }}$。←这是引用 `conf.json` 中的 `args` 的 `n` 项，然后用“好看”的格式输出。“好看”的格式如 `10^9`，`1,000,000,007`。

`prob.args['n']` 还可以写成 `prob['args']['n']`。引用 `args` 项、 `data` 项、`samples` 项和 `pre` 项现在可以简写成例如 `args['n']` 或 `args.n`。表格中也一样。

`tools` 可以简写成 `tl`，除 `hn` 外，还包括内建函数如 `tl.int`，`math` 中的对象或函数如 `tl.sin`，`datetime` 中的对象或函数如 `tl.time` 类，`num2chinese` 函数（可以把数字转化成中文）。

## {{ _('Output Format') }}

{{ self.output_file() }}

输出一个字符串 `Yes`。注意不要写成 `“Yes”（不包含引号）`。

下面是自动读入样例 `1.in/ans`（存储在 `down` 文件夹内） 然后渲染到题面中；如果只有一组样例，则去掉前两行，样例仍然保存成 `1.in/ans`。其中 `1` 可以是字符串。

{% set vars = {} -%}
{%- do vars.__setitem__('sample_id', 1) -%}
{{ self.sample_text() }}

{{ self.title_sample_description() }}

这是第一组数据的样例说明。

下面是只提示存在第二组样例，但不渲染到题面中。

{% do vars.__setitem__('sample_id', 2) -%}
{{ self.sample_file() }}

## {{ _('Subtasks') }}

不要使用markdown原生的表格，使用下列方式渲染一个表格，其中表格存放在试题目录的 `tables` 子目录下。

{{ tbl('data') }}

{{ tbl('table', width = [1, 6]) }}

表格的例子见 `oi_tools/sample/tables`。原理上用一个二维的 json 表格存储，`null` 表示和上一行合并，不支持横向合并。建议用 python 的格式写，如例子中的 `data.pyinc`，这样可以根据数据生成；跟数据无关的表格则可以像 `table.json` 那样存储。

## {{ _('Scoring') }}

这是评分方法，如果有必要的话。

## {{ _('Hint') }}

这里是一个非常温馨的提示。
