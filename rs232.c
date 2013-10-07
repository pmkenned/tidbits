#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

int main()
{
    printf("hello world\n");
    int n;
    int fd;
    char c;
    int bytes;

    char buffer[10];
    char *bufptr;
    int nbytes;
    int tries;
    int x;
    struct termios options;

    int i;


    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1)
    {
        perror("open_port: Unable to open:");
    }
    else
    {
        fcntl(fd, F_SETFL, 0);
        printf("hi again\n");
    }

    tcgetattr(fd, &options);

    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~( ICANON | ECHO | ECHOE |ISIG );
    options.c_iflag &= ~(IXON | IXOFF | IXANY );
    options.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &options);

	printf("writing...\n");
	for(i=0; i<2000; i++) {
		if(i % 100 == 0) {
			printf(".");
			fflush(stdout);
		}
	    write(fd, "0",4);
	}
    printf("\nwrote\n");
    bufptr = buffer;


    fcntl(fd, F_SETFL, FNDELAY);
     bytes = read(fd, bufptr, sizeof(buffer));
    printf("number of bytes read is %d\n", bytes);
    perror ("read error:");

    for (x = 0; x < 10 ; x++)
    {
        c = buffer[x];
        printf("%d  ",c);
    }
    close(fd);

    //puts(buffer[0]);
    printf("\nshould of put something out \n");

    return (0);
}
