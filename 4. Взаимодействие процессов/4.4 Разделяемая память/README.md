# Разделяемая память  
В Linux одновременно может исполняться множество процессов, но каждый процесс считает, что он использует все ресурсы ОС и оборудования монопольно.   
## Отображение памяти в Linux  
Уровни отображения:  
1) Физическая память - микросхемы памяти - реальное железо, хранящее биты
2) Hardware - аппаратура компьютера
3) Software - ОС
4) Пользовательские процессы. В ОС они представлены какими-то структурами, которые в том числе, описыванют и память соответствующим им процессов

***Что есть для процесса та память, которую он получает на старте?***  
Получает процесс не память, а адресное пространство (далее АП). Причем все процессы получают одно и то же множество адресов (от 0 до FFFFFFFF [8 штук] в 32-x).    

АП разделено на определенные зоны, сочетание которых называется **memory layout**. Зоны АП:  
+ Ядро, занимающее 1 Gb адресов (не физической памяти, а памяти этого виртуального АП)
+ Сам процесс, состоящий из нескольких сегментов: в одном хранится код в формате .txt, в другом - данные, в третьем - неинициализированные данные.
+ Куча - память, использующаяся процессом. Она заполняется реальной физической памятью в этом АП, когда процесс вызывает `alloc`, `new` и подобные команды.
+ Стек, растущий в сторону уменьшения адресов (стек вызовов имеется в виду как я понял)
+ Shared memory segment (или memory mapping segment). Используется для отображения динамических библиотек, а также как регион АП для обеспечения IPC.

*NB Физическая память (далее ФП) обладает своим АП, тоже от 0 до какого-то значения, но оно не должно быть такого же размера, как вышеописанное логическое АП. 
То есть может быть так, что не все АП процесса помещено в АП ФП.  

***Как логическое АП переходит в АП ФП?***  
У ОС есть механизм виртуальой памяти. Он позволяет все логическое АП процесса частично расположить на ФП (конкретно, оперативная память имеется в виду), 
а частично на диск, и обеспечивает прозрачное помещение кусочков памяти с диска в оперативную память и наоборот.  
## Shared memory  
Как мы выяснили, в АП каждого процесса есть сегмент shared memory. Процесс может зарегистрировать место какого-то размера в этом сегменте, 
получить уникальный идентификатор (id) этого региона. Другой процесс, зная id, может аллоцировать в своем АП такого же размера регион (также в shared memory),
 и оба этих региона будут отображены на ФП. В ФП будет диапазон адресов, который физически будет присутствовать в АП как первого процесса, так и второго.  
 То есть, несмотря на то, что каждый процесс обладает своим АП, внутри их АП будет такой набор указателей (адресов), осуществляя чтение и запись по которым, 
 они будут обращаться к одной и той же области ФП.  

 ## Функции для работы с shared memory  
 + `shmget` - позволяет получать или создавать регион памяти
 + `shmat` - подключение к существующему региону памяти
 + `shmdt` - shared memory detach - отключение от региона памяти
 + `shmctl` - позволяет управлять различными параметрами регионов shared memory

 *NB `size`, передаваемый в `shmget` округляется вверх до размера страницы виртуальной памяти (далее ВП). Дело в том, что ВП разбита на страницы*  
 *NBB Регионы shared memory переживают процесса. То есть этот регион памяти может жить и после завершения процесса. 
 Для того, чтобы определить какие регионы остались, есть утилита `ipcs`. Она показывает информацию об IPC. 
 `ipcs -m` для получения списка регионов shared memory*
