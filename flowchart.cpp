#include<bits/stdc++.h>
using namespace std;
string str,str1;
bool lnote=0;
int p,p1;
void reform()//ȥ��ע�ͣ�ͬʱȥ���Ʊ���Ͷ���ո� 
{
	//ȥ��ע�� 
	if(lnote)
	{
		if(str[p]=='*'&&str[p+1]=='/'){lnote=0;p+=2;return;}
		p++;return;
	}
	if(str[p]=='/'&&str[p+1]=='*'){lnote=1;p+=2;return;}
	if(str[p]=='/'&&str[p+1]=='/'){p=str.length();return;}
	//�Ʊ���Ϳո� 
	if(str[p]==' '&&str[p+1]==' '){p++;return;}
	if(str[p]==' '&&p==str.length()-1){p++;return;}
	if(str[p]=='\t'){p++;return;}
	
	str1[p1]=str[p];
	p1++;p++;
	return;
}
int main()
{
	freopen("c.in","r",stdin);
	while(getline(cin,str))
	{
		p=p1=0;
		str1="";
		while(p<str.length())
			reform();
		for(int i=0;i<p1;++i)
		cout<<str1[i];
		if(p1)cout<<endl;
	}
	return 0; 
}

