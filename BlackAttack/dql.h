#include "hacker.h"
#include <Windows.h>
#include <string>
#include <cmath>
#define PWDSIZE 20
#define NAMSIZE 20
#define IDMAX 20
#define RDMAX 4096
#define PDMAX 100

using namespace std;
//BlackAttack功能菜单输出函数
void Display();

void Display()
{
	char* p[6]={"1-创建账号","2-删除账号","3-网站404攻击",
		"4-网站篡改攻击","5-网站攻击记录查询","6-网站攻击修复"};
	for(int i=0;i<6;i++)
		cout<<p[i]<<endl;
};

//BlackAttack用户登录函数
void Login();

void Login()
{
	char name[NAMSIZE];
	char password[PWDSIZE];

	char name_tmp[NAMSIZE];
	char password_tmp[PWDSIZE];

	FILE* fp=fopen("Account.txt","r");
	if(!fp)
	{
		cout<<"Account文件打开失败"<<endl;
		Sleep(1000);
		exit(1);
	}

	do
	{
		cout<<"请输入name:";
		cin>>name;
		cout<<"请输入password:";
		cin>>password;
		do
		{
			fscanf(fp,"%s	%s",name_tmp,password_tmp);//按行格式读入Account文件中账号信息
			if(!strcmp(name,name_tmp) && !strcmp(password,password_tmp))
			{
				cout<<"输入账号正确"<<endl;
				Sleep(1000);
				fclose(fp);
				system("cls");
				break;
			}
		}while(!feof(fp));

		if(feof(fp))
		{
			cout<<"输入账号错误"<<endl;
			Sleep(1000);
			rewind(fp);//指针返回文件初始位置
			system("cls");
		}
		else
			break;
	}while(true);
}

//单功能标题输出函数
void DisplayOne(int n);

void DisplayOne(int n)
{
	char* p[6]={"创建账号","删除账号","网站404攻击",
		"网站篡改攻击","网站攻击记录查询","网站攻击修复"};
	string str(20,'=');
	cout<<str<<endl;
	cout<<p[n-1]<<endl;
	cout<<str<<endl;
}

//1-创建账号功能实现
void CreateAccount(int n);

void CreateAccount(int n)
{
	DisplayOne(n);

	char name[NAMSIZE];
	char password[PWDSIZE];

	cout<<"请输入创建账号name:";
	cin>>name;
	cout<<"请输入创建账号password:";
	cin>>password;

	FILE* fp=fopen("Account.txt","a");
	if(!fp)
	{
		cout<<"打开Account文件失败"<<endl;
		Sleep(1000);
		exit(2);
	}
	fprintf(fp,"%s	%s\n",name,password);
	fclose(fp);
	cout<<"账号创建完成"<<endl;
}

//2-删除账号功能实现
void DelectAccount(int n);

void DelectAccount(int n)
{
	DisplayOne(n);

	char name[NAMSIZE];

	char name_tmp[NAMSIZE];
	char password_tmp[PWDSIZE];
	cout<<"请输入删除的账号name:";
	cin>>name;

	FILE* fp=fopen("Account.txt","r+");
	if(!fp)
	{
		cout<<"文件Account打开失败"<<endl;
		Sleep(1000);
		exit(3);
	}
	bool key=false;
	do
	{
		fscanf(fp,"%s	%s",name_tmp,password_tmp);
		if(!strcmp(name,name_tmp))
		{
			printf("Account文件中存在%s账号信息\n",name);
			break;
		}
	}while(!feof(fp));

	if(feof(fp))
	{
		printf("Account中没有%s账号信息\n",name); 
		Sleep(1000);
		return ;
	}

	int stance=(strlen(name_tmp)+strlen(password_tmp)+1)*(-1);
	fseek(fp,stance,SEEK_CUR);
	fputc('*',fp);
	cout<<"修改完成"<<endl;
	fclose(fp);
	Sleep(1000);
}

//功能选择与使用函数
void function();

void function()
{
	int Select;
	bool Key;
	char Id[IDMAX];//存放网站id
	char Response[RDMAX] ;//接受攻击结果返回
	char Para[IDMAX];//篡改内容

	do
	{
		Display();
		cout<<"请输入功能编号:";
		cin>>Select;

		switch(Select)
		{
		case 1:
			//创建账号函数
			CreateAccount(1);	break;
		case 2:
			//删除账号函数
			DelectAccount(2);	break;
		case 3:
			DisplayOne(3);
			cout<<"请输入攻击网站的id:";
			cin>>Id;
			//网站404攻击函数
			hk_404(Id,Response);
			cout<<UTF8ToGBK(Response)<<endl;	break;
		case 4:
			DisplayOne(4);
			cout<<"请输入篡改信息:";
			cin>>Para;
			//网站篡改攻击函数
			hk_tamper(Id,Para,Response);
			cout<<UTF8ToGBK(Response)<<endl;	break;
		case 5:
			//网站攻击记录查询函数
			hk_record(Id,Response);
			cout<<UTF8ToGBK(Response)<<endl;	break;
		case 6:
			//int hk_restore(char *id, char *response);
			hk_restore(Id,Response);
			cout<<UTF8ToGBK(Response)<<endl;
		}
		cout<<"是否执行其他功能? Yes-1,No-0:";
		cin>>Key;
		system("cls");
	}while(Key);
}





