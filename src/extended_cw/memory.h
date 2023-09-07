#pragma once

#include <string.h>
#include "structs.h"

/* принимает структуру Text и очищает выделенную под неё память */
void cleanMemory(TextStruct);

/* "безопасный realloc" принимает указатель на указатель элемента, в котором нужно изменить буфер, а также размер самого буфера,
 * возвращает результат выполнения перевыделения памяти (0 - успешно; 1 - ошибка) и перевыделяет память в случае успеха */
int reallocateMemory(void **, unsigned int);

/* удаляет i-ую структуру Sentence из массива предложений (структур Sentence) структуры Text */
void deleteSentence(TextStruct *, int);