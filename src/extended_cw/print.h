#pragma once

#include "structs.h"

#define CHAR_COUNT (2 * (L'я' - L'а' + L'z' - L'a' + 3))
#define LATIN_ONE_CASE_CHAR_COUNT (L'z' - L'a' + 1)
#define CYRILLIC_ONE_CASE_CHAR_COUNT (L'я' - L'а' + 1) /* без учёта 'ё' и 'Ё' */

/* принимает структуру Text и построчно выводит все предложения, хранящиеся в ней */
void printText(TextStruct);

/* принимает массив с кодами уникальных символов, после чего выводит символы, чьё значение не равно 0 */
void printCharacters(const int *);

/* принимает количество "слов", возвращает последнюю букву в зависимости от падежа */
wchar_t endOfWord(int);

/* принимает количество удаленных слов, после чего печатает их количество */
void printResultsAfterRemoving(int);

/* принимает структуру Text с данными о словах одной длины, после печатает их с указанием количества и длины */
void printWordSameLength(TextStruct);