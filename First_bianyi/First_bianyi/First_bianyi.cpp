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
	bool cover= TRUE;
	char x;
	string in, out;

	while (1)
	{
		UI_Head();
		CMyLex lex;
		////�������ļ�·����֤
		//while (1)
		//{
		//	cout << "��������Ҫ�������ļ���/·����";
		//	cin >> in;
		//	ifstream rf;
		//	rf.open(in.c_str());
		//	if (rf){
		//		rf.close();
		//		break;
		//	}
		//	cout << "�����ļ�������,";
		//}

		////������ļ�·����֤
		//cout << "������洢������ļ���/·����";
		//cin >> out;
		//ifstream rf;
		//rf.open(out.c_str());
		//if (rf)
		//{
		//	cout << "����ļ��Ѵ����Ƿ�������ǣ�(Y/N)��";
		//	char x;
		//	cin >> x;
		//	if (x == 'N'||x == 'n') cover = FALSE;
		//}
		//rf.close();

		in = "src/test.txt";
		out = "src/out.txt";

		//����
		lex.Analysis(const_cast<char*>(in.c_str()), const_cast<char*>(out.c_str()),cover);

		CGramAly galy(lex.getShraseList());
		galy.Analysis();




		cout << "�Ƿ�������һ�ļ�(Y/N)��";
		cin >> x;
		if (x != 'Y' && x != 'y') break;
		system("cls");
	}
	return 0;
}

void UI_Head()
{
	cout << "=================================================" << endl;
	cout << "===================����ԭ��ʵ��==================" << endl;
	cout << "===================TEST���Է���==================" << endl;
	cout << "=====================������======================" << endl;
	cout << "================����Դ  5120140975===============" << endl;
	cout << "=================================================" << endl;
}