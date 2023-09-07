#include "memory.h"

void cleanMemory(TextStruct text)
{
	for (int i = 0; i < text.sentenceCount; i++)
	{
		if (text.sentenceArray[i].length)
			/* если предложение непустое (для него выделена память) */
		{
			free(text.sentenceArray[i].content);
		}
	}
	free(text.sentenceArray);
}

int reallocateMemory(void **pointer, unsigned int newBuffer)
{
	void *temp = realloc(*pointer, newBuffer);

	if (temp)
	{
		*pointer = temp;
	}
	else
	{
		return 1;
	}

	return 0;
}

void deleteSentence(TextStruct *text, int index)
{
	text->sentenceCount--;
	free(text->sentenceArray[index].content);
	memmove(text->sentenceArray + index, text->sentenceArray + index + 1,
			(text->sentenceCount - index) * (sizeof(SentStruct)));
	reallocateMemory((void **) &text->sentenceArray, text->sentenceCount * sizeof(SentStruct));
}