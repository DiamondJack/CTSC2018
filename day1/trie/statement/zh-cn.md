{{ self.title() }}

## {{ _('Description') }}

Access Globe 有若干个递增的正整数序列。为了保存这些序列，他把这些正整数序列中的每个正整数都转成十进制（无前导零），整数之间用逗号隔开。像这样把序列转换为字符串后，Access Globe 用一棵 Trie 来存储这些字符串。你并不需要知道 Trie 树究竟是什么，你只需要知道，Access Globe 得到的 Trie 是一棵有根树，每一条边上都有字符，并且从根到每一片叶子的路径上的边上的字符顺次拼接构成的字符串是一个递增的正整数序列。

可爱的小 Tommy 决定篡改这棵 Trie 树。他先将 Trie 上的一些边上的字符涂黑，然后改成另外一些字符。为了不被发现，Tommy 必须保证修改后的 Trie 仍然满足上述性质，即从根到每一片叶子的路径上的边上的字符顺次拼接构成的字符串是一个递增的正整数序列，且每个正整数无前导零。

现在 Tommy 已经涂黑了一些字符，请你帮他完成“改成其他字符”的操作。如果有多解，请输出字典序最小的解。

## {{ _('Input Format') }}

{{ self.input_file() }}



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
