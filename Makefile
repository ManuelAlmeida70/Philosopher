
NAME = philo

CC = cc

SRCS = 	main.c \
		init.c \
		monitor.c \
		utils.c \
		actions.c \
		time.c \
		thread_simulation.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
