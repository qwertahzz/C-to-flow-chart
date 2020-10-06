//写了readd函数，涵盖了if和while的回溯,但是输出有点问题，要调。
//还写了start_while。

//todo:调整flor的使用
//todo：for循环怎么把边界什么的抠出来

//中长期todo：1.实现return和continue;2.把源程序和graphviz之间的桥架好
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
string str,str1;
bool lnote=0;
int p;
bool isgap(char x)
{
	if('0'<=x&&x<='9')return false;
	if('a'<=x&&x<='z')return false;
	if('A'<=x&&x<='Z')return false;
	if(x=='_')return false;
	return true;
}
inline void reform()//去掉注释和制表符和多余空格
{
	//去掉注释
	if(lnote)
	{
		if(str[p]=='*'&&str[p+1]=='/'){lnote=0;p+=2;return;}
		p++;return;
	}
	if(str[p]=='/'&&str[p+1]=='*'){lnote=1;p+=2;return;}
	if(str[p]=='/'&&str[p+1]=='/'){p=str.length();return;}
	//去掉多余空格和制表符
	if(str[p]==' '&&str[p+1]==' '){p++;return;}
	if(str[p]==' '&&p==str.length()-1){p++;return;}
	//if(str[p]==' '&&(isgap(str[p-1])||isgap(str[p+1]))){p++;return;}
	if(str[p]=='\t'){p++;return;}
	
	str1+=str[p];
	p++;
	return;
}
//开始作妖了

string str2="",s="";//str2为检测token后的字符串，s循环储存token
bool in_quote=0;
int node=0,flor=0;
struct st{
	int node1,flor1,type1;
};
stack<st>data;//用stack储存层级信息
int bracket=0;//圆括号
int special=0;//1：这句是特殊语句 2：上一句是特殊语句
void start_if()
{
	node++;
	st a;
	a.node1=node,a.flor1=flor,a.type1=1;//flor维护（todo
	data.push(a);
	special=1;
	return;
}
void start_while()
{
	node++;
	st a;
	a.node1=node,a.flor1=flor,a.type1=2;
	data.push(a);
	special=1;
	return;
}
string label[1007];
int father=0;
void clean()
{
	label[node]=str2;str2="";
	if(special==1)
	{
		printf("\"%s\"->\"%s\"\n\"%s?\"[shape=diamond]\n",label[father].c_str(),label[node].c_str(),label[node].c_str());
	}
	else
	{
		printf("\"%s\"->\"%s\"",label[father].c_str(),label[node].c_str());
		if(special==2)
		{
			if(father==node-1)printf("[label=ture]");
			else printf("[label=false]");
		}
		printf("\n");
	}
	father=node;
	return;
}
void readd()
{
	st a=data.top();data.pop();
	if(a.type1==1)
	{
		father=a.node1;
		special=2;
		return;
	}
	if(a.type1==2)
	{
		printf("\"%s\"->\"%s\"",label[node].c_str(),label[a.node1].c_str());
		return;
	}
	/*for:todo
	if(a.type1==3)
	{

	}
	*/
	return;
}
void get_token()
{
	for(int i=0;i<str1.length();++i)
	{
		if(in_quote)//如果在引号中，就不用识别token
		{
			s+=str1[i];
			if(str1[i]=='"'){in_quote=0;}
			else {continue;}
		}
		else if(isgap(str1[i]))
		{
			//如果这个gap代表一个特殊语句的开始
			if(s=="if"){start_if();s="";}
			else if(s=="else"){s="";}
			else if(s=="while"){start_while();s="";}
			/*
			else if(s=="for")start_for(i);
			else if(s=="return")do_return(i);//todo
			else if(s=="continue")do_continue(i);//todo
			*/
			
			//...收尾(todo
			//把s和这个gap加到str2后面
			if(str1[i]!='{'&&str1[i]!='}'&&str1[i]!='"')//不要大括号，不要双引号，不要多余空格	
			s+=str1[i];
			if(s!="")str2+=s,s="";
			//处理括号
			if(str1[i]=='(')bracket++;
			else if(str1[i]==')')
			{
				bracket--;
				if(!bracket&&special==1)
				{
					clean();//这个gap代表一个特殊语句(if,while,for)的结束
					special=2;
				}
			}
			else if(str1[i]=='{')flor++;
			else if(str1[i]=='}')flor--;
			while(flor==data.top().flor1)readd();//todo!

			if(str1[i]==';'){node++;clean();}//一句话结束了，创建一个新节点
		}
		else s+=str1[i];
	}
}
int main()
{
	freopen("c.in","r",stdin);
	printf(" digraph example{\n");
	label[0]="start";
	st a;a.flor1=-2333;data.push(a);
	while(getline(cin,str))
	{
		//初处理
		p=0,str1="";
		while(p<str.length())
			reform();
		if(str1=="")continue;
		//
		get_token();

		//cout<<str1<<endl;
	}
	printf("}");

	return 0;
}