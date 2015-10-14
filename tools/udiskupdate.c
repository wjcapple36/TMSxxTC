/**
 ******************************************************************************
 * @file	udiskupdate.c
 * @brief	U盘自动升级


* @section 其他项目怎么移植
用于TMSxx项目设备通过U盘自动升级数据库、应用程序以及备份，其他Linux环境项目也可以
使用该可执行文件，只需要在 /bin/bak.sh、/bin/update.sh、/bin/doupdate.sh做相应批处理即可。
/bin/doupdate.sh脚本在启动时候运行，用于将 cp path\\file.new path\\file。\n
其余两个脚本在U盘挂载成功后自动备份、升级文件

* @section 本程序实现方式
 	-# 解析NETLINK_KOBJECT_UEVENT对象返回的字符
 	-# 遍历cat /proc/partitions得到可挂载对象
 	-# 挂载成功后执行备份、升级

Windows可以通过消息队列得到当前刚插入、拔出U盘的消息，附带盘符名，比起在linux解析若干行
符串要方便，以后对uevent了解后对本代码做修改

* @section 实际成果
*	- 采用epoll机制做服务器，主要

- 2015-6-24,Menglong Wu,DreagonWoo@163.com
 	- 通过NETLINK_KOBJECT_UEVENT监听系统事件，解析recv决定挂载、卸载U盘，

*/

#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	
#include <ctype.h>	
#include <sys/un.h>	
#include <sys/ioctl.h>	
#include <sys/socket.h>	
#include <linux/types.h>	
#include <linux/netlink.h>	
#include <errno.h>	
#include <unistd.h>	
#include <arpa/inet.h>	
#include <netinet/in.h>	

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <stdio.h>

#define UEVENT_BUFFER_SIZE 2048	

#define DISK_COUNT 16
#define DISK_NAME  32
char g_disk[DISK_COUNT][DISK_NAME];
char g_mountdisk[DISK_NAME];
char g_disk_count = 0;

int g_ismound = 1;

int mountudisk(char *disk);




static int init_hotplug_sock()		
{	
	const int buffersize = 1024;	
	int ret;	

	struct sockaddr_nl snl;	
	bzero(&snl, sizeof(struct sockaddr_nl));	
	snl.nl_family = AF_NETLINK;	
	snl.nl_pid = getpid();	
	snl.nl_groups = 1;	

	int s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);	
	if (s == -1)	 
	{	
		perror("socket");	
		return -1;	
	}	
	setsockopt(s, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));	

	ret = bind(s, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));	
	if (ret < 0)	 
	{	
		perror("bind");	
		close(s);	
	return -1;	
	}	

	return s;	
}	


void autobak()
{
	printf("-----------------------     Bak     -----------------------\n");
	mkdir("/mnt/udisk/bak",(1 & ~1 & 0777));
	printf("load /bin/bak.sh\n");
	// 导入外部脚本编写备份操作
	system("/bin/bak.sh");
	// system("cp /etc/tmsxx.db /mnt/udisk/bak/tmsxx.db");
	// system("cp /usr/MenglongWu/bin/tms4412.elf /mnt/udisk/bak/tms4412.elf");
	// system("cp /usr/MenglongWu/bin/targetExe-r /mnt/udisk/bak/targetExe-r");



}
void autoupdate()
{
	printf("-----------------------    update   -----------------------\n");
	printf("load /bin/update.sh\n");
	// 导入外部脚本编写更新操作
	system("/bin/update.sh");
	// system("cp /mnt/udisk/update/tmsxx.db /etc/tmsxx.db.new ");
	// system("cp /mnt/udisk/update/tms4412.elf /usr/MenglongWu/bin/tms4412.elf.new");
	// system("cp /mnt/udisk/update/targetExe-r /usr/MenglongWu/bin/tms4412..new");
}

int checkudisk()
{
	umount("/mnt/udisk");
	for (int i = 0; i < g_disk_count; i++) {
		printf("disk %s\n", g_disk[i]);
		if (0 == mountudisk(g_disk[i]) ) {
		// if (0 == mountudisk("sdb1") ) {
			printf("-----------------------   find %s  -----------------------\n", g_disk[i]);

			g_ismound = 1;
			return 0;
		}
	}

	g_ismound = 0;
	return -1;
}


/**
 * @brief	自动挂载
 * @see	
 */

int mountudisk(char *disk)
{
	int ret;
	char spath[256];
	char dpath[256];

	sprintf(spath, "/dev/%s", disk);
	sprintf(dpath, "/mnt/udisk");
	printf("spath %s, dpath %s\n", spath, dpath);
	// ret = umount("/mnt/udisk");
	// printf("umount = %d\n", ret);

	// 创建一个目录，mask填写阅读 man 2 mkdir
	ret = mkdir(dpath,(1 & ~1 & 0777));
	printf("mkdir = %d\n", ret);

	// ret = mount(spath, dpath, "vfat", NULL, NULL);
	ret = mount(spath, dpath, "vfat", NULL, NULL);
	printf("mount = %d\n", ret);

	return ret;
}

/**
 * @brief	检查有多少个磁盘，通过读取/proc/partitions

 root@fnc:/# cat /proc/partitions 
major minor  #blocks  name

   8        0   20971520 sda
   8        1   20051968 sda1
   8        2          1 sda2
   8        5     916480 sda5
   8       16    1953792 sdb
   8       17    1949760 sdb1
 */

int checkdisk()
{
	FILE *fp;
	char buf[1024];
	char *pret;
	char unuse0[20];
	char unuse1[20];
	char unuse2[20];
	char disk[20];

	bzero(g_disk, sizeof(g_disk));
	g_disk_count = 0;
	fp = fopen("/proc/partitions","r");
	if (fp == NULL) {
		printf("open error");
		exit(0);    
	}


	while(feof(fp) != 1) {
		// 读取缓存
		fgets(buf, 1024, fp);	
		
		// 分离出盘符
		sscanf(buf,"%*s%*s%*s%s",disk);
		// printf("find disk %s\n", disk);
		// 挂载U盘，不挂载sd卡
		if ( memcmp(disk, "sd", 2) == 0 ) {
			// printf("find disk %s\n", disk);
			if (g_disk_count > DISK_COUNT || strlen(disk) > DISK_NAME) {
				continue;
			}
			strcpy(g_disk[g_disk_count], disk);

			g_disk_count++;
		}

	}

	for( int i = 0; i < g_disk_count; i++) {
		printf("%s\n", g_disk[i]);
	}	
	fclose(fp);
	return 0;
}


int main(int argc, char* argv[])	
{	
	int hotplug_sock = init_hotplug_sock();	
	int last_count = 999;
	
	checkdisk();
	checkudisk();
	while(1)	
	{	
		/* Netlink message buffer */	
		char buf[UEVENT_BUFFER_SIZE * 2] = {0};	
		recv(hotplug_sock, &buf, sizeof(buf), 0);	
		printf("buf :%s\n", buf);

		if ( memcmp(buf,"add",strlen("add")) == 0) {
			printf("add............\n");
			checkdisk();
			printf("g_disk_count %d\n", g_disk_count);
			if (last_count != g_disk_count) {
				last_count = g_disk_count;
			
				if (g_disk_count == 0) {
					
				}
				for (int i = 0; i < 3; i++) {
					if (0 == checkudisk()) {
						// 稍作延时
						autobak();
						autoupdate();
						printf("sleep ....................\n");
						sleep(3);
						// 修补代码，防止拷贝进去后读不出
						umount("/mnt/udisk");
						printf("-----------------------      OK     -----------------------\n");

						break;
					}
					sleep(2);
				}
			}
		}
		else if ( memcmp(buf,"remove", strlen("remove")) == 0) {
			printf("remove............\n");
			umount("/mnt/udisk");
		}

		/* USB 设备的插拔会出现字符信息，通过比较不同的信息确定特定设备的插拔，在这添加比较代码 */
		
		
		continue;
		
		
		
		
		
		

	}
	return 0;	
}