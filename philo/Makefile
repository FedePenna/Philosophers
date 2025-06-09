SRC			=	init.c\
	libutils.c\
	main.c\
	monitor.c\
	philo.c\
	utils.c\

OBJS_DIR	=	objs/

OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -pthread -gdwarf-4

RM			=	rm -f

INCLUDES	=	-I/usr/include

all:			$(NAME)

$(OBJS_DIR):
				mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c | $(OBJS_DIR)
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME):		$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)
				$(RM) -r $(OBJS_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

all:			$(NAME)

.PHONY:			all clean fclean re test
