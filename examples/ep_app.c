#include "epollserver.h"
#include <stdio.h>


int epFUI_OnAccept(int cmd,void *arg)
{
	printf("----OnAccept----\n");
	return 0;
}

int epFUI_OnRecv(int cmd,void *arg)
{
	printf("----OnRecv----\n");
	return 0;
}

int epFUI_OnError(int cmd,void *arg)
{
	printf("----OnError----\n");
	return 0;
}

int epFUI_OnRemoveClose(int cmd,void *arg)
{
	printf("----OnRemoveClose----\n");
	return 0;
}

int epFUI_OnConnect(struct ep_t *pep, struct ep_con_t *pnode)
{
	printf("----epFUI_OnConnect----\n");
	return 0;
}
int epFUI_OnRelease(struct ep_t *pep)
{
	printf("----epFUI_OnRelease----\n");
	return 0;
}
int epFUI_OnClose(struct ep_t *pep, struct ep_con_t *pnode)
{
	printf("----epFUI_OnClose----\n");
	return 0;
}
void ep_Callback(struct ep_t *pep)
{
	pep->pFUI_OnAccept      = epFUI_OnAccept;
	pep->pFUI_OnConnect     = epFUI_OnConnect;
	pep->pFUI_OnRecv        = epFUI_OnRecv;
	pep->pFUI_OnError       = epFUI_OnError;
	pep->pFUI_OnRemoveClose = epFUI_OnRemoveClose;
	pep->pFUI_OnRelease     = epFUI_OnRelease;
	pep->pFUI_Close         = epFUI_OnClose;
}