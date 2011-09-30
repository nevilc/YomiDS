#include "debug.h"

void dprint(const char* msg){
#ifdef DEBUG
	nocashMessage(msg);
#endif
}
