# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 15:13:11 by yejlee            #+#    #+#              #
#    Updated: 2022/12/19 14:44:09 by yejlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Reset
Set_Color	= \033[0m

# Regular Colors
Black	= \033[0;30m
Red		= \033[0;31m
Green	= \033[0;32m
Yellow	= \033[0;33m
Blue  	= \033[0;34m
Purple	= \033[0;35m
Cyan	= \033[0;36m
White	= \033[0;37m

NAME	= philo

SRCS	= 	main.c \
	  		tool.c\
	  			.c\

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -fsanitize=thread -g

$(NAME)	: $(OBJS)
		@cc $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
		@echo "$(Cyan)philo has been created and available$(Set_Color)"
		
clean	:
		@rm -f $(NAME)
		@echo "$(Red)obj files have been successfully removed$(Set_Color)"

fclean	: clean
		@rm -f $(NAME)
		@echo "$(Blue)The program philo has been removed$(Set_Color)"

all		: $(NAME)

re		: fclean all

.PHONY	: clean fclean all re