NAME = webserv

SRC = main.cpp  ParceConf.cpp Servers.cpp Location.cpp Cgi.cpp  Multiplexing.cpp\
	  ../elidrys/src/Request.cpp\
	  ../elidrys/src/Get.cpp\
	  ../elidrys/src/Method.cpp\

CXX = c++

CXXFLAGS =  -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3 

OBJ = ${SRC:.cpp=.o}

RM	= rm -rf

all : ${NAME}

${NAME} : ${OBJ}
		${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

clean : 
		${RM} ${OBJ}

fclean : clean
		${RM} ${NAME}

re	: fclean all