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
//BlackAttack���ܲ˵��������
void Display();

void Display()
{
	char* p[6]={"1-�����˺�","2-ɾ���˺�","3-��վ404����",
		"4-��վ�۸Ĺ���","5-��վ������¼��ѯ","6-��վ�����޸�"};
	for(int i=0;i<6;i++)
		cout<<p[i]<<endl;
};

//BlackAttack�û���¼����
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
		cout<<"Account�ļ���ʧ��"<<endl;
		Sleep(1000);
		exit(1);
	}

	do
	{
		cout<<"������name:";
		cin>>name;
		cout<<"������password:";
		cin>>password;
		do
		{
			fscanf(fp,"%s	%s",name_tmp,password_tmp);//���и�ʽ����Account�ļ����˺���Ϣ
			if(!strcmp(name,name_tmp) && !strcmp(password,password_tmp))
			{
				cout<<"�����˺���ȷ"<<endl;
				Sleep(1000);
				fclose(fp);
				system("cls");
				break;
			}
		}while(!feof(fp));

		if(feof(fp))
		{
			cout<<"�����˺Ŵ���"<<endl;
			Sleep(1000);
			rewind(fp);//ָ�뷵���ļ���ʼλ��
			system("cls");
		}
		else
			break;
	}while(true);
}

//�����ܱ����������
void DisplayOne(int n);

void DisplayOne(int n)
{
	char* p[6]={"�����˺�","ɾ���˺�","��վ404����",
		"��վ�۸Ĺ���","��վ������¼��ѯ","��վ�����޸�"};
	string str(20,'=');
	cout<<str<<endl;
	cout<<p[n-1]<<endl;
	cout<<str<<endl;
}

//1-�����˺Ź���ʵ��
void CreateAccount(int n);

void CreateAccount(int n)
{
	DisplayOne(n);

	char name[NAMSIZE];
	char password[PWDSIZE];

	cout<<"�����봴���˺�name:";
	cin>>name;
	cout<<"�����봴���˺�password:";
	cin>>password;

	FILE* fp=fopen("Account.txt","a");
	if(!fp)
	{
		cout<<"��Account�ļ�ʧ��"<<endl;
		Sleep(1000);
		exit(2);
	}
	fprintf(fp,"%s	%s\n",name,password);
	fclose(fp);
	cout<<"�˺Ŵ������"<<endl;
}

//2-ɾ���˺Ź���ʵ��
void DelectAccount(int n);

void DelectAccount(int n)
{
	DisplayOne(n);

	char name[NAMSIZE];

	char name_tmp[NAMSIZE];
	char password_tmp[PWDSIZE];
	cout<<"������ɾ�����˺�name:";
	cin>>name;

	FILE* fp=fopen("Account.txt","r+");
	if(!fp)
	{
		cout<<"�ļ�Account��ʧ��"<<endl;
		Sleep(1000);
		exit(3);
	}
	bool key=false;
	do
	{
		fscanf(fp,"%s	%s",name_tmp,password_tmp);
		if(!strcmp(name,name_tmp))
		{
			printf("Account�ļ��д���%s�˺���Ϣ\n",name);
			break;
		}
	}while(!feof(fp));

	if(feof(fp))
	{
		printf("Account��û��%s�˺���Ϣ\n",name); 
		Sleep(1000);
		return ;
	}

	int stance=(strlen(name_tmp)+strlen(password_tmp)+1)*(-1);
	fseek(fp,stance,SEEK_CUR);
	fputc('*',fp);
	cout<<"�޸����"<<endl;
	fclose(fp);
	Sleep(1000);
}

//����ѡ����ʹ�ú���
void function();

void function()
{
	int Select;
	bool Key;
	char Id[IDMAX];//�����վid
	char Response[RDMAX] ;//���ܹ����������
	char Para[IDMAX];//�۸�����

	do
	{
		Display();
		cout<<"�����빦�ܱ��:";
		cin>>Select;

		switch(Select)
		{
		case 1:
			//�����˺ź���
			CreateAccount(1);	break;
		case 2:
			//ɾ���˺ź���
			DelectAccount(2);	break;
		case 3:
			DisplayOne(3);
			cout<<"�����빥����վ��id:";
			cin>>Id;
			//��վ404��������
			hk_404(Id,Response);
			cout<<UTF8ToGBK(Response)<<endl;	break;
		case 4:
			DisplayOne(4);
			cout<<"������۸���Ϣ:";
			cin>>Para;
			//��վ�۸Ĺ�������
			hk_tamper(Id,Para,Response);
			cout<<UTF8ToGBK(Response)<<endl;	break;
		case 5:
			//��վ������¼��ѯ����
			hk_record(Id,Response);
			cout<<UTF8ToGBK(Response)<<endl;	break;
		case 6:
			//int hk_restore(char *id, char *response);
			hk_restore(Id,Response);
			cout<<UTF8ToGBK(Response)<<endl;
		}
		cout<<"�Ƿ�ִ����������? Yes-1,No-0:";
		cin>>Key;
		system("cls");
	}while(Key);
}





