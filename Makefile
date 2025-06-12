# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:46:56 by abronner          #+#    #+#              #
#    Updated: 2025/06/12 11:10:51 by abronner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# **************************************************************************** #

SRC_DIR		:=	srcs/

OBJ_DIR		:=	objs/

SUB_DIR		:=	env/ errors/ exec/ expander/ readline/ tokenisation/ inbuilds/ sig/

INC_DIR		:=	incl/

# **************************************************************************** #

SRCS		:=	env_init.c envnode_init.c env_insert.c env_remove.c \
				env_arr.c env_utils.c \
				exec_cmd.c exec_pipe.c exec_reddir.c exec_reddir_heredoc.c \
				exec_shell.c exec_utils.c pipe.c exec_wrapper.c exec_inbuilt.c \
				exec_cleanup.c \
				errormsg.c \
				expander.c \
				ft_echo.c ft_pwd.c ft_cd.c ft_env.c ft_unset.c ft_export.c \
				ft_exit.c inbuilds.c wildcard.c \
				sig.c
				tokens_create.c tokens_utils.c \
				tokens_convert_str.c tokens_convert_sub.c \
				groups_handle_cmd.c groups_handle_cmd_utils.c \
				groups_handle_cmd_utils2.c groups_bracket_proc.c \
				append_tokens.c groups_create_utils.c groups_create.c \
				groups_delimiter.c groups_redirection.c groups_subtoken.c \
				create_execution_list.c create_handle_errors.c \
				main.c \
				print_group_data.c \
				

OBJS		:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

# **************************************************************************** #

LIBFT_NAME	:=	libft.a

LIBFT_DIR	:=	./libft

LIBFT		:=	$(LIBFT_DIR)/$(LIBFT_NAME)

# **************************************************************************** #

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror $(ADDCCFLAGS)
# For school PC
CPPFLAGS	:=	-I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)

LIBFLAGS	:=	-L$(LIBFT_DIR) -l:$(LIBFT_NAME) -lreadline

# For my own
# CPPFLAGS	:=	-I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I/opt/homebrew/opt/readline/include

LIBFLAGS	:=	-L$(LIBFT_DIR) -L/opt/homebrew/opt/readline/lib -lft -lreadline

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
