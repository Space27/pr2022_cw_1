#include "print.h"

void printText(TextStruct text)
{
	wprintf(L"\t\tТЕКУЩИЙ ТЕКСТ\n");
	for (int i = 0; i < text.sentenceCount; i++)
	{
		wprintf(L"%-2d: %ls.\n", i + 1, text.sentenceArray[i].content);
	}
}

void printCharacters(const int *characters)
{
	int count = 0;

	wprintf(L"\nУникальные латинские символы:");
	for (int i = 0; i < LATIN_ONE_CASE_CHAR_COUNT * 2; i++)
		/* перебор всех элементов массива, отведенных под латинские символы */
	{
		if (characters[i])
			/* если значение элемента массива не равно 0 */
		{
			count++;
			wprintf(L" %lc", characters[i]);
		}
	}
	if (!count)
		/* не было встречено ни одного латинского символа */
	{
		wprintf(L" отсутствуют");
	}
	count = 0;
	wprintf(L"\nУникальные кириллические символы:");
	for (int i = LATIN_ONE_CASE_CHAR_COUNT * 2; i < CHAR_COUNT; i++)
		/* перебор всех элементов массива, отведенных под кириллические символы */
	{
		if (characters[i])
			/* если значение элемента массива не равно 0 */
		{
			count++;
			wprintf(L" %lc", characters[i]);
		}
	}
	if (!count)
		/* не было встречено ни одного кириллического символа */
	{
		wprintf(L" отсутствуют");
	}
	wprintf(L"\n");
}

wchar_t endOfWord(int number)
{
	if (number % 100 < 5 || number % 100 > 20)
	{
		if (number % 10 == 1)
		{
			return L'о';
		}
		else if (number % 10 >= 2 && number % 10 <= 4)
		{
			return L'а';
		}
	}

	return L' ';
}

void printResultsAfterRemoving(int count)
{
	wprintf(L"\n");
	if (count)
	{
		wprintf(L"В тексте было удалено %d слов%lc\n", count, endOfWord(count));
	}
	else
	{
		wprintf(L"В тексте не оказалось слов, оканчивающихся на заглавную букву.\n");
	}
}

void printWordSameLength(TextStruct wordList)
{
	wprintf(L"\n");
	for (int i = 0; i < wordList.sentenceCount; i++)
	{
		if (wordList.sentenceArray[i].wordCount)
			/* если в строке есть слова */
		{
			if (endOfWord(wordList.sentenceArray[i].wordCount) == L' ')
			{
				wprintf(L"С длиной %-2d в тексте %-2d слов  (%ls)\n", i + 1,
						wordList.sentenceArray[i].wordCount, wordList.sentenceArray[i].content);
			}
			else
			{
				wprintf(L"С длиной %-2d в тексте %-2d слов%lc (%ls)\n", i + 1, wordList.sentenceArray[i].wordCount,
						endOfWord(wordList.sentenceArray[i].wordCount), wordList.sentenceArray[i].content);
			}
		}
	}
}