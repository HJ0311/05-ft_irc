NAME := ircserv

SRC_DIR := src
OBJ_DIR := obj
DEP_DIR := dep
INC_DIR := inc

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP := $(SRC:%.cpp=$(DEP_DIR)/%.d)
INC := -I$(INC_DIR)

RESET = "\033[0m"
YELLOW = "\033[33m"
GREEN = "\033[32m"
RED = "\033[31m"


CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address


RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(INC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(DEP_DIR)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
	@mv -f $(@:.o=.d) $(DEP_DIR)
	@echo $(YELLOW)"compilng" $< "✓" $(RESET)

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR) $(DEP_DIR)
	@echo $(RED)"deleting" $(OBJ) "✓" $(RESET)
	@echo $(RED)"deleting" $(DEP) "✓" $(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED)"deleting" $(NAME) "✓" $(RESET)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)