# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 01:02:38 by mhrima            #+#    #+#              #
#    Updated: 2022/12/09 00:55:28 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

SRCS = get_next_line.c get_next_line_utils.c

SRCS_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c


OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME): $(OBJS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS_BONUS) $(OBJS)
	$(AR) $(NAME) $(OBJS_BONUS) $(OBJS)


clean : 
	$(RM) $(OBJS) $(OBJS_BONUS)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all