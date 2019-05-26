
#ifndef _LIBMNG_TEMPLATES_H
#define _LIBMNG_TEMPLATES_H

//#define printFunctionTrace(jump) printf("[%5d] %s %s()%c", __LINE__, __FILE__, __func__, (char)(jump)?'\n':0x20);
#define printFunctionTrace(jump) cobprintf((unsigned char*)"[%5d] %s %s()%c", __LINE__, __FILE__, __func__, (char)(jump)?'\n':0x20);

#endif // LIBMNG_TEMPLATES_H