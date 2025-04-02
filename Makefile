# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:46:56 by abronner          #+#    #+#              #
#    Updated: 2025/04/02 15:55:14 by abronner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# **************************************************************************** #

SRC_DIR		:=	srcs/

OBJ_DIR		:=	objs/

INC_DIR		:=	incl/

# **************************************************************************** #

SRCS		:=	pipe_exec.c pipe.c

OBJS		:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

# **************************************************************************** #

LIBFT_NAME	:=	libft.a

LIBFT_DIR	:=	libft

LIBFT		:=	$(LIBFT_DIR)/$(LIBFT_NAME)

# **************************************************************************** #

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror $(ADDCCFLAGS)

CPPFLAGS	:=	-I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)

LIBFLAGS	:=	-L$(LIBFT_DIR) -l:$(LIBFT_NAME)

RM			:= rm -rf

# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)
	@echo "Creating program $(NAME)."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) ADDCCFLAGS=$(ADDCCFLAGS)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "Creating $(OBJ_DIR) directory."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@
	@echo "Compiling $@."

re: fclean all

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Deleting object files for program $(NAME)."
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@echo "Deleting library $(NAME)."
	@$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: all bonus re clean fclean make
