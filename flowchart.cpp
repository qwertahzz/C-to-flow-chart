//doing:return


//todo:调整flor的使用
//todo：for循环怎么把边界什么的抠出来

//中长期todo：实现return和continue;
//找graphviz，看能不能把最后输出的节点放在图片最下面
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
st a;
stack<st>data;//用stack储存层级信息
int bracket=0;//圆括号
bool special[1007];//为1则为特殊节点
///
string label[1007];
int father=0;
bool have_start=0;
void add(int fa,int nod)
{
	if((!fa)&&(!have_start))return;
	printf("\"%s\"->\"%s\"",label[fa].c_str(),label[nod].c_str());
	if(special[fa])//这个节点的父节点是特殊语句节点
	{
		if(fa==nod-1)printf("[label=ture]");
		else printf("[label=false]");
	}
	printf("\n");
	return;
}
void start_if()
{
	node++;special[node]=1;
	a.node1=node,a.flor1=flor,a.type1=1;//flor维护（todo
	data.push(a);
	return;
}
void start_while()
{
	node++;label[node]=std::to_string(node);
	add(father,node);father=node;
	a.node1=node,a.flor1=flor,a.type1=2;
	data.push(a);
	node++;special[node]=1;
	return;
}
bool in_else=0;
void readd()//回溯加边
{
	a=data.top();data.pop();
	if(a.type1==1)//if语句：把false链连到if节点上
	{
		father=a.node1;
		//把true链的最后一个节点当作新的特殊节点push进栈
		a.node1=node;
		a.type1=4;
		a.flor1=flor;
		return;
	}
	if(a.type1==2)//把while链的末尾接回while框
	{
		printf("\"%s\"->\"%s\"\n",label[node].c_str(),label[a.node1].c_str());
		//false链最后加一个point
		node++;label[node]=std::to_string(node);
		add(a.node1+1,node);
		father=node;//原:father=a.node1
		return;
	}
	/*for:todo
	if(a.type1==3)
	{
	}
	*/
	if(a.type1==4)
	{
		//false链最后加一个point
		node++;label[node]=std::to_string(node);
		add(father,node);//把false链末尾和point相连
		add(a.node1,node);//把true链末尾和point相连
		father=node;
		in_else=0;
		a.type1=0;
		return;
	}
	return;
}
bool in_or_out[1007];
void get_token()
{
	if(str1.find("#include")!=str1.npos)return;
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
			
			//else if(s=="for")start_for(i);
			else if(s=="return");//todo//////////////////////
			//else if(s=="continue")do_continue(i);//todo
			else if((s=="scanf")||(s=="printf")||(s=="getchar")){in_or_out[node+1]=1;}
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
				if((!bracket)&&(special[node])&&label[node]=="")
				{
					label[node]=str2;str2="";
					add(father,node);//这个gap代表一个特殊语句(if,while,for)的结束
					father=node;
				}
			}
			else if(str1[i]=='{')
			{
				flor++;
				if(str2[str2.length()-1]==')'&&(!special[node]))
				{
					node++;father=node;
					label[node]=str2;
					if(str2.find("main()")!=str2.npos)
					{have_start=1;add(0,node);}
					str2="";
				}//生成函数定义句，且函数定义句不与上一句相连
			}
			else if(str1[i]=='}')
			{
				flor--;
				//如果这个if没有else，直接新建point
				if((data.top().type1==4)&&(flor<=data.top().flor1)&&(!in_else))
				{
					node++;label[node]=std::to_string(node);
					add(father,node);//把false链末尾和point相连
					add(data.top().node1,node);//把true链末尾和point相连
					father=node;
					data.pop();a.type1=0;
				}
				while(flor==data.top().flor1)
				{readd();}
				if(a.type1==4){data.push(a);a.type1=0;}
			}
			//todo!
			if(str1[i]==';')
			{
				//如果这个if没有else，直接新建point
				if((data.top().type1==4)&&(flor<=data.top().flor1)&&(!in_else))
				{
					node++;label[node]=std::to_string(node);
					add(father,node);//把false链末尾和point相连
					add(data.top().node1,node);//把true链末尾和point相连
					father=node;
					data.pop();a.type1=0;
				}
				//
				node++;
				label[node]=str2;str2="";
				add(father,node);father=node;
				while(flor==data.top().flor1)readd();
				if(a.type1==4){data.push(a);a.type1=0;}
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
	a.flor1=-2333;data.push(a);
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
	while(data.size()>1)readd();
	if(!have_start){have_start=1;add(0,1);}
	//集中处理shape
	for(int i=1;i<=node;++i)
	{
		if(label[i]==std::to_string(i))
		printf("\"%d\"[shape=point]\n",i);
		else if(in_or_out[i])
		printf("\"%s\"[shape=parallelogram]\n",label[i].c_str());
		else if(special[i])
		printf("\"%s\"[shape=diamond]\n",label[i].c_str());
	}
	printf("}");

	return 0;
}