# Разрешение имен  
Напишем программу, которая будет определять IP адрес по заданному DNS имени. Для этого понадобится функция `gethostbyname` (`man gethostbyname`).  
```C
#include <netdb.h>
#include <stdio.h>

int main(int c, char **v)
{
        if(c != 2)
        return -1;

        struct hostent *h;
        h = gethostbyname(v[1]);

        if(h != NULL)
        {
                printf("Error\n");
                return -1;
        }
        printf("Canonicial name %s\n", h->h_name);
        printf("Type = %s len=%d\n", (h->h_addtype == AF_NET) ? "ipv4" : "ipv6", h->h_length);
}
```
