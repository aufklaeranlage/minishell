# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:46:56 by abronner          #+#    #+#              #
#    Updated: 2025/05/27 13:16:27 by abronner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# **************************************************************************** #

SRC_DIR		:=	srcs/

OBJ_DIR		:=	objs/

SUB_DIR		:=	env/ errors/ exec/ expander/ readline/ tokenisation/

INC_DIR		:=	incl/

# **************************************************************************** #

SRCS		:=	env.c \
				exec_cmd.c exec_pipe.c exec_reddir.c exec_reddir_heredoc.c \
				exec_shell.c exec_utils.c pipe.c exec_wrapper.c \
				errormsg.c \
				expander.c \
				create_execution_list.c groups_bracket_proc.c \
				groups_bracket_red.c groups_create.c groups_create_utils.c \
				groups_delimiter.c groups_handle_cmd.c \
				groups_handle_cmd_utils2.c groups_handle_cmd_utils.c \
				groups_redirection.c groups_subtoken.c tokens_convert_str.c \
				tokens_convert_sub.c tokens_create.c tokens_utils.c \
				main.c
				

OBJS		:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

# **************************************************************************** #

LIBFT_NAME	:=	libft.a

LIBFT_DIR	:=	libft

LIBFT		:=	$(LIBFT_DIR)/$(LIBFT_NAME)

# **************************************************************************** #

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror $(ADDCCFLAGS)

CPPFLAGS	:=	-I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)

LIBFLAGS	:=	-L$(LIBFT_DIR) -l:$(LIBFT_NAME) -lreadline

RM			:= rm -rf

# * V PATH ******************************************************************* #

vpath %.c $(SRC_DIR) $(patsubst %, $(SRC_DIR)%, $(SUB_DIR))

# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)
	@echo "Creating program $(NAME)."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) ADDCCFLAGS=$(ADDCCFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Creating $(OBJ_DIR) directories."

$(OBJ_DIR)%.o: %.c 
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c -o $@
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
