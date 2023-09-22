#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd;
	fd = open("/dev/sym_chrdev", O_RDWR);
	if(fd < 0){
		printf('Error');
	}
	read(fd,&tmp,6);
	close(fd);
	
	return 0;
}
