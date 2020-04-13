#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<string.h>
#include<string>
#include<stack>
using namespace std;
int n;
char prior[9][9]=
{//运算符优先表
	{'>','>','<','<','<','<','>','>','>'},
	{'>','>','<','<','<','<','>','>','>'},
	{'>','>','>','>','>','<','>','>','>'},
	{'>','>','>','>','>','<','>','>','>'},
	{'>','>','>','>','>','<','>','>','>'},
	{'<','<','<','<','<','<','=',' ',' '},
	{'>','>','>','>','>',' ','>','>','>'},
	{'<','<','<','<','<','<',' ','=','>'},
	{'<','<','<','<','<','<',' ','<','='}
};
int to_ope(char c)
{
	switch(c)
	{
	case'+':return 0;
	case'-':return 1;
	case'*':return 2;
	case'/':return 3;
	case'%':return 4;
	case'(':return 5;
	case')':return 6;
	case'=':return 7;
	case'#':return 8;
	}
}
int youxian(char c1,char c2)
{//判断运算符优先
	if(prior[to_ope(c1)][to_ope(c2)]=='<')
		return 2;
	else if(prior[to_ope(c1)][to_ope(c2)]=='>')
		return 1;
	else
		return 0;
}
void deal(string str)
{
	int cur=1,s=0;
	bool flag=true;
	bool t=false;
	stack<char>opn,op;
	op.push('#');
	while(flag)
	{
		if(op.top()=='#'&&t&&s>=str.length())
			flag=false;
		else if(op.top()=='('&&str[s]==')')
		{
			op.pop();
			s++;
			t=true;
		}
		else if(isalpha(str[s]))
		{
			opn.push(str[s]);
			s++;
		}
		else if(youxian(op.top(),str[s])==2)
		{
			op.push(str[s]);
			s++;
			t=true;
		}
		else if(youxian(op.top(),str[s])==1||(s>str.length()&&op.size()>1&&opn.size()>=2))
		{
			char c3=op.top();
			op.pop();
			char c4=opn.top();
			opn.pop();
			char c5=opn.top();
			opn.pop();
			cout<<"T"<<cur<<":=";
			if(islower(c4)&&islower(c5))
			{
				cout<<c5<<c3<<c4<<"     ";
				cout<<"("<<c3<<","<<c5<<","<<c4<<",T"<<cur<<")"<<endl;
			}
			else if(islower(c4)&&!islower(c5))
			{
				int k=c5-'A';
				cout<<"T"<<k<<c3<<c4<<"     ";
				cout<<"("<<c3<<",T"<<k<<","<<c4<<",T"<<cur<<")"<<endl;
			}
			else if(!islower(c4)&&islower(c5))
			{
				int k=c4-'A';
				cout<<c5<<c3<<"T"<<k<<"     ";
				cout<<"("<<c3<<","<<c5<<",T"<<k<<",T"<<cur<<")"<<endl;
			}
			else if(!islower(c4)&&!islower(c5))
			{
				int a=c4-'A';
				int b=c5-'A';
				cout<<"T"<<b<<c3<<"T"<<a<<"     ";
				cout<<"("<<c3<<",T"<<b<<",T"<<a<<",T"<<cur<<")"<<endl;
			}
			char cc='A'+cur;
		    opn.push(cc);
		    cur++;
	}
   }
	cout<<"x:="<<"T"<<cur-1<<"     ";
	cout<<"(:=,T"<<cur-1<<",-,x)"<<endl;
}
int main()
{
	string str;
	getline(cin,str);
	for(string::iterator it=str.begin();it!=str.end();it++)
		if(*it==':')
			str.erase(it);
	string::iterator it=str.begin();
	str.erase(it);
	it=str.begin();
	str.erase(it);
	deal(str);
	return 0;
}
