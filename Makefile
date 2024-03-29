# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 04:21:55 by jestrada          #+#    #+#              #
#    Updated: 2022/06/06 21:17:12 by jarredon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

# src / obj files
SRC		=	main.c \
			lexer/lexer.c \
			lexer/split_command.c \
			parser/parser.c \
			parser/parser_utils_commands.c \
			parser/parser_redirects.c \
			parser/parser_quotes.c \
			parser/parser_utils.c \
			parser/parser_utils_1.c \
			utils/tables.c \
			utils/strrange.c \
			utils/env.c \
			utils/terminal.c \
			executor/executor.c \
			executor/utils.c \
			builtins/environ.c \
			builtins/others.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/parser
	mkdir -p $(OBJDIR)/lexer
	mkdir -p $(OBJDIR)/executor
	mkdir -p $(OBJDIR)/utils
	mkdir -p $(OBJDIR)/builtins

$(OBJDIR)%.o:$(SRCDIR)%.c
ifeq ($(shell uname), Linux)
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -g -o $@ -c $<
else
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -I ${HOME}/.brew/opt/readline/include -g -o $@ -c $<
endif

$(FT_LIB):
	make -C $(FT)


$(NAME): $(OBJ)
ifeq ($(shell uname), Linux)
	$(CC) $(OBJ) $(FT_LNK) -o $(NAME) -lreadline  -g
else
	$(CC) $(OBJ) $(FT_LNK) -o $(NAME) -L${HOME}/.brew/opt/readline/lib -lreadline  -g
endif

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

r: all
	./$(NAME)

re: fclean
	$(MAKE)

.PHONY: re r fclean clean all
