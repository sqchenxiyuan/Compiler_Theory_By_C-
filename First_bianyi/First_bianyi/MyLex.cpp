#include "stdafx.h"
#include "MyLex.h"

CMyLex::CMyLex()
{
	init();
}


CMyLex::~CMyLex()
{
}

void CMyLex::Analysis(char *input, char* output, bool cover)
{
	ifstream rf;//��ȡ�ļ�
	ofstream wf;//����ļ�
	rf.open(input);
	if (cover)
	{
		wf.open(output);
	}
	else
	{
		wf.open(output, ios_base::app);
	}
	wf.close();

	Sleep(500);
	if (!rf)  //��ȡtxt�ļ�
	{
		printf("��ȡ�ļ�ʧ�� \n ");
	}
	else
	{
		cout << "��ȡ�ɹ�" << endl;
		char c = ' ';
		rf.read(&c, 1);
		while (!rf.eof())
		{
			int last_statu = m_statu;//�洢��һ��״̬�������жϵ������ͣ�������Դ
			m_statu = ST(m_statu, c);

			////��ȷ
			if (m_statu != last_statu&&m_statu == 0)//��ʼ״̬Ϊ0 ����  ��Ϊ0  �������  
			{
					LexShrase sh;
					sh.line = m_line;
					string word;
					word.insert(word.begin(), m_shrase.begin(), m_shrase.end());
					sh.word = word;
					sh.endstatu = last_statu;
					f_settype(&sh);

					m_ShraseList.push_back(sh);

					m_statu = 0;
					m_shrase.clear();
					continue;
			}

			////����
			if (m_statu < 0)
			{
				if (last_statu == 0)
				{
					m_shrase.push_back(c);
					rf.read(&c, 1);
				}
				f_saveError(m_statu);
				continue;
			}



			if (c == '\n')
			{
				m_line++;
			}

			if (c != ' '&&c!='\n')
			{
				m_shrase.push_back(c);
				rf.read(&c, 1);
			}
			else
			{
				rf.read(&c, 1);
			}


		}



		if (m_shrase.size() != 0)
		{
			f_saveError(-2);
		}

		for (int i = 0; i <m_ShraseList.size(); i++)
		{
			f_settype(&m_ShraseList.at(i));
		}
		for (int i = 0; i <m_ErroList.size(); i++)
		{
			f_erromessage(&m_ErroList.at(i));
		}

		OutShrase();
		OutError();
		OutCode(&rf);
		SaveFile(output);
	}
	rf.close();
	wf.close();
}

int CMyLex::ST(int st, char in)
{
	switch (st)
	{
	case 0:return ST_00(in);
	case 1:return ST_01(in);
	case 2:return ST_02(in);
	case 3:return ST_03(in);
	case 4:return ST_04(in);
	case 5:return ST_05(in);
	case 6:return ST_06(in);
	case 7:return ST_07(in);
	case 8:return ST_08(in);
	case 9:return ST_09(in);
	case 10:return ST_10(in);
	case 11:return ST_11(in);
	}
	return -1;
}
int CMyLex::ST_00(char in)
{
	if (If_ABC(in)) return 1;//ǰ��״̬1   ID
	if (If_NUB(in) && in != '0') return 2;//ǰ��״̬2   NUB
	if (in == '0' ) return 3;//ǰ��״̬3   NUB
	if (in == '/') return 4;//ǰ��״̬4   /
	if (If_Sings(in)) return 8;//�����Ž���
	if (If_FrontSings(in)) return 9;//ǰ��״̬7   ǰ����
	if (in == '!') return 11;//ǰ��״̬7   ǰ����
	if (in == ' ' || in == '\n') return 0;
	return -1;
}
int CMyLex::ST_01(char in)
{
	if (If_NUB(in) || If_ABC(in)) return 1;
	return 0;
}
int CMyLex::ST_02(char in)
{
	if (If_NUB(in)) return 2;
	return 0;
}
int CMyLex::ST_03(char in)
{
	return 0;
}
int CMyLex::ST_04(char in)
{
	if (in == '*') return 5;//ǰ��״̬5   /*
	return 0;
}
int CMyLex::ST_05(char in)
{
	if (in == '*') return 6;//ǰ��״̬6  /**
	return 5;

}
int CMyLex::ST_06(char in)
{
	if (in == '/') return 7;//ǰ��״̬7  /**/
	return 5;
}
int CMyLex::ST_07(char in)
{
	return 0;
}
int CMyLex::ST_08(char in)
{
	return 0;
}
int CMyLex::ST_09(char in)
{
	if (in == '=')return 10;
	return 0;
}
int CMyLex::ST_10(char in)
{
	return 0;
}
int CMyLex::ST_11(char in)
{
	if (in == '=')return 10;
	return -2;
}



void CMyLex::init()
{
	m_statu = 0;
	m_line = 1;

	//���ر������б�
	m_keywords.push_back("if");
	m_keywords.push_back("else");
	m_keywords.push_back("for");
	m_keywords.push_back("while");
	m_keywords.push_back("do");
	m_keywords.push_back("int");
	m_keywords.push_back("write");
	m_keywords.push_back("read");



}


bool CMyLex::If_ABC(char in)
{
	if ((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z'))
	{
		return true;
	}
	return false;
}
bool CMyLex::If_NUB(char in)
{
	if (in >= '0' && in <= '9' )
	{
		return true;
	}
	return false;
}
bool CMyLex::If_Sings(char in)
{
	char m_sgins[] = { '(', ')', '{', '}', ';', '+', '-', '*' };
	for (int i = 0; i < 8; i++)
	{
		if (in == m_sgins[i]) {
			return true;
		}
	}
	return false;
}
bool CMyLex::If_FrontSings(char in)
{
	char m_sgins[] = { '=', '<', '>' };
	for (int i = 0; i < 3; i++)
	{
		if (in == m_sgins[i]) {
			return true;
		}
	}
	return false;
}




void CMyLex::f_settype(LexShrase* Shrase)
{
	string a="";
	string b = "";
	switch (Shrase->endstatu)
	{
	case 1:a = "��־��"; Shrase->LexType ="ID"; break;
	case 2:a = "�޷�������"; Shrase->LexType="NUM"; break;
	case 3:a = "�޷�������"; Shrase->LexType = "NUM"; break;
	case 7:a = "ע��"; Shrase->LexType = "NOTES"; break;
	case 8:a = "�ֽ��"; Shrase->LexType = Shrase->word; break;
	case 9:a = "�����"; Shrase->LexType = Shrase->word; break;
	case 10:a = "�����"; Shrase->LexType = Shrase->word; break;
	}

	if (Shrase->endstatu == 1)
	{
		int l = m_keywords.size();
		for (int i = 0; i < l; i++)
		{
			if (m_keywords.at(i)==Shrase->word)
			{
				a = "������";
				Shrase->LexType = Shrase->word;
				break;
			}
		}
	}
	Shrase->type = a;

}

bool CMyLex::f_ShraseComType(string type, vector<char>v)
{
	bool iftrue = true;
	if (type.size() == v.size())
	{
		int l = v.size();
		for (int i = 0; i < l; i++)
		{
			if (type.at(i) != v.at(i))
			{
				iftrue = false;
				break;
			}
		}
	}
	else
	{
		iftrue = false;
	}
	return iftrue;
}

void CMyLex::f_saveError(int laststatu)
{
	LexErro er;
	er.line = m_line;
	string word;
	word.insert(word.begin(), m_shrase.begin(), m_shrase.end());
	er.word = word;
	er.endstatu = laststatu;
	m_ErroList.push_back(er);
	m_statu = 0;
	m_shrase.clear();
}

void CMyLex::f_erromessage(LexErro* Erro)
{
	string a = "";

	switch (Erro->endstatu)
	{
	case -2:a = "�ṹ��ȫ"; break;
	default:a = "�Ƿ��ַ�"; break;
	}

	Erro->message = a;
}


void CMyLex::OutShrase()
{
	cout << "=====================SHRASE=====================" << endl;
	cout << "|����|    <==> |�ʷ�����| <==>  |����|" << endl;
	for (int i = 0; i <m_ShraseList.size(); i++)
	{
		cout << m_ShraseList.at(i).type;

		int l = 10 - m_ShraseList.at(i).type.size();
		for (int j = 0; j < l; j++) cout << " ";

		cout << "  <==>  " << m_ShraseList.at(i).LexType;

		 l = 10 - m_ShraseList.at(i).LexType.size();
		for (int j = 0; j < l; j++) cout << " ";



		cout << "  <==>  " << m_ShraseList.at(i).word<<endl;
	}
}

void CMyLex::OutError()
{
	cout << "=====================ERROR======================" << endl;
	cout << "|����|      <==>  |����|  <==> |����|" << endl;
	for (int i = 0; i <m_ErroList.size(); i++)
	{
		cout << m_ErroList.at(i).message;
		int l = 10 - m_ErroList.at(i).message.size();
		for (int j = 0; j < l; j++) cout << " ";


		cout << "  <==>  " << m_ErroList.at(i).line;
		int m = m_ErroList.at(i).line;
		int x;
		for (x = 1; m > 10; x++) m = m / 10;
		l = 8 - x;
		for (int j = 0; j < l; j++) cout << " ";
		cout << "<==>  " << m_ErroList.at(i).word << endl;
	}
}
void CMyLex::OutCode(ifstream* rf)
{
	cout << "=====================ԭ��=======================" << endl;
	rf->clear();
	rf->seekg(0);
	while (!rf->eof())
	{
		char c = ' ';
		rf->read(&c, 1);
		cout << c;
	}

	cout << endl;
	cout << "=====================ԭ��=======================" << endl;
}
void CMyLex::SaveFile(char* output)
{
	OutShrase(output);
	OutError(output);
}
void CMyLex::OutShrase(char* output)
{
	ofstream wf;
	wf.open(output, ios_base::app);
	wf << "=====================SHRASE=====================" << endl;
	wf << "|����|    <==> |�ʷ�����| <==>  |����|" << endl;
	for (int i = 0; i <m_ShraseList.size(); i++)
	{
		wf << m_ShraseList.at(i).type;

		int l = 10 - m_ShraseList.at(i).type.size();
		for (int j = 0; j < l; j++) wf << " ";

		wf << "  <==>  " << m_ShraseList.at(i).LexType;

		 l = 10 - m_ShraseList.at(i).LexType.size();
		for (int j = 0; j < l; j++) wf << " ";

		wf << "  <==>  " << m_ShraseList.at(i).word << endl;
	}
	wf.close();
}
void CMyLex::OutError(char* output)
{
	ofstream wf;
	wf.open(output, ios_base::app);
	wf << "=====================ERROR======================" << endl;
	wf << "|����|      <==>  |����|  <==> |����|" << endl;
	for (int i = 0; i <m_ErroList.size(); i++)
	{
		wf << m_ErroList.at(i).message;
		int l = 10 - m_ErroList.at(i).message.size();
		for (int j = 0; j < l; j++) wf << " ";


		wf << "  <==>  " << m_ErroList.at(i).line;

		int m = m_ErroList.at(i).line;
		int x;
		for (x = 1; m > 10; x++) m = m / 10;

		l = 8 - x;
		for (int j = 0; j < l; j++) wf << " ";

		wf << "<==>  " << m_ErroList.at(i).word << endl;
	}
	wf.close();
}

vector<LexShrase> CMyLex::getShraseList()
{
	return m_ShraseList;
}