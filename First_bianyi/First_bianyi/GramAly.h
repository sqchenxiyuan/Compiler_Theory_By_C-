#pragma once
class CGramAly
{
public:
	CGramAly(vector<LexShrase> Shrases);
	~CGramAly();
	void Analysis();

private:

	int m_pos=0;//��ǰ��������λ��
	vector<string> m_Shrase;

	vector<string> FR_E;// = { "if", "while", "for", "wirte", "read", "{", "(", "ID", "NUM" };
	vector<string> FR_L;//  = { "(", "ID", "NUM" };
	vector<string> FR_M;//  = { "(", "ID", "NUM" };


	vector<string> FL_B1;//  = { "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", "}", "#" };
	vector<string> FL_D1;//  = { "}", "#" };
	vector<string> FL_N1;// = { ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FL_O1;// = { "+", "-", ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FL_P1;//  = { ";", ")" };


	void reset();//��ʼ��
	void nextchar();//��һ������

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

	bool infrfl(string shr, vector<string>fl);//�ж��Ƿ���Follow����
	void error();

};

