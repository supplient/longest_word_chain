* 单词大小写不敏感
* 文件不存在、文件不合法时应报错
* 输出单词为小写

----------------------

* 单词为被非英文字符间隔的连续英文字符序列
	* 构造一个空的words
	* 构造只有一个字母的单词
	
* 单词链至少两个单词，不存在重复单词
	* 构造一个没有任何两个单词能连上的情况
	* 构造有多个重复单词的words
	* 构造一个首尾字母相同的单词
	
* 非-r情况下，遇见会构成单词环的情况应报错（就算不是最长的也要报错）
	* 构造单词环
		* 为唯一最长
		* 为最长之一
		* 非最长

* 若有多组最长单词链，则选取任意一组即可
	* 构造存在多组的情况，随意选取一组。

------------------------

* -w：最多单词数量的单词链
* -c: 最多字母数量的单词链
* -h: 指定单词链的首字母
* -t: 指定单词链的尾字母
	* -h, -t可同时被使用
* -r: 允许单词环

------------------------

* -c
  * 是唯一的单词数量最长也是字母数量最长
  * 是单词数量最长中的一个，但是是所有单词数量最长中的字母数量最长的
  * 不是单词数量最长的，但是是字母数量最长的。
  * 是字母数量最长中的一个。

* 复合使用-w/-c,-h&-t
  * 指定后的本身就是最长的
  * 指定后是元最长的一部分
  * 指定后的本身不是最长的
  * 指定后最长的中的一个

* -r
  * 结果是环
    * 全部连成一个环
    * 只有环
    * 局部可成环
    * 是多个环中的一个
  * 结果不是环

* 符合使用-r, -h&-t
  * 对于自身成环
    * 有多个环中可选的节点用于切入
    * 环中有且只有一个节点可以用于切入