#include "my_misc_ioctl.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void) {
	int fd = 0;	
	int baud = 9600;
	fd = open("/dev/my_misc" , O_RDWR);
	if (fd < 0) {
		perror("fail open\n");
		return -1;
	}
	ioctl(fd, SET_BAUBRATE, &baud);

	ioctl(fd, GET_INFO_DEV, &baud);
	

	close(fd);
	return 0;
}
