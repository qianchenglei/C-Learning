#include "danlianbiao.h"
SingleLinkList_Data* SingleLinkList;
int main(){
	srand((unsigned int)time(NULL));
	InitSingleLinkList(&SingleLinkList);
	printf("Welcome to Simplefy Student Manger System\n");
	InitSingleLinkList(&SingleLinkList);
	printf("Welcome to Simplefy Student Manger System\n");
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
			printf("2. Initialize Single Link List\n");
			printf("3. Insist eume into the list\n");
			printf("4. Count Currently List Eume Uint\n");
			printf("5. Looking SingleLinkList By Index\n");
			printf("6. Looking SingleLinkList By Mark\n");
			printf("7. Looking SingleLinkList By Name\n");
			printf("8. Looking SingleLinkList By Gender\n");
			printf("9. NextLever\n");
			break;
		}
		case 2: {
			if (InitSingleLinkList(&SingleLinkList) == true) {
				printf("Initialize Single Link List success\n");
			}
			else
			{
				printf("Initialize Single Link List Faile\n");
			}
			break;
		}
		case 3: {
			Students_Data TempData;
			int index = 0;
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
			printf("please enter Studentindex\n");
			scanf("%d",&index);
			if (AddEumeForTheList(&SingleLinkList,TempData, index) == true) {
				printf("Insite success\n");
			}
			else
			{
				printf("Insite Faile\n");
			}
			break;
		}
		case 4: {
			getchar();
			int Ans_Code=SingleLinkListLength(SingleLinkList);
			if (Ans_Code==-1)
			{
				printf("Currently List was Empty\n");
			}
			else {
				printf("Currently List was has %d Data Base\n", Ans_Code);
			}
			break;
		}
		case 5: {
			getchar();
			int LookingIndex = 0;
			printf("What index of the data base do you want looking for\n");
			scanf("%d", &LookingIndex);
			SingleLinkList_Data data = { 0 };
			int Ans_Code = LookingSingleLinkListByIndex(SingleLinkList,LookingIndex,&data);
			if (Ans_Code == -1)
			{
				printf("Currently List was Empty\n");
			}
			else {
				
				printf("The data base was at %d\n ", Ans_Code);
				printf("StudentsMark: %d\n ", data.Students_Data.StudentsMark);
				printf("StudentsName: %s\n ", data.Students_Data.StudentName);
				if (data.Students_Data.StudentGender == false) {
					printf("StudentsGebder:Manl\n");
				}else
				{
					printf("StudentsGebder:famanl\n");
				}
				printf("StudentsUUID: %d\n ", data.Students_Data.StudentUUID);
			}
			break;
		}
		case 6: {
			getchar();
			int LookingMark = 0;
			printf("What Mark of the data do you want looking for\n");
			scanf("%d", &LookingMark);
			SingleLinkList_Data data = { 0 };
			int Ans_Code = LookingSingleLinkListByMark(SingleLinkList, LookingMark, &data);
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
		case 7: {
			getchar();
			char LookingName[MaxStudentNameSize] = { 0 };
			printf("What Name of the data do you want looking for\n");
			scanf("%49s", &LookingName);
			SingleLinkList_Data data = { 0 };
			int Ans_Code = LookingSingleLinkListByName(SingleLinkList, LookingName, &data);
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
		case 8: {
			getchar();
			bool LookingGender = false;
			int Temp = 0;
			printf("What Gender of the data do you want looking for,0 for man 1 for female\n");
			scanf("%d", &Temp);
			//printf("[DEBUG] 我读到的 Temp = %d\n", Temp);
			if (Temp == 0)
			{
				LookingGender = false;
			}
			else {
				LookingGender = true;
			}
			//printf("[DEBUG] 我读到的 LookingGender = %d\n", LookingGender);
			SingleLinkList_Data data = { 0 };
			int Ans_Code = LookingSingleLinkListByGender(SingleLinkList, LookingGender, &data);
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
		case 9: {
			sub();
		}
		default:
			break;
		}
	}
}