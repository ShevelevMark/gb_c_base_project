#include <stdbool.h>
#include <stdio.h>

/**
 * Проверка на соответствие завершаемой нулём строки шаблону входных данных:
 * ^\d{4}(;[ \d]\d){4};( \d|-\d\d|-\d)$
 * Конец строки - завершающий ноль
 * @param char const * str указатель на верную память, начало строки; возможно пустую строку,
 *                         но обязательно с завершающим нулём
 * @return bool true, если строка соответсвует шаблону, иначе - false
 */
bool validate_string(char const *str);

/**
 * Проверка входящих данных на соответствие верным значениям
 * года, месяца, дня, часов, минут и температуры. Принимаемаея строка 
 * должна соответствовать шаблону ^\d{4}(;[ \d]\d){4};( \d|-\d\d|-\d)$.
 * 
 * @param char const * str - указательна на начало строки, содержаещей необходимые данные.
 * @param int * year        - год в пределах от 1900 до 3000
 * @param int * month       - номер месяца от 1 до 12
 * @param int * day         - номер дня в пределах от 1 до 31
 * @param int * hour        - номер часа от 0 до 23
 * @param int * minute      - номер минуты от 0 до 59
 * @param int * temperature - зафиксированная температура от -99 до 99
 * 
 * @return bool - true, если данные удалось успешно прочитать и они лежат в нужных пределах, иначе - false;
 *                не следует читать данные по переданным адресам, если функция не вернула true, возможно данные 
 *                не были записаны.
 */
bool validate_data(char const *str, int *year, int *month, int *day, int *hour, int *minute, int *temperature);

/**
 * Функция считывает из потока по переданному дескриптору строку данных в буфер.
 * Считывается не более 21 символа до первого символа перевода строки '\n', 
 * что наступит раньше. Передаваемый буфер должен содержать достаточно памяти 
 * для 22 элементов типа char (21 символ из файла + 1 на завершающий ноль).
 * После считывания 21 символа функция пропустит все данные до символаа перевода
 * строки, а затем и сам символ перевода строки '\n'.
 * 
 * @param FILE * fd     - указатель-десткриптор потока ввода
 * @param char * buffer - буфер, в который происходит запись считанных символов
 * 
 * @return bool - если считать данные не удалось (не считалось ни одного символа), 
 *                функция вернёт false, иначе - true  
 */
bool read_line(FILE *fd, char *buffer);