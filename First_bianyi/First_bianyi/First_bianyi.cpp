// First_bianyi.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
//int _tmain(int argc, _TCHAR* argv[])
//{
//	int x;
//	CMyLex lex;
//	lex.Analysis("src/test.txt","");
//	cin >> x;
//	cin >> x;
//	return 0;
//}
#include "stdafx.h"


void UI_Head();

int _tmain(int argc, _TCHAR* argv[])
{
	char x;
	CMyLex lex;
	string in, out;

	while (1)
	{
		UI_Head();
		while (1)
		{
			cout << "��������Ҫ�������ļ���/·����";
			cin >> in;
			ifstream rf;
			rf.open(in.c_str());
			if (rf){
				rf.close();
				break;
			}
			cout << "�����ļ�������,";
		}
		cout << "������洢������ļ���/·����";
		cin >> out;
		lex.Analysis(const_cast<char*>(in.c_str()), const_cast<char*>(out.c_str()));

		cout << "�Ƿ�������һ�ļ�(Y/N)��";
		cin >> x;
		if (x != 'Y' || x != 'y') break;
		system("cls");
	}
	return 0;
}

void UI_Head()
{
	cout << "=================================================" <<endl;
	cout << "================����ԭ���һ��ʵ��===============" << endl;
	cout << "=================TEST���Դʷ�����================" << endl;
	cout << "=====================������======================" << endl;
	cout << "================����Դ  5120140975===============" << endl;
	cout << "================��  ��  5120140988===============" << endl;
	cout << "================��  ��  5120140548===============" << endl;
	cout << "================�����  5120140970===============" << endl;
	cout << "=================================================" << endl;
}