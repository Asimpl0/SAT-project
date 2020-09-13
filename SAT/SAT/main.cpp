
/*****************************************************************
*问题：基于SAT的二进制数独游戏求解程序
*CS1806 U201814658 范攀
*2020.2.20
*****************************************************************/

#include "sat.h"

/********************************
*主函数
*调用其他函数实现主要功能
***********************************/
int main(void)
{
	int op = 1;

	while (op)
	{
		system("cls");
		clock_t start, finish; // 定义变量
		double time;           //计算时间
		CNF* root;                //cnf链表的指针,及图中的root
		result* root_value;             //变元取值
		root_value = (result*)malloc(sizeof(result));
		root_value->tempnum = 0;                         //将当前变元数初始化为0
		root = CreatCNF();           //生成cnf链表
		FILE* fp1, * fp2;
		BT* bt;
		printf("\n\n        基于SAT的二进制数独游戏求解程序 \n\n");
		printf("-------------------------------------------------\n\n");
		printf("    1. SAT		2. SAT-OPTIMLLY\n");
		printf("    3. PUZLLE		0. Exit\n");
		printf("-------------------------------------------------\n\n");
		printf("    请选择你的操作[0~3]:");


		scanf("%d", &op);
		switch (op) {
		case 1:

		case 2:
			printf("请输入需要读取的CNF文件名！\n");
			char filename[30];
			char filename_copy[30];
			int i;
			

			

			scanf("%s", filename);

			//开始读入cnf文件
			if ((fp1 = fopen(filename, "r")) == NULL)
			{
				printf("文件打开失败！\n");
				return  ERROR;
				//文件打开失败，返回ERROR
			}
			for (i = 0; i < 30; i++) {
				if (filename[i] != '.')
					filename_copy[i] = filename[i];
				else
					break;
			}
			
			filename_copy[i] = '.';
			filename_copy[i+1] = 'r';
			filename_copy[i + 2] = 'e';
			filename_copy[i + 3] = 's';
			filename_copy[i + 4] = 0;
			LoadCNF(root, root_value, fp1);                 //读入cnf文件
			SaveList(root);
			if (op == 2) {
				SortResult(root_value);                       //对变元进行排序
			}
			fclose(fp1);
			start = clock();     //开始
			if (DPLL(root, root_value) == TRUE)
			{
				printf("cnf为可满足!\n");
				if ((fp1 = fopen(filename_copy, "w")) == NULL)
				{
					printf("文件打开失败！\n");
					return  ERROR;
					//文件打开失败，返回ERROR
				}
				fprintf(fp1, "s 1\nt ");
				SortOut(root_value);
				for (i = 2; i <=root_value->argunum+1; i++) {
					if(root_value->value[i].status==1)
						fprintf(fp1, "%d ",root_value->value[i].argu);
					else
						fprintf(fp1, "-%d ", root_value->value[i].argu);
				}
				fprintf(fp1, "\n");
				finish = clock();    //结束
				time = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
				fprintf(fp1,"t %lfs\n", time);
				fclose(fp1);
			}
			else
			{
				printf("cnf为不可满足!\n");
				if ((fp1 = fopen(filename_copy, "w")) == NULL)
				{
					printf("文件打开失败！\n");
					return  ERROR;
					//文件打开失败，返回ERROR
				}
				fprintf(fp1, "s 0\n");
				finish = clock();    //结束
				time = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
				fprintf(fp1, "t %lfs\n", time);
				fclose(fp1);
			}
			printf("time=%.4lfs\n", time);//输出运行时间
			getchar();
			getchar();
			break;

		case 3:

			bt = ReadBP();
			fp2 = SUDOCNF();
			fp2 = CREAT_SIGCLA(bt, fp2);
			fp2 = Limit1(fp2);
			fp2 = Limit2(fp2);
			fp2 = Limit3(fp2);
			printf("\n**已解析为sudo.cnf**\n\n");
			fclose(fp2);
			if ((fp2 = fopen("D:/SAT/sudo.cnf", "r")) == NULL)
			{
				printf("文件打开失败！\n");
				//文件打开失败，返回ERROR
			}
			printf("\n**正在处理sudo.cnf**\n\n");
			LoadCNF(root, root_value, fp2);                 //读入cnf文件
			SaveList(root);
			SortResult(root_value);
			DPLL(root, root_value);
			fclose(fp2);
			PrintSudo(bt);
			getchar();
			getchar();
			break;
		case 0:
			break;
		default :
			printf("	input error!\n");
			getchar();
			getchar();
			break;
		}
	}
	

	printf("欢迎下次再使用本系统！\n");
	return 0;

}