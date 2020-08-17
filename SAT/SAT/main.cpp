
/*****************************************************************
*���⣺����SAT�Ķ�����������Ϸ������
*CS1806 U201814658 ����
*2020.2.20
*ע�⣬�������ɵĴ���ṹ��Ҫ������ظ�ʹ��
*****************************************************************/

#include "sat.h"

/********************************
*������
*������������ʵ����Ҫ����
***********************************/
int main(void)
{
	int op = 1;

	clock_t start, finish; // �������
	double time;           //����ʱ��
	CNF* root;                //cnf�����ָ��,��ͼ�е�root
	result* root_value;             //��Ԫȡֵ
	root_value = (result*)malloc(sizeof(result));
	root_value->tempnum = 0;                         //����ǰ��Ԫ����ʼ��Ϊ0
	root = CreatCNF();           //����cnf����
	FILE* fp1,*fp2;
	BT* bt;
		printf("      ����SAT�Ķ�����������Ϸ������ \n");
		printf("-------------------------------------------------\n");
		printf("    1. SAT			2. PUZLLE\n");
		printf("    0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~2]:");


		scanf("%d", &op);
		switch (op) {
		case 1:
			printf("��������Ҫ��ȡ��CNF�ļ�����\n");
			char filename[30];
			scanf("%s", filename);

			//��ʼ����cnf�ļ�
			if ((fp1 = fopen(filename, "r")) == NULL)
			{
				printf("�ļ���ʧ�ܣ�\n");
				return  ERROR;
				//�ļ���ʧ�ܣ�����ERROR
			}
			LoadCNF(root, root_value, fp1);                 //����cnf�ļ�
			SaveList(root);
			start = clock();     //��ʼ
			SortResult(root_value);                       //�Ա�Ԫ��������
			if (DPLL(root, root_value) == TRUE) printf("cnfΪ������!\n");
			else
				printf("cnfΪ��������!\n");
			finish = clock();    //����
			time = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
			printf("time=%lf\n", time);//�������ʱ��
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
				printf("�ļ���ʧ�ܣ�\n");
				//�ļ���ʧ�ܣ�����ERROR
			}
			LoadCNF(root, root_value, fp2);                 //����cnf�ļ�
			SaveList(root);
			SortResult(root_value);                       //�Ա�Ԫ��������
			DPLL(root, root_value);
			PrintSudo(bt);
			getchar();
			getchar();
			break;
		case 0:
			break;
		}

	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;

}