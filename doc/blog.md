# 1
# 2
# 3

# 4

## a.算法概述

我们认为这次结对编程的题目可以抽象为有向有环图求最长路径，目前我们使用的算法还是深度遍历穷举所用可能的路径，该图有26个点对应26个英文字母，每个边代表输入的单词，例如输入"hello"可以化为从点'h'到'o'的边。

首先根据五项需求-w-r-h-t-c, 其中单独的-w是可以约化到-r的，而单独的-r是不能约化到-w，对于-h-t只是对路径首尾进行检测约束，对于-c只是将图的边加权。所以算法应该针对-r设计。深度遍历的过程将从一个点开始，例如'h'，如果该点有指向点的边，则递归访问下一点，下一点的递归完成后才会访问'h'的其他边的指向。

## b.算法数据结构

边和点的struct分别是：

```C++
struct Edge {  
	std::string word;  
	int code;  
	int weight;  
	int next;  
}; 
``` 

边Edge的word存储输入的原始字符串；code是该边的识别编码；weight是该边权重，weight默认为1，在-c时为字符串长度；next是字符串末尾字符ascii码-'a'的值，方便将点的编码都归为0-25。

	
```C++
struct WordMap {
	std::vector<Edge> toLast;
};
```
	
点WordMap只包含一个边的vector。
	
## c.类和函数

核心计算包括两个类Core和ChainSolver，Core负责标准输入，所有外部类和函数只调用Core，Core再调用ChainSolver的get_max_chain函数。

ChainSolver类有三个函数公有函数get_max_chain、私有函数CreateMap、私有函数Recursion，get_max_chain调用CreateMap来创建图，再调用Recursion递归DFS创建过的图。

### get_max_chain函数

接收以下参数：
```C++
char *input[], int num, char *result[], char head, char tail, bool isGetMaxChar, bool enable_loop
```

以上参数分别是输入的单词数组，输入的单词量，需要输出结果的result，head为-h的头部要求，tail为-t的尾部要求，isGetMaxChar是-c的边权重修改要求，enable_loop是-r的要求。

### CreateMap函数

这个部分需要考虑重复输入的单词并将其抛弃，map<string,int>类型的inputWord存储的是已录入的单词。
```C++
	if (inputWord.find(s) != inputWord.end()) {
		return 0;
	}
	inputWord.insert(std::pair<std::string, int>(s, code));
```
单词编码部分使用最普通的线性编码0-100，最开始想到过APHash编码但是对于作业里面的小规模的输入太过拖沓。

### Recursion函数

使用的是递归法DFS，对传入节点进行路径穷举遍历，进入过的点和边都会被记载在isUsedPoint和isUsedEdge中，递归返回后再将记载记录释放。优化部分会在第六节描述。


# 5
# TODO UML

# 6

我们对DFS穷举法的主要优化是自环剪枝，很明显在求-r最长路径的过程中自环是必定需要走的边，不需要再递归判定了，所以在Recursion进入节点的时候先将该节点所有**未走过的自环边**加入路径中。

```C++
	//ensure the edge that wait to push is not used before.
	if (isUsedEdge[iter.code])
		continue;//'continue' will jump this edge.
	//push every self-circle edge.
	path.push_back(iter.word);
	if (iter.next == point) {
		len+=iter.weight;
		continue;
	}
	...
        ...
        ...
	//pop every self-circle edge.
	for (auto iter : map[point].toLast) {
            if (iter.next == point) {
                isUsedEdge[iter.code] = false;
                path.pop_back();
            }
            else {
                break;
            }
	}
```


# 8
Core模块的单元测试覆盖率：
![](cover.png)

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
  a. 分析作业要求，找出边界条件，构造边界样例。
  b. 根据算法的搜索方式的性质，构造针对性样例。
  c. 使用简单算法自动生成大样例，构造压力样例。
  d. 针对可能被抛出的异常，构造异常样例。

## a. 边界样例
我们首先细读作业文档，从中划出可以得出边界条件的语句，然后针对该语句构造边界样例。这一过程在demand_analyze.md的前半段被体现。摘取其中一段：

* 单词链至少两个单词，不存在重复单词
	* 构造一个没有任何两个单词能连上的情况
	* 构造有多个重复单词的words
	* 构造一个首尾字母相同的单词

## b. 针对性样例
在完成算法编写后，针对算法中可能存在的分支、迭代，构造针对性样例试图去覆盖，检验是否如预期那样执行。这一过程在demand_analyze.md的后半段被体现。摘取其中一段：

* -c
  * 是唯一的单词数量最长也是字母数量最长
  * 是单词数量最长中的一个，但是是所有单词数量最长中的字母数量最长的
  * 不是单词数量最长的，但是是字母数量最长的。
  * 是字母数量最长中的一个。

## c. 压力样例
我们设计了一种简单的算法来自动生成大的测试样例。我们称这种算法为PyramidGenerator。

算法的基本思路是构造一个最多只有26个非根节点的树，且该树具有最长深度的节点有且仅有一个。

![](pyramid.png)

如图构造树，每一个节点代表一个字母，每条边表示以起点为首字母、以终点为尾字母的一族单词。由此，每条边上都可以生成无数单词。
而如果我们控制root-t-e-o这条路径上的每条边都只生成一个单词，例如：tme-ego，那么该路径的单词连起来就是唯一最长单词链。

通过使用PyramidGenerator，我们可以生成任意大小的无环测试样例。

## d. 异常样例
我们简单地针对Core执行中会抛出的异常构造对应的样例，当该样例被输入后，尝试捕获异常。

# 9.
计算部分一处异常处理，当没有启用-r功能却检查到有环图时将抛出异常w_c_h_t_ChainLoop，以下代码的判定条件是该边的终点已被走过，同时没有开启-r，同时不是自环。

```C++
	if (isUsedPoint[iter.next] && !isEnableLoop && point != iter.next) {
		throw w_c_h_t_ChainLoop;
	}
```
另外也需要考虑对Core的单元测试异常抛出，其实以下异常在程序作为整体运行时不会抛出：
传入的尾部要求是否合理：
```C++
	if (tail_input != 0 && (tail_input < 'a' || tail_input > 'z')) {
		throw para_tail_error;
	}
```
传入的头部要求是否合理：
```C++
	if (head_input != 0 && (head_input <'a' || head_input > 'z')) {
		throw para_head_error;
	}
```
传入的enable_loop是否合法：
```C++
	try {
		isEnableLoop = enable_loop;
	}
	catch(...){
		throw para_loop_error;
	}
```
传入的input数组里面是不是的确有num个值：
```C++
	for (i = 0; i < num; i++) {
		try {
			CreateMap(input[i], isGetMaxChar);
		}
		catch (...) {
			throw para_input_error;
		}
	}
```
传入的res是否能接受结果：
```C++
	try {
		for (auto iter : maxPath) {
			char *new_str = new char[iter.length() + 2];
			// std::cout << iter << " ";
			for (unsigned int j = 0; j < iter.length(); j++)
				new_str[j] = iter[j];
			new_str[iter.length()] = '\0';
			result[i] = new_str; // TODO release such memory
			i++;
		}
	}
	catch (...) {
		throw para_res_error;
	}
```
传入input输入字符串是否包括非法字符(在创建图时统一抛出异常)：
```C++
	int ChainSolver::CreateMap(char *c_s, bool isGetMaxChar) {
	try {
		...
		...
		...
	}
	catch (...) {
		throw create_map_error;
	}
	return 0;
```

# 10.
界面分为三个组成部分：
a. UIUtility: UI共通的代码的集合
b. cmdUI: 基于命令行实现的UI
c. MFCUI: 基于MFC实现的GUI

## a. UIUtility
因为无论是命令行实现还是MFC实现，只要是UI界面就会有部分共通的逻辑需要处理。
所以我们将这部分逻辑抽离出来，编译成UIUtility.dll。

实际被抽离出来的逻辑为对文本输入进行分词，得到英语单词数组的部分。我们将其称为StreamReader，它接受一个输入流，输出对应的单词数组。
为了方便调用，我们也提供了一个作为StreamReader的封装的FileReader，它接受一个文件名，并将该文件的输入流作为StreamReader的输入。

StreamReader的具体实现是从流中逐字符读取，自身维护一个临时单词与单词数组。
* 当读到非英文字母时，检查临时单词的长度，若非空，则将临时单词加进单词数组中，然后清空临时单词，否则什么也不做。
* 当读到英文字母时，简单地追加到临时单词的最后。

## b. cmdUI
这部分实现了以命令行参数为用户输入的用户界面。

对命令行参数进行解析的工作被抽离出来在CoreSetting中被实现。CoreSetting会检验参数的合法性，并解析它的含义。
cmdUI的主程序就可以使用CoreSetting解析出来的结果做进一步的操作。

之后主程序简单地调用Core模块，然后将结果输出至文件即结束程序。

## c. MFCUI
这部分实现了基于MFC实现的GUI。

按照作业要求，GUI实现需要
* 直接输入与文件输入两种输入模式
* 选项选择的功能
* 直接打印出结果并提供导出到指定位置的功能

我们的设计中，整个界面分为4块：

* 输入
    
    通过两个单选按钮来控制输入方式。对于直接输入就直接用一个文本框接收输入，对于文件输入就提供一个地址输入栏和文件打开按钮来让用户给出文件地址。
* 选项
    
    选项分为三组。对于-w, -c这组，使用单选按钮保证用户只可以选取其中一个按钮。对于-h, -t，使用勾选框来控制是否添加，同时给出一个只接受一个英文字符的文本框来接受指定字母作为参数。对于-r，简单地使用一个勾选框来表示是否启用该参数。
* 运行

    运行包括程序的执行与程序的关闭两部分。也就是Run和Cancel两个按钮。当用户点击Run时，程序将会读取输入和选项中的数据，并检查数据合法性，之后委托给Core执行，最后将返回的结果填充进输出部分。当Cancel被点击时，简单地结束程序的运行。
* 输出

    输出分为两部分。第一部分是打印显示，当Run被点击，并且数据被顺利处理以后，返回的结果会直接打印到一个文字框中。第二部分是导出，类似于输入部分的地址选择，我们也提供了接口供用户选择输出文件，并提供Export按钮来执行导出功能。

大部分代码都是简单显然的。值得一提的是选项中的-h, -t所使用的文本框的实现。我们的做法是，每当文本框内容被改变，检查文本长度，若大于1，则截断前面的，只留下最后一个字符。然后检查该字符是否为英文字母（大小写无所谓，自动转化成小写字母），若非英文字母则忽略。


# 11.
UI模块的设计已在10中详细描述，此处不重复。

## 模块的对接方式
我们将Core模块作为一个独立的dll抽离出了代码。我们准备了一个导出类Core来作为Core模块整体对外的接口，UI模块可以通过简单地调用这个Core类的静态函数来调用Core模块。

在UI模块调用dll模块时，我们采取的方案是隐式调用。为了支持这样的做法，我们在UI模块的附加依赖项中加入了Core.lib，并且将Core.dll和UI模块的可执行文件放在了同一个文件夹中。

关于具体函数接口，我们只是简单地按照作业的要求实现了Core的接口。接口函数内部会建立ChainSolver类来执行真正的计算过程。当然，这对UI模块而言是透明的。

## 实现的功能
### cmdUI
对于cmdUI，它能解析命令行参数并输出结果至solution.txt中。

例如，命令行参数如下：

![](function_1.png)

运行后的控制台显示：

![](function_2.png)

同时，BIN目录下产生输出文件solution.txt:

![](function_3.png)

而如果参数不正确，例如下图的非法参数-k：

![](error_1.png)

则会提示错误，并终止程序：

![](error_2.png)


### MFCUI
对于MFCUI，它能提供一组控件来让用户输入，并提供一组控件来让用户得到输出。

例如，执行后用户界面如下：

![](function_4.png)

用户可以通过这部分来选择输入模式，上面的是直接输入文本内容，下面的是选择文本文件作为输入：

![](function_5.png)

可以通过这部分来控制选项：

![](function_6.png)

可以通过这部分来查看输出并选择文件来导出：

![](function_7.png)

例如，如下作为输入：

![](function_8.png)

点击Run后就会得到如下输出：

![](function_9.png)

点击Open选择导出文件：

![](function_10.png)

再点击Export执行导出，如果成功就会有如下提示：

![](function_11.png)

如果选项不正确，例如下图的明明勾选了-h，却没有给出对应的首字母：

![](function_12.png)

就会给出报错提示：

![](function_13.png)

# 交换模块
我们和马振亚&马浩翔组交换了模块。

名字|学号
-| -
马振亚|16061109
马浩翔|16061097

## 我们的界面模块、测试模块 + 他们的核心模块
因为我们两组都将Core模块封装成了dll，所以交换过程非常简单便捷。他们将他们Core的dll, lib, h文件给我们，然后我们调整了一下编译选项、调用关系就可以方便地使用他们的代码。

衔接过程最大的不顺利是因为我们仿照了作业示例中的那样将Core类的所有方法都声明为静态方法，而他们组选择的是将接口声明为Core类的成员函数。所以我们不得不修改我们的代码去符合他们组的接口要求。

另一个不顺利是因为他们组是直接在Core类中实现了算法，所以他们的Core.h中包含了一些运行需要的库函数的头文件。而在我们的机子上，他们所需要的stdc++.h头文件并不存在，所以我们不得不删去这句，再包含vector和map来满足编译需求。

衔接完成后在测试过程中也发现了不同。主要是需求理解的不同，对于他们的Core模块而言，空输入、空输出都是会抛出异常的、不合法的，但对于我们的程序而言，这些都是合法的。

# 12

我们两人的结对一直紧紧围绕邹欣老师《构建之法》一书的要求：

>在结对编程模式下，一对程序员肩并肩、平等
>地、互补地进行开发工作。他们并排坐在一台电
>脑前，面对同一个显示器，使用同一个键盘、同
>一个鼠标一起工作。他们一起分析，一起设计，
>一起写测试用例，一起编码，一起做单元测试，
>一起做集成测试，一起写文档等。

我们两人在此次结对编程之前就已熟识，这次结对编程的任务也必然是无缝衔接般地完成。在结对的过程中我们大部分地代码都是坐在一起完成的，一起分析一起设计。当然第一次尝试这样的编程方式也会带来很多疑惑，比如编程一方难免会出现一些不必要的而且较为复杂的构想，比如在计算核心的部分是否需要将字符串进行哈希编码，此时需要另一方加入思考博弈，这样的过程很有趣不过也很花时间。

总的来说，我们觉得结对编程是个高强度、注重思维碰撞的编程方式，和传统那种“各自码各自的代码再push”的方式，结对编程的过程中我们感受到了实时性的交流和code review，这是一种非常敏捷的软件开发方式。