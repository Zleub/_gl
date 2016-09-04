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
CFLAGS = -arch x86_64 -Os -Wall -Werror -Wextra -Iincs
LDFLAGS = -Llibs/glfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework OpenCL -framework IOKit -framework CoreVideo

all: $(NAME)

$(NAME): $(OBJ) main.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $^

glfw:
	(cd libs/glfw ; cmake . ; make)

clean:
	rm -rf $(OBJ)
	rm -rf $(KC)
	rm -rf $(KOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all test

test: $(OBJ) main_test.c
	$(CC) -framework OpenGL -framework AppKit -lmlx $(CFLAGS) -o temoin main_test.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o test $^
