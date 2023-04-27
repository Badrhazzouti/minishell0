# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 21:30:08 by bhazzout          #+#    #+#              #
#    Updated: 2023/04/27 10:27:23 by bhazzout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address

RM		=	rm -rf

SOURCES	=	minishell.c env_processor.c helper/helper_1.c helper/helper_2.c helper/helper_3_linked_list.c \
			line_processor.c split.c checker/check_pipe.c checker/op_checker.c checker/special_char_check.c \
			checker/quotes_check.c \

OBJECTS	=	$(SOURCES:.c=.o)

all		:	$(NAME)

$(NAME) : 	$(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline

clean	:
	$(RM) $(OBJECTS)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all