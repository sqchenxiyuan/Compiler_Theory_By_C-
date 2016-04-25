#pragma once
struct LexErro
{
	int line = 0;
	int endstatu = 0;
	string message;
	string word;
};
struct LexShrase
{
	int line = 0;
	int endstatu = 0;
	string type;
	string LexType;
	string word;
};


class CMyLex
{
public:
	CMyLex();
	~CMyLex();
	void Analysis(char *input, char* output, bool cover);//�����ӿ�
private:

	void init();//��ʼ��

	int m_statu = 0;
	int m_line = 1;
	vector<string> m_keywords;//���ڻ���ؼ���

	int ST(int st, char in);//״̬���亯��
	int ST_00(char in);//״̬���� 
	int ST_01(char in);//ID
	int ST_02(char in);//NUB 
	int ST_03(char in);//NUB 0
	int ST_04(char in);//ע��1
	int ST_05(char in);//ע��2
	int ST_06(char in);//ע��3
	int ST_07(char in);//ע�ͽ���
	int ST_08(char in);//�����Ž���
	int ST_09(char in);//˫ǰ
	int ST_10(char in);//˫
	int ST_11(char in);//!

	vector<char> m_shrase;//���ﻺ��
	vector<LexShrase> m_ShraseList;//��ȷ���ﻺ��
	vector<LexErro> m_ErroList;//������Ϣ����

	//�ж�
	bool If_ABC(char in);
	bool If_NUB(char in);
	bool If_Sings(char in);
	bool If_FrontSings(char in);


	void f_settype(LexShrase* Shrase);//ͨ��������Ϣ�����ö�������
	void f_erromessage(LexErro* Erro);//ͨ��ERROR��Ϣ������ERROR������ʾ
	bool f_ShraseComType(string type, vector<char>v);//string��vector<char>�Ա�
	void f_saveError(int laststatu);//���������Ϣ




	//����̨���
	void OutShrase();//������ж��ﻺ��
	void OutError();//������д��󻺴�
	void OutCode(ifstream* rf);//���Դ�ļ�
	//�ļ�
	void SaveFile(char* output);//����ļ�
	void OutShrase(char* output);//���ļ������ȷ�Ĵ�
	void OutError(char* output);//���ļ��������
};

