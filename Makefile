# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 21:30:08 by bhazzout          #+#    #+#              #
#    Updated: 2023/04/17 22:24:13 by bhazzout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address

RM		=	rm -rf

SOURCES	=	minishell.c env_processor.c helper_1.c helper_2.c helper_3_linked_list.c line_processor.c split.c

OBJECTS	=	$(SOURCES:.c=.o)

all		:	$(NAME)

$(NAME) : 	$(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline

clean	:
	$(RM) $(OBJECTS)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all