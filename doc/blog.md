# 1
# 2
# 3

# 8
# TODO 代码覆盖率

对Core模块进行单元测试的过程是：构造测试样例=>传入进Core模块=>检查返回的单词链的长度与内容是否正确。

其中，我们将后两步独立出来，封装进了testutil的两个函数中。

两个函数分别是：
    
    void testRight(char* words[], int words_len, char* res[], int res_len, bool is_max_char, char head, char tail, bool enable_loop);
    void testRightMulti(char* words[], int words_len, vector<char**> res, vector<int> res_len, bool is_max_char, char head, char tail, bool enable_loop);

两个函数的区别在于testRightMulti允许符合要求的最长单词链有多条，Core模块只要返回其中一条即为正解。

值得关注的是enable_loop参数。
当enable_loop为假时，会按索引序比较正解与Core返回的解；
当enable_loop为真时，只会进行无序比较。

作为展示的一个简单的测试样例：

    TEST_METHOD(simple)
	{
		char* words[] = {
			"hello",
			"world",
			"ofk",
			"kw"
		};
		char* res[] = {
			"hello",
			"ofk",
			"kw",
			"world"
		};

		testRight(words, 4, res, 4);
	}

我们构造测试样例的方式有以下四种：
  1. 分析作业要求，找出边界条件，构造边界样例。
  2. 根据算法的搜索方式的性质，构造针对性样例。
  3. 使用简单算法自动生成大样例，构造压力样例。
  4. 针对可能被抛出的异常，构造异常样例。

## 1. 边界样例
我们首先细读作业文档，从中划出可以得出边界条件的语句，然后针对该语句构造边界样例。这一过程在demand_analyze.md的前半段被体现。摘取其中一段：

* 单词链至少两个单词，不存在重复单词
	* 构造一个没有任何两个单词能连上的情况
	* 构造有多个重复单词的words
	* 构造一个首尾字母相同的单词

## 2. 针对性样例
在完成算法编写后，针对算法中可能存在的分支、迭代，构造针对性样例试图去覆盖，检验是否如预期那样执行。这一过程在demand_analyze.md的后半段被体现。摘取其中一段：

* -c
  * 是唯一的单词数量最长也是字母数量最长
  * 是单词数量最长中的一个，但是是所有单词数量最长中的字母数量最长的
  * 不是单词数量最长的，但是是字母数量最长的。
  * 是字母数量最长中的一个。

## 3. 压力样例
我们设计了一种简单的算法来自动生成大的测试样例。我们称这种算法为PyramidGenerator。

算法的基本思路是构造一个最多只有26个非根节点的树，且该树具有最长深度的节点有且仅有一个。

![](pyramid.png)

如图构造树，每一个节点代表一个字母，每条边表示以起点为首字母、以终点为尾字母的一族单词。由此，每条边上都可以生成无数单词。
而如果我们控制root-t-e-o这条路径上的每条边都只生成一个单词，例如：tme-ego，那么该路径的单词连起来就是唯一最长单词链。

通过使用PyramidGenerator，我们可以生成任意大小的无环测试样例。

## 4. 异常样例
我们简单地针对Core执行中会抛出的异常构造对应的样例，当该样例被输入后，尝试捕获异常。