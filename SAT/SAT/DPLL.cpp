#include "sat.h"

/******************************
*�������ƣ�DPLL
*�������ã���cnf����DPLL���ݹ��㷨
*����ֵ��cnf�ĵ�ַָ��root
*���ֵ���ܷ����
***************************/
status DPLL(CNF* root,result *root_value)
{
	int L;  //���Ӿ��Ԫ
	L= FindSingle(root);    //�ҵ����Ӿ��Ԫ
	while (L != NULL) {        //S�д��ڵ��Ӿ�Ļ�
		//���ݵ��Ӿ����ɾ�������а���L���Ӿ䣬LΪ��򻯵õ�S1��ɾ��-L��Ԫ���õ�S2
		if (L > 0)  makeresult(root_value, L, 1);    //��Lȡֵ��Ϊ1
		else makeresult(root_value, L, 0);
		RemoveClause(root, L);                   //��S�а���L�����ɾ�����õ�S1
		RemoveArgu(root, -L);                    //��S�а���-L�ı�Ԫɾ�����õ�S2
		if (root->clause_num == 0) { SaveResult(root_value); return TRUE; }
		else
			if (ISEmptyClause(root) == 1) { return NULL; }        //S�д��ڿ��Ӿ䣬�������� 
		L = FindSingle(root);    //�ҵ����Ӿ��Ԫ
	}

	//ͨ��ѡȡ���ִ������ı�ԪΪv����ԪƵ���Ѿ���������root_value��
	int v;
	v = FindMost(root_value);
	CNF* new_root;
	new_root = CopyRoot(root);
	result* new_value;
	new_value = CopyResult(root_value);
	if ( DPLL(AddClause(root, v), root_value)==TRUE) return TRUE;
	return DPLL(AddClause(new_root, -v), new_value);
}



/**********************************
*�������ƣ�LoadCNF
*�������ã��Ӹ����ļ��ж���CNF��ʽ��������ʽ�ṹ���䴢��
*����ֵ������ɹ�����TURE������ʧ�ܷ���ERROR
*���õĺ�����
************************************/
status LoadCNF(CNF*root,result *root_value, FILE*fp)
{

	//��һ����������ͷע��
	//cnf��������Ϣ��p��ͷ��������һ������ע��
	//˼��Ϊ������ȡ��һֱ����p����
	char pre[2];//�ж��Ƿ�Ϊ\n
	fgets(pre, 2, fp);
	if (pre[0] != 'p')      //��c��ͷ
	{
		for (; ; )
		{
			if (pre[0] == '\n')
			{
				fgets(pre, 2, fp);
				if (pre[0] == 'p') break;
			}
			else
				fgets(pre, 2, fp);
		}
	}

	//��p��ͷ��ִ�в���

	//�ɹ���λ��������Ϣ
	
	//�ڶ���������������Ϣ
	//����fscanf����
	char cnfname[5];
	int ArguNum;//������Ԫ����
	int ClauseNum;//�Ӿ�����
	fgets(cnfname, 5, fp);
	fscanf(fp,"%d %d",&ArguNum,&ClauseNum);
	//�ɹ��������Ϣ

	root_value->argunum = ArguNum;          //������������鸳��Ԫ����ֵ
	root_value->tempnum = 0;
	 
	//���������ú�������cnf��ʽ�ṹ                
	Clause* nextclause;            //�����м������Ӿ���м�C1,C2
	Argu* nextargu;               //�����м������Ӿ�ı�Ԫ ��l11
	root->argu_num = ArguNum;     //����cnf�ı�Ԫ��
	root->clause_num = ClauseNum;      // ����cnf���Ӿ���
	int argu;                      //���ڶ����Ԫ
	int i = 0;

	//��ʼ����Num���Ӿ�
	//�Ӿ��������ͷ��㣬��Ԫ�������ͷ���

	nextclause= (Clause*)malloc(sizeof(Clause));  //���ɵ�һ���Ӿ俪ͷ��C1
	root->first = nextclause;         //��cnfָ��    
	nextclause->clause_next = (Clause*)malloc(sizeof(Clause));        //�����Ӿ��ͷ���
	nextclause = nextclause->clause_next;


	//�����������������Ƕ�����Ӿ�

	int addnum;    //������Ǳ�Ԫ����


	//�������һ����������,����ClauseNum-1��
	for (i = 0; i < ClauseNum; i++) {    //һ��һ�ж��룬ÿ�ж�������ѭ��
		//������C1,  C2��C3.......
		addnum = 0;   //������������Ϊ0
		//��ʼ������һ�е�һ����Ԫ
		fscanf(fp, "%d", &argu); 
		makeresult(root_value, argu,-1);   //������Ϣ�����ڱ�Ԫ������
		nextargu = (Argu*)malloc(sizeof(Argu));                 //�Ӿ����ɱ�ͷ���
		nextclause->next = nextargu;
		nextargu->argu_next = (Argu*)malloc(sizeof(Argu));
		nextargu = nextargu->argu_next;
		nextargu->argu = argu;
		//������һ�к����Ԫ
		for (fscanf(fp, "%d", &argu); argu != 0;addnum++) {
			makeresult(root_value, argu,-1);   //������Ϣ�����ڱ�Ԫ������
			nextargu->argu_next = (Argu*)malloc(sizeof(Argu));
			nextargu = nextargu->argu_next;            //ָ���һ����Ԫ
			nextargu->argu = argu;
			fscanf(fp, "%d", &argu); 
		}
		nextclause->num = addnum + 1;
		nextargu->argu_next = NULL;  //βָ���ÿ�
		nextclause->clause_next = (Clause*)malloc(sizeof(Clause));
		nextclause = nextclause->clause_next;
	}
	return OK;

}

/***************************
*�������ƣ�CreatCNF
*�������ã�����CNF����,�ձ�
*����ֵ��������������ĵ�ַ
***************************/
CNF* CreatCNF(void)
{
	CNF* cnf;
	cnf = (CNF*)malloc(sizeof(CNF));
	cnf->first = NULL;//��Ϊ��
	return cnf;//�������ַ
}

/*******************************
*�������ƣ�SaveList
*�������ã�������ṹ�е�cnf�ļ������log.txt�ļ��У�������֤
*����ֵ���ɹ�״̬
*******************************/
status SaveList(CNF* root)
{
	FILE* fp;
	if ((fp = fopen("D:/SAT/log.txt", "w")) == NULL)       //������ṹ�����������log.txt
	{
		printf("�ļ���ʧ�ܣ�\n");
		return  ERROR;
		//�ļ���ʧ�ܣ�����ERROR
	}
	fprintf(fp, "%d,%d\n", root->argu_num, root->clause_num);    //�����Ԫ
	Clause* nextclause;
	Argu* nextargu;
	nextclause = root->first->clause_next;        //ָ���ͷ���һ���Ӿ�
	int i;
	for (i = 0; i < root->clause_num; i++) {
		nextargu = nextclause->next->argu_next;          //ָ���Ӿ��ͷ���һ����Ԫ
		fprintf(fp, "%d      ", nextclause->num);
		for (; nextargu != NULL; nextargu = nextargu->argu_next)
		{
			fprintf(fp, "%d ", nextargu->argu);
		}
		nextclause = nextclause->clause_next;
		fprintf(fp,"\n");
	}
	return OK;
}



/****************************
*��������:FindSingle
*��������:�ҵ����Ӿ���Ǹ���Ԫ
*����ֵ:cnf�ṹ��rootָ��
*����ֵ:�����ڵ��Ӿ䷵�ظñ�Ԫ�����򷵻�NULL��Ĭ�Ϸ��ص�һ�����Ӿ��Ԫ
****************************/
int FindSingle(CNF* root)
{
	int i;
	Clause* nextclause;
	nextclause = root->first->clause_next;
	for (i = 0; i < root->clause_num; i++) {
		if (nextclause->num == 1) return nextclause->next->argu_next->argu;    //���ظõ��Ӿ�ı�Ԫ
		else
			nextclause = nextclause->clause_next;
	}
	return NULL;       //�����ڵ��Ӿ�
}


/*********************************
*�������ƣ�makeresult
*�������ã����ڸ�result�б�Ԫ������ִ�����ȡֵ
*����ֵ����Ԫ��
*���ֵ��status
************************************/
void makeresult(result *root_value,int argu,int status)
{
	//�ճ���һ�������������β����
	root_value->value[0].argu = abs(argu);
	//���������������Ƿ���ڸñ�Ԫ
	int i;        //������β��ʼ����
	for (i = root_value->tempnum; i >= 0; i--) {
		if (abs(root_value->value[i].argu) == abs(argu)) break;      //���ҳɹ�
	}
	
	if (i == 0) {             //�ñ�Ԫδ������������
		root_value->value[root_value->tempnum + 1].argu = abs(argu);     //���ñ�Ԫ������������
		root_value->value[root_value->tempnum + 1].num = 1;          //���ñ�Ԫ����Ƶ����Ϊ1
		root_value->value[root_value->tempnum + 1].status = -1;  //���ñ�Ԫȡֵ��ΪNULL
		root_value->tempnum++;
	}
	else                      //�ñ�Ԫ��������������
	{
		root_value->value[i].num++;   //Ƶ����һ
		root_value->value[i].status = status;
	}
}


/***************************
*�������ƣ�RemoveClause
*�������ã�����ɾȥ���а���argu���Ӿ䣬cnf�Ӿ�����Ҫ��һ
*����ֵ��cnf����ָ�룬Ҫɾ����argu
***************************/
void RemoveClause(CNF* root, int argu)
{
	Clause* nextclause;
	Clause* preclause;
	Clause* tempclause;
	Argu* nextargu;
	Argu* tempargu;    //����free����Ԫ

	int i;
	int num;
	num = root->clause_num;
	preclause = root->first;  //ָ���ͷ���
	nextclause = preclause->clause_next;     //ָ���һ���Ӿ�
	for (i = 0; i < num; i++) {

		nextargu = nextclause->next->argu_next;  //ָ���һ����Ԫ
		for (; nextargu != NULL; nextargu = nextargu->argu_next) {
			if (nextargu->argu == argu) break;
		}
		if (nextargu != NULL) {   //���Ӿ��д��ڸñ�Ԫ
			for (nextargu = nextclause->next; nextargu != NULL; ) {
				tempargu = nextargu;
				nextargu = nextargu->argu_next;   //ָ���һ��Ԫ
				free(tempargu);    //�ͷŵ���Ԫ�ռ�
			}
			root->clause_num--;       //�Ӿ�����һ
			tempclause = nextclause;
			nextclause = nextclause->clause_next;
			free(tempclause);
			preclause->clause_next = nextclause;
		}
		else {
			preclause = preclause->clause_next;
			nextclause = nextclause->clause_next;
		}
	}

}


/****************************
*�������ƣ�RemoveArgu
*�������ã�ɾ����Ԫ
*����ֵ��CNFָ��root����ɾ����Ԫ
����ֵ����
******************************/
void RemoveArgu(CNF* root, int argu)
{
	int i;
	Clause* nextclause;
	Argu* nextargu;
	Argu* tempargu;
	Argu* preargu;
	nextclause = root->first->clause_next;     //ָ���һ���Ӿ�
	preargu = nextclause->next;                     //ָ���Ӿ��ͷ
	for (i = 0; i < root->clause_num; i++) {
		nextargu = nextclause->next->argu_next;  //ָ���һ����Ԫ
		for (; nextargu != NULL; ) {                       //���ڸñ�Ԫ
			if (nextargu->argu == argu) {
				tempargu = nextargu;
				nextargu = nextargu->argu_next;
				free(tempargu);
				preargu->argu_next = nextargu;
				nextclause->num--;                //��Ԫ����һ
			}
			else {
				preargu = preargu->argu_next;
				nextargu = nextargu->argu_next;
			}
		}
		nextclause = nextclause->clause_next;
		preargu = nextclause->next;
	}
}


/*****************************
*�������ƣ�ISEmptyClause
*�������ã��ж�cnf�Ƿ���ڿ��Ӿ�
*����ֵ��cnf��ַroot
*����ֵ�����ڿ��Ӿ�,����OK�����򷵻�FALSE
****************************/
status ISEmptyClause(CNF* root)
{
	int i;
	Clause* nextclause;
	nextclause = root->first->clause_next;                       //ָ���ͷ�����һ���Ӿ�
	for (i = 0; i < root->clause_num; i++) {
		if (nextclause->num == 0) break;
		nextclause = nextclause->clause_next;
	}
	if (i==root->clause_num) return  FALSE;    //�����ڿ��Ӿ�
	else return OK;                                         //���ڿ��Ӿ�
}


/*******************************
*�������ƣ�SortResult
*�������ã���result�б�Ԫ��Ƶ������
*����ֵ��root_value
*����ֵ����
****************************/
void SortResult(result* root_value)
{
	int i, j;

	//Ϊ�˷���������Ƚ���Ԫ��Ƶ����С�������������㷨����ð�ݷ�
	for (j = 1; j <= root_value->argunum; j++) {
		for (i = 1; i <= root_value->argunum; i++) {
			if (root_value->value[i].num < root_value->value[i + 1].num)
			{
				root_value->value[0] = root_value->value[i + 1];
				root_value->value[i + 1] = root_value->value[i];
				root_value->value[i] = root_value->value[0];
			}
		}
	}
}


/*****************************
*�������ƣ�FindMost
*�������ã��ҵ���Ԫ��δ��ֵ��Ƶ������
*����ֵ��root_value
*����ֵ������Ԫ
**************************/
int FindMost(result* root_value)
{
	int i;
	for (i = 1; i <= root_value->argunum; i++) {
		if (root_value->value[i].status == -1) return root_value->value[i].argu;
	}
}


/************************
*�������ƣ�AddClause
*�������ã����ӵ��Ӿ䣬��ԪΪv
*����ֵ��cnfָ��root�������Ӿ�ı�Ԫ
*����ֵ����
*************************/
CNF* AddClause(CNF* root, int v)
{
	//Ϊ�˼���ʱ��ռ�ã����Ӿ���ڱ�ͷ����
	Clause* nextclause;
	Argu* nextargu;
	nextclause = (Clause*)malloc(sizeof(Clause));      //�������Ӿ�
	nextargu = (Argu*)malloc(sizeof(Argu));       //���ɱ�ͷ���
	nextargu->argu_next= (Argu*)malloc(sizeof(Argu));    //���ɱ�Ԫ���
	nextargu->argu_next->argu = v;                     //��Ԫ��ֵ
	nextargu->argu_next->argu_next = NULL;        //��β��־
	nextclause->clause_next = root->first->clause_next;       //���ڵ�һ���Ӿ���ǰ
	nextclause->next = nextargu;
	nextclause->num = 1;
	root->first->clause_next = nextclause;
	root->clause_num++;
	return root;
}

/*******************************
*�������ƣ�SaveResult
*�������ã�����������result.txt�ļ��У�������֤
*����ֵ���ɹ�״̬
*******************************/
status SaveResult(result* root_value)
{
	FILE* fp;
	if ((fp = fopen("D:/SAT/result.txt", "w")) == NULL)       //������ṹ�����������log.txt
	{
		printf("�ļ���ʧ�ܣ�\n");
		return  ERROR;
		//�ļ���ʧ�ܣ�����ERROR
	}
	fprintf(fp, "%d\n", root_value->argunum);    //�����Ԫ����
	int i;
	for (i = 1; i <=root_value->argunum; i++) {
		fprintf(fp, "%d       %d", root_value->value[i].argu,  root_value->value[i].status);
		fprintf(fp, "\n");
	}
	return OK;
}


/*****************************
*�������ƣ�CopyRoot
*�������ã�����cnf
*����ֵ��rootָ��
*���ֵ�������ɵ�rootָ��
****************************/
CNF* CopyRoot(CNF* root)
{
	CNF* newroot;   //�����µ�root
	newroot= CreatCNF();
	newroot->argu_num = root->argu_num;    //������ֵ
	newroot->clause_num = root->clause_num;

	Clause* nextclause;
	Clause* rootclause;
	Argu* nextargu;
	Argu* rootargu;
	nextclause = (Clause*)malloc(sizeof(Clause));  
	newroot->first = nextclause;         //��cnfָ��    
	nextclause->clause_next = (Clause*)malloc(sizeof(Clause));        //�����Ӿ��ͷ���
	nextclause = nextclause->clause_next;
	rootclause = root->first->clause_next;   //ָ��root��һ���Ӿ�
	
	int i;
	for (i = 0; i < root->clause_num; i++) {  
		nextargu = (Argu*)malloc(sizeof(Argu));                 //�Ӿ����ɱ�ͷ���
		nextclause->next = nextargu;
		rootargu = rootclause->next->argu_next;

		for (; rootargu != NULL ;rootargu=rootargu->argu_next) {
			nextargu->argu_next = (Argu*)malloc(sizeof(Argu));
			nextargu = nextargu->argu_next;            //ָ���һ����Ԫ
			nextargu->argu = rootargu->argu;
		}
		nextclause->num = rootclause->num;
		nextargu->argu_next = NULL;  //βָ���ÿ�
		nextclause->clause_next = (Clause*)malloc(sizeof(Clause));
		nextclause = nextclause->clause_next;
		rootclause = rootclause->clause_next;
	}
	return newroot;
}


/*****************************
*�������ƣ�CopyResult
*�������ã�����result
*����ֵ��root_value
*����ֵ��new_value
*****************************/
result* CopyResult(result* root_value)
{
	result* new_value;             //��Ԫȡֵ
	new_value = (result*)malloc(sizeof(result));
	new_value->argunum = root_value->argunum;
	new_value->tempnum = root_value->tempnum;
	int i;
	for (i = 1; i <=root_value->argunum; i++)
	{
		new_value->value[i] = root_value->value[i];
	}
	return new_value;
}
