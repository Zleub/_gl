




#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

struct Class { size_t size;
	void * (* ctor) (void * self, va_list * app);
	void * (* dtor) (void * self);
 };


