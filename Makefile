NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c
OBJS = $(SRCS:.c=.o)

all:	$(NAME)
$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:	
		rm -f $(OBJS)
fclean: clean
		rm -f $(NAME)
re: fclean all
