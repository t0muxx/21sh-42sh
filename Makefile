# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2018/03/15 10:05:23 by tmaraval         ###   ########.fr        #
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

SRCS = 		$(READLINE)readline.c \
			$(READLINE)readline_print.c \
			$(READLINE)readline_history.c \
			$(READLINE)readline_history_lst.c \
			$(READLINE)key_others.c \
			$(READLINE)key.c \
			$(READLINE)cursor.c \
			$(READLINE)cursor_tbuffer.c \
			$(READLINE)term.c \
			$(ENV)env_get.c \
			$(ERROR)error.c \
			$(UTILS)string.c

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
