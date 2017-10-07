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
CFLAGS = -O3 -Wall -Werror -Wextra -Iincs -Ilibs/glfw/include/GLFW
LDFLAGS = -Llibs/glfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework OpenCL -framework IOKit -framework CoreVideo
GLFW = libs/glfw/src/libglfw3.a

all: $(GLFW) $(NAME) _gl test

$(NAME): $(OBJ) main.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $^

_gl: $(OBJ)
	ar rc lib_gl.a $^
	ranlib lib_gl.a

libs/glfw/src/libglfw3.a:
	(cd libs/glfw ; cmake . ; make) ;

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all test

test: $(OBJ)
	$(CC) -O3 -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit -o temoin demo/main_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o main_test -L. -l_gl demo/main_test.c

run:
	./temoin &
	./test &

kill:
	pkill temoin test
