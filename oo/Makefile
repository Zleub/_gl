# @Author: Debray Arnaud <adebray>
# @Date:   2017-08-12T09:29:05+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-08-12T10:13:29+02:00

NAME = ft_oo

SRC = test.c
OBJ = $(subst .c,.o,$(SRC))

export CC = clang
export CFLAGS = -Wall -Werror -Wextra -I.
export LDFLAGS =

all: $(NAME) test

%.h: %.h4
	m4 $< > $(basename $<).h

%.o: %.c
	m4 transpile.m4 $< | $(CC) -fPIC $(CFLAGS) -c -o $@ -xc -

$(NAME): oo.h $(OBJ)
	ar rc liboo.a $(OBJ)
	ranlib liboo.a

test: main.o
	$(CC) -L. -loo $^ -o a.out

clean:
	rm -f $(OBJ)
	rm -f main.o

fclean:
	rm -f $(OBJ)
	rm -f main.o
	rm -f liboo.a

re:
	make fclean
	make all

.PHONY: all $(NAME) clean fclean re test
