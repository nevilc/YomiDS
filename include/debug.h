#ifndef H_DEBUG
#define H_DEBUG

#include <nds.h>

#include "options.h"

#define DPRINTF_BUFFER_SIZE 128
#define SASSERTF_BUFFER_SIZE 128

#define dprintf(msg, ...)													\
		do{																	\
			char _dprintf_buffer[DPRINTF_BUFFER_SIZE];						\
			int _dprintf_len = sprintf(_dprintf_buffer, msg, __VA_ARGS__);	\
			if (_dprintf_len < 0){											\
				dprint("dprintf buffer overflow\n");						\
			}else{															\
				dprint(_dprintf_buffer);										\
			}																\
		}while(false)

void dprint(const char* msg);

#define sassertf(e, msg, ...)													\
		do{																		\
			if (!(e)){															\
				char _sassertf_buffer[SASSERTF_BUFFER_SIZE];					\
				int _sassertf_len = sprintf(_sassertf_buffer, msg, __VA_ARGS__);\
				if (_sassertf_len < 0){											\
					sassert(false, "sassertf buffer overflow\n");				\
				}else{															\
					sassert(false, _sassertf_buffer);							\
				}																\
			}																	\
		}while(false)

#endif//H_DEBUG
