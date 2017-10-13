#include <oo.h>

void * String_ctor(void * _self, va_list * app);
void * String_dtor(void * _self);

type(String, {
	char * text;
})

void delete(void * item);
void *new(const void * _class, ...)
{
	const struct Class * class = _class;
	void * p = calloc(1, class->size);
	if (!p)
		exit(EXIT_FAILURE);
	*(const struct Class **)p = class;
	if (class->ctor)
	{
		va_list ap;
		va_start(ap, _class);
		p = class->ctor(p, & ap);
		va_end(ap);
	}
	return p;
}

void * String_ctor(void * _self, va_list * app)
{
	struct String * self = _self;
	const char * text = va_arg(* app, const char *);
	// self->text = malloc(strlen(text) + 1);
	// strcpy(self->text, text);
	printf("%s %s\n", __func__, (char *)text);
	return self;
}
