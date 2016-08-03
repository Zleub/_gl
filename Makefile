NAME = glfw_test
SRC = \
	gl/callback.c \
	gl/renderer.c \
	gl/shader.c \
	gl/util.c \
	gl/vertices.c \
	gl/window.c \
	ps/_ps.c \
	cl/compute.c \
	cl/kernel.c \
	main.c

OBJ = $(SRC:.c=.o)

CC = clang
CFLAGS = -arch x86_64 -Os -Wall -Werror -Wextra -Iincs
LDFLAGS = -Llibs/glfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework OpenCL -framework IOKit -framework CoreVideo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $^ ; echo $$?

glfw:
	(cd libs/glfw ; cmake . ; make)

clean:
	rm -rf $(OBJ)
	rm -rf $(KC)
	rm -rf $(KOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
