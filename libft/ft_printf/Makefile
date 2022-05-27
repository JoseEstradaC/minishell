# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 04:21:55 by jestrada          #+#    #+#              #
#    Updated: 2022/05/10 19:44:22 by jestrada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

SRCS	=	ft_printf.c \
			ft_printf_analysis_flags.c \
			ft_printf_analysis.c \
			ft_printf_print_placeholder.c \
			ft_printf_analysis_flags_extras.c \
			ft_printf_transform.c \
			ft_printf_print_placeholder_type.c \
			ft_printf_print_placeholder_utils.c


OBJS	=	${SRCS:.c=.o}

FLAGS	= -Wall -Wextra -Werror

$(NAME): 
	gcc $(FLAGS) -c $(SRCS) -I./
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:     all clean fclean re bonus
