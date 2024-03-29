# Сокеты ориентированные на соединения. Протокол TCP  
Реализуем клиент-серверное приложение:  
```C
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int server()
{
	int ss = socket(AF_INET, SOCK_STREAM, 0);
	int cs; // client socket

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;

	bind(ss, (struct sockaddr*) &local, sizeof(local)); /* Сервер не может начать слушать входящее соединение,
не определив на каком порте он это делает */ 
	listen(ss, 5); /* 5 - backlog - то кол-во клиентов, которое одновременно пытаются установить соединение.
Дело в том, что установка соединения занимает некоторое время. И пока пакеты с инфой об установке соединения ходят туда-сюда,
могут несколько клиентов подключиться. Мы ограничили их до 5. */

	cs = accept(ss, NULL, NULL); // accept возвращает сокет, связанный с клиентом, который попытался сделать connect

	char buf[BUFSIZ];
	read(cs, buf, BUFSIZ);
	printf("%s\n", buf);
	close(cs);
}

int client()
{
	int s = socket(AF_INET, SOCK_STREAM, 0);

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;

	connect(s, (struct sockaddr*) &local, sizeof(local)); // Пытаемся установить соединение сокета с сервером

	char buf[BUFSIZ] = "Hello\n";
	write(s, buf, strlen(buf)+1); // В плане чтения и записи fid и сокет ничем не отличаются
	close(s);
}

int main(int c, char **v)
{
	if(c != 2)
	{
		return printf("Use: %s [s|c]\n", v[0]);
	}

	struct sockaddr_in local;

	if(v[1][0] == 's')
	{
		server();
	}

	if(v[1][0] == 'c')
	{
		client();
	}
}
```

*NB `send`, `recv` - декораторы `read` и `write`. По сути их отличает лишь поле флагов, которые можно задать для первой пары команд.  
`sendto` и `recvfrom` с чуть более расширенным функционалом и нужны для UDP.  
В TCP как только установили соединение, чтение и запись в сокеты происходит аналогично чтению и записи в файл.*
