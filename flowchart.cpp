#include<bits/stdc++.h>
using namespace std;
string str,str1;
bool lnote=0;
int p;
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
	if(str[p]=='\t'){p++;return;}
	
	str1+=str[p];
	p++;
	return;
}
//开始作妖了

string str2="",s="";//str2为检测token后的字符串，s循环储存token
bool in_quote=0;
bool isgap(char x)
{
	if('0'<=x&&x<='9')return false;
	if('a'<=x&&x<='z')return false;
	if('A'<=x&&x<='Z')return false;
	if(x=='_')return false;
	return true;
}
int bracket;
string shape;
void start_if(int i)
{
	bracket=1;
	shape="shape=diamond";
	return;
}
void get_token()
{
	str2=s="";
	for(int i=0;i<str1.length(),++i)
	{
		s+=str1[i];
		if(in_quote)//如果在引号中，就不用识别token
		{
			if(str1[i]=='"'){in_quote=0;}
			else {continue;}
		}
		if(isgap(str1[i]))
		{
			//如果这个gap代表一个特殊语句的开始
			if(s=="if")start_if(i);
			else if(s=="while")start_while(i);
			else if(s=="for")start_for(i);
			else if(s=="return")do_return(i);
			else if(s=="return")do_return(i);
			else if(s=="continue")do_continue(i);
			//...
			
			//把s加到str2后面
			str2+=s,s="";
			if(str1[i]!=' ')str2+=" ";
			str2+=str[i];
			//
			if(str1[i]==';')clean();//一句话结束了，创建一个新节点
		}
	}
}
int main()
{
	freopen("c.in","r",stdin);
	printf("digraph example{\n");
	while(getline(cin,str))
	{
		p=0,str1="";
		while(p<str.length())
			reform();
		if(str1=="")continue;

		get_token();

		//cout<<str1<<endl;
	}
	return 0;
}

