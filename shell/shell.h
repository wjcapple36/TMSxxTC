/**
 ******************************************************************************
 * @file	shell.h
 * @brief	MenglongWu\n
 minishell 命令行各命令入口函数定义

 仿照Uboot编写的minishell目前尚不支持随时变动命令行入口函数“列表”，需要将
 所用到的函数逐个写到INIT_CMD宏定义下如要实现一个命令名为 sn 的接口，在本shell.h
 里声明，在其他文件里实现 cmd_sn 代码
 \code {.cpp}
 int cmd_sn(int argc, char **argv);

 #define INIT_CMD \
		{(char*)"sn",cmd_sn,(char*)" get sn"}, \
 \endcode
 
 minishell.c 会定义里声明INIT_CMD列表为
 \code {.cpp}
static struct cmd_table cmd_tbl_list[] = 
{
	INIT_CMD,
	{(char*)"help",do_help,(char*)"shell help"},
	{(char*)"quit",do_null,(char*)"quit shell"},
	{0,0,0},
};
 \endcode
 其中默认包含help、quit命令，命令末端以全空指针结束。\n
 \n
 最新的 minishell_core_ex.c 在开发中，支持命令行随意变动，命令提示，命令自动补全


- 2014-11-11,Menglong Wu,DreagonWoo@163.com
 	- Add sh_editpath

 *****************************************************************************
*/


#ifndef _MINI_SHELL_H_
#define _MINI_SHELL_H_

// int do_setenv(char **argv,int argc);
// int do_saveenv(char **argv,int argc);
// int do_help(int argc,char **argv);
// int do_null(int argc,char **argv);
// int do_hostname(int argc,char **argv);

// extern int do_sector(int argc,char **argv);
// extern int do_erase(int argc,char **argv);
// extern int do_writepage(int argc,char **argv);
// extern int do_readpage(int argc,char **argv);
// extern int do_nandscan(int argc,char **argv);

// extern int do_format(int argc,char **argv);
// extern int do_ls(int argc,char **argv);
// extern int do_mkdir(int argc,char **argv);
// extern int do_rm(int argc,char **argv);
// extern int do_wfile(int argc,char **argv);
// extern int do_rfile(int argc,char **argv);

// extern int do_copy_sdram2nand(int argc,char **argv);
// extern int do_file2nand(int argc,char **argv);
// extern int do_mount(int argc,char **argv);
#include "minishell_core.h"

int cmd_InfoServer(int argc,char **argv);
int cmd_Connect(int argc,char **argv);
int cmd_Close(int argc,char **argv);


int cmd_listfile(int argc, char **argv);
int cmd_tmsall(int argc,char **argv);
int cmd_tmsscan(int argc,char **argv);
int cmd_intface(int argc,char **argv);
int cmd_sudo(int argc,char **argv);
int cmd_Disp(int argc,char **argv);
int cmd_sql(int argc, char **argv);
int cmd_select(int argc, char **argv);
int cmd_delete(int argc, char **argv);
int cmd_insert(int argc, char **argv);
int cmd_im(int argc, char **argv);
int cmd_remotecmd(int argc, char **argv);
int cmd_opm(int argc, char **argv);
int cmd_olp(int argc, char **argv);
int cmd_enable(int argc, char **argv);
int cmd_term_connect(int argc,char **argv);
int cmd_update(int argc, char **argv);
int cmd_device(int argc, char **argv);
int cmd_setip(int argc, char **argv);
int cmd_osw(int argc, char **argv);

int cmd_sms(int argc, char **argv);
int cmd_otdr(int argc, char **argv);
int cmd_gver(int argc, char **argv);
int cmd_gdev(int argc, char **argv);
int cmd_sn(int argc, char **argv);
int cmd_route(int argc, char **argv);
int cmd_produce(int argc, char **argv);
int cmd_atb(int argc, char **argv);
int cmd_sip(int argc, char **argv);
int cmd_epsend(int argc, char **argv);
int cmd_testnetpacket(int argc, char **argv);
int cmd_testnetpacket_file(int argc, char **argv);
// W_BOOT_CMD(epsend,cmd_epsend,"cmd epoll server send");

#define INIT_CMD \
		{(char*)"epsend",cmd_epsend,(char*)" set ip"}, \
		{(char*)"sip",cmd_sip,(char*)" set ip"}, \
		{(char*)"sn",cmd_sn,(char*)" get sn"}, \
		{(char*)"routeline",cmd_route,(char*)" get sn"}, \
		{(char*)"gver",cmd_gver,(char*)" otdr"}, \
		{(char*)"gdev",cmd_gdev,(char*)" otdr"}, \
		{(char*)"otdr",cmd_otdr,(char*)" otdr"}, \
		{(char*)"sms",cmd_sms,(char*)"config sms"}, \
		{(char*)"osw",cmd_osw,(char*)"config osw"}, \
		{(char*)"sip",cmd_setip,(char*)"Set device IP"}, \
		{(char*)"inf",cmd_InfoServer,(char*)"shell help"}, \
		{(char*)"connect",cmd_Connect,(char*)"shell help"}, \
		{(char*)"close",cmd_Close,(char*)"shell help"}, \
		\
		{(char*)"sql",cmd_sql,(char*)"call sqlite3 console"}, \
		{(char*)"dbselect",cmd_select,(char*)"Datebase select tmsxxdb"}, \
		{(char*)"dbdelete",cmd_delete,(char*)"Datebase delete tmsxxdb"}, \
		{(char*)"dbinsert",cmd_insert,(char*)"Datebase insert tmsxxdb"}, \
		{(char*)"im",cmd_im,(char*)"Announce manager"}, \
		{(char*)"r",cmd_remotecmd,(char*)"Run shell on target"}, \
		{(char*)"tconnect",cmd_term_connect,(char*)"terminal connect"}, \
		{(char*)"opm",cmd_opm,(char*)"Specity OPM configuration"}, \
		{(char*)"update",cmd_update,(char*)"Update target program"}, \
		{(char*)"olp",cmd_olp,(char*)"Specity OLP configuration"}, \
		{(char*)"enable",cmd_enable,(char*)"Enable/Disable something"}, \
		{(char*)"tms",cmd_tmsall,(char*)"shell help"}, \
		{(char*)"lf",cmd_listfile,(char*)"shell help"}, \
		{(char*)"scan",cmd_tmsscan,(char*)"Scan and update connect state"}, \
		{(char*)"interface",cmd_intface,(char*)""}, \
		{(char*)"dev",cmd_device,(char*)"Specity device and change"}, \
		{(char*)"sudo",cmd_sudo,(char*)"shell help"}, \
		{(char*)"gpro",cmd_produce,(char*)" get sn"}, \
		{(char*)"atb",cmd_atb,(char*)" get sn"}, \
		{(char*)"tnp",cmd_testnetpacket,(char*)"Test net packet id"}, \
		{(char*)"tnpf",cmd_testnetpacket_file,(char*)"Test net packet id"}, \
		{(char*)"display",cmd_Disp,(char*)"Display current system information"} 


		
// {"inf",NULL,},
#endif

