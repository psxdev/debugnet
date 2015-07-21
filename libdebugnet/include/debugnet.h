/*
 *	debugnet library for PSP2 
 *	Copyright (C) 2010,2015 Antonio Jose Ramos Marquez (aka bigboss) @psxdev on twitter
 *  Repository https://github.com/psxdev/debugnet
 */
#ifndef _DEBUGNET_H_
#define _DEBUGNET_H_

#define NET_INIT_SIZE 1*1024*1024

#define NONE 0
#define INFO 1
#define ERROR 2
#define DEBUG 3	



int debugNetInit(char *serverIp, int port, int level);
void debugNetFinish();
void debugNetPrintf(int level, char* format, ...);
void debugNetSetLogLevel(int level);



#endif