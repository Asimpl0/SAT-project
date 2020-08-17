#include "sat.h"

int bpnum = 0;
//所用到的数独棋盘在文件中按行显示，存在即显示0或1，不存在显示为.
//用于解决6*6数独游戏

/***************************
*函数名称：ReadBP
*函数作用：读入数独棋盘，生成二元数组
*输入值：fp
*返回值：BT*
**************************/
BT* ReadBP(void)
{
	printf("请输入要读入的数独棋盘\n");
	char name[20];
	FILE* fp;
	scanf("%s", name);

	//开始读入cnf文件
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("文件打开失败！\n");
		return  NULL;
		//文件打开失败，返回NULL
	}

	BT* bt;
	bt = (BT*)malloc(sizeof(BT));//
	int i,j=0;
	char pre[2];
	bt->order = 6;
	for (i = 0; i <6; i++) {
		for (j=0; j<=6; j++) {
			fgets(pre, 2, fp);
			if (pre[0] == '0') { bt->sudo[i][j] = pre[0] - '0', bpnum++; }  //读入初始值
			if (pre[0] == '1') { bt->sudo[i][j] = pre[0] - '0', bpnum++; }
			if (pre[0] == '.') bt->sudo[i][j] = -1;
		}
	}

	return bt;
}

/*********************
*函数名称:SUDOCNF
*函数作用:生成数独的CNF文件
*输入值:无
*返回值:fp
**********************/
FILE* SUDOCNF(void)
{
	FILE* fp;
	if ((fp = fopen("D:\SAT\sudo.cnf", "w")) == NULL)       //将储存结构中内容输出到log.txt
	{
		printf("文件打开失败！\n");
		return  NULL;
		//文件打开失败，返回ERROR
	}
	fprintf(fp, "p cnf 606 %d\n", bpnum+2285);
	return fp;
}


/*****************
*函数名称:CREATE_SIGCLA
*函数作用:根据已填入内容生成单子句
*输入值:BT指针,fp
*返回值:fp
********************/
FILE* CREAT_SIGCLA(BT* bt, FILE* fp)
{
	int i, j;
	int argu;
	for(i=0;i<6;i++)
		for (j = 0; j < 6; j++)
		{
			argu = 6 * i  + j+1; //转换成变元
			if (bt->sudo[i][j] == 0) fprintf(fp, "%d 0\n", -argu);
			if (bt->sudo[i][j] == 1) fprintf(fp, "%d 0\n", argu);
		}
	return fp;
}


/*********************
*函数名称: Limit1
*函数作用: 根据限制条件1生成子句
*输入值：fp
返回值：fp
**********************/
FILE* Limit1(FILE* fp)
{
	//先考虑行
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
*函数名称：Limit2
*函数作用：根据限制2生成子句
*输入值：fp
*输出值：fp
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
*函数名称：Limit3
*函数作用：根据限制3生成子句
*输入值：fp
*返回值：fp
***********************/
FILE* Limit3(FILE* fp)
{
	int i, j,k;
	int argu1, argu2;
	int temp1, temp0, temp[6], total;
	for (i = 0; i < 5; i++) //第一行
	{
		for (j = i + 1; j <= 5; j++) //比较的一行
		{
			
			for (k = 0; k < 6; k++)   //列数
			{
				argu1 = 6 * i + k+1;
				argu2 = 6 * j + k+1;
				temp1 = 10000 + (i + 1) * 1000 + (j + 1) * 100 + (k+1) * 10 + 1;
				temp0 = 10000 + (i + 1) * 1000 + (j + 1) * 100 + (k + 1) * 10 + 0;
				temp[k] = 1000 + (i + 1) * 100 + (j + 1) * 10 + (k + 1);
				fprintf(fp, "%d %d 0\n", argu1, -temp1); //第一个
				fprintf(fp, "%d %d 0\n", argu2, -temp1); //第二个
				fprintf(fp, "%d %d %d 0\n", -argu1,-argu2, temp1); //第三个

				fprintf(fp, "%d %d 0\n", -argu1, -temp0); //第一个
				fprintf(fp, "%d %d 0\n", -argu2, -temp0); //第二个
				fprintf(fp, "%d %d %d 0\n", argu1, argu2, temp0); //第三个

				fprintf(fp, "%d %d 0\n", -temp1, temp[k]); //第一个
				fprintf(fp, "%d %d 0\n", -temp0, temp[k]); //第二个
				fprintf(fp, "%d %d %d 0\n", temp1, temp0, -temp[k]); //第三个
			}
			total = 100 + (i + 1) * 10 + (j + 1);
			fprintf(fp, "%d %d %d %d %d %d %d 0\n",
				-total, -temp[0],-temp[1], -temp[2], -temp[3], -temp[4], -temp[5]); //第一个
			fprintf(fp, "%d %d 0\n", total, temp[0]); //第2个
			fprintf(fp, "%d %d 0\n", total, temp[1]); //第3个
			fprintf(fp, "%d %d 0\n", total, temp[2]); //第4个
			fprintf(fp, "%d %d 0\n", total, temp[3]); //第5个
			fprintf(fp, "%d %d 0\n", total, temp[4]); //第6个
			fprintf(fp, "%d %d 0\n", total, temp[5]); //第7个
		}
	}

	for (i = 0; i < 5; i++) //第一列
	{
		for (j = i + 1; j <= 5; j++) //比较的一列
		{

			for (k = 0; k < 6; k++)   //行数
			{
				argu1 = 6 * k + i + 1;
				argu2 = 6 * k + j + 1;
				temp1 = 20000 + (i + 1) * 1000 + (j + 1) * 100 + (k + 1) * 10 + 1;
				temp0 = 20000 + (i + 1) * 1000 + (j + 1) * 100 + (k + 1) * 10 + 0;
				temp[k] = 2000 + (i + 1) * 100 + (j + 1) * 10 + (k + 1);
				fprintf(fp, "%d %d 0\n", argu1, -temp1); //第一个
				fprintf(fp, "%d %d 0\n", argu2, -temp1); //第二个
				fprintf(fp, "%d %d %d 0\n", -argu1, -argu2, temp1); //第三个

				fprintf(fp, "%d %d 0\n", -argu1, -temp0); //第一个
				fprintf(fp, "%d %d 0\n", -argu2, -temp0); //第二个
				fprintf(fp, "%d %d %d 0\n", argu1, argu2, temp0); //第三个

				fprintf(fp, "%d %d 0\n", -temp1, temp[k]); //第一个
				fprintf(fp, "%d %d 0\n", -temp0, temp[k]); //第二个
				fprintf(fp, "%d %d %d 0\n", temp1, temp0, -temp[k]); //第三个
			}
			total = 200 + (i + 1) * 10 + (j + 1);
			fprintf(fp, "%d %d %d %d %d %d %d 0\n",
				-total, -temp[0], -temp[1], -temp[2], -temp[3], -temp[4], -temp[5]); //第一个
			fprintf(fp, "%d %d 0\n", total, temp[0]); //第2个
			fprintf(fp, "%d %d 0\n", total, temp[1]); //第3个
			fprintf(fp, "%d %d 0\n", total, temp[2]); //第4个
			fprintf(fp, "%d %d 0\n", total, temp[3]); //第5个
			fprintf(fp, "%d %d 0\n", total, temp[4]); //第6个
			fprintf(fp, "%d %d 0\n", total, temp[5]); //第7个
		}
	}
	return fp;
}

/***********************
*函数名称：PrintSudo
*函数作用：打印数独
*输入值：无
*返回值：无
**********************/
void PrintSudo(BT*bt)
{
	FILE* fp;
	if ((fp = fopen("D:/SAT/result.txt", "r")) == NULL)
	{
		printf("文件打开失败！\n");
		//文件打开失败，返回ERROR
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
	//用于测试是否读入正确
	printf("\nSAT求解如下：\n\n");
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			printf("%d ", bt->sudo[i][j]);
		}
		printf("\n");
	}
}