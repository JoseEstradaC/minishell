# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 04:21:55 by jestrada          #+#    #+#              #
#    Updated: 2022/05/11 17:42:52 by jestrada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_calloc.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_striteri.c \
			ft_intlen.c \
			ft_isset.c \
			get_next_line.c

OBJS	=	${SRCS:.c=.o}

BONUS	=	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

BONUS_OBJS	=	${BONUS:.c=.o}

FLAGS		= -Wall -Wextra -Werror

$(NAME):
	make -C ./ft_printf
	cp ./ft_printf/libftprintf.a $(NAME)
	gcc $(FLAGS) -c $(SRCS) $(BONUS) -I./
	ar rcs $(NAME) $(OBJS)

bonus:		
	gcc $(FLAGS) -c $(SRCS) $(BONUS) -I./
	ar crs $(NAME) $(OBJS) $(BONUS_OBJS)

all: $(NAME)

clean:
	make clean -C ./ft_printf
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make fclean -C ./ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY:     all clean fclean bonus re
