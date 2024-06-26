#pragma once

#include <wchar.h>
#include "error.h"
#include "read.h"

#define START_TIP L"Введите текст для его дальнейшей обработки"
#define DESCRIPTION L"С введённым текстом программа может сделать следующее:"
#define EXIT_OPTION L"0 - Завершить выполнение программы."
#define FIRST_OPTION L"1 - Сделать сдвиг слов в предложении на натуральное число;"
#define SECOND_OPTION L"2 - Вывести все уникальные кириллические и латинские символы в тексте;"
#define THIRD_OPTION L"3 - Подсчитать и вывести количество слов и сами слова, длина которых равна 1, 2, и т.д.;"
#define FOURTH_OPTION L"4 - Удалить все слова, которые заканчиваются на заглавный символ;"
#define FIFTH_OPTION L"5 - Отсортировать предложения по уменьшению количества слов четной длины в них;"
#define OPTION_COUNT 5
#define EXIT_MESSAGE L"Выполнение программы завершено. Спасибо за пользование!"

/* принимает код меню (1 - стартовое меню; 2 - подсказка доступных действий; 3 - конечное сообщение)
 * печатает соответствующее меню-подсказку */
void printMenu(int);

/* принимает строку запроса и максимально возможное число (минимальное - 0), возвращает считанное число */
int getAnswer(const wchar_t *, int);

/* принимает указатель на структуру Text и пытается её заполнить, пока пользователь не введёт непустой текст,
 * возвращает статус работы функции (0 - текст считан успешно; 1 - произошла ошибка при перевыделении памяти) */
int getTextAnswer(TextStruct *);