SRCS = src/main.c src/utils.c src/begin_end.c src/printers.c

OBJS = ${SRCS:.c=.o}

HEADERF = include

HEADER = philo.h

NAME = philo

CC = gcc

RM = rm -f

FLAGS = #-fsanitize=address -g3#-Wall -Wextra -Werror  

%.o:	%.c ${HEADERF}/${HEADER}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I${HEADERF}

$(NAME):	${OBJS}
			${CC} ${FLAGS} -lncurses -o ${NAME} ${OBJS} -I${HEADERF}

all:		${NAME}

test:		all
			./philo 80 100 200 100 2

clean:
			${RM} ${OBJS} ${OBJBONUS}

fclean:		clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re