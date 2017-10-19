NAME = _gl
SRC = \
	gl/core.c \
	gl/callback.c \
	gl/renderer.c \
	gl/shader.c \
	gl/util.c \
	gl/mlx_hook.c \
	gl/vertices.c \
	gl/window.c \
	gl/image.c \
	ps/_ps.c \
	cl/compute.c \
	cl/kernel.c

OBJ = $(SRC:.c=.o)

CC = clang
CFLAGS = \
	-O3 \
	-Wall \
	-Werror \
	-Wextra \
	-Iincs \
	-Ilibs/glfw/include/GLFW \
	-Ilibs/libft/inc \
	-Icolors

LDFLAGS = \
	-Llibs/libft -lft \
	-Llibs/glfw/src -lglfw3 \
	-framework Cocoa \
	-framework OpenGL \
	-framework OpenCL \
	-framework IOKit \
	-framework CoreVideo

GLFW = libs/glfw/src/libglfw3.a
LIBFT = libs/libft/libft.a
COLORS = colors/libcolors.a

TESTS = $(shell find ./demo -name "[^.]*.c")

all: $(LIBFT) $(COLORS) $(GLFW) $(NAME) test

$(NAME): $(OBJ)
	ar rc lib_gl.a $^
	ranlib lib_gl.a

$(GLFW):
	(cd libs/glfw ; cmake . ; make) ;

$(LIBFT):
	(cd libs/libft ; make) ;

$(COLORS):
	(cd colors ; make) ;

clean:
	rm -rf $(OBJ)
	(cd libs/glfw ; cmake . ; make clean) ;
	(cd libs/libft ; make clean) ;

fclean: clean
	rm -rf $(NAME)
	rm -rf $(subst .c,,$(notdir $(TESTS)))
	rm -rf $(subst .c,_temoin,$(notdir $(TESTS)))
	(cd libs/libft ; make fclean) ;

re: fclean all test

test: $(OBJ)
	$(foreach file,$(TESTS), \
		$(CC) -Llibs/libft -lft -Ilibs/libft/inc -lmlx -framework OpenGL -framework AppKit -o $(basename $(notdir $(file)))_temoin $(file); \
		$(CC) -D _GL $(CFLAGS) $(LDFLAGS) -o $(basename $(notdir $(file))) -L. -l_gl $(file); \
	)

.PHONY: all $(NAME) _gl clean fclean re test run kill
