# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apesic <apesic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 14:56:03 by apesic            #+#    #+#              #
#    Updated: 2025/03/27 14:56:04 by apesic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	=	pipex

CC          =	cc # clang
CFLAGS_ANA  =   -fsanitize=address,leak,undefined -g3 -g
CFLAGS      =	-Wall -Wextra -Werror # $(CFLAGS_ANA)
AR          =	ar

LIBFT_DIR = libft/libft/
PRINTF_DIR = libft/

LIBFT_SRC = $(LIBFT_DIR)libft.a
PRINTF_SRC = $(PRINTF_DIR)libftprintf.a

PROJECT_DIR = .
PROJECT_SRC =		main_simple\
                    utils1\
                    utils2\
                    fork_simple\
                    here_doc\

PROJECT_DS = $(addprefix $(PROJECT_DIR)/, $(addsuffix .c, $(PROJECT_SRC)))
OBJS = $(PROJECT_DS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_SRC) $(PRINTF_SRC) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -I./ -c $< -o $@ -g # enlever -g

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re : fclean all

# en plus

psclean :
	rm -f $(OBJS)
	rm -f $(NAME)

psre : psclean all


.PHONY: all clean fclean re
