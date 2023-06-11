NAME = philo
CC = cc
CFLAGS = -Wextra -Werror -Wall
LINKFLAGS =  -L/Users/crepou/Documents/LeakSanitizer -llsan -lc++
SRCS = actions.c main.c philosophers.c time.c initialize.c threads.c mutex.c ft_atoi.c utils.c error.c ft_split.c ft_atol.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o philo

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean