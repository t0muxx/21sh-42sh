# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2018/10/19 12:12:37 by tmaraval         ###   ########.fr        #
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
PARSER   = parser/
EXEC	 = exec/
MEM	 	 = memory/
COMPLETION = completion/

SRCS = 			$(READLINE)readline.c \
 			$(READLINE)readline_mline.c \
 			$(READLINE)input_arrow_mline.c \
			$(READLINE)input_arrow.c \
			$(READLINE)insert.c \
			$(READLINE)term.c \
			$(READLINE)line.c \
			$(READLINE)prompt.c \
			$(READLINE)cursor.c \
			$(READLINE)cursor_pos.c \
			$(READLINE)history.c \
			$(READLINE)history_print.c \
			$(READLINE)history_lst.c \
			$(READLINE)input_key.c \
			$(READLINE)input_key2.c \
			$(READLINE)cutpaste.c \
			$(READLINE)sig.c \
			$(READLINE)sig_ml.c \
			$(COMPLETION)completion_utils.c \
			$(COMPLETION)completion.c \
			$(COMPLETION)completion_cmp.c \
			$(COMPLETION)completion_print.c \
			$(COMPLETION)completion_print_utils.c \
			$(COMPLETION)completion_trim.c \
			$(ENV)env.c \
			$(ENV)env_modify.c \
			$(BUILTINS)builtin_cd.c \
			$(BUILTINS)builtin_cd_chdir.c \
			$(BUILTINS)builtin_cd_opt.c \
			$(BUILTINS)builtin_echo.c \
			$(BUILTINS)builtin_env.c \
			$(BUILTINS)builtin_env_utils.c \
			$(BUILTINS)builtin_exit.c \
			$(BUILTINS)builtin_setenv.c \
			$(BUILTINS)builtin_unsetenv.c \
			$(ERROR)error.c \
			$(LEXER)quotes_in_word.c \
			$(LEXER)init.c \
			$(LEXER)ampersand.c \
			$(LEXER)asterisk.c \
			$(LEXER)dash.c \
			$(LEXER)bang.c \
			$(LEXER)brace.c \
			$(LEXER)bracket.c \
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
			$(PARSER)global.c \
			$(PARSER)global_utils.c \
			$(PARSER)separator.c \
			$(PARSER)parser.c \
			$(PARSER)astree.c \
			$(PARSER)astree_utils.c \
			$(EXEC)redirection.c \
			$(EXEC)dless_redir.c \
			$(EXEC)aggregators.c \
			$(EXEC)and_if.c \
			$(EXEC)or_if.c \
			$(EXEC)semi.c \
			$(EXEC)node.c \
			$(EXEC)pipe.c \
			$(EXEC)pipe_routine.c \
			$(EXEC)exec.c \
			$(EXEC)global.c \
			$(EXEC)cmd.c \
			$(EXEC)sig_routine.c \
			$(EXEC)std_redir.c \
			$(UTILS)string.c \
			$(UTILS)string2.c \
			$(UTILS)makepath.c \
			$(UTILS)makepath_utils.c \
			$(UTILS)utils.c \
			$(UTILS)utils_array.c \
			$(UTILS)in_quotes.c \
		   	$(MEM)free_fun.c \
			builtin.c \
			path.c \
			main_utils.c \
			main.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: printmess $(NAME)

$(NAME): $(OBJ)
	@+$(MAKE) -C libft/
	@gcc $(CFLAGS) -I$(INC_PATH) $(OBJ) libft/libft.a -lncurses -o $(NAME)
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
	@echo "\033[92mCompilation de 21sh...\033[0m"

.PHONY: all clean fclean re
