/*
	编译选项
	@$(CC) -o ./tools/keyboard.elf ./tools/keyboard.c 
	# ./tools/keymap.c  ./tools/map_uk.c

*/
#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include "unistd.h"
#include "keymap.h"

// #include <linux/kb.h>
// #define DEV_PATH "/dev/input/event6"   //difference is possible


char dev[100]= "/dev/input/event";   //difference is possible

#define aa  0x11111100
#define bb (0x11111100U)
int main(int argc, char **argv)
{
	int keys_fd;
	char ret[2];
	struct input_event t;

	if (argc != 2) {
		printf("input error :elf <n>\n"
			"\tn: /dev/input/event<n>\n");
	}

	snprintf(dev,100, "/dev/input/event%s",argv[1]);
	keys_fd=open(dev, O_RDONLY);
	
	
	printf("%c\n%c\n",162,163);
	if(keys_fd <= 0)
	{
		printf("open %s error!\n", dev);
		return -1;
	}
	int op;

	op=fcntl(keys_fd, F_GETFL);
	printf("opt = %d\n", op);
	// printf("[%8.8x \n", op);
	// if (fcntl(keys_fd, F_SETFL, op|O_NONBLOCK) < 0) {
	// 	perror("ep_Setnonblocking fctl error\n");

	// 	return -1;
	// }
	int oldkbmode;
	
	// if (ioctl(keys_fd,0x4B44,&oldkbmode)) {
	// 	perror("KDSKBMODE  get");
	// 	return 1;	
	// }
	// if (ioctl(keys_fd,0x4B45, 0x02)) {
	// 	perror("KDSKBMODE");
	// 	return 1;	
	// }
	 
	printf("old mod %x\n", oldkbmode);
	
	// ioctl(keys_fd,KDGKBMODE,&oldkbmode);
	char vk;
	while(1)
	{
		// c = getc(stdin);
		// printf("%2x   ",c);
		if(read(keys_fd, &t, sizeof(t)) == sizeof(t))
		{
			if(t.type==EV_KEY)
				// if(t.value==0 || t.value==1)
				if(t.value==1)
				{
					// vk = keymap(&t);
					printf("key %d %s vk %c  %d %2.2x\n", t.code, (t.value) ? "Pressed" : "Released", vk, vk,vk);
					// if(t.code == KEY_ESC)
					// 	break;
				}
		}
		// else {
		// 	printf("null\n");
		// 	sleep(1);
		// }
	}
	close(keys_fd);
	return 0;
}
