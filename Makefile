NAME = glfw_test
SRC = \
	gl/core.c \
	gl/callback.c \
	gl/renderer.c \
	gl/shader.c \
	gl/util.c \
	gl/vertices.c \
	gl/window.c \
	gl/image.c \
	ps/_ps.c \
	cl/compute.c \
	cl/kernel.c

OBJ = $(SRC:.c=.o)

CC = clang
CFLAGS = -O3 -Wall -Werror -Wextra -Iincs
LDFLAGS = -Llibs/glfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework OpenCL -framework IOKit -framework CoreVideo

all: glfw $(NAME) _gl test

$(NAME): $(OBJ) main.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $^

_gl: $(OBJ)
	ar rc lib_gl.a $^
	ranlib lib_gl.a

glfw:
	(cd libs/glfw ; cmake . ; make)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all test

test: $(OBJ) main_test.c
	$(CC) -O3 -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit -o temoin main_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test $^

run:
	./temoin &
	./test &

kill:
	pkill temoin test
