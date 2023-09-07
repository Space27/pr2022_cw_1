#pragma once

#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "memory.h"

#define CHAR_COUNT (2 * (L'я' - L'а' + L'z' - L'a' + 3))
#define LATIN_ONE_CASE_CHAR_COUNT (L'z' - L'a' + 1)
#define CYRILLIC_ONE_CASE_CHAR_COUNT (L'я' - L'а' + 1) /* без учёта 'ё' и 'Ё' */
#define WORD_COUNT_BUFFER 3

/* принимает две структуры Sentence, возвращает результат их сравнения без учёта регистра (1 - равны, 0 - нет) */
int compareSentenceCaseIntensive(SentStruct, SentStruct);

/* принимает указатели на структуры Sentence и Text, возвращает результат поиска предложения в тексте (1 - найдено; 0 - нет) */
int isRepeated(SentStruct *, TextStruct *);

/* принимает указатель на структуру Text, после чего удаляет в ней одинаковые предложения без учёта регистра */
void deleteRepeatedSentence(TextStruct *);

/* принимает указатель на структуру Sentence и удаляет лишние символы табуляции в начале предложения */
void deleteTabs(SentStruct *);

/* принимает указатель на структуру Text и удаляет лишние символы табуляции в начале каждого предложения */
void deleteTabsInText(TextStruct *);

/* принимает указатель на структуру Text и удаляет лишние табуляции и повторяющиеся предложения */
void cleanText(TextStruct *);

/* принимает символ и проверяет, является ли он латинским (1 - является; 0 - нет) */
int isLatin(wchar_t);

/* принимает символ и проверяет, является ли он кириллическим (1 - является; 0 - нет) */
int isCyrillic(wchar_t);

/* принимает структуру Text и возвращает массив с кодами найденных символов (0 - символа с соответствующим индексом нет) */
int *findUniqueCharacters(TextStruct);

/* принимает строку и слово, после чего удаляет слово с левыми разделителями из строки и возвращает длину удалённой подстроки */
int removeWord(wchar_t *, const wchar_t *);

/* принимает структуру Sentence и возвращает указатель на скопированную строку этого предложения */
wchar_t *copyString(SentStruct);

/* принимает указатель на структуру Text и удяляет в ней все слова, оканчивающиеся на заглавную букву
 * возвращает количество удалённых слов */
int removeWordsWithLastUpperCase(TextStruct *);

/* принимает символ и проверяет, является ли он разделителем (1 - является; 0 - нет) */
int isSeparator(wchar_t);

/* принимает структуру Text, возвращает максимальную длину слова среди всех предложений структуры */
int findMaxWordLen(TextStruct);

/* принимает структуру Text и возвращает другую структуру Text с заполненной информацией о словах одной длины */
TextStruct getWordsSameLength(TextStruct);

/* принимает указатель на структуру Sentence и число, на которое нужно сдвинуть слова в предложении */
void moveWords(SentStruct *, int);

/* принимает указатель на структуру Text, номер сдвигаемого предложения (0 для всего текста) и сдвиг слов в нём
 * сдвигает слова в предложении на сдвиг вправо */
void moveWordsInText(TextStruct *, int, int);

/* принимает указатель на структуру Sentence и возвращает количество слов четной длины в нём */
int getEvenWordCount(SentStruct *);

/* компаратор по количеству слов четной длины в предложении в порядке убывания */
int cmp(const void *, const void *);

/* принимает указатель на структуру Text и сортирует предложения в нём в порядке убывания количества слов четной длины */
void sortSentencesByEvenWordCount(TextStruct *);