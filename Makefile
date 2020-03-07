# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: david <david@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/27 18:55:07 by srobert-          #+#    #+#              #
#    Updated: 2019/08/23 23:46:07 by david            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc
FLAGS = -Wall -Werror -Wextra -g
LIBRARIES = -lm -lft -L$(LIBFT_DIR) 
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEAD)

LIBFT_DIR = ./libft/
LIBFT_HEAD = $(LIBFT_DIR)includes/
LIBFT = $(LIBFT_DIR)libft.a

HEADERS_LIST = my_ls.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRCS_DIR = ./srcs/
SRCS_LIST = outputs.c my_ls.c parse.c sort.c file_funcs.c dir_funcs.c util.c count_staff.c outputs_util.c merge.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)obj files have been created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) has been created$(RESET)"
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GREEN)$(OBJ_DIR) has been created$(RESET)"

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) has been deleted$(RESET)"
	@echo "$(NAME): $(RED)object files have been deleted$(RESET)"

fclean: clean
	@echo "$(NAME): $(RED)$(MINILIBX) has been deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) has been deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) has been deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all