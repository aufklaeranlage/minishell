# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:46:56 by abronner          #+#    #+#              #
#    Updated: 2025/06/25 18:10:04 by akuzmin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# **************************************************************************** #

SRC_DIR		:=	srcs/

OBJ_DIR		:=	objs/

SUB_DIR		:=	env/ errors/ exec/ expander/ readline/ tokenisation/ inbuilds/ sig/

INC_DIR		:=	incl/

# **************************************************************************** #

SRCS		:=	main.c \
                print_group_data.c \
                sig.c \
				env_arr.c env_init.c env_insert.c env_insert_sep.c \
				envnode_init.c env_remove.c env_utils.c \
				errormsg.c \
				exec_cleanup.c exec_inbuilt.c exec_reddir.c exec_shell.c \
				exec_cmd.c exec_pipe.c exec_reddir_heredoc.c \
				exec_utils.c pipe.c \
				expander.c expand_value.c \
				ft_cd.c ft_env.c ft_export.c ft_unset.c inbuild_utils.c \
				ft_echo.c  ft_exit.c  home.c\
				ft_pwd.c inbuilds.c wildcard.c wildcard_utils.c \
				readline_append.c readline_heredoc.c \
				append_tokens.c groups_create_utils.c groups_redirection.c \
				tokens_create.c create_execution_list.c groups_delimiter.c \
				groups_subtoken.c tokens_utils.c create_handle_errors.c \
				groups_handle_cmd.c handle_quatation.c groups_bracket_proc.c \
				groups_handle_cmd_utils2.c lexer.c groups_create.c \
				groups_handle_cmd_utils.c tokens_convert_sub.c
				

OBJS		:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

# **************************************************************************** #

LIBFT_NAME	:=	libft.a

LIBFT_DIR	:=	./libft

LIBFT		:=	$(LIBFT_DIR)/$(LIBFT_NAME)

# **************************************************************************** #

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror

g:	CFLAGS	+=	-g

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

g: fclean $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)
	@echo "Creating program $(NAME)."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)"

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
