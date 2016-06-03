//�ʷ���������
#include<stdio.h>
#include<ctype.h>
#include<string.h>
//���涨�屣���ֱ�Ϊ�򻯳���ʹ���ַ�ָ�����鱣�����б����� //��������ӱ�����,�ɼ�-��ӣ����޸ı�������ĿkeywordSum 
#define keywordSum 8
char * keyword[keywordSum]={"if","else","for","while","do","int","read","write"};
//���涨�崿���ֽ��,����Ҫ�����
char singleword[50] = "+_*(){},;";
//���涨��˫�ֽ�������ַ�
char doubleword[10] ="><=!";
extern char Scanin [300], Scanout [300];
//���ڽ�����������ļ�������tesr_main.c�ж���
extern FILE * fin, * fout;	//����ָ����������ļ���ָ�룬��main.c���ж���
int TESTscan()	//�ʷ���������
{
	char ch,token[40];	//chΪÿ�ζ�����ַ���token���ڱ���ʶ����ĵ���
	int es=0,j,n;	    //es������룬0��û�д���
	//j,nΪ��ʱ������������ϵ���ʱ���±�� 
	printf("������Դ�����ļ���������·��)��"); 
	scanf ("%s",Scanin);
    printf("������ʷ���������ļ���������·��)��"); 
	scanf("%s",Scanout);
	if ((fin = fopen(Scanin, "r")) == NULL)	//�ж������ļ����Ƿ���ȷ
	{
		printf("\n�򿪴ʷ����������ļ�����\n");
		return(1);                          	//�����ļ������ش������1
	}
	if ((fout=fopen (Scanout, "w"))==NULL)	    //�ж�����ļ����Ƿ���ȷ
	{
		printf ("\n�����ʷ���������ļ����� \n");
		return(2);	                            //����ļ������ش������2
		
	}
	ch=getc (fin); 
	while(ch!=EOF)
	{
		while (ch== ' '|| ch== '\n'|| ch== '\t') ch=getc (fin);
		if (ch == EOF) break;
		if(isalpha(ch)) 	                 //�������ĸ�������ʶ������
		{
			token[0]=ch; j=1;
			ch=getc(fin);
			while (isalnum(ch))	            //�������ĸ��������ϱ�ʶ�� 
				                            //����������ʶ����Ͻ���
			{
				token [j++] = ch;	        //��ϵı�ʶ���ִ���token��
			    ch = getc(fin);            	//����һ���ַ�
			}

			token [j]='\0';	                //��ʶ����Ͻ���
			//�鱣����
			n=0;
			while ((n< keywordSum) && strcmp (token, keyword[n])) n++ ;
			if (n>= keywordSum)	                 //���Ǳ����֣������ʶ�� 
				fprintf(fout,"%s\t%s\n","ID",token); //�����ʶ������
			else		                             //�Ǳ����֣����������
				fprintf (fout, "%s\t%s\n",token, token) ; //��������ַ���

		}else if (isdigit (ch))                  	//���ִ��� 
		{ 
			token[0] = ch; j = 1;
			ch=getc(fin);	                        //����һ���ַ� 
			while (isdigit(ch))		                //������������������;���������������Ͻ���
			{
				token[j++] = ch;                    //�������������token�� 
				ch = getc(fin);	                    //����һ���ַ�
			}
			token[j] = '\0';	                    //������Ͻ���
			fprintf(fout,"%s\t%s\n","NUM",token); 	//�����������

		}else if (strchr (singleword, ch)>0)	   //���ֽ������
		{
			token[0] = ch; token[1]= '\0';
			ch=getc(fin);	//����һ�������Ա�ʶ����һ������
			fprintf (fout, "%s\t%s\n", token, token); //������ֽ������ 
		}else if (strchr (doubleword, ch) >0)	//˫�ֽ������
		{
			token [0] = ch;
			ch=getc(fin);  //����һ���ַ��ж��Ƿ�Ϊ˫�ֽ��
			if (ch=='=')	//�����=,���˫�ֽ��
			{
				token [1] = ch;token [2]= '\0';	//���˫�ֽ������ 
				ch=getc(fin); 	//����һ�������Ա�ʶ����һ������ 
			} else	//����=��Ϊ���ֽ�� 
				token[1] = '\0';
			fprintf (fout, "%s\t%s\n",token,token); //�������˫�ֽ������ 
		}else if (ch== '/' )	//ע�ʹ���
		{
			ch=getc (fin);	//����һ���ַ�
			if(ch=='*')	    //�����* ,��ʼ����ע��
			{
				char chl;
				chl=getc (fin);	//����һ���ַ�
				do
				{  ch=chl;chl=getc (fin);} //ɾ��ע��
				while ((ch != '*'||chl!='/') && chl!= EOF);
				//ֱ������ע�ͽ�����* /���ļ�β 
				ch=getc(fin);	//����һ�������Ա�ʶ����һ������ 
			
			}else	//����*�����ֽ��
			{
				token[0]='/'; token[1]= '\0';
				fprintf (fout, "%s\t%s\n",token, token); //������ֽ��
			}
		}else	//������
			{
				token[0] = ch;token[1]= '\0';
				ch=getc (fin);		//����һ�������Ա�ʶ����һ������ 
				es=3;	//���ô������ 
				fprintf (fout, "%s\t%s\n","ERROR",token);	//����������
			}
		}
		fclose (fin);	//�ر���������ļ�
		fclose(fout);
		return (es);	//����������
}