# 1
# 2
# 3

# 8
对Core模块进行单元测试的过程是：构造测试样例=>传入进Core模块=>检查返回的单词链的长度与内容是否正确。

其中，我们将后两步独立出来，封装进了testutil的两个函数中。

两个函数分别是：
    
    void testRight(char* words[], int words_len, char* res[], int res_len, bool is_max_char, char head, char tail, bool enable_loop);
    void testRightMulti(char* words[], int words_len, vector<char**> res, vector<int> res_len, bool is_max_char, char head, char tail, bool enable_loop);

两个函数的区别在于testRightMulti允许符合要求的最长单词链有多条，Core模块只要返回其中一条即为正解。

值得关注的是enable_loop参数。
当enable_loop为假时，会按索引序比较正解与Core返回的解；
当enable_loop为真时，只会进行无序比较。

我们构造测试样例的方式有以下四种：
  1. 分析作业要求，找出边界条件，构造边界样例。
  2. 根据算法的搜索方式的性质，构造针对性样例。
  3. 使用简单算法自动生成大样例，构造压力样例。
  4. 针对可能被抛出的异常，构造异常样例。


