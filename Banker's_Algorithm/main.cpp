#define _CRT_SECURE_NO_WARNINGS 1
#include"Menu.h"


int main()
{
	Resources R;

	while (1)
	{
		switch (menu_select())
		{
		case 1:
			Init(R);
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			std::cout << "\t\tÏµÍ³ÍË³ö!" << std::endl;
			system("pause");
			exit(0);
		}
	}

	return 0;
}