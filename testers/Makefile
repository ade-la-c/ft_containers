NAME =		containers

SRCS =		./map_tester.cpp	\
			./stack_tester.cpp	\
			./vector_tester.cpp	\
			./main.cpp

CXX =		c++

CXXFLAGS +=	-Wall -Werror -Wextra -std=c++98 # -fsanitize=address -g3

RM =		rm -rf

OBJS =		${SRCS:.cpp=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
