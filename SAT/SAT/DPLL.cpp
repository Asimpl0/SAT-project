#include "sat.h"

/******************************
*函数名称：DPLL
*函数作用：对cnf利用DPLL，递归算法
*输入值：cnf的地址指针root
*输出值：能否求解
***************************/
status DPLL(CNF* root,result *root_value)
{
	int L;  //单子句变元
	L= FindSingle(root);    //找到单子句变元
	while (L != NULL) {        //S中存在单子句的话
		//根据单子句规则，删除掉所有包含L的子句，L为真简化得到S1，删除-L变元，得到S2
		if (L > 0)  makeresult(root_value, L, 1);    //将L取值赋为1
		else makeresult(root_value, L, 0);
		RemoveClause(root, L);                   //将S中包含L的语句删除，得到S1
		RemoveArgu(root, -L);                    //将S中包含-L的变元删除，得到S2
		if (root->clause_num == 0) { SaveResult(root_value); return TRUE; }
		else
			if (ISEmptyClause(root) == 1) { return NULL; }        //S中存在空子句，不可满足 
		L = FindSingle(root);    //找到单子句变元
	}

	//通过选取出现次数最多的变元为v，变元频数已经储存在了root_value中
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
*函数名称：LoadCNF
*函数作用：从给定文件中读入CNF公式，并用链式结构将其储存
*返回值：读入成功返回TURE，读入失败返回ERROR
*调用的函数：
************************************/
status LoadCNF(CNF*root,result *root_value, FILE*fp)
{

	//第一步，跳过开头注释
	//cnf的总体信息以p开头，利用这一点跳过注释
	//思想为连续读取，一直读到p结束
	char pre[2];//判断是否为\n
	fgets(pre, 2, fp);
	if (pre[0] != 'p')      //以c开头
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

	//以p开头不执行操作

	//成功定位到总体信息
	
	//第二步，读入主体信息
	//利用fscanf读入
	char cnfname[5];
	int ArguNum;//布尔变元数量
	int ClauseNum;//子句数量
	fgets(cnfname, 5, fp);
	fscanf(fp,"%d %d",&ArguNum,&ClauseNum);
	//成功读入该信息

	root_value->argunum = ArguNum;          //给结果储存数组赋变元数量值
	root_value->tempnum = 0;
	 
	//第三步调用函数生成cnf链式结构                
	Clause* nextclause;            //用于中间生成子句的行即C1,C2
	Argu* nextargu;               //用于中间生成子句的变元 即l11
	root->argu_num = ArguNum;     //储存cnf的变元数
	root->clause_num = ClauseNum;      // 储存cnf的子句数
	int argu;                      //用于读入变元
	int i = 0;

	//开始读入Num行子句
	//子句链表带表头结点，变元链表带表头结点

	nextclause= (Clause*)malloc(sizeof(Clause));  //生成第一个子句开头，C1
	root->first = nextclause;         //给cnf指针    
	nextclause->clause_next = (Clause*)malloc(sizeof(Clause));        //生成子句表头结点
	nextclause = nextclause->clause_next;


	//！！！！！！不考虑读入空子句

	int addnum;    //用来标记变元个数


	//读入除第一行外其他行,共有ClauseNum-1行
	for (i = 0; i < ClauseNum; i++) {    //一行一行读入，每行读入利用循环
		//先生成C1,  C2，C3.......
		addnum = 0;   //计数变量重置为0
		//开始读入这一行第一个变元
		fscanf(fp, "%d", &argu); 
		makeresult(root_value, argu,-1);   //将其信息储存在变元数组中
		nextargu = (Argu*)malloc(sizeof(Argu));                 //子句生成表头结点
		nextclause->next = nextargu;
		nextargu->argu_next = (Argu*)malloc(sizeof(Argu));
		nextargu = nextargu->argu_next;
		nextargu->argu = argu;
		//读入这一行后面变元
		for (fscanf(fp, "%d", &argu); argu != 0;addnum++) {
			makeresult(root_value, argu,-1);   //将其信息储存在变元数组中
			nextargu->argu_next = (Argu*)malloc(sizeof(Argu));
			nextargu = nextargu->argu_next;            //指向后一个变元
			nextargu->argu = argu;
			fscanf(fp, "%d", &argu); 
		}
		nextclause->num = addnum + 1;
		nextargu->argu_next = NULL;  //尾指针置空
		nextclause->clause_next = (Clause*)malloc(sizeof(Clause));
		nextclause = nextclause->clause_next;
	}
	return OK;

}

/***************************
*函数名称：CreatCNF
*函数作用：创建CNF链表,空表
*返回值：返回生成链表的地址
***************************/
CNF* CreatCNF(void)
{
	CNF* cnf;
	cnf = (CNF*)malloc(sizeof(CNF));
	cnf->first = NULL;//置为空
	return cnf;//返回其地址
}

/*******************************
*函数名称：SaveList
*函数作用：将储存结构中的cnf文件输出到log.txt文件中，用以验证
*返回值：成功状态
*******************************/
status SaveList(CNF* root)
{
	FILE* fp;
	if ((fp = fopen("D:/SAT/log.txt", "w")) == NULL)       //将储存结构中内容输出到log.txt
	{
		printf("文件打开失败！\n");
		return  ERROR;
		//文件打开失败，返回ERROR
	}
	fprintf(fp, "%d,%d\n", root->argu_num, root->clause_num);    //输出变元
	Clause* nextclause;
	Argu* nextargu;
	nextclause = root->first->clause_next;        //指向表头后第一行子句
	int i;
	for (i = 0; i < root->clause_num; i++) {
		nextargu = nextclause->next->argu_next;          //指向子句表头后第一个变元
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
*函数名称:FindSingle
*函数作用:找到单子句的那个变元
*输入值:cnf结构的root指针
*返回值:若存在单子句返回该变元，否则返回NULL，默认返回第一个单子句变元
****************************/
int FindSingle(CNF* root)
{
	int i;
	Clause* nextclause;
	nextclause = root->first->clause_next;
	for (i = 0; i < root->clause_num; i++) {
		if (nextclause->num == 1) return nextclause->next->argu_next->argu;    //返回该单子句的变元
		else
			nextclause = nextclause->clause_next;
	}
	return NULL;       //不存在单子句
}


/*********************************
*函数名称：makeresult
*函数作用：用于给result中变元储存出现次数及取值
*输入值：变元名
*输出值：status
************************************/
void makeresult(result *root_value,int argu,int status)
{
	//空出第一个，方便从数组尾搜索
	root_value->value[0].argu = abs(argu);
	//先在数组中搜索是否存在该变元
	int i;        //从数组尾开始查找
	for (i = root_value->tempnum; i >= 0; i--) {
		if (abs(root_value->value[i].argu) == abs(argu)) break;      //查找成功
	}
	
	if (i == 0) {             //该变元未储存在数组上
		root_value->value[root_value->tempnum + 1].argu = abs(argu);     //将该变元储存在数组中
		root_value->value[root_value->tempnum + 1].num = 1;          //将该变元出现频数置为1
		root_value->value[root_value->tempnum + 1].status = -1;  //将该变元取值置为NULL
		root_value->tempnum++;
	}
	else                      //该变元储存在了数组上
	{
		root_value->value[i].num++;   //频数加一
		root_value->value[i].status = status;
	}
}


/***************************
*函数名称：RemoveClause
*函数作用：用于删去所有包含argu的子句，cnf子句数需要减一
*输入值：cnf储存指针，要删除的argu
***************************/
void RemoveClause(CNF* root, int argu)
{
	Clause* nextclause;
	Clause* preclause;
	Clause* tempclause;
	Argu* nextargu;
	Argu* tempargu;    //用于free掉变元

	int i;
	int num;
	num = root->clause_num;
	preclause = root->first;  //指向表头结点
	nextclause = preclause->clause_next;     //指向第一个子句
	for (i = 0; i < num; i++) {

		nextargu = nextclause->next->argu_next;  //指向第一个变元
		for (; nextargu != NULL; nextargu = nextargu->argu_next) {
			if (nextargu->argu == argu) break;
		}
		if (nextargu != NULL) {   //即子句中存在该变元
			for (nextargu = nextclause->next; nextargu != NULL; ) {
				tempargu = nextargu;
				nextargu = nextargu->argu_next;   //指向后一变元
				free(tempargu);    //释放掉变元空间
			}
			root->clause_num--;       //子句数减一
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
*函数名称：RemoveArgu
*函数作用：删除变元
*输入值：CNF指针root，待删除变元
返回值：无
******************************/
void RemoveArgu(CNF* root, int argu)
{
	int i;
	Clause* nextclause;
	Argu* nextargu;
	Argu* tempargu;
	Argu* preargu;
	nextclause = root->first->clause_next;     //指向第一个子句
	preargu = nextclause->next;                     //指向子句表头
	for (i = 0; i < root->clause_num; i++) {
		nextargu = nextclause->next->argu_next;  //指向第一个变元
		for (; nextargu != NULL; ) {                       //存在该变元
			if (nextargu->argu == argu) {
				tempargu = nextargu;
				nextargu = nextargu->argu_next;
				free(tempargu);
				preargu->argu_next = nextargu;
				nextclause->num--;                //变元数减一
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
*函数名称：ISEmptyClause
*函数作用：判断cnf是否存在空子句
*输入值：cnf地址root
*返回值：存在空子句,返回OK，否则返回FALSE
****************************/
status ISEmptyClause(CNF* root)
{
	int i;
	Clause* nextclause;
	nextclause = root->first->clause_next;                       //指向表头结点后第一个子句
	for (i = 0; i < root->clause_num; i++) {
		if (nextclause->num == 0) break;
		nextclause = nextclause->clause_next;
	}
	if (i==root->clause_num) return  FALSE;    //不存在空子句
	else return OK;                                         //存在空子句
}


/*******************************
*函数名称：SortResult
*函数作用：将result中变元按频数排序
*输入值：root_value
*返回值：无
****************************/
void SortResult(result* root_value)
{
	int i, j;

	//为了方便起见，先将变元按频数大小降序排序，排序算法采用冒泡法
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
*函数名称：FindMost
*函数作用：找到变元中未赋值且频数最大的
*输入值：root_value
*返回值：最大变元
**************************/
int FindMost(result* root_value)
{
	int i;
	for (i = 1; i <= root_value->argunum; i++) {
		if (root_value->value[i].status == -1) return root_value->value[i].argu;
	}
}


/************************
*函数名称：AddClause
*函数作用：增加单子句，变元为v
*输入值：cnf指针root，增加子句的变元
*返回值：无
*************************/
CNF* AddClause(CNF* root, int v)
{
	//为了减少时间占用，将子句加在表头结点后
	Clause* nextclause;
	Argu* nextargu;
	nextclause = (Clause*)malloc(sizeof(Clause));      //生成新子句
	nextargu = (Argu*)malloc(sizeof(Argu));       //生成表头结点
	nextargu->argu_next= (Argu*)malloc(sizeof(Argu));    //生成变元结点
	nextargu->argu_next->argu = v;                     //变元赋值
	nextargu->argu_next->argu_next = NULL;        //结尾标志
	nextclause->clause_next = root->first->clause_next;       //放在第一个子句结点前
	nextclause->next = nextargu;
	nextclause->num = 1;
	root->first->clause_next = nextclause;
	root->clause_num++;
	return root;
}

/*******************************
*函数名称：SaveResult
*函数作用：将结果输出到result.txt文件中，用以验证
*返回值：成功状态
*******************************/
status SaveResult(result* root_value)
{
	FILE* fp;
	if ((fp = fopen("D:/SAT/result.txt", "w")) == NULL)       //将储存结构中内容输出到log.txt
	{
		printf("文件打开失败！\n");
		return  ERROR;
		//文件打开失败，返回ERROR
	}
	fprintf(fp, "%d\n", root_value->argunum);    //输出变元个数
	int i;
	for (i = 1; i <=root_value->argunum; i++) {
		fprintf(fp, "%d       %d", root_value->value[i].argu,  root_value->value[i].status);
		fprintf(fp, "\n");
	}
	return OK;
}


/*****************************
*函数名称：CopyRoot
*函数作用：复制cnf
*输入值：root指针
*输出值：新生成的root指针
****************************/
CNF* CopyRoot(CNF* root)
{
	CNF* newroot;   //生成新的root
	newroot= CreatCNF();
	newroot->argu_num = root->argu_num;    //赋基本值
	newroot->clause_num = root->clause_num;

	Clause* nextclause;
	Clause* rootclause;
	Argu* nextargu;
	Argu* rootargu;
	nextclause = (Clause*)malloc(sizeof(Clause));  
	newroot->first = nextclause;         //给cnf指针    
	nextclause->clause_next = (Clause*)malloc(sizeof(Clause));        //生成子句表头结点
	nextclause = nextclause->clause_next;
	rootclause = root->first->clause_next;   //指向root第一个子句
	
	int i;
	for (i = 0; i < root->clause_num; i++) {  
		nextargu = (Argu*)malloc(sizeof(Argu));                 //子句生成表头结点
		nextclause->next = nextargu;
		rootargu = rootclause->next->argu_next;

		for (; rootargu != NULL ;rootargu=rootargu->argu_next) {
			nextargu->argu_next = (Argu*)malloc(sizeof(Argu));
			nextargu = nextargu->argu_next;            //指向后一个变元
			nextargu->argu = rootargu->argu;
		}
		nextclause->num = rootclause->num;
		nextargu->argu_next = NULL;  //尾指针置空
		nextclause->clause_next = (Clause*)malloc(sizeof(Clause));
		nextclause = nextclause->clause_next;
		rootclause = rootclause->clause_next;
	}
	return newroot;
}


/*****************************
*函数名称：CopyResult
*函数作用：复制result
*输入值：root_value
*返回值：new_value
*****************************/
result* CopyResult(result* root_value)
{
	result* new_value;             //变元取值
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
