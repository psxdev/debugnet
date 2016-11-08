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

typedef struct debugNetConfiguration
{
	int debugnet_initialized;
	int SocketFD;
	int logLevel;
	
} debugNetConfiguration;

#ifdef __cplusplus
extern "C"
{
#endif


int debugNetInit(const char *serverIp, int port, int level);
int debugNetInitWithConf(debugNetConfiguration *conf);
debugNetConfiguration *debugNetGetConf();
int debugNetSetConf(debugNetConfiguration *conf);
void debugNetFinish();
void debugNetUDPSend(const char *text);
void debugNetUDPPrintf(const char *format, ...);
void debugNetPrintf(int level, const char* format, ...);
void debugNetSetLogLevel(int level);
int debugNetCreateConf();

#ifdef __cplusplus
}
#endif
#endif
