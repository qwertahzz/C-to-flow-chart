# C-to-flow-chart

## done:

去掉注释；

顺序输出代码（忽略头文件，大括号）；

判断语句在出边上显示true/false；

if和else；

while；

if,while的嵌套；

自定义函数；（另起一图

continue;（在if后

break;

各种语句对应的节点形状

## todo:

for;

else if;

## 优化空间：

把图的最后一个点放在最下面，使图好看；




***
***
***
***




### 10.2 共3h

注册，摸索github，看github入门教程 **1h**

下载，安装，学习graphviz入门 **1h**

因为只学过C++，又去看C语言教程 **1h**


### 10.3 共5h

早起去自习室，继续学着用graphviz **1h**

上午有C语言课，自己看enum。

下午把任务书不懂的名词都查了一下，又翻阅了一些功能类似的网站和其构建教程，终于有了些思路。

四点半开始装windows下的c环境（之前一直用ubuntu虚拟机写代码），六点放弃了（配置文件下载不下来

### 10.4 共5h

去1006实(划)习(水)一天。

上午十点多才开门，上午写了把注释去掉的功能 **1.5h**

看《两周自制脚本语言》 **2h**

又去看了一些乱七八糟的相关知识。

晚上旁听了程序组大大们的组会，不明觉厉，希望自己也能成为其中一员。

### 10.5 共3h

现在的想法是把int之类的关键词和数字全部直接当成普通字符串，符号也识别成普通字符串，输出时各字符串之间无脑空一格；然后只把if，while这种会影响到框图的关键词当作关键词识别。

中午下午学了点map，enum，正则表达式，但一时难以掌握，决定还是用蠢方法先写个大概框架出来。

把get_token函数写了个框架，不过至少是有方向，可以填了。

终于开始写代码了，思路也有了。

### 10.6 共5h

想到了用stack处理逻辑，目前思维上没有什么想不通的地方了。

·

处理graphviz的label不能带符号和汉字的问题 2h

写了readd函数，涵盖了if和while的回溯,但是输出有点问题，要调。

以及优化输出格式，还写了start_while。 3h

今天终于有输出的图看了。

### 10.7 共7h

今天做出了差不多完整的if。

晚上加while的时候，while和if的嵌套搞炸了，写了一晚上(4h)bug。

对了，今天在ubuntu虚拟机也装了graphviz，从而实现一句./run就弹出图片的效果。

### 10.8 共7h

换了思路，上午把if重新写了 1h

下午给while后面也加了点，于是if和while的嵌套终于调好了 2h

处理自定义函数 2h

写continue 2h

### 10.9

写break，调整节点的形状和颜色 2h（上午
