# # -*- Makefile -*-
# NAME = ft_printf
NAME= philo
CC= cc
CFLAGS = -g -Wall -Wextra -Werror -pthread
FILES = philo init philo_cycle philo_monitor utils utils1

all: $(NAME)

$(NAME) : $(FILES:=.o)
	$(CC) $(CFLAGS) $(FILES:=.o) -o $(NAME)
clean:
	rm -f $(FILES:=.o)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
