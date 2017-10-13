define(BaseClass,
	size_t size;
	void * (* ctor) (void * self, va_list * app);
	void * (* dtor) (void * self);
)

define(type, `struct $1 {
	BaseClass
	char * text;
};

extern const void *$1;

const struct Class _$1 = {
	sizeof(struct $1),
	$1_ctor,
	$1_dtor
};

const void *$1 = & _$1;

')
