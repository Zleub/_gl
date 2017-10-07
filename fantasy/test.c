#include <stdio.h>
#include <fantasy.h>

struct my_set {
	struct {
		bool (*equals)(struct my_set *);
	};
};

int main(int argc, char const *argv[]) {
	(void)argc;
	(void)argv;

	struct my_set s;
	printf("%p\n", &s);
	return 0;
}
