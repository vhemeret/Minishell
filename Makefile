# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 16:43:53 by vahemere          #+#    #+#              #
#    Updated: 2022/07/14 01:01:57 by brhajji-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR = objs
SRCS_DIR = $(shell find srcs -type d)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir))
SRCS = main.c \
manage_cmd.c manage_cmd_utils.c put_word.c first_check.c tokenizer.c is_type.c redir.c syntax_check.c print_error.c expand.c split_word.c expand_utils.c manage_expantion.c remove_quote.c len_expand.c new_node.c \
ft_strdup.c ft_strjoin.c ft_split.c ft_strlen.c is_whitespace.c quoting_state.c is_word.c next_quote.c copy_env.c len_darr.c isdigits.c \
cleaning.c  exec_utils.c execve.c init_exec.c ft_itoa.c here_doc.c ft_strcmp.c manage_export.c env.c pwd.c cd.c manage_built_in.c export.c unset.c ft_strcpy.c export_parsing.c echo.c\

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

NAME = minishell
NORM = norminette

########################### COMPILATION AND FLAGS ###########################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

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

re: fclean
	make all

.PHONY: all clean fclean norm re
