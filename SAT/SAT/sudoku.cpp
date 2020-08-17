#include "sat.h"

int bpnum = 0;
//���õ��������������ļ��а�����ʾ�����ڼ���ʾ0��1����������ʾΪ.
//���ڽ��6*6������Ϸ

/***************************
*�������ƣ�ReadBP
*�������ã������������̣����ɶ�Ԫ����
*����ֵ��fp
*����ֵ��BT*
**************************/
BT* ReadBP(void)
{
	printf("������Ҫ�������������\n");
	char name[20];
	FILE* fp;
	scanf("%s", name);

	//��ʼ����cnf�ļ�
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return  NULL;
		//�ļ���ʧ�ܣ�����NULL
	}

	BT* bt;
	bt = (BT*)malloc(sizeof(BT));//
	int i,j=0;
	char pre[2];
	bt->order = 6;
	for (i = 0; i <6; i++) {
		for (j=0; j<=6; j++) {
			fgets(pre, 2, fp);
			if (pre[0] == '0') { bt->sudo[i][j] = pre[0] - '0', bpnum++; }  //�����ʼֵ
			if (pre[0] == '1') { bt->sudo[i][j] = pre[0] - '0', bpnum++; }
			if (pre[0] == '.') bt->sudo[i][j] = -1;
		}
	}

	return bt;
}

/*********************
*��������:SUDOCNF
*��������:����������CNF�ļ�
*����ֵ:��
*����ֵ:fp
**********************/
FILE* SUDOCNF(void)
{
	FILE* fp;
	if ((fp = fopen("D:\SAT\sudo.cnf", "w")) == NULL)       //������ṹ�����������log.txt
	{
		printf("�ļ���ʧ�ܣ�\n");
		return  NULL;
		//�ļ���ʧ�ܣ�����ERROR
	}
	fprintf(fp, "p cnf 606 %d\n", bpnum+2285);
	return fp;
}


/*****************
*��������:CREATE_SIGCLA
*��������:�����������������ɵ��Ӿ�
*����ֵ:BTָ��,fp
*����ֵ:fp
********************/
FILE* CREAT_SIGCLA(BT* bt, FILE* fp)
{
	int i, j;
	int argu;
	for(i=0;i<6;i++)
		for (j = 0; j < 6; j++)
		{
			argu = 6 * i  + j+1; //ת���ɱ�Ԫ
			if (bt->sudo[i][j] == 0) fprintf(fp, "%d 0\n", -argu);
			if (bt->sudo[i][j] == 1) fprintf(fp, "%d 0\n", argu);
		}
	return fp;
}


/*********************
*��������: Limit1
*��������: ������������1�����Ӿ�
*����ֵ��fp
����ֵ��fp
**********************/
FILE* Limit1(FILE* fp)
{
	//�ȿ�����
	int i;
	int j;
	int argu;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 4; j++)
		{
			argu = 6 * i + j + 1;
			fprintf(fp, "%d %d %d 0\n", argu,argu+1,argu+2);
			fprintf(fp, "%d %d %d 0\n", -argu, -argu - 1, -argu - 2);
		}
	}

	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 4; i++)
		{
			argu = 6 * i + j + 1;
			fprintf(fp, "%d %d %d 0\n", argu, argu + 6, argu + 12);
			fprintf(fp, "%d %d %d 0\n", -argu, -argu - 6, -argu - 12);
		}
	}
	return fp;
}

/*********************
*�������ƣ�Limit2
*�������ã���������2�����Ӿ�
*����ֵ��fp
*���ֵ��fp
*********************/
FILE* Limit2(FILE* fp)
{
	int i, j;
	int argu;
	for (i = 0,j=0; i < 6; i++)
	{
		argu = 6 * i + j + 1;
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 3, argu + 4, argu + 5);   //12
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 3, -argu - 4, -argu - 5);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 2, argu + 4, argu + 5);   //13
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 2, -argu - 4, -argu - 5);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 2, argu + 3, argu + 5);    //14
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 2, -argu - 3, -argu - 5);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 2, argu + 3, argu + 4);   //15
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 2, -argu - 3, -argu - 4);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1, argu + 4, argu + 5);   //23
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 1, -argu - 4, -argu - 5);
			fprintf(fp, "%d %d %d %d 0\n",
				argu, argu + 1, argu + 3, argu + 5);   //24
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 1, -argu - 3, -argu - 5);
			fprintf(fp, "%d %d %d %d 0\n",
				argu, argu + 1, argu + 3, argu + 4);   //25
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 1, -argu - 3, -argu - 4);
			fprintf(fp, "%d %d %d %d 0\n",
				argu, argu + 1, argu + 2, argu + 5);   //34
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 1, -argu - 2, -argu - 5);
			fprintf(fp, "%d %d %d %d 0\n",
				argu, argu + 1, argu + 2, argu + 4);   //35
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 1, -argu - 2, -argu - 4);
			fprintf(fp, "%d %d %d %d 0\n",
				argu, argu + 1, argu + 2, argu + 3);   //45
			fprintf(fp, "%d %d %d %d 0\n",
				-argu, -argu - 1, -argu - 2, -argu - 3);
	
		fprintf(fp, "%d %d %d %d 0\n",
			argu+1, argu + 3, argu + 4, argu + 5);   //2
		fprintf(fp, "%d %d %d %d 0\n",
			-argu-1, -argu - 3, -argu - 4, -argu - 5);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1, argu + 2, argu + 4, argu + 5);   //3
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1, -argu - 2, -argu - 4, -argu - 5);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1, argu + 2, argu + 3, argu + 5);   //4
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1, -argu - 2, -argu - 3, -argu - 5);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1, argu + 2, argu + 3, argu + 4);   //5
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1, -argu - 2, -argu - 3, -argu - 4);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 2, argu + 3, argu + 4, argu + 5);   //01
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 2, -argu - 3, -argu - 4, -argu - 5);

	}

	for (i = 0, j = 0; j < 6; j++)
	{
		argu = 6 * i + j + 1;
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 3*6, argu + 4*6, argu + 5*6);   //12
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 3*6, -argu - 4*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 2*6, argu + 4*6, argu + 5*6);   //13
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 2*6, -argu - 4*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 2*6, argu + 3*6, argu + 5*6);    //14
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 2*6, -argu - 3*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 2*6, argu + 3*6, argu + 4*6);   //15
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 2*6, -argu - 3*6, -argu - 4*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1*6, argu + 4*6, argu + 5*6);   //23
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 1*6, -argu - 4*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1*6, argu + 3*6, argu + 5*6);   //24
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 1*6, -argu - 3*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1*6, argu + 3*6, argu + 4*6);   //25
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 1*6, -argu - 3*6, -argu - 4*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1*6, argu + 2*6, argu + 5*6);   //34
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 1*6, -argu - 2*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1*6, argu + 2*6, argu + 4*6);   //35
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 1*6, -argu - 2*6, -argu - 4*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu, argu + 1*6, argu + 2*6, argu + 3*6);   //45
		fprintf(fp, "%d %d %d %d 0\n",
			-argu, -argu - 1*6, -argu - 2*6, -argu - 3*6);

		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1*6, argu + 3*6, argu + 4*6, argu + 5*6);   //2
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1*6, -argu - 3*6, -argu - 4*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1*6, argu + 2*6, argu + 4*6, argu + 5*6);   //3
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1*6, -argu - 2*6, -argu - 4*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1*6, argu + 2*6, argu + 3*6, argu + 5*6);   //4
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1*6, -argu - 2*6, -argu - 3*6, -argu - 5*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 1*6, argu + 2*6, argu + 3*6, argu + 4*6);   //5
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 1*6, -argu - 2*6, -argu - 3*6, -argu - 4*6);
		fprintf(fp, "%d %d %d %d 0\n",
			argu + 2*6, argu + 3*6, argu + 4*6, argu + 5*6);   //01
		fprintf(fp, "%d %d %d %d 0\n",
			-argu - 2*6, -argu - 3*6, -argu - 4*6, -argu - 5*6);

	}
	return fp;
}

/***********************
*�������ƣ�Limit3
*�������ã���������3�����Ӿ�
*����ֵ��fp
*����ֵ��fp
***********************/
FILE* Limit3(FILE* fp)
{
	int i, j,k;
	int argu1, argu2;
	int temp1, temp0, temp[6], total;
	for (i = 0; i < 5; i++) //��һ��
	{
		for (j = i + 1; j <= 5; j++) //�Ƚϵ�һ��
		{
			
			for (k = 0; k < 6; k++)   //����
			{
				argu1 = 6 * i + k+1;
				argu2 = 6 * j + k+1;
				temp1 = 10000 + (i + 1) * 1000 + (j + 1) * 100 + (k+1) * 10 + 1;
				temp0 = 10000 + (i + 1) * 1000 + (j + 1) * 100 + (k + 1) * 10 + 0;
				temp[k] = 1000 + (i + 1) * 100 + (j + 1) * 10 + (k + 1);
				fprintf(fp, "%d %d 0\n", argu1, -temp1); //��һ��
				fprintf(fp, "%d %d 0\n", argu2, -temp1); //�ڶ���
				fprintf(fp, "%d %d %d 0\n", -argu1,-argu2, temp1); //������

				fprintf(fp, "%d %d 0\n", -argu1, -temp0); //��һ��
				fprintf(fp, "%d %d 0\n", -argu2, -temp0); //�ڶ���
				fprintf(fp, "%d %d %d 0\n", argu1, argu2, temp0); //������

				fprintf(fp, "%d %d 0\n", -temp1, temp[k]); //��һ��
				fprintf(fp, "%d %d 0\n", -temp0, temp[k]); //�ڶ���
				fprintf(fp, "%d %d %d 0\n", temp1, temp0, -temp[k]); //������
			}
			total = 100 + (i + 1) * 10 + (j + 1);
			fprintf(fp, "%d %d %d %d %d %d %d 0\n",
				-total, -temp[0],-temp[1], -temp[2], -temp[3], -temp[4], -temp[5]); //��һ��
			fprintf(fp, "%d %d 0\n", total, temp[0]); //��2��
			fprintf(fp, "%d %d 0\n", total, temp[1]); //��3��
			fprintf(fp, "%d %d 0\n", total, temp[2]); //��4��
			fprintf(fp, "%d %d 0\n", total, temp[3]); //��5��
			fprintf(fp, "%d %d 0\n", total, temp[4]); //��6��
			fprintf(fp, "%d %d 0\n", total, temp[5]); //��7��
		}
	}

	for (i = 0; i < 5; i++) //��һ��
	{
		for (j = i + 1; j <= 5; j++) //�Ƚϵ�һ��
		{

			for (k = 0; k < 6; k++)   //����
			{
				argu1 = 6 * k + i + 1;
				argu2 = 6 * k + j + 1;
				temp1 = 20000 + (i + 1) * 1000 + (j + 1) * 100 + (k + 1) * 10 + 1;
				temp0 = 20000 + (i + 1) * 1000 + (j + 1) * 100 + (k + 1) * 10 + 0;
				temp[k] = 2000 + (i + 1) * 100 + (j + 1) * 10 + (k + 1);
				fprintf(fp, "%d %d 0\n", argu1, -temp1); //��һ��
				fprintf(fp, "%d %d 0\n", argu2, -temp1); //�ڶ���
				fprintf(fp, "%d %d %d 0\n", -argu1, -argu2, temp1); //������

				fprintf(fp, "%d %d 0\n", -argu1, -temp0); //��һ��
				fprintf(fp, "%d %d 0\n", -argu2, -temp0); //�ڶ���
				fprintf(fp, "%d %d %d 0\n", argu1, argu2, temp0); //������

				fprintf(fp, "%d %d 0\n", -temp1, temp[k]); //��һ��
				fprintf(fp, "%d %d 0\n", -temp0, temp[k]); //�ڶ���
				fprintf(fp, "%d %d %d 0\n", temp1, temp0, -temp[k]); //������
			}
			total = 200 + (i + 1) * 10 + (j + 1);
			fprintf(fp, "%d %d %d %d %d %d %d 0\n",
				-total, -temp[0], -temp[1], -temp[2], -temp[3], -temp[4], -temp[5]); //��һ��
			fprintf(fp, "%d %d 0\n", total, temp[0]); //��2��
			fprintf(fp, "%d %d 0\n", total, temp[1]); //��3��
			fprintf(fp, "%d %d 0\n", total, temp[2]); //��4��
			fprintf(fp, "%d %d 0\n", total, temp[3]); //��5��
			fprintf(fp, "%d %d 0\n", total, temp[4]); //��6��
			fprintf(fp, "%d %d 0\n", total, temp[5]); //��7��
		}
	}
	return fp;
}

/***********************
*�������ƣ�PrintSudo
*�������ã���ӡ����
*����ֵ����
*����ֵ����
**********************/
void PrintSudo(BT*bt)
{
	FILE* fp;
	if ((fp = fopen("D:/SAT/result.txt", "r")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		//�ļ���ʧ�ܣ�����ERROR
	}
	int i, j,k;
	int argu;
	int status;
	fscanf(fp, "%d", &argu);
	for (k = 0; k < 36; k++)
	{
		fscanf(fp, "%d", &argu);
		fscanf(fp, "%d", &status);
		j = (argu - 1) % 6;
		i = (argu - 1 - j) / 6;
		bt->sudo[i][j] = status;
	}
	//���ڲ����Ƿ������ȷ
	printf("\nSAT������£�\n\n");
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			printf("%d ", bt->sudo[i][j]);
		}
		printf("\n");
	}
}