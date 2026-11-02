#include "danlianbiao.h"

void sub() {
	while (1)
	{
		int UserInput;
		printf("Press 1 to look System Memo\n");
		scanf("%d", &UserInput);
		switch (UserInput)
		{
		case 1: {
			printf("System Memo:\n");
			printf("1. Look System Memo\n");
			printf("2. Looking SingleLinkList By UUID\n");
			printf("3. Insist eume into the list by being\n");
			printf("4. Insist eume into the list by Ending\n");
			printf("0. break to main\n");
			break;
		}
		case 2: {
			getchar();
			int UUID = 0;
			printf("What UUID of the data do you want looking for,\n");
			scanf("%d", &UUID);
			SingleLinkList_Data data = { 0 };
			int Ans_Code = LookingSingleLinkListByUUID(SingleLinkList, UUID, &data);
			if (Ans_Code == -1)
			{
				printf("Currently List was Empty\n");
			}
			else {
				SingleLinkList_Data* p = data.NextDataNode;
				while (p != NULL)
				{

					printf("The data base was at %d\n ", Ans_Code);
					printf("StudentsMark: %d\n ", p->Students_Data.StudentsMark);
					printf("StudentsName: %s\n ", p->Students_Data.StudentName);
					if (p->Students_Data.StudentGender == false) {
						printf("StudentGender:Manl\n");
					}
					else
					{
						printf("StudentGender:famanl\n");
					}
					printf("StudentsUUID: %d\n ", p->Students_Data.StudentUUID);
					p = p->NextDataNode;
				}
			}
			break;
		}
		case 3: {
			Students_Data TempData;
			printf("please enter StudentsMark\n");
			scanf("%d", &TempData.StudentsMark);
			getchar();
			printf("please enter StudentName\n");
			scanf("%49s", TempData.StudentName);
			getchar();
			printf("please enter StudentGender 0 for man 1 for female\n");
			scanf("%d", &TempData.StudentGender);
			getchar();
			TempData.StudentUUID = GenerateUID();
			if (LookingSingleInsertForTheListBeing(&SingleLinkList, TempData) == 0)
			{
				printf("Insert For Beging success\n");
			}
			else {
				printf("Insert For Beging Failt see detial in log\n");
			}
			break;
		}
		case 4: {
			Students_Data TempData;
			printf("please enter StudentsMark\n");
			scanf("%d", &TempData.StudentsMark);
			getchar();
			printf("please enter StudentName\n");
			scanf("%49s", TempData.StudentName);
			getchar();
			printf("please enter StudentGender 0 for man 1 for female\n");
			scanf("%d", &TempData.StudentGender);
			getchar();
			TempData.StudentUUID = GenerateUID();
			if (LookingSingleInsertForTheListEding(&SingleLinkList, TempData) == 0)
			{
				printf("Insert For Ending success\n");
			}
			else {
				printf("Insert For Ending Failt see detial in log\n");
			}
			break;
		}
		case 0: {
			return;
		}
		default:
			break;
		}
	}
}

long long GenerateUID() {
	// 当前时间戳（秒）× 10000 + 随机数（0~9999）
	long long uid = (long long)time(NULL) * 10000 + rand() % 10000;
	return uid;
}

bool InitSingleLinkList(SingleLinkList_Data** List) {
	*List = (SingleLinkList_Data*)calloc(1, sizeof(SingleLinkList_Data));
	if (*List == NULL) {
		return false;
	}
	/*(*List)->Students_Data.StudentGender =  0 ;
	(*List)->Students_Data.StudentsMark =  0 ;
	(*List)->Students_Data.StudentUUID =  0 ;
	(*List)->SingleLinkListLength = 0;
	(*List)->NextDataNode = NULL;*/
	memset(*List, 0, sizeof(SingleLinkList_Data));
	(*List)->NextDataNode = NULL;
	(*List)->EndDataNode = NULL;
	return true;
}

bool AddEumeForTheList(SingleLinkList_Data** List, Students_Data Students_Data, int Index) {
	if (List == NULL || Index < 1)
	{
		return false;
	}
	SingleLinkList_Data* NewPrintPosition = *List;
	for (int Count = 0; Count < Index - 1; Count++)
	{
		if (NewPrintPosition->NextDataNode == NULL)
		{
			return false;
		}
		NewPrintPosition = NewPrintPosition->NextDataNode;
	}
	SingleLinkList_Data* AddDataEume = (SingleLinkList_Data*)calloc(1, sizeof(SingleLinkList_Data));
	if (AddDataEume == NULL) {
		return false;
	}
	AddDataEume->Students_Data = Students_Data;
	AddDataEume->NextDataNode = NewPrintPosition->NextDataNode;
	NewPrintPosition->NextDataNode = AddDataEume;
	return true;
}

int SingleLinkListLength(SingleLinkList_Data* List)
{
	if (List == NULL) {
		return -1;
	}
	//printf("DEBUG: Head Node Next is at address: %p\n", List->NextDataNode);
	int Count = 0;
	SingleLinkList_Data* NewPrintPosition = List;
	while (NewPrintPosition->NextDataNode != NULL)
	{
		NewPrintPosition = NewPrintPosition->NextDataNode;
		Count++;
	}
	return Count;
}

int LookingSingleLinkListByIndex(SingleLinkList_Data* List, int Index, SingleLinkList_Data* BackData)
{
	int Count = 0;
	int CurrentIndex = 1;
	SingleLinkList_Data* NextPrintPosition = List->NextDataNode;
	if (List->NextDataNode == NULL)
	{
		return -1;
	}
	else {
		while (NextPrintPosition->NextDataNode != NULL && CurrentIndex < Index)
		{
			CurrentIndex++;
			NextPrintPosition = NextPrintPosition->NextDataNode;
			Count++;
		}
	}
	if (NextPrintPosition == NULL)
	{
		return -1;
	}
	BackData->Students_Data = NextPrintPosition->Students_Data;
	return Count;
}

int LookingSingleLinkListByMark(SingleLinkList_Data* List, int Mark, SingleLinkList_Data* BackData)
{
	int Count = 0;
	SingleLinkList_Data* NextPrintPosition = List;
	if (List->NextDataNode == NULL)
	{
		return -1;
	}
	else {
		while (NextPrintPosition != NULL)
		{
			if (NextPrintPosition->Students_Data.StudentsMark == Mark)
			{
				Count += 1;
				AddEumeForTheList(&BackData, NextPrintPosition->Students_Data, Count);
			}
			NextPrintPosition = NextPrintPosition->NextDataNode;
		}

		return Count;
	}

}

int LookingSingleLinkListByName(SingleLinkList_Data* List, char Name[MaxStudentNameSize], SingleLinkList_Data* BackData)
{
	int Count = 0;
	SingleLinkList_Data* NextPrintPosition = List;
	if (List->NextDataNode == NULL)
	{
		return -1;
	}
	else {
		while (NextPrintPosition != NULL)
		{
			if (strcmp(NextPrintPosition->Students_Data.StudentName, Name) == 0)
			{
				Count += 1;
				AddEumeForTheList(&BackData, NextPrintPosition->Students_Data, Count);
			}
			NextPrintPosition = NextPrintPosition->NextDataNode;
		}

		return Count;
	}
}

int LookingSingleLinkListByGender(SingleLinkList_Data* List, bool Gender, SingleLinkList_Data* BackData)
{
	int Count = 0;
	SingleLinkList_Data* NextPrintPosition = List->NextDataNode;
	if (List->NextDataNode == NULL)
	{
		return -1;
	}
	else {
		while (NextPrintPosition != NULL)
		{
			//printf("[DEBUG] 节点性别值 = %d, 查找值 = %d\n",
				//NextPrintPosition->Students_Data.StudentGender, Gender);
			if (NextPrintPosition->Students_Data.StudentGender == Gender)
			{
				Count += 1;
				AddEumeForTheList(&BackData, NextPrintPosition->Students_Data, Count);
			}
			NextPrintPosition = NextPrintPosition->NextDataNode;
		}

		return Count;
	}
}

int LookingSingleLinkListByUUID(SingleLinkList_Data* List, int uuid, SingleLinkList_Data* BackData)
{
	int Count = 0;
	SingleLinkList_Data* NextPrintPosition = List;
	if (List->NextDataNode == NULL)
	{
		return -1;
	}
	else {
		while (NextPrintPosition != NULL)
		{
			if (NextPrintPosition->Students_Data.StudentUUID == uuid)
			{
				Count += 1;
				AddEumeForTheList(&BackData, NextPrintPosition->Students_Data, Count);
			}
			NextPrintPosition = NextPrintPosition->NextDataNode;
		}

		return Count;
	}
}

int LookingSingleInsertForTheListBeing(SingleLinkList_Data** List, Students_Data StudentsData)
{
	SingleLinkList_Data* InsertData = { 0 };
	InsertData = (SingleLinkList_Data*)malloc(sizeof(SingleLinkList_Data));
	InsertData->Students_Data = StudentsData;
	InsertData->NextDataNode = (*List)->NextDataNode;
	(*List)->NextDataNode = InsertData;
	return 0;
}

int LookingSingleInsertForTheListEding(SingleLinkList_Data** List, Students_Data StudentsData)
{
	SingleLinkList_Data* InsertData = { 0 };
	InsertData = (SingleLinkList_Data*)malloc(sizeof(SingleLinkList_Data));
	InsertData->Students_Data = StudentsData;
	InsertData->NextDataNode = NULL;
	(*List)->EndDataNode = InsertData;
	if ((*List)->EndDataNode == NULL) {
		(*List)->NextDataNode = InsertData;
	}
	else {
		(*List)->EndDataNode->NextDataNode = InsertData;
	}

	(*List)->EndDataNode = InsertData;

	return 0;
}

Students_Data DeleteSingleInsertDataUnit(SingleLinkList_Data** List, int Index)
{
	SingleLinkList_Data* ForwardData = (*List);
	for (int count = 0; count < Index - 1; count++)
	{
		ForwardData = (*List)->NextDataNode;
	}
	SingleLinkList_Data* DeleteNode = ForwardData->NextDataNode;
	ForwardData->NextDataNode = DeleteNode->NextDataNode;
	free(DeleteNode);
	DeleteNode = NULL;
	// 如果要删的就是尾节点，删完后要把 EndDataNode 回退到新的尾节点
	if ((*List)->EndDataNode == DeleteNode) {
		(*List)->EndDataNode = ForwardData;  // 尾节点回退到前驱
	}
	return ;
}
