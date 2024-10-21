NAME = minishell
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
SRCS =  srcs/main.c 		\
		srcs/ft_split.c 	\
		srcs/ft_split_one.c

OBJS = $(SRCS:.c=.o)

all:	$(NAME)
$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:	
		rm -f $(OBJS)
fclean: clean
		rm -f $(NAME)
re: fclean all
