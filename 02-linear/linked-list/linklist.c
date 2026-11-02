#include "linklist.h"

void EnableANSI()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= 0x0004;  // ENABLE_VIRTUAL_TERMINAL_PROCESSING
	SetConsoleMode(hOut, dwMode);
}
int InitLinkList(LinkList** List,int ListType) {
	if (List == NULL)
	{	
		return 201;
	}
	else
	{	
		switch (ListType)
		{
		case LIST_SINGLE: {
			(*List) = (LinkList*)calloc(1, sizeof(**List));
			(*List)->NextDataUnitAdd = NULL;
			(*List)->NowListType = LIST_SINGLE;
			return 0;
		}
		case LIST_DOUBLE:{
			(*List) = (LinkList*)calloc(1, sizeof(**List));
			(*List)->NextDataUnitAdd = NULL;
			(*List)->PrimaryDataUnitAdd = NULL;
			(*List)->NowListType = LIST_DOUBLE;
			return 0;
		}case LIST_CIRC_SINGLE: {
			(*List) = (LinkList*)calloc(1, sizeof(**List));
			(*List)->NextDataUnitAdd = *List;
			(*List)->NowListType = LIST_CIRC_SINGLE;
			return 0;
		}
		case LIST_CIRC_DOUBLE: {
			(*List) = (LinkList*)calloc(1, sizeof(**List));
			(*List)->NextDataUnitAdd = *List;
			(*List)->PrimaryDataUnitAdd = *List;
			(*List)->NowListType = LIST_CIRC_DOUBLE;
			return 0;
		}
		default:
			break;
		}
	}
	return 202;
}
uint64_t GenarateUUID()
{
	time_t raw_time = time(NULL);
	return (UUID_MAKER_CODE << 24) | ((uint64_t)raw_time & 0xFFFFFFULL);
}
int InsertAt(LinkList* List, int index, Students_Data TempData)
{
	switch (List->NowListType)
	{
	case LIST_SINGLE: {
		int returecode = 0;
		returecode = IEILASub_Single(List, TempData, index);
		if (returecode ==201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode==202) {
			printf("The manren was fill");
		}
		else if(returecode==203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_DOUBLE: {
		int returecode = 0;
		returecode = IEILASub_DOUBLE(List, TempData, index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_CIRC_SINGLE: {
		int returecode = 0;
		returecode = IEILASub_cyc_Single(List, TempData, index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_CIRC_DOUBLE: {
		int returecode = 0;
		returecode = IEILASub_cyc_DOUBLE(List, TempData, index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{	
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	default:
		break;
	}
	return 0;
}
int IEILASub_Single(LinkList* List, Students_Data TempData,int index) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* CDataUnit = List;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	for (int i = 0; i < index; i++)
	{
		CDataUnit = CDataUnit->NextDataUnitAdd;
		if (CDataUnit == NULL) {
			free(InsertDataUnit); 
			return 203; 
		}
	}
	InsertDataUnit->NextDataUnitAdd = CDataUnit->NextDataUnitAdd;
	CDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEILASub_DOUBLE(LinkList* List, Students_Data TempData, int index)
{
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* PreDataUnit = List;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1,sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	for (int i = 0; i < index; i++)
	{
		PreDataUnit = PreDataUnit->NextDataUnitAdd;
		if (PreDataUnit==NULL)
		{
			free(InsertDataUnit);
			return 203;
		}
	}
	InsertDataUnit->NextDataUnitAdd = PreDataUnit->NextDataUnitAdd;
	if (PreDataUnit->NextDataUnitAdd != NULL)
	{
		PreDataUnit->NextDataUnitAdd->PrimaryDataUnitAdd = InsertDataUnit;
	}
	InsertDataUnit->PrimaryDataUnitAdd = PreDataUnit;
	PreDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEILASub_cyc_Single(LinkList* List, Students_Data TempData, int index)
{
	if (List == NULL)
	{
		return 201;
	}

	struct LinkListData* CDataUnit = List;
	struct LinkListData* FirstDataUnit = CDataUnit;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	for (int i = 0; i < index; i++)
	{
		CDataUnit = CDataUnit->NextDataUnitAdd;
		if (CDataUnit == FirstDataUnit)  // 绕了一圈回到起点
		{
			free(InsertDataUnit);
			return 203;
		}
	}
	InsertDataUnit->NextDataUnitAdd = CDataUnit->NextDataUnitAdd;
	CDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEILASub_cyc_DOUBLE(LinkList* List, Students_Data TempData, int index)
{
	if (List==NULL)
	{
		return 201;
	}
	struct LinkListData* PreDataUnit = List;
	struct LinkListData* FirstDataUnit = PreDataUnit;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1,sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	for (int i = 0; i < index; i++)
	{
		PreDataUnit = PreDataUnit->NextDataUnitAdd;
		if (PreDataUnit == FirstDataUnit)
		{
			free(InsertDataUnit);
			return 203;
		}
	}
	InsertDataUnit->NextDataUnitAdd = PreDataUnit->NextDataUnitAdd;
	InsertDataUnit->PrimaryDataUnitAdd = PreDataUnit;
	PreDataUnit->NextDataUnitAdd->PrimaryDataUnitAdd = InsertDataUnit;
	PreDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int InsertEumeIntotheListByHand(LinkList* List, Students_Data TempData) {
	switch (List->NowListType)
	{
	case LIST_SINGLE: {
		int returecode = 0;
		returecode = IEITLBHSub_SingleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_DOUBLE: {
		int returecode = 0;
		returecode = IEITLBHSub_DoubleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_CIRC_SINGLE: {
		int returecode = 0;
		returecode = IEITLBHSub_Cyc_SingleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_CIRC_DOUBLE: {
		int returecode = 0;
		returecode = IEITLBHSub_Cyc_DoubleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	default:
		break;
	}
	return 0;
}
int IEITLBHSub_SingleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	InsertDataUnit->NextDataUnitAdd = List->NextDataUnitAdd;
	List->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEITLBHSub_DoubleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	InsertDataUnit->NextDataUnitAdd = List->NextDataUnitAdd;
	InsertDataUnit->PrimaryDataUnitAdd = List;
	if (List->NextDataUnitAdd != NULL)
	{
		List->NextDataUnitAdd->PrimaryDataUnitAdd = InsertDataUnit;
	}
	List->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEITLBHSub_Cyc_SingleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}

	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	InsertDataUnit->NextDataUnitAdd = List->NextDataUnitAdd;
	List->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEITLBHSub_Cyc_DoubleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	if (List->NextDataUnitAdd==List)
	{
		InsertDataUnit->NextDataUnitAdd = List;
		InsertDataUnit->PrimaryDataUnitAdd = List;
		List->NextDataUnitAdd = InsertDataUnit;
		List->PrimaryDataUnitAdd = InsertDataUnit;
	}
	else {
		struct LinkListData* FirstDataUnit = List->NextDataUnitAdd;
		InsertDataUnit->PrimaryDataUnitAdd = List;
		InsertDataUnit->NextDataUnitAdd = FirstDataUnit;
		FirstDataUnit->PrimaryDataUnitAdd = InsertDataUnit;
		List->NextDataUnitAdd = InsertDataUnit;
	}
	return 0;
}
int InsertEumeIntotheListByEnd(LinkList* List, Students_Data TempData) {
	switch (List->NowListType)
	{
	case LIST_SINGLE: {
		int returecode = 0;
		returecode = IEITLBESub_SingleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_DOUBLE: {
		int returecode = 0;
		returecode = IEITLBESub_DoubleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_CIRC_SINGLE: {
		int returecode = 0;
		returecode = IEITLBESub_Cyc_SingleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	case LIST_CIRC_DOUBLE: {
		int returecode = 0;
		returecode = IEITLBESub_Cyc_DoubleLinkList(List, TempData);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Insert Success ");
		}
		break;
	}
	default:
		break;
	}
	return 0;
}
int IEITLBESub_SingleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* CurrentDataUnit = List;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	while (CurrentDataUnit->NextDataUnitAdd != NULL)
	{
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	InsertDataUnit->NextDataUnitAdd = NULL;
	CurrentDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEITLBESub_DoubleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* CurrentDataUnit = List;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	while (CurrentDataUnit->NextDataUnitAdd != NULL)
	{
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	InsertDataUnit->NextDataUnitAdd = NULL;
	InsertDataUnit->PrimaryDataUnitAdd = CurrentDataUnit;
	CurrentDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEITLBESub_Cyc_SingleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* CurrentDataUnit = List;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	while (CurrentDataUnit->NextDataUnitAdd != List)
	{
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	InsertDataUnit->NextDataUnitAdd = List;
	CurrentDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int IEITLBESub_Cyc_DoubleLinkList(LinkList* List, Students_Data TempData) {
	if (List == NULL)
	{
		return 201;
	}
	struct LinkListData* CurrentDataUnit = List->PrimaryDataUnitAdd;
	struct LinkListData* InsertDataUnit = (struct LinkListData*)calloc(1, sizeof(struct LinkListData));
	if (InsertDataUnit == NULL)
	{
		return 202;
	}
	InsertDataUnit->StudentsData = TempData;
	InsertDataUnit->NextDataUnitAdd = List;
	InsertDataUnit->PrimaryDataUnitAdd = CurrentDataUnit;
	List->PrimaryDataUnitAdd = InsertDataUnit;
	CurrentDataUnit->NextDataUnitAdd = InsertDataUnit;
	return 0;
}
int DeleteDataUnit(LinkList* List, Students_Data* BackData, int index)
{
	switch (List->NowListType)
	{
	case LIST_SINGLE: {
		int returecode = 0;
		returecode = DDUSub_BySingle(List, BackData,index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Delete Success ");
		}
		break;
	}
	case LIST_DOUBLE: {
		int returecode = 0;
		returecode = DDUSub_ByDouble(List, BackData, index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Delete Success ");
		}
		break;
	}
	case LIST_CIRC_SINGLE: {
		int returecode = 0;
		returecode = DDUSub_By_Cyc_Single(List, BackData, index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Delete Success ");
		}
		break;
	}
	case LIST_CIRC_DOUBLE: {
		int returecode = 0;
		returecode = DDUSub_By_Cyc_Double(List, BackData, index);
		if (returecode == 201)
		{
			printf("The list was uninitialize");
		}
		else if (returecode == 202) {
			printf("The manren was fill");
		}
		else if (returecode == 203)
		{
			printf("The input index was Invalid ");
		}
		else
		{
			printf("Delete Success ");
		}
		break;
	}
	default:
		break;
	}
	return 0;
}
int DDUSub_BySingle(LinkList* List, Students_Data* BackData, int index)
{
	if (List == NULL)
	{
		return 201;
	}
	if (BackData == NULL)
	{
		return 204;
	}
	struct LinkListData* CurrentDataUnit = List;

	for (int i = 0; i < index; i++)
	{
		if (CurrentDataUnit->NextDataUnitAdd == NULL)
		{
			return 205;
		}
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	if (CurrentDataUnit->NextDataUnitAdd == NULL)
	{
		return 205;
	}
	struct LinkListData* DeleteDataUnit = CurrentDataUnit->NextDataUnitAdd;
	(*BackData) = DeleteDataUnit->StudentsData;
	CurrentDataUnit->NextDataUnitAdd = DeleteDataUnit->NextDataUnitAdd;
	free(DeleteDataUnit);
	return 0;
}
int DDUSub_ByDouble(LinkList* List, Students_Data* BackData, int index)
{
	if (List == NULL)
	{
		return 201;
	}
	if (BackData == NULL)
	{
		return 204;
	}
	struct LinkListData* CurrentDataUnit = List;

	for (int i = 0; i < index; i++)
	{
		if (CurrentDataUnit->NextDataUnitAdd == NULL)
		{
			return 205;
		}
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	if (CurrentDataUnit->NextDataUnitAdd == NULL)
	{
		return 205;
	}
	struct LinkListData* DeleteDataUnit = CurrentDataUnit->NextDataUnitAdd;
	(*BackData) = DeleteDataUnit->StudentsData;
	CurrentDataUnit->NextDataUnitAdd = DeleteDataUnit->NextDataUnitAdd;
	if (DeleteDataUnit->NextDataUnitAdd != NULL){
	DeleteDataUnit->NextDataUnitAdd->PrimaryDataUnitAdd = CurrentDataUnit;
	}
	free(DeleteDataUnit);
	return 0;
}
int DDUSub_By_Cyc_Single(LinkList* List, Students_Data* BackData, int index)
{
	if (List == NULL)
	{
		return 201;
	}
	if (BackData == NULL)
	{
		return 204;
	}
	struct LinkListData* CurrentDataUnit = List;
	struct LinkListData* FristDataUnit = List->NextDataUnitAdd;
	for (int i = 0; i < index; i++)
	{
		if (CurrentDataUnit->NextDataUnitAdd == FristDataUnit)
		{
			return 205;
		}
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	struct LinkListData* DeleteDataUnit = CurrentDataUnit->NextDataUnitAdd;
	(*BackData) = DeleteDataUnit->StudentsData;
	CurrentDataUnit->NextDataUnitAdd = DeleteDataUnit->NextDataUnitAdd;
	free(DeleteDataUnit);
	return 0;
}
int DDUSub_By_Cyc_Double(LinkList* List, Students_Data* BackData, int index)
{
	if (List == NULL)
	{
		return 201;
	}
	if (BackData == NULL)
	{
		return 204;
	}
	struct LinkListData* CurrentDataUnit = List;
	struct LinkListData* FristDataUnit = List->NextDataUnitAdd;
	for (int i = 0; i < index; i++)
	{
		if (CurrentDataUnit->NextDataUnitAdd == FristDataUnit)
		{
			return 205;
		}
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
	struct LinkListData* DeleteDataUnit = CurrentDataUnit->NextDataUnitAdd;
	(*BackData) = DeleteDataUnit->StudentsData;
	CurrentDataUnit->NextDataUnitAdd = DeleteDataUnit->NextDataUnitAdd;
	DeleteDataUnit->NextDataUnitAdd->PrimaryDataUnitAdd = CurrentDataUnit;
	if (DeleteDataUnit->NextDataUnitAdd == List)
	{
		List->PrimaryDataUnitAdd = CurrentDataUnit;
	}
	free(DeleteDataUnit);
	return 0;
}
int PrintAllList(LinkList* List) {
	struct LinkListData* CurrentDataUnit = List->NextDataUnitAdd;
	LinkList* tailMarker = (List->NowListType == LIST_CIRC_SINGLE ||List->NowListType == LIST_CIRC_DOUBLE) ? List : NULL;
	int index = 1;
	while (CurrentDataUnit != tailMarker)
	{
		PrintStudents_Date(CurrentDataUnit->StudentsData, index);
		index++;
		CurrentDataUnit = CurrentDataUnit->NextDataUnitAdd;
	}
}
int PrintStudents_Date(Students_Data TempData, int index) {

	printf("This %d Student\n", index);
	printf("StudentsMark：%d\n", TempData.StudentsMark);
	printf("StudentName：%50s\n", TempData.StudentName);
	printf("StudentGender: %s\n", TempData.StudentGender ? "Male" : "Female");
	printf("StudentUUID：%" PRIu64 "\n", TempData.StudentUUID);
	return 0;
}
// ==================== 查找功能 ====================

// 单链表查找子函数
int SearchSub_Single(LinkList* List, int SearchField, const void* SearchValue)
{
	if (List == NULL) return 201;
	if (SearchValue == NULL) return 204;

	LinkList* p = List->NextDataUnitAdd;
	int count = 0;
	int index = 1;   // 与打印索引一致

	while (p != NULL)
	{
		int match = 0;
		switch (SearchField)
		{
		case SEARCH_BY_UUID:
			match = (p->StudentsData.StudentUUID == *(const uint64_t*)SearchValue);
			break;
		case SEARCH_BY_NAME:
			match = (strcmp(p->StudentsData.StudentName, (const char*)SearchValue) == 0);
			break;
		case SEARCH_BY_GENDER:
			match = (p->StudentsData.StudentGender == *(const bool*)SearchValue);
			break;
		default:
			return 206;   // 未知查找字段
		}

		if (match)
		{
			PrintStudents_Date(p->StudentsData, index);
			count++;
		}

		p = p->NextDataUnitAdd;
		index++;
	}
	return count;
}

// 双链表查找子函数
int SearchSub_Double(LinkList* List, int SearchField, const void* SearchValue)
{
	if (List == NULL) return 201;
	if (SearchValue == NULL) return 204;

	LinkList* p = List->NextDataUnitAdd;
	int count = 0;
	int index = 1;

	while (p != NULL)
	{
		int match = 0;
		switch (SearchField)
		{
		case SEARCH_BY_UUID:
			match = (p->StudentsData.StudentUUID == *(const uint64_t*)SearchValue);
			break;
		case SEARCH_BY_NAME:
			match = (strcmp(p->StudentsData.StudentName, (const char*)SearchValue) == 0);
			break;
		case SEARCH_BY_GENDER:
			match = (p->StudentsData.StudentGender == *(const bool*)SearchValue);
			break;
		default:
			return 206;
		}

		if (match)
		{
			PrintStudents_Date(p->StudentsData, index);
			count++;
		}

		p = p->NextDataUnitAdd;
		index++;
	}
	return count;
}

// 循环单链表查找子函数
int SearchSub_CycSingle(LinkList* List, int SearchField, const void* SearchValue)
{
	if (List == NULL) return 201;
	if (SearchValue == NULL) return 204;

	LinkList* p = List->NextDataUnitAdd;
	LinkList* tailMarker = List;
	int count = 0;
	int index = 1;

	while (p != tailMarker)
	{
		int match = 0;
		switch (SearchField)
		{
		case SEARCH_BY_UUID:
			match = (p->StudentsData.StudentUUID == *(const uint64_t*)SearchValue);
			break;
		case SEARCH_BY_NAME:
			match = (strcmp(p->StudentsData.StudentName, (const char*)SearchValue) == 0);
			break;
		case SEARCH_BY_GENDER:
			match = (p->StudentsData.StudentGender == *(const bool*)SearchValue);
			break;
		default:
			return 206;
		}

		if (match)
		{
			PrintStudents_Date(p->StudentsData, index);
			count++;
		}

		p = p->NextDataUnitAdd;
		index++;
	}
	return count;
}

// 循环双链表查找子函数
int SearchSub_CycDouble(LinkList* List, int SearchField, const void* SearchValue)
{
	if (List == NULL) return 201;
	if (SearchValue == NULL) return 204;

	LinkList* p = List->NextDataUnitAdd;
	LinkList* tailMarker = List;
	int count = 0;
	int index = 1;

	while (p != tailMarker)
	{
		int match = 0;
		switch (SearchField)
		{
		case SEARCH_BY_UUID:
			match = (p->StudentsData.StudentUUID == *(const uint64_t*)SearchValue);
			break;
		case SEARCH_BY_NAME:
			match = (strcmp(p->StudentsData.StudentName, (const char*)SearchValue) == 0);
			break;
		case SEARCH_BY_GENDER:
			match = (p->StudentsData.StudentGender == *(const bool*)SearchValue);
			break;
		default:
			return 206;
		}

		if (match)
		{
			PrintStudents_Date(p->StudentsData, index);
			count++;
		}

		p = p->NextDataUnitAdd;
		index++;
	}
	return count;
}

// 统一查找分发函数
int SearchDataUnit(LinkList* List, int SearchField, const void* SearchValue)
{
	if (List == NULL)
	{
		printf("The list was uninitialize");
		return 0;
	}

	int returecode = 0;
	switch (List->NowListType)
	{
	case LIST_SINGLE:
		returecode = SearchSub_Single(List, SearchField, SearchValue);
		break;
	case LIST_DOUBLE:
		returecode = SearchSub_Double(List, SearchField, SearchValue);
		break;
	case LIST_CIRC_SINGLE:
		returecode = SearchSub_CycSingle(List, SearchField, SearchValue);
		break;
	case LIST_CIRC_DOUBLE:
		returecode = SearchSub_CycDouble(List, SearchField, SearchValue);
		break;
	default:
		returecode = 206;
		break;
	}

	// 输出结果
	if (returecode == 201)
		printf("The list was uninitialize");
	else if (returecode == 204)
		printf("The input parameter was invalid");
	else if (returecode == 206)
		printf("The search field is invalid");
	else if (returecode == 0)
		printf("No matching student found");
	else
		printf("Found %d student(s)", returecode);

	return 0;
}