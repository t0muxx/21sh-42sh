# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2018/05/11 18:10:29 by cormarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME OF THE PROG#
NAME = 		21sh

#FLAG AND COMPILATOR#
CC =		gcc
CFLAGS = 	-g3

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
PARSER	 = parser/

SRCS = 		$(LEXER)ampersand.c \
			$(LEXER)asterisk.c \
			$(LEXER)bang.c \
			$(LEXER)brace.c \
			$(LEXER)bracket.c \
			$(LEXER)dash.c \
			$(LEXER)dollar.c \
			$(LEXER)eol.c \
			$(LEXER)escape.c \
			$(LEXER)great.c \
			$(LEXER)hashtag.c \
			$(LEXER)less.c \
			$(LEXER)lexer.c \
			$(LEXER)list.c \
			$(LEXER)pipe.c \
			$(LEXER)quote.c \
			$(LEXER)semi.c \
			$(LEXER)space.c \
			$(LEXER)word.c \
			$(PARSER)and_or.c \
			$(PARSER)cmd.c \
			$(PARSER)command.c \
			$(PARSER)complete_cmd.c \
			$(PARSER)io.c \
			$(PARSER)list.c \
			$(PARSER)pipeline.c \
			$(PARSER)separator.c \
			../main.c \

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: printmess $(NAME)

$(NAME): $(OBJ)
	@(cd libft ; make; make clean)
	@gcc $(CFLAGS) -o $(NAME) -I$(INC_PATH) $(OBJ) libft/libft.a -ltermcap
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
