# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 16:55:38 by plouvel           #+#    #+#              #
#    Updated: 2022/02/16 17:59:48 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	=	srcs

INC_DIR		=	includes

OBJS_DIR	=	objs

LIBFT_DIR	=	libft

SRCS		=	main.c	\
				pipe.c	\
				test.c	\
				utils.c

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

NAME		=	push_swap_tester

CFLAGS		=	-Wall -Werror -Wextra -MD -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR)

CLIBS		=	-L . -lft

LIBFT		=	libft.a

RM			=	rm -rf

$(NAME):		$(LIBFT) $(OBJS)
				$(CC) $(OBJS) $(CFLAGS) $(CLIBS) -o $(NAME)

$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR) all
				mv $(LIBFT_DIR)/$(LIBFT) .
				$(MAKE) -C $(LIBFT_DIR) fclean

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
				$(RM) $(OBJS_DIR)

fclean:			clean
				$(RM) $(LIBFT)
				$(RM) $(NAME)

re:				fclean all

-include $(OBJS:.o=.d)

.PHONY:			all clean fclean re bonus
