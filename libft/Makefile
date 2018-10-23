# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 11:35:52 by tmaraval          #+#    #+#              #
#    Updated: 2018/10/19 11:51:44 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ_PATH =  obj

SRC = ft_memset.c \
 	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcat.c  \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_itoa.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstnew2.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstsortedinsert.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_strrpl.c \
	ft_strlowcase.c \
	ft_strupcase.c \
	ft_str_is_numeric.c \
	ft_str_is_lowercase.c \
	ft_putstr_color.c \
	ft_strrev.c \
	ft_itoa_base.c \
	ft_str_isalnum.c \
	ft_2darraylen.c \
	ft_split_whitespace.c \
	ft_lst_append.c \
	ft_lst_free.c \
	ft_date.c \
	ft_wcstrjoin.c \
	ft_wcstrlen.c \
	ft_wcstrsub.c \
	ft_printf/conv/ft_conv.c \
	ft_printf/conv/ft_conv_char.c \
	ft_printf/conv/ft_conv_integer.c \
	ft_printf/conv/ft_conv_str.c \
	ft_printf/conv/ft_lltoa_base.c \
	ft_printf/conv/ft_sitoa_base.c \
	ft_printf/conv/ft_ulltoa_base.c	\
	ft_printf/ft_printf.c \
	ft_printf/ft_printf_cwidth.c \
	ft_printf/ft_printf_flag_utils.c \
	ft_printf/ft_printf_num_flag.c \
	ft_printf/ft_printf_parser.c \
	ft_printf/ft_printf_parser_utils.c \
	ft_printf/ft_printf_precision.c \
	ft_printf/ft_printf_str_precision.c \
	ft_printf/ft_printf_utils.c \
	ft_printf/ft_printf_width.c \
	ft_printf/ft_printf_width_utils.c \
	gnl/get_next_line.c

OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)

all: printmess $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[92mLibft.a created\033[0m"

$(OBJ): $(OBJ_PATH)/%.o : %.c
	@mkdir -p $(dir $@)
	@gcc -o $@ -Wall -Wextra -Werror -c $<

clean:
	@/bin/rm -rf $(OBJ)
	@echo "\033[92mLibft object file cleaned\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

printmess:
	@echo "\033[92mCompiling Libft...\033[0m"

.PHONY: all clean fclean re
