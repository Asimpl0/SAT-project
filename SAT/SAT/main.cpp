
/*****************************************************************
*问题：基于SAT的二进制数独游戏求解程序
*CS1806 U201814658 范攀
*2020.2.20
*注意，所有生成的储存结构需要清空再重复使用
*****************************************************************/

#include "sat.h"

/********************************
*主函数
*调用其他函数实现主要功能
***********************************/
int main(void)
{
	int op = 1;

	clock_t start, finish; // 定义变量
	double time;           //计算时间
	CNF* root;                //cnf链表的指针,及图中的root
	result* root_value;             //变元取值
	root_value = (result*)malloc(sizeof(result));
	root_value->tempnum = 0;                         //将当前变元数初始化为0
	root = CreatCNF();           //生成cnf链表
	FILE* fp1,*fp2;
	BT* bt;
		printf("      基于SAT的二进制数独游戏求解程序 \n");
		printf("-------------------------------------------------\n");
		printf("    1. SAT			2. PUZLLE\n");
		printf("    0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~2]:");


		scanf("%d", &op);
		switch (op) {
		case 1:
			printf("请输入需要读取的CNF文件名！\n");
			char filename[30];
			scanf("%s", filename);

			//开始读入cnf文件
			if ((fp1 = fopen(filename, "r")) == NULL)
			{
				printf("文件打开失败！\n");
				return  ERROR;
				//文件打开失败，返回ERROR
			}
			LoadCNF(root, root_value, fp1);                 //读入cnf文件
			SaveList(root);
			start = clock();     //开始
			SortResult(root_value);                       //对变元进行排序
			if (DPLL(root, root_value) == TRUE) printf("cnf为可满足!\n");
			else
				printf("cnf为不可满足!\n");
			finish = clock();    //结束
			time = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
			printf("time=%lf\n", time);//输出运行时间
			getchar();
			getchar();
			break;

		case 2:

			bt = ReadBP();
			fp2 = SUDOCNF();
			fp2 = CREAT_SIGCLA(bt, fp2);
			fp2 = Limit1(fp2);
			fp2 = Limit2(fp2);
			fp2 = Limit3(fp2);
			fclose(fp2);
			if ((fp2 = fopen("D:\SAT\sudo.cnf", "r")) == NULL)
			{
				printf("文件打开失败！\n");
				//文件打开失败，返回ERROR
			}
			LoadCNF(root, root_value, fp2);                 //读入cnf文件
			SaveList(root);
			SortResult(root_value);                       //对变元进行排序
			DPLL(root, root_value);
			PrintSudo(bt);
			getchar();
			getchar();
			break;
		case 0:
			break;
		}

	printf("欢迎下次再使用本系统！\n");
	return 0;

}