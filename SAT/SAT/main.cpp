
/*****************************************************************
*���⣺����SAT�Ķ�����������Ϸ������
*CS1806 U201814658 ����
*2020.2.20
*****************************************************************/

#include "sat.h"

/********************************
*������
*������������ʵ����Ҫ����
***********************************/
int main(void)
{
	int op = 1;

	while (op)
	{
		system("cls");
		clock_t start, finish; // �������
		double time;           //����ʱ��
		CNF* root;                //cnf�����ָ��,��ͼ�е�root
		result* root_value;             //��Ԫȡֵ
		root_value = (result*)malloc(sizeof(result));
		root_value->tempnum = 0;                         //����ǰ��Ԫ����ʼ��Ϊ0
		root = CreatCNF();           //����cnf����
		FILE* fp1, * fp2;
		BT* bt;
		printf("\n\n        ����SAT�Ķ�����������Ϸ������ \n\n");
		printf("-------------------------------------------------\n\n");
		printf("    1. SAT		2. SAT-OPTIMLLY\n");
		printf("    3. PUZLLE		0. Exit\n");
		printf("-------------------------------------------------\n\n");
		printf("    ��ѡ����Ĳ���[0~3]:");


		scanf("%d", &op);
		switch (op) {
		case 1:

		case 2:
			printf("��������Ҫ��ȡ��CNF�ļ�����\n");
			char filename[30];
			char filename_copy[30];
			int i;
			

			

			scanf("%s", filename);

			//��ʼ����cnf�ļ�
			if ((fp1 = fopen(filename, "r")) == NULL)
			{
				printf("�ļ���ʧ�ܣ�\n");
				return  ERROR;
				//�ļ���ʧ�ܣ�����ERROR
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
			LoadCNF(root, root_value, fp1);                 //����cnf�ļ�
			SaveList(root);
			if (op == 2) {
				SortResult(root_value);                       //�Ա�Ԫ��������
			}
			fclose(fp1);
			start = clock();     //��ʼ
			if (DPLL(root, root_value) == TRUE)
			{
				printf("cnfΪ������!\n");
				if ((fp1 = fopen(filename_copy, "w")) == NULL)
				{
					printf("�ļ���ʧ�ܣ�\n");
					return  ERROR;
					//�ļ���ʧ�ܣ�����ERROR
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
				finish = clock();    //����
				time = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
				fprintf(fp1,"t %lfs\n", time);
				fclose(fp1);
			}
			else
			{
				printf("cnfΪ��������!\n");
				if ((fp1 = fopen(filename_copy, "w")) == NULL)
				{
					printf("�ļ���ʧ�ܣ�\n");
					return  ERROR;
					//�ļ���ʧ�ܣ�����ERROR
				}
				fprintf(fp1, "s 0\n");
				finish = clock();    //����
				time = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
				fprintf(fp1, "t %lfs\n", time);
				fclose(fp1);
			}
			printf("time=%.4lfs\n", time);//�������ʱ��
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
			printf("\n**�ѽ���Ϊsudo.cnf**\n\n");
			fclose(fp2);
			if ((fp2 = fopen("D:/SAT/sudo.cnf", "r")) == NULL)
			{
				printf("�ļ���ʧ�ܣ�\n");
				//�ļ���ʧ�ܣ�����ERROR
			}
			printf("\n**���ڴ���sudo.cnf**\n\n");
			LoadCNF(root, root_value, fp2);                 //����cnf�ļ�
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
	

	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;

}