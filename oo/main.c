#include <stdio.h>
#include <oo.h>

void delete (void * item);
void *new(const void * _class, ...);

int main(void) {
	printf("%s\n", "Hello World !");

	void * s = new(String, "Hello !", "World !");
	(void)s;
	return (0);
}
