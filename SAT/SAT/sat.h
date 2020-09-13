#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "time.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1  //-1需要退回到主程序
#define OK 1;         //函数返回值

typedef int status;

///////////////////////////////////////////////////////////////////////
/*****************
*定义cnf储存的结构
********************/

//单个变元
typedef struct Argu {
	int argu;
	Argu* argu_next;
}Argu;

//单个子句
typedef struct Clause {
	int num;  //记录变元数量，判断是否为空子句或单子句
	Clause* clause_next;//指向下一个子句
	Argu* next;//指向子句的首个变元
}Clause;

//整体cnf储存结构
typedef struct {
	Clause* first;//指向cnf第一个子句
	int argu_num;//cnf变元个数
	int clause_num;//cnf子句个数
}CNF;

//用来储存变元出现次数和最终取值
typedef struct argustatus {
	int argu;               //变元名
	int num;               //变元出现频率
	int status;            //变元取值
}argustatus;

//用来储存结果的最终取值
typedef struct result {
	int argunum;               //变元个数
	int tempnum;                 //当前已经储存变元个数，方便储存
	argustatus value[2000];               //变元取值储存
}result;

//数独棋盘
typedef struct BT {
	int order;   //阶数
	int sudo[6][6];   //储存棋盘
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