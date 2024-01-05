# # -*- Makefile -*-
# NAME = ft_printf
NAME= philo
CC= cc
CFLAGS = -g -Wall -Wextra -Werror
FILES = main init utils

all: $(NAME)

$(NAME) : $(FILES:=.o)
	$(CC) $(CFLAGS) $(FILES:=.o) -o $(NAME)
clean:
	rm -f $(FILES:=.o) $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
