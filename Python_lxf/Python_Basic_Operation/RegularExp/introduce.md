字符串是编程时涉及到的最多的一种数据结构, 对字符串进行操作的
需求几乎无处不在.
正则表达式是一种用来匹配字符串的强有力的武器. 他的设计思想是
用一种描述性的语言来给字符串定义一个规则, 服饰符合规则的字符串, 
我们就认为它匹配了, 否则, 该字符串是不合法的


所以判断一个字符串是否是合法的Email:
	创建一个匹配Email的正则表达式;
	用该正则表达式去匹配用户的输入来判断是否合法


在正则表达式中, 如果直接给出字符, 就是精确匹配, 用
'\d'		可以匹配一个数字,
'\w'		可以匹配一个字母或数字, 
'.'			可以匹配任意字符
要匹配变长的字符, 在正则表达式中, 
'*'			表示任意个字符(包括0个)
'+'			表示至少一个字符
'?' 		表示0个或1个字符
'{n}' 		表示n个字符
'{n, m}'	表示[n, m]个字符
***
example
\d{3}\s+\d{3, 8}
\d{3} 		表示匹配3个数字
\s 			可以匹配一个空格(也包括Tab等空白符就), 
\s+ 		表示至少有一个空格
\d{3, 8} 	表示3-8个数字

要匹配'010-12345'
\d{3}\-\d{3, 8} 		'-'是特殊字符要用'\'转义

要做更精确的匹配, 可以用[]表示范围,
[0-9a-zA-Z\_] 					可以匹配一个数字, 字母或者下划线

[0-9a-zA-Z\_]+ 					可以匹配至少由一个	数字字母或者下划线组成的	字符串
	
[a-zA-Z\_][0-9a-zA-Z\_]* 		可以匹配由字母或下划线开头, 后接任意个由一个
								数字字母或者下划线组成的 字符串,也就是python的合法变量
[a-zA-Z\_][0-9a-zA-Z\_]{0, 19} 	更精确的限制了变量的长度是1-20个字符

'A|B'		可以匹配A或B, 所以[P|p]ython可以匹配Python或者python
'^'			表示行的开头
'^\d' 		表示必须以数字开头
'$'			表示行的结束
'\d$'		表示必须以数字结束
