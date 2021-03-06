#pragma once
struct GramCode
{
	string T1;//操作符
	int sum=-1;//地址 或者 数
};


struct GramError
{
	int type;
	int line;
	string input_f;
	string input;
	string input_l;
	string need;
};

struct GramShrase
{
	int line = -1;
	string type;
	string word;
};

struct GramSignal
{
	int num;
	int adress;
	string name;
};


class CGramAly
{
public:
	CGramAly(vector<LexShrase> Shrases);
	~CGramAly();
	void Analysis();

private:

	bool m_error = false;
	int m_pos=0;//当前读到单词位置
	vector<GramShrase> m_Shrase;
	vector<GramError> m_Erorr;

	vector<string> FR_D;//{ "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", ";" };
	vector<string> FR_D1;//{ "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", ";" };
	vector<string> FR_E;//{ "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", ";" };
	vector<string> FR_L;//{ "(", "ID", "NUM", ";" };
	vector<string> FR_M;//{ "(", "ID", "NUM" };
	vector<string> FR_N;//{ "(", "ID", "NUM" };
	vector<string> FR_O;//{ "(", "ID", "NUM" };
	vector<string> FR_P;//{ "(", "ID", "NUM" };
	vector<string> FR_Q;//{ "(", "ID", "NUM" };

	vector<string> FL_B;//{ "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", "}" };
	vector<string> FL_B1;//{ "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", "}" };
	vector<string> FL_D1;//{ "}" };
	vector<string> FL_N1;//{ ";", ")" };
	vector<string> FL_O1;//{ ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FL_P1;//{ "+", "-", ")", ";", ">", "<", ">=", "<=", "==", "!=" };


	void reset();//初始化
	void nextchar();//下一个单词
	void end();//结束输出
	void cmpshrase(string cmp);

	void ST_to(string st);
	void S_start();
	void A_programe();//<programe>
	void B_declaration_list();//<declaration_list>
	void B1_declaration_list();//<declaration_list_2>
	void C_declaration_stat();//<declaration_stat>
	void D_statement_list();//<statement_list>
	void D1_statement_list();//<statement_list>
	void E_statement();//<statement>
	void F_if_stat();//<if_stat>
	void G_while_stat();//<while_stat>
	void H_for_stat();//<for_stat>
	void I_write_stat();//<write_stat>
	void J_read_stat();//<read_stat>
	void K_commpound_stat();//<commpound_stat>
	void L_expression_stat();//<expression_stat>
	void M_expression();//<expression>
	void N_bool_expr();//<bool_expr>
	void N1_bool_expr();//<bool_expr>
	void O_additive_expr();//<additive_expr>
	void O1_additive_expr();//<additive_expr>
	void P_term();//<term>
	void P1_term();//<term>
	void Q_factor();//<factor>

	bool infrfl(string shr, vector<string>fl);//判断是否在Follow集中
	void error(int type,string need="");
	void outerror();

	//动作
	vector<GramCode> m_Code;
	vector<GramSignal> m_Signal;
	void wrcode(string code, int num = -1);
	void outcode();

	void addSignal(string ID);

};

