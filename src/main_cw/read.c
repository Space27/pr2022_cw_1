#include "read.h"

int getWordCount(SentStruct sent)
{
	int wordCount = 0;

	if (!isSeparator(sent.content[0]) && sent.content[0] != L'\0')
		/* первый символ - начало слова и не конец строки */
	{
		wordCount++;
	}
	for (int i = 0; i < sent.length - 1; i++)
	{
		if (isSeparator(sent.content[i]) && !isSeparator(sent.content[i + 1]))
			/* текущий символ разделительный, следующий - нет, то есть дальше начинается слово */
		{
			wordCount++;
		}
	}

	return wordCount;
}

int getSentence(SentStruct *newSent)
{
	int sentenceCapacity = SENTENCE_BUF_SIZE;
	wchar_t character = getwchar();

	while (character != L'\n' && character != L'.')
	{
		if (newSent->length == sentenceCapacity - 1)
		{
			sentenceCapacity += SENTENCE_BUF_SIZE;
			if (reallocateMemory((void **) &newSent->content, sentenceCapacity * sizeof(wchar_t)))
				/* произошла ошибка при перевыделении памяти */
			{
				return 2;
			}
		}
		newSent->content[newSent->length++] = character;
		character = getwchar();
	}
	newSent->content[newSent->length] = L'\0';
	newSent->wordCount = getWordCount(*newSent);
	reallocateMemory((void **) &newSent->content, (newSent->length + 1) * sizeof(wchar_t));
	if (character == L'\n')
		/* предложение является последним */
	{
		return 1;
	}

	return 0;
}

int getText(TextStruct *newText)
{
	int textCapacity = TEXT_BUF_SIZE;
	SentStruct currentSent;
	int sentOption; /* отслеживание состояния текущего предложения */

	do {
		currentSent = makeSentStruct();
		sentOption = getSentence(&currentSent);
		if (currentSent.wordCount && sentOption != 2)
			/* если предложение непустое и не было ошибок выделения памяти */
		{
			if (newText->sentenceCount == textCapacity)
			{
				textCapacity += TEXT_BUF_SIZE;
				if (reallocateMemory((void **) &newText->sentenceArray, textCapacity * sizeof(SentStruct)))
					/* произошла ошибка при перевыделении памяти */
				{
					return 2;
				}
			}
			newText->sentenceArray[newText->sentenceCount++] = currentSent;
		}
		else
		{
			free(currentSent.content);
			if (sentOption == 2)
				/* при перевыделении памяти под предложение произошла ошибка */
			{
				return 2;
			}
		}
	} while (sentOption != 1);
		/* пока предложение не последнее */
	if (newText->sentenceCount == 0)
		/* текст пустой */
	{
		return 1;
	}
	reallocateMemory((void **) &newText->sentenceArray, newText->sentenceCount * sizeof(SentStruct));

	return 0;
}

void cleanStdIn()
{
	while (getwchar() != L'\n');
}

int checkInput()
{
	int input;
	int successReadCount;

	successReadCount = wscanf(L"%d", &input);
	cleanStdIn(); /* очистка потока ввода */
	if (successReadCount)
		/* если значение было успешно считано */
	{
		return input;
	}

	return -1;
}