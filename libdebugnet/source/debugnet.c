/*
 *	debugnet library for PSP2 
 *	Copyright (C) 2010,2015 Antonio Jose Ramos Marquez (aka bigboss) @psxdev on twitter
 *  Repository https://github.com/psxdev/debugnet
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/types.h>
#include <psp2/kernel/clib.h>
#include "debugnet.h"

int debugnet_external_conf=0;
debugNetConfiguration *dconfig=NULL;
static void *net_memory = NULL;
static SceNetInAddr vita_addr;

/**
 * UDP printf for debugnet library 
 *
 * @par Example:
 * @code
 * debugNetUDPPrintf("This is a test\n");
 * @endcode
 */
void debugNetUDPPrintf(const char* fmt, ...)
{
  char buffer[0x800];
  va_list arg;
  va_start(arg, fmt);
  sceClibVsnprintf(buffer, sizeof(buffer), fmt, arg);
  va_end(arg);
  sceNetSend(dconfig->SocketFD, buffer, strlen(buffer), 0);
}
/**
 * Log Level printf for debugnet library 
 *
 * @par Example:
 * @code
 * debugNetPrintf(INFO,"This is a test\n");
 * @endcode
 *
 * @param level - NONE,INFO,ERROR or DEBUG
 */
void debugNetPrintf(int level, char* format, ...) 
{
	char msgbuf[0x800];
	va_list args;
	
		if (level>dconfig->logLevel)
		return;
       
	va_start(args, format);
       
	sceClibVsnprintf(msgbuf,2048, format, args);
	msgbuf[2047] = 0;
	va_end(args);
	switch(level)
	{
		case INFO:
	    	debugNetUDPPrintf("[INFO]: %s",msgbuf);  
	        break;
	   	case ERROR: 
	    	debugNetUDPPrintf("[ERROR]: %s",msgbuf);
	        break;
		case DEBUG:
	        debugNetUDPPrintf("[DEBUG]: %s",msgbuf);
	        break;
		case NONE:
			break;
	    default:
		    debugNetUDPPrintf("%s",msgbuf);
       
	}
}
/**
 * Set log level for debugnet library 
 *
 * @par Example:
 * @code
 * debugNetSetLogLevel(DEBUG);  
 * @endcode
 * @param level - DEBUG,ERROR,INFO or NONE 
 */
void debugNetSetLogLevel(int level)
{
	if(dconfig)
	{
		dconfig->logLevel=level;	
	}
}
/**
 * Init debugnet library 
 *
 * @par Example:
 * @code
 * #define LOGLEVEL 3  
 * int ret;
 * ret = debugNetInit("172.26.0.2", 18194, DEBUG);
 * @endcode
 *
 * @param serverIP - your pc/mac server ip
 * @param port - udp port server
 * @param level - DEBUG,ERROR,INFO or NONE 
 */
int debugNetInit(char *serverIp, int port, int level)
{
    int ret;
    SceNetInitParam initparam;
    SceNetCtlInfo info;
    struct SceNetSockaddrIn stSockAddr;
	
	if(debugNetCreateConf())
	{
		return dconfig->debugnet_initialized;
	}
	
	debugNetSetLogLevel(level);
    
    
    /*net initialazation code from xerpi at https://github.com/xerpi/FTPVita/blob/master/ftp.c*/
    /* Init Net */
    if (sceNetShowNetstat() == SCE_NET_ERROR_ENOTINIT) {
        net_memory = malloc(NET_INIT_SIZE);

        initparam.memory = net_memory;
        initparam.size = NET_INIT_SIZE;
        initparam.flags = 0;

        ret = sceNetInit(&initparam);
        //printf("sceNetInit(): 0x%08X\n", ret);
    } else {
        //printf("Net is already initialized.\n");
    }

    /* Init NetCtl */
    ret = sceNetCtlInit();
    //printf("sceNetCtlInit(): 0x%08X\n", ret);
   

    /* Get IP address */
    ret = sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info);
    //printf("sceNetCtlInetGetInfo(): 0x%08X\n", ret);


    /* Save the IP of PSVita to a global variable */
    sceNetInetPton(SCE_NET_AF_INET, info.ip_address, &vita_addr);
	
	/* Create datagram udp socket*/
    dconfig->SocketFD = sceNetSocket("debugnet_socket",
        SCE_NET_AF_INET , SCE_NET_SOCK_DGRAM, SCE_NET_IPPROTO_UDP);
   
    memset(&stSockAddr, 0, sizeof stSockAddr);
	
	/*Populate SceNetSockaddrIn structure values*/
    stSockAddr.sin_family = SCE_NET_AF_INET;
    stSockAddr.sin_port = sceNetHtons(port);
    sceNetInetPton(SCE_NET_AF_INET, serverIp, &stSockAddr.sin_addr);

	/*Connect socket to server*/
    sceNetConnect(dconfig->SocketFD, (struct SceNetSockaddr *)&stSockAddr, sizeof stSockAddr);

	/*Show log on pc/mac side*/
	debugNetUDPPrintf("debugnet initialized\n");
	debugNetUDPPrintf("Copyright (C) 2010,2015 Antonio Jose Ramos Marquez aka bigboss @psxdev\n");
	debugNetUDPPrintf("This Program is subject to the terms of the Mozilla Public\n"
		"License, v. 2.0. If a copy of the MPL was not distributed with this\n"
		"file, You can obtain one at http://mozilla.org/MPL/2.0/.\n");
    debugNetUDPPrintf("ready to have a lot of fun...\n");

	/*library debugnet initialized*/
    dconfig->debugnet_initialized = 1;

    return dconfig->debugnet_initialized;
}

debugNetConfiguration *debugNetGetConf()
{	
	if(dconfig)
	{
		return dconfig;
	}
	
	return NULL;	
}
int debugNetSetConf(debugNetConfiguration *conf)
{	
	if(conf)
	{
		dconfig=conf;
		debugnet_external_conf=1;
		return dconfig->debugnet_initialized;
	}
	
	return 0;	
}
int debugNetInitWithConf(debugNetConfiguration *conf)
{
	int ret;
	ret=debugNetSetConf(conf);
	if(ret)
	{
		debugNetPrintf(INFO,"debugnet already initialized using configuration from ps4link\n");
		debugNetPrintf(INFO,"debugnet_initialized=%d SocketFD=%d logLevel=%d\n",dconfig->debugnet_initialized,dconfig->SocketFD,dconfig->logLevel);
		debugNetPrintf(INFO,"ready to have a lot of fun...\n");
		return dconfig->debugnet_initialized;
	}
	else
	{
		return 0;
	}
	
}
int debugNetCreateConf()
{	
	if(!dconfig)
	{
		dconfig=malloc(sizeof(debugNetConfiguration));
		dconfig->debugnet_initialized=0;
		dconfig->SocketFD = -1;
		dconfig->logLevel=INFO;	
		return 0;
	}
	
	if(dconfig->debugnet_initialized)
	{
		return 1;
	}
	return 0;			
}


/**
 * Finish debugnet library 
 *
 * @par Example:
 * @code
 * debugNetFinish();
 * @endcode
 */
void debugNetFinish()
{
	
	if(!debugnet_external_conf)
	{
    	if (dconfig->debugnet_initialized) {
        	dconfig->debugnet_initialized = 0;
			dconfig->SocketFD=-1;
			
	        if (net_memory) {
	            free(net_memory);
	            net_memory = NULL;
	        }
    	}
	}
   
}