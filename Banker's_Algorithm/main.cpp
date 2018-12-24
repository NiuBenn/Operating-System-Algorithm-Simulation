#define _CRT_SECURE_NO_WARNINGS 1
#include"Menu.h"


int main()
{
	Resources R;

	while (1)
	{
		system("cls");
		switch (menu_select())
		{
		case 1:
			Init(R);
			break;
		case 2:
			PrintResources(R);
			break;
		case 3:
			Banker(R);
			break;
		case 0:
			std::cout << "\t\tÏµÍ³ÍË³ö!" << std::endl;
			system("pause");
			exit(0);
		}
	}

	return 0;
}