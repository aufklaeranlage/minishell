# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 10:46:56 by abronner          #+#    #+#              #
#    Updated: 2025/04/02 12:49:05 by abronner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a

# **************************************************************************** #

SRC_DIR		:=	srcs/

OBJ_DIR		:=	objs/

INC_DIR		:=	incl/

# **************************************************************************** #

CTY_SRCS	:=	ft_ctype_0.c ft_ctype_1.c ft_ctype_2.c ft_charchange.c

MEM_SRCS	:=	ft_memsearch.c ft_memchange.c ft_memcreat.c

STR_SRCS	:=	ft_strsearch.c ft_strmove.c ft_strcreat.c ft_split.c \
				ft_striter.c

PUT_SRCS	:=	ft_put.c

LST_SRCS	:=	ft_listadd.c ft_listutils.c ft_listdel.c ft_listiter.c \
				ft_wrapadd.c ft_wrapdel.c ft_wrapiter.c

CONV_SRCS	:=	ft_conv.c ft_strtol.c ft_ltostr.c

GNL_SRCS	:=	ft_gnl.c

ENV_SRCS	:=	ft_environ.c

CTY_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(CTY_SRCS))

MEM_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(MEM_SRCS))

STR_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(STR_SRCS))

PUT_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(PUT_SRCS))

LST_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(LST_SRCS))

CONV_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(CONV_SRCS))

GNL_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(GNL_SRCS))

ENV_OBJS	:=	$(patsubst %.c,$(OBJ_DIR)%.o,$(ENV_SRCS))

# **************************************************************************** #

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror $(ADDCCFLAGS)

CPPFLAGS	:=	-I$(INC_DIR)

LIBFLAGS	:=

RM			:= rm -rf

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_DIR) cty mem str put list conv gnl env

cty: $(CTY_OBJS)
	@ar rcs $(NAME) $(CTY_OBJS)
	@echo "Adding CType objects to library $(NAME)."

mem: cty $(MEM_OBJS)
	@ar rcs $(NAME) $(MEM_OBJS)
	@echo "Adding memory objects to library $(NAME)."

str: cty $(STR_OBJS)
	@ar rcs $(NAME) $(STR_OBJS)
	@echo "Adding string objects to library $(NAME)."

put: str $(PUT_OBJS)
	@ar rcs $(NAME) $(PUT_OBJS)
	@echo "Adding put objects to library $(NAME)."

list: $(LST_OBJS)
	@ar rcs $(NAME) $(LST_OBJS)
	@echo "Adding list objects to library $(NAME)."

conv: $(CONV_OBJS)
	@ar rcs $(NAME) $(CONV_OBJS)
	@echo "Adding conversion objects to library $(NAME)."

gnl: str list $(GNL_OBJS)
	@ar rcs $(NAME) $(GNL_OBJS)
	@echo "Adding get_next_line objects to library $(NAME)."

env: str $(ENV_OBJS)
	@ar rcs $(NAME) $(ENV_OBJS)
	@echo "Adding environ objects to library $(NAME)."

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "Creating $(OBJ_DIR) directory."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@$(CC) $(CFLAGS) $< $(CPPFLAGS) -c -o $@
	@echo "Compiling $@."

re: fclean all

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Deleting object files for library $(NAME)."

fclean: clean
	@$(RM) $(NAME)
	@echo "Deleting library $(NAME)."

.PHONY: all cty mem str put list gnl env bonus re clean fclean make
