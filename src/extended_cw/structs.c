#include "structs.h"

TextStruct makeTextStruct()
{
	TextStruct newText;

	newText.sentenceCount = 0;
	newText.sentenceArray = (SentStruct *) malloc(TEXT_BUF_SIZE * sizeof(SentStruct));

	return newText;
}

SentStruct makeSentStruct()
{
	SentStruct newSent;

	newSent.length = 0;
	newSent.wordCount = 0;
	newSent.evenWordCount = 0;
	newSent.content = (wchar_t *) malloc(SENTENCE_BUF_SIZE * sizeof(wchar_t));

	return newSent;
}