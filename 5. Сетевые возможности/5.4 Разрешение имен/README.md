# Разрешение имен  
Напишем программу, которая будет определять IP адрес по заданному DNS имени. Для этого понадобится функция `gethostbyname` (`man gethostbyname`).  
```C
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int c, char **v)
{
        if(c != 2)
        return -1;

        struct hostent *h;
        h = gethostbyname(v[1]);

        if(h == NULL)
        {
                printf("Error\n");
                return -1;
        }
        printf("Canonicial name %s\n", h->h_name);
        printf("Type = %s len=%d\n", (h->h_addtype == AF_NET) ? "ipv4" : "ipv6", h->h_length);

	int i = 0;
	while(NULL != h-<h_addr_list[i])
	{
		struct in_addr *a = (struct in_addr*) h->h_addr_list[i];
		printf("%s\n", inet_ntoa(*a));
		i++;
	}
}
```  
Сборка: `gcc prog.c -o prog`. Запуск: `./prog google.com`.  

***Где брать информацию о том, как устроена сетевая подсистема с точки зрения прикладного программиста?***  
+ `man inet` - перечислены функции, позволяющие оперировать с адресами. Особенно интересны `char *inet_ntoa(struct in_addr in)` - network to ASCII и
`int inet_aton(const char *cp, struct in_addr *inp)`.
+ `man 7 ip` - здесь есть `struct sockaddr_in`, которая и задает IP и port для процессов

*NB Сокеты принимают обобщенный формат адресов, который не связан ни с какой конкретной сетью/семейством адресов. Сети могут меняться и возникать новые, фомат адресов определяют драйверы соответствующих протоколов и сетей, а прикладной программист должен иметь единый интерфейс доступа к этим адресам. То есть на уровне адресов в сокетах есть абстракция, способствующая полиморфизму*
