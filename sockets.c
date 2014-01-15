#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char * argv[]) {

    if(argc < 2) {
        printf("usage: %s [host name]\n",argv[0]);
        exit(1);
    }

    struct hostent * he = gethostbyname(argv[1]);

    if(he == NULL) {
        printf("error\n");
        exit(1);
    }

    char ** h_addr_list = he->h_addr_list;

    struct in_addr * ia;
    char * hbo_str;

    int i;
    for(i=0; h_addr_list[i] != NULL; i++) {
        ia = (struct in_addr *) h_addr_list[0];
        hbo_str = inet_ntoa(*ia);
        printf("%d: %s\n", i, hbo_str);
    }

    return 0;
}
