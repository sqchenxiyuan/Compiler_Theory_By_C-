//�﷨������������������ɳ��� 
#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#define maxvartablep 500 	//���V���ű������
int TESTparse(); 
int program();
int statement();	
int expression_stat();
int expression();
int bool_expr();	
int additive_expr();
int term();	
int factor();	
int if_stat();	
int while_stat();
int for_stat();	
int write_stat();
int read_stat();	
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
int name_def(char *name);
char token[20], token1[40];          //token���浥�ʷ���,token1���浥��ֵ  
extern char Scanout[300],Codeout[300];//����ʷ���������ļ���
FILE *fp, *fout;                     //����ָ����������ļ���ָ�� 
 
struct{                               //������ű�ṹ
	char name[8]; 
	int address;
	int initialize;
}vartable[maxvartablep];              //�ķ��ű��������maxvarltablep����¼           

int vartablep=0, labelp= 0, datap= 0;

//������ű���@ nameһ def n,t�ĳ������£� 
int name_def(char * name)
{
   int i,es=0;
   if(vartablep>=maxvartablep) return(21); 
   for(i=vartablep-1;i>=0;i--)              //����ű�
   {
	   if(strcmp(vartable[i].name,name)==0) 
	   {
		 es=22;                                    //22��ʾ�����ظ�����
		 break;
      }
    }
   if(es>0) return(es);
   strcpy(vartable[vartablep].name,name); 
   vartable[vartablep].address=datap;
   vartable[vartablep].initialize = 0;
   datap++;                                     //����һ����Ԫ,������ָ���1
   vartablep++; 
   return(es);
}

//��ѯ���ű��ص�ַ
int lookup(char * name, int * paddress) 
{
   int i,es=0;
   for(i=0;i<vartablep;i++)
   {
     if(strcmp(vartable[i].name,name)==0)
      {
        *paddress=vartable[i].address;
		if (vartable[i].initialize == 1) es = 0;
		else es = 24;//var dont initilize 
		vartable[i].initialize = 1;
        return(es);
       }
     }
   es=23;                                       //����û������
   return(es);
}

//�﷨������������������ɳ��� 
int TESTparse()
{
   int es=0;
   if((fp=fopen(Scanout,"r"))== NULL)
   { 
      printf("\n��%s����\n",Scanout);
      es=10;
      return(es);
    }

   printf("������Ŀ���ļ���(����·��):");
   scanf("%s",Codeout); 
   if((fout=fopen(Codeout,"w"))==NULL)
   {     
     printf("\n ����%s ���� \n",Codeout);
     es=10;
     return(es);
    }
   if(es==0) es=program();
   printf("==�﷨������������������ɳ�����==\n"); 
   switch(es)
  {
    case 0: printf("�﷨����������ɹ��������������ɴ���!\n");break;
    case 10:printf("���ļ� %s ʧ��\n",Scanout);break;
    case 1: printf("ȱ�� {! \n") ;break;
    case 2: printf("ȱ�� }! \n") ;break;
    case 3: printf("ȱ�ٱ�ʶ��!");break;
    case 4: printf("�ٷֺ�! \n") ;break;
    case 5: printf("ȱ��(��\n");break;
    case 6: printf("ȱ�� )��\n") ;break;
    case 7: printf("ȱ�ٲ�����!\n");break;
    case 21:printf("���ű������\n");break;
    case 22:printf("�����ظ����壡\n");break;
    case 23:printf("����δ����!\n");break;
	case 24:printf("����δ��ʼ��!\n"); break;

   }

   fclose(fp);
   fclose(fout);
   return(es);
}

//program::= {<declaration_list><statement list> }.
int program()
{
  int es=0,i;
  fscanf(fp,"%s %s\n",token,token1);
  printf("%s %s\n",token,token1);
  if(strcmp(token,"{"))	                             //�ж��Ƿ�"{"
   {   
     es=1;
     return(es);
    }
   fscanf(fp,"%s %s\n",&token,&token1);
   printf("%s %s\n",token,token1); 
   es=declaration_list(); 
   if(es>0) return(es); 
 /*  printf("\t���ű�\n");
   printf("\t����\t��ַ\n");
   for(i=0;i<vartablep;i++)
	   printf("\t%s\t%d\n",vartable[i].name,vartable[i].address);*/
   es= statement_list();
   if(es>0) return(es);
   if(strcmp(token,"}")) //�ж��Ƿ�"}"
   {
       es=2;
      return(es);
    }
   fprintf(fout,"STOP\n");	            //����ָֹͣ��
   return(es);
}

//<declaration_list> :: = < declaration_list>< decIaratibn_stat>y| < declaration_stat> //3CJ^<declaration_list> ::* {<declaration_stat> } 
int declaration_list()
 {
    int es=0;
    while(strcmp(token,"int")== 0)
    {
       es= declaration_stat();
       if(es>0) return(es);
     }
    return(es);
}

//<declaration_stat> \ vartabiep,datap,codep~^int IDf n @ name- def + n,t :
 int declaration_stat()
{
	 int es=0;
	 fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n",token,token1);
	 if(strcmp(token,"ID")) return(es=3);	     //���Ǳ�ʶ��
	 es=name_def(token1);	                     //������ű�
	 if(es>0) return(es);
	 fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n", token,token1);
	 if(strcmp(token,";") ) return(es=4);
	 fscanf(fp,"%s %s\n", &token, &token1) ;printf("%s %s\n",token,token1);
	 return(es);
}

//< statement_list> :: = <statement_list><statement> | <statement>
//�ĳ�<statement_list> ::= {<statement> } 
int statement_list()
{
  int es=0;
  while(strcmp(token,"}"))
  {
        es=statement();
        if(es>0) return(es);
   }
  return(es);
}

//<statement> ::*<if_stat> |<while_stat> |<for_stat>
//  	        |<compound_stat> |<expression_stat> ^
int statement()
{
  int es=0;
  if(es==0 && strcmp(token,"if")== 0)       es=if_stat();//<if���>
  else if(es==0 && strcmp(token,"while")==0) es=while_stat();//<while ���> 
  else if (es == 0 && strcmp(token, "for") == 0)   es = for_stat();//<for���>
  //���ڴ˴���ӹ�do������
  else if (es == 0 && strcmp(token, "read") == 0)  es = read_stat();//<read ���>
  else if (es == 0 && strcmp(token, "write") == 0) es = write_stat();//<write @^> 
  else if (es == 0 && strcmp(token, "{") == 0)es = compound_stat();//<�������> 
  else if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0))
	es=expression_stat();	        //<���ʽ���>
  return(es);
}

//< if stat> :: = if(< expr> ) < statement>[else< statement> ]
/*
if(<expression> ) @ BRFfiaben < statement> @ BR+ iabei2 @ SETlabeljiaseii[else<statement>] @ SETlabel|iabei2
���ж������ŵĺ�������
0BRFtiabeu,:��� BRF label1.
 
BRf iabei2 ����� BR label2 0SETlabel|iabeii �����ñ�� label1 0SETlabel|iabei2 �����ñ�� label2
*/
int if_stat() 
{
  int es=0,label1,label2;                      //if
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token, token1);
  if(strcmp(token,"(")) return(es=5);        //��������
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token,token1);
  es=expression();
  if(es> 0) return(es);
  if(strcmp(token,")")) return(es=6);      //�������� 
  label1= labelp++;                            //��label1��ס����Ϊ��ʱҪת��ı��
  fprintf(fout,"BRF LABEL%d\n",label1);//�����ת��ָ��
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n", token, token1);
  es=statement();
  if(es>0) return(es);
  label2= labelp++;                            //��label2��סҪת��ĻӺ�                  
  fprintf(fout,"BR LABEL%d\n",label2);      //���������ת��ָ��
  fprintf(fout,"LABEL%d: \n", label1);       //����label1��ס�ı��  
  if(strcmp(token,"else")==0)               //else���ִ���
   {
       fscanf(fp,"%s %s\n",&token, &token1);
       printf("%s %s\n",token,token1);
       es= statement(); 
       if(es>0) return(es);
   }

   
  fprintf(fout,"LABEL%d:\n",label2);                    //����1մ612��ס�ı��
  return(es);

}

//<while_stat> :: = while(<expr> ) < statement>
//<while_stat> :: = while @ SETlabeltxaben(<expression>) @ BRFf 13&6]:2 //	<statement>0BRoabeu0SETlabel4iabei2
//�����������£� //0SETlabeltiabeii �����ñ�� label1 //0BRFt !abe!2 | ��� BRF label2 //0BR* !aben :��� BR label1 .
//@ SET1 abe 11 iabei2 �����ñ�� label2 
int while_stat()
{ 
  int es=0,label1,label2; label1=labelp++;
  fprintf(fout,"LABEL%d:\n",label1) ;	//����1��ذ611���
  fscanf(fp,"%s %s\n",&token, &token1); printf("%s %s\n",token,token1);
  if(strcmp(token,"(")) return(es=5);	//��������
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token,token1);
  es=expression();
  if(es>0) return(es) ;
  if(strcmp(token,")")) return(es= 6);	//��������
  label2= labelp++;
  fprintf(fout,"BRF LABEL%d\n",label2); //�����ת��ָ��
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token,token1);
  es= statement();
  if(es>0) return(es);
  fprintf(fout,"BR LABEL%d\n",label1);	//���������ת��ָ��
  fprintf(fout,"LABEL%d:\n",label2);	    //����1��ذ612���.
  return(es);

} 

//< for_stat> ::~ior(<expr> ,<expr> ,<expr>) < statement>
/*
< for_stat> :: = for(<expression> @ POP;
@ SETlabel \ iabeii < expression> @ BRF|iabei2 @ BR+ iabei3 :
@ SETlabel 1 iabei4< expression> @ POP0 BR* iabeii)
@ SETlabel : ^13 <iS^I > 0 BR \ label46SETlabel|iabei2
�������ͣ� 1.	0SETlabeluabeii �����ñ�� label1
0BRFf iabei2 ����� BRF label2 3 . @ BR| iabei3 ����� BR label3
0SETlabeluabei4 �����ñ�� label4
0BRfiabeu :��� BR label1
@36713&61ح131^13:���ñ��13^13
@ BRf !abei4 ����� BR lsfcel4
0 SETlabel : iabei2 �����ñ�� lab.el2
*/
int for_stat()
{
	int es=0,label1,label2,label3,label4; 
	fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1);
	if(strcmp(token,"(")) return(es=5);	//��������
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token, token1);
	es=expression();
	if(es>0) return(es);
	fprintf(fout,"POP\n");                 //�����ջָ��
	if(strcmp(token,";")) return(es*=4);//�ٷֺ�
	label1=labelp++ ;                      
	fprintf(fout,"LABEL%d:\n",label1);       //���� label1���
	fscanf(fp,"%s %s\n",&token,&token1);    
	printf("%s %s\n",token,token1);
	es=expression();
	if(es>0) return(es); 
	label2=labelp++;
	fprintf(fout,"BRF LABEL%d\n",label2); //���������ת��ָ��  
	label3=labelp++;
	fprintf(fout,"BR LABEL%d\n",label3);   //���������ת��ָ��
	if(strcmp(token,";"))  return(es=4);         //�ٷֺ�
	label4=labelp++;
	fprintf(fout,"LABEL%d:\n", label4);         //����label4���
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if(es>0) return(es) ;
	fprintf(fout,"POP\n");                //�������ָ��        
	fprintf(fout,"BR LABEL%d\n", label1);     //���������ת��ָ��
	if(strcmp(token,")")) return(es= 6);        //��������
	fprintf(fout,"LABEL%d:\n",label3);          //����label3���
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement();
	if(es>0) return(es);
	fprintf(fout,"BR LABEL%d\n",label4);     //���������ת��ָ��
	fprintf(fout,"LABEL%d:\n", label2);       //����label2���
	return(es);
	
}

//<write_stat> ::-write<expressipn> ;- //<write_stat> :: = write<expression>0OUT;
//�������ͣ�
//0OUT:��� OUT
int write_stat() 
{
	int es=0;
	fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1);
	es=expression(); 
	if(es>0) return(es);
	if(strcmp(token,";")) return(es=4);	//�ٷֺ�
    fprintf(fout,"OUT\n") ;	            //���0utָ��
	fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1) ; 
	return(es);
}

//< read_stat> ::==read ID;
//<read_stat> :: = read IDfnLOOK|nfd6lN0 STO|d0POP; //�������ͣ�
//@100��11^:����ű�?����������ַd;��û��,�����δ���� //0IN:��� IN
//@3|11"�����ָ�����31��d
int read_stat()
{
	int es= 0,address;
	fscanf(fp,"%s %s\n",&token, &token1); 
	printf("%s %s\n",token,token1); 
	if(strcmp(token,"ID")) return(es=3);    //�ٱ�ʶ��
	es = lookup(token1, &address);
	if (es == 24) es = 0;
	if(es > 0) return(es);		
	fprintf(fout,"IN \n");               //����ָ��
	fprintf(fout,"STO %d\n",address);    //���STOָ��
	fprintf(fout,"POP\n");
    fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1);
	if(strcmp(token,";")) return(es=4);    //�ٷֺ�
	fscanf(fp,"%s %s\n",&token, &token1); 
	printf("%s%s\n",token,token1); 
	return(es);
}

 
//<compound_stat> ::= {<statement_list> } 
int compound_stat()
{
	int es = 0;
	fscanf ( fp,"%s %s\n", &token, &token1); //������亯��
	printf("%s %s\n", token, token1);
	es = statement_list();
	if(es>0) return es;
	if (strcmp(token, "}") == 0){			//�� } ��ƥ��
		fscanf(fp, "%s %s\n", &token, &token1);
		printf("%s %s\n", token, token1);
	}
	else{
		es = 2;
		return(es);
	}
	return es;
}

//<expression_stat> i :==<expression> @ POP; |; 
int expression_stat()
{
	int es=0;
	if(strcmp(token,";")== 0)
	{
		fscanf(fp,"%s%s\n",&token,&token1); 
		printf("%s%s\n",token,token1); 
		return(es);
	}
	es=expression(); 
	if(es>0) return(es) ; 
	fprintf(fout,"POP\n");       //���POPָ��
	if(strcmp(token,";") == 0)    
	{
		fscanf(fp,"%s %s\n",&token, &token1);
		printf("%s %s\n",token,token1); 
		return(es);
	}else
	{
		es=4;
		return(es);                //�ٷֺ�

		}

}

//<expression> :: = ID^n0 LOOKj nfd6 ASSIGN=<boo:l_expr>@ STO{d0 POP |<bool_expr> 
int expression()
{
	int es=0,fileadd;
	char token2[20],token3[40];
	if(strcmp(token,"ID")==0)
	{
		fileadd=ftell(fp);	//@ASSIGN��ס��ǰ�ļ�λ��
		fscanf(fp,"%s %s\n", &token2, &token3); 
		fseek(fp, fileadd, 0);
		if(strcmp(token2,"=") == 0)
		{
			int address;
			es=lookup(token1,&address);
			if (es == 24) es = 0; //var  initilize complete
			if (es>0)  return(es);
			fscanf(fp,"%s %s\n", &token, &token1);
			printf("%s %s\n",token,token1); 
			fscanf(fp, "%s %s\n", &token, &token1);
			printf("%s %s\n", token, token1);
			es=bool_expr(); 
			if(es>0)  return(es);
			fprintf(fout,"STO %d\n",address);
			
		}else
		{
			es=bool_expr(); 
			if(es> 0) return(es);
		}
	}else es=bool_expr();

	return(es);
} 

//<bool_expr> :: = <additive_expr>
//   	|<additive__expr>(> |<1>�� I<= l"=1 !=)<additivej_expr>
/*  <bool_expr> :: = < additive_expr>
| < additive_expr>> < additive_expr> 0 GT 
| < addi tive_exp r > < < additive_expr> @ LES 
| < Additive_expr>> = < additive_expr> @ GE 
| < additive_expr> < = < additive_expr> @ LE 
| < additive_expr> == <additive_expr> @ EQ 
| < additive_expr> ! = < additive_expr> 0 NOTEQ 
*/
int bool_expr()
{
	int es=0;
	es= additive_expr();
	if(es>0) return(es);
	if(strcmp(token,">")==0|| strcmp(token,">=")== 0 || strcmp(token,"<")== 0 || strcmp(token,"<=")==0 || strcmp(token,"==") == 0||strcmp(token,"!=")== 0)
	{
			char token2[20];
			strcpy(token2,token);	//���������
			fscanf(fp,"%s %s\n", &token, &token1);
			printf("%s%s\n",token,token1); 
			es = additive_expr();
			if (es > 0) return(es);
			if(strcmp(token2,">") ==0) fprintf(fout,"GT\n");
			if(strcmp(token2,">=")==0) fprintf(fout,"GE\n1");
			if(strcmp(token2,"<") ==0) fprintf(fout,"LES\n");
			if(strcmp(token2,"<=")==0) fprintf(fout,"LE\n");
			if(strcmp(token2,"==")==0) fprintf(fout,"EQ\n");
			if(strcmp(token2,"!=")==0) fprintf(fout,"NOTEQ\n");
		}
	
	return(es);
}

//< additive_expr> :: = <term> {(+ | - )<term> } 
//<additive_expr> ::*<term> {(+<term>0ADD|-<^>0SUB) }
int additive_expr()
{
	int es=0;
	es=term();
	if(es>0) return(es);
	while(strcmp(token,"+")== 0 || strcmp(token,"-") == 0)
	{
		char token2[20];
		strcpy(token2,token);
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=term();
		if(es>0) return(es);
		if(strcmp(token2,"+")== 0) fprintf(fout,"ADD\n");
		if(strcmp(token2,"-") == 0)fprintf(fout,"SUB\n");
	}
	
	return(es);
}

//< term> :: = < factor> {( * | /) < fagtor> }
//<term> :: = <factor> {( * <factor>6MULT ح /< factor>gDIV> } s
int term()
{
	int es=0;
	es=factor();
	if(es>0) return(es);
	while(strcmp(token,"*")== 0 ||strcmp(token,"/")== 0)
	{
		char token2[20];
		strcpy(token2, token);
		fscanf(fp,"%s %s\n",&token,&token1); 
		printf("%s %s\n",token,token1); 
		es= factor(); if(es>0) return(es);
		if(strcmp(token2,"*") == 0) fprintf(fout,"MULT\n");
		if(strcmp(token2,"/") == 0)fprintf(fout,"DIV\n");
	}
		
	return(es);
	
}

//< factor> ::=(<additive_expr> ) | ID,|NUM
//< factor> ::*=(<expression> ) j IDt n 0 LOOK| nf d*6 LOADfd INUMf i 0 LOADI\ �� 
int factor()
{
	int es=0;
	if(strcmp(token,"(") == 0)
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token, token1); 
		es=expression(); 
		if(es>0) return(es);
		if(strcmp(token,")")) return(es= 6);	//��������
		fscanf(fp,"%s %s\n",&token, & token1); printf("%s %s\n",token,token1);
	}else
	{ 
		if(strcmp(token,"ID")== 0)
		{
			int address;
			es=lookup(token1, &address) ;	//�˷��ű�,��ȡ������ַ
			if(es>0) return(es);	        //����û����
			fprintf(fout,"LOAD %d\n",address);
			fscanf(fp,"%s %s\n", &token, &token1);
			printf("%s %s\n",token,token1);
			return(es);
		}
		if(strcmp(token,"NUM")==0)
		{
			fprintf(fout,"LOADI %s\n",token1);
			fscanf(fp,"%s %s\n",&token,&token1); 
			printf("%s %s\n",token,token1);
			return(es);
		}else
		{
			es=7;	//ȱ�ٲ�����
			return(es);
		}
	}
		
	return(es);
}