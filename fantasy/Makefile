NAME = libfantasy.a
SRC = \
	setoid.c

OBJ = $(SRC:.c=.o)

CC = clang
CFLAGS = -O3 -Wall -Werror -Wextra -I. -Xclang -fdump-record-layouts
LDFLAGS =

all: $(NAME) test

%.o: %.c
	m4 $< | $(CC) $(CFLAGS) -c -o $@ -xc -

$(NAME): $(OBJ)
	ar rc $(NAME) $^
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all test

test: $(OBJ) test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test $^

run:
	./temoin &
	./test &

kill:
	pkill temoin test
