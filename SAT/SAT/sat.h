#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "time.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1  //-1��Ҫ�˻ص�������
#define OK 1;         //��������ֵ

typedef int status;

///////////////////////////////////////////////////////////////////////
/*****************
*����cnf����Ľṹ
********************/

//������Ԫ
typedef struct Argu {
	int argu;
	Argu* argu_next;
}Argu;

//�����Ӿ�
typedef struct Clause {
	int num;  //��¼��Ԫ�������ж��Ƿ�Ϊ���Ӿ���Ӿ�
	Clause* clause_next;//ָ����һ���Ӿ�
	Argu* next;//ָ���Ӿ���׸���Ԫ
}Clause;

//����cnf����ṹ
typedef struct {
	Clause* first;//ָ��cnf��һ���Ӿ�
	int argu_num;//cnf��Ԫ����
	int clause_num;//cnf�Ӿ����
}CNF;

//���������Ԫ���ִ���������ȡֵ
typedef struct argustatus {
	int argu;               //��Ԫ��
	int num;               //��Ԫ����Ƶ��
	int status;            //��Ԫȡֵ
}argustatus;

//����������������ȡֵ
typedef struct result {
	int argunum;               //��Ԫ����
	int tempnum;                 //��ǰ�Ѿ������Ԫ���������㴢��
	argustatus value[2000];               //��Ԫȡֵ����
}result;

//��������
typedef struct BT {
	int order;   //����
	int sudo[6][6];   //��������
};


///////////////////////////////////////////////////////////////////////////




status LoadCNF(CNF* root, result* root_value, FILE*fp);
CNF* CreatCNF(void);
status SaveList(CNF* root);
int FindSingle(CNF* root);
void makeresult(result* root_value, int argu, int status);
status DPLL(CNF* root, result* root_value);
void RemoveClause(CNF* root, int argu);
void RemoveArgu(CNF* root, int argu);
status ISEmptyClause(CNF* root);
int FindMost(result* root_value);
void SortResult(result* root_value);
//void SortResult(result* root_value, int low, int high);
CNF* AddClause(CNF* root, int v);
status SaveResult(result* root_value);
CNF* CopyRoot(CNF* root);
result* CopyResult(result* root_value);
BT* ReadBP(void);
FILE* SUDOCNF(void);
FILE* CREAT_SIGCLA(BT* bt, FILE* fp);
FILE* Limit1(FILE* fp);
FILE* Limit2(FILE* fp);
FILE* Limit3(FILE* fp);
void PrintSudo(BT* bt);
void SortOut(result* root_value);