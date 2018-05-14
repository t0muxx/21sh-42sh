# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2018/04/23 09:48:47 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME OF THE PROG#
NAME = 		21sh

#FLAG AND COMPILATOR#
CC =		gcc
CFLAGS = 	-Wall -Werror -Wextra -g

#PATH#
OBJ_PATH =  obj
SRC_PATH =  sources
INC_PATH =  includes

#SUBDIR#
BUILTINS = builtins/
PARSECFG = parsecfg/
ENV		 = env/
READLINE = readline/
ERROR	 = error/
UTILS	 = utils/
LEXER	 = lexer/

SRCS = 		$(READLINE)readline.c \
			$(READLINE)input_arrow.c \
			$(READLINE)insert.c \
			$(READLINE)term.c \
			$(READLINE)line.c \
			$(READLINE)prompt.c \
			$(READLINE)cursor.c \
			$(READLINE)cursor_pos.c \
			$(READLINE)history.c \
			$(READLINE)history_lst.c \
			$(READLINE)input_key.c \
			$(READLINE)cutpaste.c \
			$(READLINE)sig.c \
			$(ENV)env.c \
			$(ENV)env_modify.c \
			$(BUILTINS)builtin_echo.c \
			$(BUILTINS)builtin_env.c \
			$(BUILTINS)builtin_env_utils.c \
			$(BUILTINS)builtin_exit.c \
			$(BUILTINS)builtin_setenv.c \
			$(BUILTINS)builtin_unsetenv.c \
			$(ERROR)error.c \
			$(UTILS)string.c \
			$(UTILS)utils.c \
			$(UTILS)utils_array.c \
		   	builtin.c \
			path.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: printmess $(NAME)

$(NAME): $(OBJ)
	@(cd libft ; make; make clean)
	@gcc $(CFLAGS) -I$(INC_PATH) $(OBJ) libft/libft.a -ltermcap -o $(NAME)
	@echo "\033[92m21sh created\033[0m"

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@gcc -o $@ $(CFLAGS) -I$(INC_PATH) -c $<

clean:
	@echo "\033[92mClean des .o...\033[0m"
	/bin/rm -rf $(OBJ_PATH)
	@(cd libft ; make clean)

fclean: clean
	@echo "\033[92mFclean...\033[0m"
	/bin/rm -f $(NAME)
	/bin/rm -f libft/libft.a

re: fclean all

printmess:
	@echo "\033[92mCompilation de minishell...\033[0m"

.PHONY: all clean fclean re
