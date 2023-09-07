#pragma once

#include <wchar.h>
#include <stdlib.h>

#define TEXT_BUF_SIZE 3
#define SENTENCE_BUF_SIZE 20

typedef struct Sentence {
	wchar_t *content;
	int length;
	int wordCount;
	int evenWordCount;
} SentStruct;

typedef struct Text {
	SentStruct *sentenceArray;
	int sentenceCount;
} TextStruct;

/* возвращает структуру Text с обнуленным количеством предложений и выделенной динамической памятью */
TextStruct makeTextStruct();

/* возвращает структуру Sentence с обнуленными длиной и количеством слов (в т.ч. четных) и выделенной динамической памятью */
SentStruct makeSentStruct();