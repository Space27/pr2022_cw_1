#include "user_tips.h"

void printMenu(int menuType)
{
	switch (menuType)
	{
		case 1:
			wprintf(L"%ls\n", START_TIP);
			break;
		case 2:
			wprintf(L"\n%ls\n%ls\n%ls\n%ls\n%ls\n%ls\n%ls\n", DESCRIPTION, FIRST_OPTION, SECOND_OPTION, THIRD_OPTION,
					FOURTH_OPTION, FIFTH_OPTION, EXIT_OPTION);
			break;
		case 3:
			wprintf(L"%ls", EXIT_MESSAGE);
			break;
		default:
			break; /* тип меню не был найден */
	}
}

int getAnswer(const wchar_t *question, int maxNumber)
{
	int answer;

	wprintf(L"%ls:", question);
	answer = checkInput(); /* безопасный ввод */
	while (answer > maxNumber || answer < 0)
		/* пока число не лежит в допустимом диапазоне */
	{
		panic(1);
		wprintf(L"%ls:", question);
		answer = checkInput();
	}

	return answer;
}

int getTextAnswer(TextStruct *text)
{
	int option = getText(text);

	while (option)
		/* пока текст незаполненный (пустой(1) или с ошибкой(2)) */
	{
		if (option == 2)
			/* ошибка перевыделения памяти */
		{
			return 1;
		}
		panic(3);
		option = getText(text);
	}

	return 0;
}