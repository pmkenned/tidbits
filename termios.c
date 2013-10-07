/*   #define OLD_TERMIO  */

#ifdef __STDC__
#define PROTOTYPICAL
#endif
#ifdef __cplusplus
#define PROTOTYPICAL
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#ifdef OLD_TERMIO
#include <termio.h>
#else
#include <termios.h>
#endif

#ifdef PROTOTYPICAL
int main(int argc, char *argv[])
#else
main(argc,argv)
char *argv[];
#endif

{
#ifdef OLD_TERMIO
        struct termio orig,now;
#else
        struct termios orig,now;
#endif

    FILE * fp = NULL;
    char filename[100];
    struct timeval times[10000];
    struct timeval t0;
    float t;

    unsigned long int scores[10000];
    unsigned long int score = 0;
    int dt = 0;
    int c, i, j, done;

    setvbuf(stdout, NULL, _IONBF ,0);

#ifdef OLD_TERMIO
    ioctl(0, TCGETA, (char *) &orig);
#else
    tcgetattr(0, &orig);
#endif
    now=orig;
    now.c_lflag &= ~(ISIG|ICANON|ECHO);
    now.c_cc[VMIN]=1;
    now.c_cc[VTIME]=2;
#ifdef OLD_TERMIO
    ioctl(0,TCSETA, (char *) &now);
#else
    tcsetattr(0, TCSANOW, &now);
#endif
    done=0;
    gettimeofday(&t0,NULL);
    i=0;
    while(!done) {
        c=getchar();
        if(c == '1')
        {
            gettimeofday(times+i,NULL);
            score *= 2;
            scores[i] = score;
            i++;
        }
        if(c == '2')
        {
            gettimeofday(times+i,NULL);
            dt += 10;
            score += dt;
            scores[i] = score;
            i++;
        }
        done = (c =='q');
    }

#ifdef OLD_TERMIO
    ioctl(0,TCSETA, (char *) &orig);
#else
    tcsetattr(0, TCSANOW, &orig);
#endif

    printf("enter file name: ");
    scanf("%s",filename);

    fp = fopen(filename, "w");

    for(j=0; j<i; j++)
    {
        t = (times[j].tv_sec*1000 + times[j].tv_usec/1000.0) - (t0.tv_sec*1000 + t0.tv_usec/1000.0);
        fprintf(fp,"%f\t",t/1000);
        fprintf(fp,"%d\n",scores[j]);
    }

    exit(0);
}
