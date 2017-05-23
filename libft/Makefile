# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggane <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/21 11:27:40 by ggane             #+#    #+#              #
#    Updated: 2017/04/21 15:32:18 by ggane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAG = -c -Wall -Werror -Wextra

SRC = ft_strlen.c\
	ft_putchar.c\
	ft_put_array.c\
	ft_dup_array.c\
	ft_putchar_fd.c\
	ft_putstr.c\
	ft_putstr_fd.c\
	ft_putnbr.c\
	ft_putnbr_fd.c\
	ft_putendl.c\
	ft_putendl_fd.c\
	ft_strclr.c\
	ft_memset.c\
	ft_bzero.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strequ.c\
	ft_strnew.c\
	ft_memdel.c\
	ft_memalloc.c\
	ft_strdel.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strnstr.c\
	ft_strcmp.c\
	ft_memcmp.c\
	ft_memchr.c\
	ft_strcpy.c\
	ft_strncmp.c\
	ft_strdup.c\
	ft_strjoin.c\
	ft_strsplit.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_atoi.c\
	ft_itoa.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_iswspace.c\
	ft_strtrim.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_putstr_color.c\
	ft_lennb.c\
	ft_abs.c\
	ft_lstfree.c\
	ft_lentab.c\
	ft_freetab.c\
	get_next_line.c\



OFL = $(SRC:.c=.o)
AR = ar rc
RLIB = ranlib
HDR = -I libft.h
RM = rm -f


$(NAME):
	@$(CC) $(CFLAG) $(SRC)
	@$(AR) $(NAME) $(OFL)
	@$(RLIB) $(NAME)

all : $(NAME)

.PHONY: clean
clean:
	@$(RM) $(OFL)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
