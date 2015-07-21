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
#include "debugnet.h"




static int debugnet_initialized=0;
int SocketFD = -1;
static void *net_memory = NULL;
static SceNetInAddr vita_addr;
int sceClibVsnprintf(char *, SceSize, const char *, va_list); 
int logLevel=INFO;

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
  sceNetSend(SocketFD, buffer, strlen(buffer), 0);
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
	
		if (level>logLevel)
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
	logLevel=level;	
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
	debugNetSetLogLevel(level);
    if (debugnet_initialized) {
        return debugnet_initialized;
    }
    /*net initialazation code from xerpi at https://github.com/xerpi/FTPVita/blob/master/ftp.c*/
    /* Init Net */
    if (sceNetShowNetstat() == PSP2_NET_ERROR_ENOTINIT) {
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
    ret = sceNetCtlInetGetInfo(PSP2_NETCTL_INFO_GET_IP_ADDRESS, &info);
    //printf("sceNetCtlInetGetInfo(): 0x%08X\n", ret);


    /* Save the IP of PSVita to a global variable */
    sceNetInetPton(PSP2_NET_AF_INET, info.ip_address, &vita_addr);
	
	/* Create datagram udp socket*/
    SocketFD = sceNetSocket("debugnet_socket",
        PSP2_NET_AF_INET , PSP2_NET_SOCK_DGRAM, PSP2_NET_IPPROTO_UDP);
   
    memset(&stSockAddr, 0, sizeof stSockAddr);
	
	/*Populate SceNetSockaddrIn structure values*/
    stSockAddr.sin_family = PSP2_NET_AF_INET;
    stSockAddr.sin_port = sceNetHtons(port);
    sceNetInetPton(PSP2_NET_AF_INET, serverIp, &stSockAddr.sin_addr);

	/*Connect socket to server*/
    sceNetConnect(SocketFD, (struct SceNetSockaddr *)&stSockAddr, sizeof stSockAddr);

	/*Show log on pc/mac side*/
	debugNetUDPPrintf("debugnet initialized\n");
	debugNetUDPPrintf("Copyright (C) 2010,2015 Antonio Jose Ramos Marquez aka bigboss @psxdev\n");
	debugNetUDPPrintf("This Program is subject to the terms of the Mozilla Public\n"
		"License, v. 2.0. If a copy of the MPL was not distributed with this\n"
		"file, You can obtain one at http://mozilla.org/MPL/2.0/.\n");
    debugNetUDPPrintf("ready to have a lot of fun...\n");

	/*library debugnet initialized*/
    debugnet_initialized = 1;

    return debugnet_initialized;
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
    if (debugnet_initialized) {
       
        sceNetCtlTerm();
        sceNetTerm();

        if (net_memory) {
            free(net_memory);
            net_memory = NULL;
        }

        debugnet_initialized = 0;
    }
}