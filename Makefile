# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 15:13:11 by yejlee            #+#    #+#              #
#    Updated: 2022/12/22 18:15:42 by yejlee           ###   ########.fr        #
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
	  		check.c\
	  		init.c\
			print_message.c\
			routine.c\
			time_set.c\
			tool.c

OBJS	= $(SRCS:.c=.o)

HEADER	= ./philo/


CFLAGS	= -Wall -Wextra -Werror -pthread -g3 #-fsanitize=thread -g

.c.o:
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $(<:.c=.o)

$(NAME)	: $(OBJS)
		@cc $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(Cyan)philo has been created and available$(Set_Color)"
		
clean	:
		@rm -f $(OBJS)
		@echo "$(Red)obj files have been successfully removed$(Set_Color)"

fclean	: clean
		@rm -f $(NAME)
		@echo "$(Blue)The program philo has been removed$(Set_Color)"

all		: $(NAME)

re		: fclean all

.PHONY	: clean fclean all re
