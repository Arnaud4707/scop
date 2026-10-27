NAME= prog

MODEL ?= 0

CXX= c++
CXXFLAGS= -Wall -Wextra -std=c++11 -D MODEL=$(MODEL) -g3
LDFLAGS= -lGL -lglfw -ldl -g3
HEADER= include/header.hpp include/shader.hpp include/camera.hpp include/ObjectBlender.hpp \
		include/fonction_math.hpp include/Vec2.hpp include/Vec3.hpp include/Vec4.hpp \
		include/Mat2.hpp include/Mat3.hpp include/Mat4.hpp include/global.hpp include/structure.hpp
DIR_SRC = src/
PATH_SRC= Shader.cpp ObjectBlender.cpp global.cpp image.cpp fonction.cpp init.cpp main.cpp
SRC= $(addprefix $(DIR_SRC), $(PATH_SRC))
DIR_OBJ= obj/
OBJ= $(addprefix  $(DIR_OBJ), $(PATH_SRC:.cpp=.o))
OBJ_GLAD= obj/glad.o
GLAD= glad.c

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp -I"$HOME/local/include $(HEADER)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(OBJ_GLAD) -I"$HOME/local/include $(HEADER)
	$(CXX) $(OBJ) $(OBJ_GLAD) $(LDFLAGS) -o $(NAME)

$(OBJ_GLAD): -I"$HOME/local/include $(GLAD)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $(GLAD) -o $(OBJ_GLAD)

all: $(NAME)

clean: 
	rm -rf $(OBJ) $(DIR_OBJ) $(OBJ_GLAD)

fclean: clean 
	rm -rf $(NAME)

re: fclean
	@make --no-print-directory all

teapot: 
		$(MAKE) fclean
		$(MAKE) MODEL=2 all

teapot2: 
		$(MAKE) fclean
		$(MAKE) MODEL=3 all

42: 
		$(MAKE) fclean
		$(MAKE) MODEL=0 all

42N: 
		$(MAKE) fclean
		$(MAKE) MODEL=1 all

dragon: 
		$(MAKE) fclean
		$(MAKE) MODEL=4 all

luffy: 
		$(MAKE) fclean
		$(MAKE) MODEL=5 all


.PHONY: all clean fclean re teapot teapot2 42 42N dragon luffy skull