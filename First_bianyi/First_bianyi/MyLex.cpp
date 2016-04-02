#include "stdafx.h"
#include "MyLex.h"

CMyLex::CMyLex()
{
	init();
}


CMyLex::~CMyLex()
{
}

void CMyLex::Analysis(char *input, char* output)
{
	ifstream rf;
	rf.open("src/test.txt");


	if (!rf)  //��ȡtxt�ļ�
	{
		printf("��ȡ�ļ�ʧ�� \n ");
	}
	else
	{
		m_shrase;
		m_shrase.clear();
		cout << "��ȡ�ɹ�" << endl;
		while (!rf.eof())
		{
			char c=' ';
			rf.read(&c, 1);
			int ms = m_statu;
			m_statu = ST(m_statu, c);
			//cout << c <<"--"<<ms<<"--"<<m_statu<< endl;
			if (m_statu != ms&&m_statu==0||ms==0)//��ʼ״̬Ϊ0 ����  ��Ϊ0  �������  
			{
				if (m_shrase.size() != 0)
				{
					LexShrase sh;
					sh.line = m_line;
					sh.word = f_vectorcopy(m_shrase);
					sh.endstatu = ms;
					m_ShraseList.push_back(sh);
					m_statu = 0;
					//f_outtype(ms);
					f_outshrase();
					m_shrase.clear();
				}
			}
			if (c == '\n')
			{
				//c = ' ';
				m_line++;
			}
			if (c != ' '&&c!='\n')
			{
				m_shrase.push_back(c);
				if (m_statu == 0)
				{
					m_statu = ST(m_statu, c);
					if (m_statu == -1)
					{
						LexErro er;
						er.line = m_line;
						er.word = f_vectorcopy(m_shrase);
						m_ErroList.push_back(er);
						m_statu = 0;
						m_shrase.clear();
						continue;
					}
				}
				else if (m_statu == -1)
				{
					LexErro er;
					er.line = m_line;
					er.word = f_vectorcopy(m_shrase);
					m_ErroList.push_back(er);
					m_statu = 0;
					m_shrase.clear();
					continue;
				}
			}
		}
		if (m_shrase.size() != 0)
		{
			LexErro er;
			er.line = m_line;
			er.word = f_vectorcopy(m_shrase);
			m_ErroList.push_back(er);
			m_statu = 0;
			m_shrase.clear();
		}





		cout << "=====================share=====================" << endl;
		for (int i = 0; i <m_ShraseList.size(); i++)
		{
			f_settype(&m_ShraseList.at(i));
			cout << m_ShraseList.at(i).type << "  <==>  " << m_ShraseList.at(i).endstatu << "  <==>  ";
			f_outword(&m_ShraseList.at(i).word);
			cout << endl;
		}
		cout << "=====================erro=====================" << endl;
		for (int i = 0; i <m_ErroList.size(); i++)
		{
			f_outword(&m_ErroList.at(i).word);
			cout << "<==>" << m_ErroList.at(i).line << endl;
		}

		cout << "=====================ԭ��====================="<<endl;
		rf.clear();
		rf.seekg(0);
		while (!rf.eof())
		{
			char c = ' ';
			rf.read(&c, 1);
			cout << c;
		}
	}
	cout << m_line;
	rf.close();
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
	return -1;
}



void CMyLex::init()
{
	m_statu = 0;
	m_line = 1;
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
		//cout << m_sgins[i] << "--------" << in << endl;
		if (in == m_sgins[i]) {
			//cout << "aaaaaaa";
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
		//cout << m_sgins[i] << "--------" << in << endl;
		if (in == m_sgins[i]) {
			//cout << "aaaaaaa";
			return true;
		}
	}
	return false;
}



void CMyLex::f_outshrase()
{
	for (int i = 0; i < m_shrase.size();)
	{
		cout << m_shrase.at(i);
		i++;
		if (i == m_shrase.size())
		{
			cout << endl;
		}
	}
}

void CMyLex::f_settype(LexShrase* Shrase)
{
	string a="";
	switch (Shrase->endstatu)
	{
	case 1:a = "��־��"; break;
	case 2:a = "�޷�������"; break;
	case 3:a = "�޷�������"; break;
	case 7:a = "ע��"; break;
	case 8:a = "���ַ�"; break;
	case 9:a = "���ַ�"; break;
	case 10:a = "˫�ַ�"; break;
	}

	if (Shrase->endstatu == 1)
	{
		int l = m_keywords.size();
		for (int i = 0; i < l; i++)
		{
			if (f_ShraseComType(m_keywords.at(i), Shrase->word))
			{
				a = m_keywords.at(i);
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





vector<char> CMyLex::f_vectorcopy(vector<char>v)
{
	vector<char> co(v);
	return co;
}

void CMyLex::f_outword(vector<char>* word)
{
	int l = word->size();
	for (int i = 0; i < l; i++)
	{
		cout << word->at(i);
	}
}