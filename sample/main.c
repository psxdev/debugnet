/*
 *	debugnet library sample for PSP2 
 *	Copyright (C) 2010,2015 Antonio Jose Ramos Marquez (aka bigboss) @psxdev on twitter
 *  Repository https://github.com/psxdev/debugnet
 */
#include <debugnet.h>
#include <psp2/kernel/processmgr.h>



#define ip_server "192.168.1.3"
#define port_server 18194
int main()
{
	int ret;
	ret=debugNetInit(ip_server,port_server,DEBUG);
	debugNetPrintf(DEBUG,"Test debug level %d\n",ret);
	debugNetPrintf(ERROR,"Test error level %d\n",ret);
	debugNetPrintf(INFO,"Test info level %d\n",ret);	
	debugNetFinish();
	sceKernelExitProcess(0);
	return 0;
}