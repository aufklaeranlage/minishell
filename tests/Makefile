# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:46:56 by abronner          #+#    #+#              #
#    Updated: 2025/04/23 13:43:42 by abronner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	ms_pwd ms_rl

# **************************************************************************** #

SRC_DIR		:=	./

OBJ_DIR		:=	objs/

INC_DIR		:=	./

# **************************************************************************** #

PWD_SRCS	:=	pwd.c

RL_SRCS		:=	readline.c

PWD_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(PWD_SRCS))

RL_OBJS		:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(RL_SRCS))

# **************************************************************************** #

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror $(ADDCCFLAGS)

CPPFLAGS	:=	-I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)

RM			:= rm -rf

# **************************************************************************** #

all: pwd rl

pwd: $(OBJ_DIR) $(PWD_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PWD_OBJS) -o ms_pwd

rl: $(OBJ_DIR) $(RL_OBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(RL_OBJS) -lreadline -o ms_rl

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

re: fclean all

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

.PHONY: all bonus re clean fclean make
