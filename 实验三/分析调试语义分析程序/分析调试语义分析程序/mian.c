//������
#include< stdio.h>
#include< ctype.h> 
extern int TESTmachine(); 
char Scanin[300], Scanout[300],Codeout[300];
FILE * fin, *fout;
extern int TESTscan();
extern int TESTparse();

void main ()
{

	int es = 0;
	es = TESTscan();
	if (es > 0){
		printf("�ʷ������д�����ֹͣ��");
	}
	if (es == 0){
		es = TESTparse();
		if (es == 0){
			es=TESTmachine();	//���ó����ģ����
		}
		else{
			printf("�﷨��������!\n");
		}
	}
	scanf("%d", es);
	scanf("%d", es);
	
}