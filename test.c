//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  test.c
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2016-08-14 22:42:12
// :ddddddddddhyyddddddddddd: Modified: Zleub
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <stdio.h>

struct test
{
	char a[3];
	struct {
		char b[3];
	};
	struct {
		char c[3];
	};
};

void print(struct test *t)
{
	printf("%s\n", t->a);
}

int main(void)
{
	struct test t = {
		"42",
		"43",
		"44"
	};

	print(&t);
	print((struct test *)((char *)(&t) + sizeof(char) * 3));
	print((struct test *)((char *)(&t) + sizeof(char) * 3 * 2));
	return (0);
}
