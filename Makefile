# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 16:43:53 by vahemere          #+#    #+#              #
#    Updated: 2022/04/09 18:24:17 by vahemere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR = objs
SRCS_DIR = $(shell find srcs -type d)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir))
SRCS = main.c \
get_cmd.c \
check_pipe.c ft_strlen.c \

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

NAME = minishell
NORM = norminette

########################### COMPILATION AND FLAGS ###########################

CC = gcc
CFLAGS = -Wall -Wextra -Werror

##################################### COLOR ##################################

COLOUR_PURPLE = \033[0;35m
COLOUR_END = \033[0m

##################################### MAIN ###################################

all: $(NAME)

##################################### MANDATORY ##############################

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) minishell.h $(OBJS) -lreadline -o $(NAME)
	@echo "\n\t$(COLOUR_PURPLE)***EXECUTABLE CREATED SUCCESSFULL***\n\n$(COLOUR_END)"

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -lreadline -o $@ -c $<

$(OBJS_DIR):
	mkdir -p $@
	@echo "\n\t$(COLOUR_PURPLE)OBJECT DIRECTORY CREATED\n\n$(COLOUR_END)"

clean:
	rm -rf $(OBJS) $(OBJS_DIR)
	@echo "\n\t$(COLOUR_PURPLE)OBJECT DIRECTORY CREATED\n\n$(COLOUR_END)"

fclean: clean
	rm -rf $(NAME)
	@echo "\n\t$(COLOUR_PURPLE)DELETE EXECUTABLE SUCCESSFULL\n\n$(COLOUR_END)"

norm:
	@echo "$(COLOUR_PURPLE)***CHECK NORM FILES***$(COLOUR_END)"
	@$(NORM)

re: fclean all

.PHONY: all clean fclean norm re