#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/ioctl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/watchdog.h>
// #include "led.h"
extern void led_print(void);

// int main(void)
// {
//     int fd = open("/dev/watchdog", O_WRONLY);
//     int ret = 0;
//     char ch = 1;
//     if (fd == -1) {
//         perror("watchdog");
//         exit(EXIT_FAILURE);
//     } 
//     printf("tick2222");
//     while (1) {
//         ret = write(fd, "\0", 1); 
//         if (ret != 1) {
//             ret = -1; 
//             printf("12");
//             break;
//         } 
//         printf("tick");
//         sleep(1);
//         // ret = fsync(fd);
//         // if (ret)
//         //     break;
//         // sleep(10);
//     } 
//     close(fd);
//     return ret;
// }

int ma3in(int argc,char *argv[])
{
	int fd;
	char buf[40] = {0};
	char argv1;

	if(argc == 1) {
		printf("Usage:\n");
		printf("\t1:\tTurn on all led\n");
		printf("\t0:\tTurn off all led\n");
		exit(1);
	}
	fd = open("/dev/leds",O_WRONLY);
	
	if(fd < 0) {
		printf("open device mydevled0\n");
		exit(1);
	}
	argv1 = atoi(argv[1]);
	switch(argv1) {
	case 0:
		printf("LED_ON\n");
		ioctl(fd,1,0);
		break;
	case 1:
		printf("LED_ON\n");
		ioctl(fd,1,1);
		break;
	case 2:
		printf("LED_ON\n");
		ioctl(fd,0,0);
		ioctl(fd,0,1);
		break;
	default:
		break;
	}
	close(fd);
	//led_print();
	return 0;
}


int mainbuzzer(int argc,char *argv[])
{
	int fd;
	char buf[40] = {0};
	char argv1;

	if(argc == 1) {
		printf("Usage:\n");
		printf("\t1:\tTurn on all led\n");
		printf("\t0:\tTurn off all led\n");
		exit(1);
	}
	fd = open("/dev/buzzer_ctl",O_WRONLY);
	
	if(fd < 0) {
		printf("open device mydevled0\n");
		exit(1);
	}
	argv1 = atoi(argv[1]);
	switch(argv1) {
	case 0:
		printf("LED_ON\n");
		ioctl(fd,0);
		break;
	case 1:
		printf("LED_ON\n");
		ioctl(fd,1);
		break;
	case 2:
		printf("LED_ON\n");
		ioctl(fd,0,0);
		ioctl(fd,0,1);
		break;
	default:
		break;
	}
	close(fd);
	//led_print();
	return 0;
}

// ad
int main(int argc,char *argv[])
{
	int fd;
	char buf[40] = {0};
	char argv1;

	if(argc == 1) {
		printf("Usage:\n");
		printf("\t1:\tTurn on all led\n");
		printf("\t0:\tTurn off all led\n");
		exit(1);
	}
	fd = open("/dev/adc",O_WRONLY);
	
	if(fd < 0) {
		printf("open device mydevled0\n");
		exit(1);
	}
	argv1 = atoi(argv[1]);
	switch(argv1) {
	case 0:
		printf("LED_ON\n");
		ioctl(fd,0xc000fa01,0);
		break;
	case 1:
		printf("LED_ON\n");
		ioctl(fd,0xc000fa01,1);
		break;
	case 2:
		printf("LED_ON\n");
		ioctl(fd,0xc000fa01,2);
		break;
	case 3:
		printf("LED_ON\n");
		ioctl(fd,0xc000fa01,3);
		break;
	default:
		break;
	}

	short val;
	int ret;
	for (int i = 0;i < 30;i++) {
		ret = read(fd, &val,2);
		printf("ret = %d\n%d\n",ret,val);
		sleep(1);
	}
	

	close(fd);
	//led_print();
	return 0;
}

