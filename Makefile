CC = cc
FLAGES= -Wall -Wextra -Werror
NAME = philo
RM = rm -f

SORCE = mainc.c lib.c philo.c timer.c 
OBC = $(SORCE:.c=.o)