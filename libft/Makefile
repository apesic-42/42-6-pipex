# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apesic <apesic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 16:00:33 by apesic            #+#    #+#              #
#    Updated: 2024/12/04 18:00:38 by apesic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar

PRINTF_DIR = printf/
LIBFT_DIR = libft/
GNL_DIR = get_next_line/

PRINTF_SRC		=	ft_itoa_hexa  ft_itoa_hexa_ll  ft_itoa_hexa_upper  ft_putnumber_u  ft_printf  percent_csdiu  percent_pxXpercent
PRINTF_DS = $(addprefix $(PRINTF_DIR), $(addsuffix .c, $(PRINTF_SRC)))

GNL_SRC		=	get_next_line get_next_line_utils
GNL_DS = $(addprefix $(GNL_DIR), $(addsuffix .c, $(GNL_SRC)))

OBJS = $(PRINTF_DS:.c=.o) $(GNL_DS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)libft.a $(NAME)
	$(AR) -rcs $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(FLAGS) -I./ -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
