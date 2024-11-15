NAME = minishell
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
SRCS =  srcs/main.c 					\
		srcs/ft_split.c 				\
		srcs/ft_itoa.c					\
		srcs/ft_split_one.c 			\
		srcs/utils_one.c				\
		srcs/utils_two.c				\
		srcs/memory_free.c				\
		srcs/checker_command.c			\
		srcs/parsing_command.c			\
		srcs/verefy_commands.c			\
		srcs/builtins/binarios.c		\
		srcs/builtins/binarios_one.c	\
		srcs/builtins/binarios_two.c	\
		srcs/builtins/binarios_treen.c	\
		srcs/builtins/binarios_four.c	\
		srcs/builtins/binarios_cd.c		\
		srcs/builtins/ft_sort_params.c	
		

OBJS = $(SRCS:.c=.o)
BG_GREEN = '\e[42m'

all:	$(NAME)
$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:	
		rm -f $(OBJS)
fclean: clean
		rm -f $(NAME)
re: fclean all
