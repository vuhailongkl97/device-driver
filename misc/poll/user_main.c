#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/select.h> 
 
#define CHAR_DEVICE "/dev/my_misc_poll"

int main(void) {
	int fd, ret; 
    ssize_t read_count; 
	fd_set readfds; 
	fd = open(CHAR_DEVICE, O_RDONLY);
	if (fd < 0) {
		perror("fail open :");
		return -1;
	}

   FD_ZERO(&readfds); 
   FD_SET(fd, &readfds); 
ret = select(fd + 1, &readfds, NULL, NULL, NULL); 
         /* From this line, the process has been notified already */ 
   if (ret == -1) { 
            fprintf(stderr, "select call on %s: an error occurred", CHAR_DEVICE); 
			return -1;
   } 
	return 0;
}
