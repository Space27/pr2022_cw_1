#include <locale.h>
#include <limits.h>
#include "structs.h"
#include "error.h"
#include "user_tips.h"
#include "print.h"
#include "processing.h"

int main()
{
	TextStruct text = makeTextStruct();
	int continueStatus = 1;
	setlocale(LC_ALL, "");

	printMenu(1);
	if (getTextAnswer(&text))
		/* если произошла ошибка при перевыделении памяти */
	{
		crash(text);
		return 1;
	}

	cleanText(&text);
	printText(text);
	while (continueStatus)
		/* пока пользователь не ввёл '0' (завершение программы) */
	{
		printMenu(2);
		switch (getAnswer(L"Выберите действие", OPTION_COUNT))
		{
			case 1:
			{
				moveWordsInText(&text, getAnswer(L"Введите сдвиг слов в предложении", INT_MAX),
						getAnswer(L"Выберите номер предложения (0 - весь текст)", text.sentenceCount));
				printText(text);
				break;
			}
			case 2:
			{
				int *uniq = findUniqueCharacters(text);
				printCharacters(uniq);
				free(uniq);
				break;
			}
			case 3:
			{
				TextStruct wordList = getWordsSameLength(text);
				if (wordList.sentenceCount != -1)
					/* если при заполнении списка слов не произошло ошибки перевыделения памяти */
				{
					printWordSameLength(wordList);
					cleanMemory(wordList);
				}
				else
				{
					crash(wordList);
				}
				break;
			}
			case 4:
			{
				int count = removeWordsWithLastUpperCase(&text);
				printResultsAfterRemoving(count);
				if (text.sentenceCount && count)
				{
					printText(text);
				}
				else if (text.sentenceCount == 0)
				{
					panic(4);
					continueStatus = 0;
				}
				break;
			}
			case 5:
			{
				sortSentencesByEvenWordCount(&text);
				printText(text);
				break;
			}
			case 0:
			{
				continueStatus = 0;
				break;
			}
			default:
				break;
		}
	}
	if (text.sentenceCount)
		/* если под текст была выделена память */
	{
		cleanMemory(text);
	}
	printMenu(3);

	return 0;
}