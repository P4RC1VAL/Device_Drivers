#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd;
	char tmp[7];
	fd = open("/dev/sym_chrdev", O_RDONLY);
	if(fd < 0){
		printf("Error \n");
	}
	read(fd,tmp,7);
	for(int i =0; i<7; i++){
		printf("%c\n" , tmp[i]);
	}
	close(fd);
	return 0;
}
