NAME = minishell
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
SRCS =  srcs/main.c 			\
		srcs/ft_split.c 		\
		srcs/ft_split_one.c 	\
		srcs/utils_one.c		\
		srcs/memory_free.c		\
		srcs/checker_command.c	\
		srcs/parsing_command.c	\
		srcs/verefy_commands.c
		

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
