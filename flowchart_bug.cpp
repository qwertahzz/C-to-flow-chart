//写while ing
//bug：while内最后一句话不能是if


//todo(to think)：for循环怎么把边界什么的抠出来

//中长期todo：1.实现return和continue;
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<cstdlib>
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
int father=0;bool in_else=0;
void add(int fa,int nod)
{
	if(special==1)//这个节点是特殊语句节点
	{
		printf("\"%s\"->\"%s\"\n\"%s\"[shape=diamond]\n",label[fa].c_str(),label[nod].c_str(),label[nod].c_str());
	}
	else
	{
		printf("\"%s\"->\"%s\"",label[fa].c_str(),label[nod].c_str());
		if(special==2)//这个节点的父节点是特殊语句节点
		{
			if(fa==nod-1)printf("[label=true]");
			else printf("[label=false]");
			special=0;
		}
		printf("\n");
	}
	return;
}
void readd()//回溯加边
{
	st a=data.top();data.pop();
	if(a.type1==1)//if语句：把false链连到if节点上
	{
		father=a.node1;
		//把true链的最后一个节点当作新的特殊节点push进栈
		//a.node1=node;
		//a.type1=4;
		//a.flor1=flor;
		//data.push(a);
		//true链后再建一个节点当作新的特殊节点push进栈
		a.node1=++node;
		a.type1=4;
		a.flor1=flor;
		data.push(a);
		label[node]=std::to_string(node);
		add(node-1,node);
		printf("\"%s\"[shape=point]\n",label[node].c_str());
		
		
		special=2;
		return;
	}
	if(a.type1==2)
	{
		printf("\"%s\"->\"%s\"\n",label[node].c_str(),label[a.node1].c_str());
		father=a.node1;
		special=2;
		return;
	}
	/*for:todo
	if(a.type1==3)
	{

	}
	*/
	if(a.type1==4)
	{
		father=a.node1;
		if(in_else) add(node,a.node1);
		else add(a.node1,node);
		return;
	}
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
			if(s=="if"){start_if();}
			else if(s=="else"){in_else=1;s="";}//else的处理todo
			else if(s=="while"){start_while();}
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
				if((!bracket)&&(special==1))
				{
					//str2+="?";
					label[node]=str2;str2="";
					add(father,node);//这个gap代表一个特殊语句(if,while,for)的结束
					father=node;
					special=2;
				}
			}
			else if(str1[i]=='{')flor++;
			else if(str1[i]=='}')
			{
				flor--;
				if(flor==data.top().flor1){readd();}
				while(flor==data.top().flor1&&data.top().type1!=4)
				{readd();}
			}
			//todo!

			if(str1[i]==';')
			{
				//cout<<str2<<endl;
				node++;
				label[node]=str2;str2="";
				int test=0;
				if(special==2&&data.top().type1==4&&(!(in_else)))
				{add(father,data.top().node1);test++;}
				
				add(father,node);
				father=node;
				if(flor==data.top().flor1){readd();}
				while(flor==data.top().flor1&&data.top().type1!=4)
				{readd();}
			}//一句话结束了，创建一个新节点
		}
		else s+=str1[i];
	}
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
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
	while(data.size()>1){readd();}
	printf("}");

	return 0;
}