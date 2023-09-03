# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 14:11:17 by ajakubcz          #+#    #+#              #
#    Updated: 2023/09/02 22:46:24 by cprojean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

RM = $(RM) -f

HEADERS =	$(DIR_INCLUDES)philo.h

MKDIR = mkdir -p

RM = rm -rf

DIR_OBJ = ./.obj/

DIR_SRCS = srcs/

DIR_INCLUDES = ./inc/

SRCS =			$(DIR_SRCS)main.c \
				$(DIR_SRCS)philo.c \
				$(DIR_SRCS)death.c  \
				$(DIR_SRCS)ft_atoi.c \
				$(DIR_SRCS)rest.c \
				$(DIR_SRCS)think.c \
				$(DIR_SRCS)dinner.c \
				$(DIR_SRCS)routine.c \
				$(DIR_SRCS)print_timestamp.c \

OBJS =			$(patsubst %.c, $(DIR_OBJ)%.o, $(SRCS))

all :			$(NAME)

$(DIR_OBJ)%.o: %.c $(HEADERS)
				@mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) -I inc -c $< -o $@

$(NAME) :		$(OBJS)
				$(CC) $(OBJS) -lpthread -o $(NAME)
clean :
				$(RM) $(OBJS)

fclean :		clean
				@$(RM) $(DIR_OBJ)
				$(RM) $(NAME)

re :			fclean all

rebonus :		fclean bonus
