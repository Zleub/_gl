struct test {
	struct {
		int x;
		int y;
	};

	struct tata {
		int w;
		int h;
	} t;

	int i;
};

int main(int argc, char const *argv[]) {
	struct test t;

	t.i = 42;
	printf("%d\n", t.i);
	return 0;
}
