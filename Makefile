# -----------------------------------------
# project Configuration
# -----------------------------------------

NAME := ircserv

# Directories
SRC_DIR := src
OBJ_DIR := obj
DEP_DIR := dep
INC_DIR := inc

# Files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP := $(SRC:%.cpp=$(DEP_DIR)/%.d)
INC := -I$(INC_DIR)

# Color for output
RESET := "\033[0m"
YELLOW := "\033[33m"
GREEN := "\033[32m"
RED := "\033[31m"

# Compiler Settings
CXX := c++
CXXFLAGS := -std=c++98 #-Wall -Wextra -Werror #-fsanitize=address

#Clean up command
RM := rm -rf

# -----------------------------------------
# Targets
# -----------------------------------------

# Default target
all: $(NAME)

# Linking the final executable
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(INC) $^ -o $@
	@echo $(GREEN)"creating" $(NAME) "✓" $(RESET)

# Compilation rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(DEP_DIR)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
	@mv -f $(@:.o=.d) $(DEP_DIR)
	@echo $(YELLOW)"compilng" $< "✓" $(RESET)

# Directories creation (obj and dep)
$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

# -----------------------------------------
# Clean Targets
# -----------------------------------------

clean:
	@$(RM) $(OBJ_DIR) $(DEP_DIR)
	@for obj in $(OBJ); do \
		echo $(RED)"deleting $$obj" "✓" $(RESET); \
		sleep 0.2; \
	done
	@for dep in $(DEP); do \
		echo $(RED)"deleting $$dep" "✓" $(RESET); \
		sleep 0.2; \
	done

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED)"deleting" $(NAME) "✓" $(RESET)

# Rebuild everything
re: fclean all

# -----------------------------------------
# Include Dependencies
# -----------------------------------------

# Include automatically generated dependency files
-include $(DEP)

.PHONY: all clean fclean re
