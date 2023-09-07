#include "processing.h"

int compareSentenceCaseIntensive(SentStruct firstSentence, SentStruct secondSentence)
{
	if (firstSentence.length == secondSentence.length && firstSentence.wordCount == secondSentence.wordCount)
		/* если предложения одной длины и содержат одинаковое количество слов */
	{
		for (int i = 0; i < firstSentence.length; i++)
		{
			if (towlower(firstSentence.content[i]) != towlower(secondSentence.content[i]))
				/* если символы в одном регистре не равны */
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

int isRepeated(SentStruct *sent, TextStruct *text)
{
	int repeatedCount = 0;

	for (int i = 0; i < text->sentenceCount; i++)
	{
		if (compareSentenceCaseIntensive(*sent, text->sentenceArray[i]))
		{
			repeatedCount++;
			if (repeatedCount > 1)
			{
				return 1;
			}
		}
	}

	return 0;
}

void deleteRepeatedSentence(TextStruct *text)
{
	for (int i = text->sentenceCount - 1; i > 0; i--)
	{
		if (isRepeated(&text->sentenceArray[i], text))
		{
			deleteSentence(text, i);
		}
	}
}

void deleteTabs(SentStruct *sent)
{
	int firstWordChar = -1;

	while (iswblank(sent->content[++firstWordChar]));
		/* пока текущий символ не станет началом слова */
	if (firstWordChar)
		/* если первый символ - "пустой" */
	{
		wmemmove(sent->content, sent->content + firstWordChar, sent->length - firstWordChar + 1);
		sent->length -= firstWordChar;
		reallocateMemory((void **) &sent->content, (sent->length + 1) * sizeof(wchar_t));
	}
}

void deleteTabsInText(TextStruct *text)
{
	for (int i = 0; i < text->sentenceCount; i++)
	{
		deleteTabs(&text->sentenceArray[i]);
	}
}

void cleanText(TextStruct *text)
{
	deleteTabsInText(text);
	deleteRepeatedSentence(text);
}

int isLatin(wchar_t character)
{
	return (character >= L'a' && character <= L'z') || (character >= L'A' && character <= L'Z');
}

int isCyrillic(wchar_t character)
{
	return (character >= L'а' && character <= L'я') || (character >= L'А' && character <= L'Я')
		   || character == L'ё' || character == L'Ё';
}

int *findUniqueCharacters(TextStruct text)
{
	int *uniqChars = calloc(CHAR_COUNT, sizeof(int));

	for (int i = 0; i < text.sentenceCount; i++)
	{
		for (int j = 0; j < text.sentenceArray[i].length; j++)
		{
			if (iswalpha(text.sentenceArray[i].content[j]))
			{
				if (isLatin(text.sentenceArray[i].content[j]))
				{
					if (iswlower(text.sentenceArray[i].content[j]))
					{
						uniqChars[text.sentenceArray[i].content[j] - L'a'] = text.sentenceArray[i].content[j];
					}
					else
					{
						uniqChars[text.sentenceArray[i].content[j] - L'A' + LATIN_ONE_CASE_CHAR_COUNT] =
								text.sentenceArray[i].content[j];
					}
				}
				else if (isCyrillic(text.sentenceArray[i].content[j]))
				{
					if (text.sentenceArray[i].content[j] == L'ё')
					{
						uniqChars[CHAR_COUNT - 2] = text.sentenceArray[i].content[j];
					}
					else if (text.sentenceArray[i].content[j] == L'Ё')
					{
						uniqChars[CHAR_COUNT - 1] = text.sentenceArray[i].content[j];
					}
					else if (iswlower(text.sentenceArray[i].content[j]))
					{
						uniqChars[text.sentenceArray[i].content[j] - L'а' + 2 * LATIN_ONE_CASE_CHAR_COUNT] =
								text.sentenceArray[i].content[j];
					}
					else
					{
						uniqChars[text.sentenceArray[i].content[j] - L'А' + 2 * LATIN_ONE_CASE_CHAR_COUNT +
								  CYRILLIC_ONE_CASE_CHAR_COUNT] = text.sentenceArray[i].content[j];
					}
				}
			}
		}
	}

	return uniqChars;
}

int removeWord(wchar_t *string, const wchar_t *word)
{
	wchar_t *startPoint;
	wchar_t *endPoint;

	startPoint = wcsstr(string, word);
	endPoint = startPoint + wcslen(word);
	while (startPoint > string && isSeparator(*(startPoint - 1)))
		/* пока стартовая точка в пределах строки и символ за ней - разделитель */
	{
		startPoint--;
	}
	if (startPoint == string)
		/* если удаляется слово в начале строки */
	{
		while (endPoint < string + wcslen(string) && isSeparator(*endPoint))
			/* пока конечная точка в пределах строки и она указывает на разделитель */
		{
			endPoint++;
		}
	}
	wmemmove(startPoint, endPoint, wcslen(string) - (startPoint - string));

	return (int) (endPoint - startPoint);
}

wchar_t *copyString(SentStruct sent)
{
	wchar_t *stringCopy = (wchar_t *) malloc((sent.length + 1) * sizeof(wchar_t));
	wcsncpy(stringCopy, sent.content, sent.length + 1);

	return stringCopy;
}

int removeWordsWithLastUpperCase(TextStruct *text)
{
	int deletedCount = 0;

	for (int i = 0; i < text->sentenceCount; i++)
	{
		wchar_t *pointer;
		wchar_t *stringCopy = copyString(text->sentenceArray[i]);
		wchar_t *word = wcstok(stringCopy, L" ,", &pointer);
		while (word != NULL)
		{
			if (iswupper(word[wcslen(word) - 1]))
				/* если последний символ заглавный */
			{
				text->sentenceArray[i].length -= removeWord(text->sentenceArray[i].content, word);
				text->sentenceArray[i].wordCount--;
				deletedCount++;
			}
			word = wcstok(NULL, L" ,", &pointer);
		}
		if (text->sentenceArray[i].wordCount == 0)
			/* после удалений слов предложение стало пустым */
		{
			deleteSentence(text, i);
			i--;
		}
		else
		{
			reallocateMemory((void **) &text->sentenceArray[i].content,
							 (text->sentenceArray[i].length + 1) * sizeof(wchar_t));
		}
		free(stringCopy);
	}

	return deletedCount;
}

int isSeparator(wchar_t character)
{
	return character == L',' || character == L' ';
}

int findMaxWordLen(TextStruct text)
{
	int max = 0;
	int len;

	for (int i = 0; i < text.sentenceCount; i++)
	{
		len = 0;
		for (int j = 0; j < text.sentenceArray[i].length; j++)
		{
			if (isSeparator(text.sentenceArray[i].content[j]))
			{
				if (len > max)
				{
					max = len;
				}
				len = 0;
			}
			else
			{
				len++;
			}
		}
		if (len > max)
		{
			max = len;
		}
	}

	return max;
}

TextStruct getWordsSameLength(TextStruct text)
{
	int wordLen;
	TextStruct wordList;
	wordList.sentenceCount = findMaxWordLen(text);
	wordList.sentenceArray = (SentStruct *) malloc(wordList.sentenceCount * sizeof(SentStruct));
	for (int i = 0; i < wordList.sentenceCount; i++)
	{
		wordList.sentenceArray[i].length = 0;
		wordList.sentenceArray[i].wordCount = 0;
	}

	for (int i = 0; i < text.sentenceCount; i++)
	{
		wchar_t *pointer;
		wchar_t *stringCopy = copyString(text.sentenceArray[i]);
		wchar_t *word = wcstok(stringCopy, L" ,", &pointer);
		while (word != NULL)
		{
			wordLen = (int) wcslen(word);
			if (wordList.sentenceArray[wordLen - 1].wordCount == 0)
				/* '-1' требуется для полного занятия пространства массива */
			{
				wordList.sentenceArray[wordLen - 1].content = (wchar_t *) calloc(WORD_COUNT_BUFFER * (wordLen + 1) + 2,
																				 sizeof(wchar_t));
					/* выделение памяти на несколько слов с пробелами и '\0' */
				wordList.sentenceArray[wordLen - 1].length = 1;
				wordList.sentenceArray[wordLen - 1].content[0] = L' ';
			}
			wordList.sentenceArray[wordLen - 1].wordCount++;
			wordList.sentenceArray[wordLen - 1].length += wordLen + 1;
			if ((wordList.sentenceArray[wordLen - 1].wordCount - 1) % WORD_COUNT_BUFFER == 0 &&
				wordList.sentenceArray[wordLen - 1].wordCount != 1)
				/* количество слов до вставки кратно буферу, значит он переполнен */
			{
				if (reallocateMemory((void **) &wordList.sentenceArray[wordLen - 1].content,
									 (WORD_COUNT_BUFFER *
									  (wordList.sentenceArray[wordLen - 1].wordCount / WORD_COUNT_BUFFER + 1) *
									  (wordLen + 1) + 2) * sizeof(wchar_t)))
					/* выделение памяти на ещё несколько слов с пробелами */
				{
					wordList.sentenceCount = -1;
					return wordList;
				}
			}
			wcsncat(wordList.sentenceArray[wordLen - 1].content, word, wordLen);
			wcsncat(wordList.sentenceArray[wordLen - 1].content, L" ", 1);
			word = wcstok(NULL, L" ,", &pointer);
		}
		free(stringCopy);
	}
	for (int i = 0; i < wordList.sentenceCount; i++)
	{
		if (wordList.sentenceArray[i].wordCount)
		{
			reallocateMemory((void **) &wordList.sentenceArray[i].content,
							 (wordList.sentenceArray[i].length + 1) * sizeof(wchar_t));
		}
	}

	return wordList;
}

void moveWords(SentStruct *sent, int shift)
{
	shift %= sent->wordCount;

	if (shift)
	{
		wchar_t *stringCopy = copyString(*sent);
		int generalCounter = 0; /* положение текущего символа в конечной строке */
		int separatorCounter = 0; /* положение текущего первого невставленного символа - разделителя */
		int wordCounter = sent->length; /* положение текущего первого невставленного символа - не разделителя */
		while (shift)
		{
			while (isSeparator(sent->content[--wordCounter]) || !isSeparator(sent->content[wordCounter - 1]));
				/* пока предыдущий символ - разделитель или предыдущий за ним - не разделитель*/
			shift--;
		}
		while (isSeparator(stringCopy[generalCounter]))
			/* пока текущий символ - разделитель */
		{
			sent->content[generalCounter++] = stringCopy[separatorCounter++];
		}
		do {
			while (!isSeparator(stringCopy[separatorCounter]) && separatorCounter < sent->length)
				/* пока текущий символ - не разделитель и он не выходит за пределы строки */
			{
				separatorCounter++;
			}
			while (isSeparator(stringCopy[wordCounter % sent->length]))
				/* пока текущий символ - разделитель */
			{
				wordCounter++;
			}
			while (!isSeparator(stringCopy[wordCounter % sent->length]))
				/* пока текущий символ - не разделитель */
			{
				sent->content[generalCounter++] = stringCopy[wordCounter++ % sent->length];
				if (wordCounter == sent->length)
					/* началось новое слово с начала строки */
				{
					break;
				}
			}
			while (isSeparator(stringCopy[separatorCounter]) && separatorCounter < sent->length)
				/* пока текущий символ - разделитель и он не выходит за пределы строки */
			{
				sent->content[generalCounter++] = stringCopy[separatorCounter++];
			}
		} while (generalCounter < sent->length);
			/* пока предолжение не заполнено */
	}
}

void moveWordsInText(TextStruct *text, int shift, int number)
{
	if (number)
	{
		moveWords(&text->sentenceArray[number - 1], shift);
	}
	else
	{
		for (int i = 0; i < text->sentenceCount; i++)
		{
			moveWords(&text->sentenceArray[i], shift);
		}
	}
}