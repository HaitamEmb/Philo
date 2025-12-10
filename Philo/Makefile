NAME	=	philo

HEADER	=	philo.h

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -pthread -g

SRCS	=	main.c init.c threading.c routines.c utils.c time_utils.c

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADER)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re