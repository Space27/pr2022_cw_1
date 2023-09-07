#include "error.h"

void panic(int errorId)
{
	switch (errorId)
	{
		case 1:
			wprintf(L"%ls\n", INPUT_ERROR_MESSAGE);
			break;
		case 2:
			wprintf(L"%ls\n", MEMORY_ALLOCATION_ERROR_MESSAGE);
			break;
		case 3:
			wprintf(L"%ls\n", EMPTY_TEXT_ERROR_MESSAGE);
			break;
		case 4:
			wprintf(L"%ls\n", EMPTY_TEXT_MESSAGE);
			break;
		default:
			break; /* код ошибки не был найден */
	}
}

void crash(TextStruct text)
{
	cleanMemory(text);
	panic(2);
}