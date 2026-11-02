#include "linklist.h"

LinkList* DefaltLinkList;
int StatusCode;
int main() {
	EnableANSI();
	while (1)
	{
		system("cls");
		if (MainMenu()==true) {
			return 0;
		}
	}
}