# Обработка параметров командной строки. Getopt  
***Как обрабатывать множество вариаций параметров, которые поступают с командами различных утилит, вводимых на вход с интерфейсом терминала?***  
`man 3 getopt` - группа функций, решающих эту проблему. Для описания каждого аргумента используется `struct option`  

```C
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int main(int c, char **v)
{
	int is_brackets = 0;
	int opindex = 0;
	int opchar = 0;
	char string[] = "Und wenn du lange in einen Abgrund blickst, blickt der Abgrund auch in dich hinein";
	int length = 0;

	struct option opts[] = { // Опции командной строки, которые будем передавать в утилиту
		// set flag example
		{"brackets", no_argument, &is_brackets, 1}, // Цитата будет напечатана в скобках или без
		// Передаем в переменную is_brackets значение флага

		// option args
		{"length", nrequired_argument, 0, 'l'}, // Задаст ту часть подстроки с начала, которая будет напечатана
		// Полученное значение будет возвращаться функцией getopt (в нашем случае, getopt_long)

		// longname option
		{"authornameshouldbeprinted", no_argument, 0, 'a'}, // Будет напечатано имя автора или нет
		{0, 0, 0, 0}. // стандартный способ указать конец массива структур
	};

	while(-1 != (opchar = getopt_long(c, v, "bl:aq", opts, &opindex))) /* Разбор параметров командной строки.
c и v - аргументы main,
"bl:aq" - форматная строчка, в которой перечисляются опции, которые ожидаем встретить в вводе.
Если опция имеет аргумент, обозначаем двоеточием. length его имеет, поэтому после нее ':'.
'q' добавлена в качестве эксперимента: посмотреть, что будет, если добавить несуществующую опцию.
opindex - индекс опции в командной строке. Нужно для того, чтобы необходимый в некоторых случаеях
порядок аргументов можно было определить
(в некоторых случаях смысл опции определяем в зависимости от того, за какими другими опциями она следует) */
	{
		switch(opchar)
		{
			 case 0:
				printf("0\n");
				break;
			case 'l':
				length = atoi(optarg);
				printf("length = %d\n", length);
				break;
			case 'a':
				printf("(c) Friedrich Nietzsche\n");
				break;
			default:
				printf("optchar: %c\n", opchar); // Если встретили какую-то неописанную опцию
		}
	}

	if(strlen(string) > length && 0 != length)
		string[length] = '\0';
	if(is_brackets)
		printf("[%s]\n", string);
	else
		printf("%s\n", string)

	printf("Done.\n");
}
```
*NB getopt проверяет соответствие того, что введено на однозначность поиска в списке опций. Если имя уникально, то используется опция, 
которая ближе всего подходит. Т.е. `./quotation -a`, `./quotation --authornameshouldbeprinted` и `./quotation --authornameshouldb` 
выполнятся одинаково программой выше.  
`./quotation --authornameshouldb -a -a -a` выведет автора 4 раза.  
`./quotation --brackets -b -b -b` выдаст 4 раза 0 (4 раза были в этом `case`), но в скобки обернет только 1 раз  
`./quotation -l 18` и `./quotation -l18` отработают одинаково, в коротких опциях такая запись допускается.  
`./quotation -al18` или `./quotation -a -l18`- и обрежем, и автора укажем  
`./quotation -l18a` - `a` не отработает, т.к. все, что находится после `l` пытаемся превратить в число по коду
