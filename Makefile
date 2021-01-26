# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 20:39:01 by iharchi           #+#    #+#              #
#    Updated: 2020/12/16 04:07:18 by iharchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

GNL = gnl/*.c
SRC = 	srcs/*.c
MLX = -I /usr/local/include
LIBFT = libft/
FLAG =  -L /usr/local/lib -lmlx -framework OpenGl -framework AppKit -D BUFFER_SIZE=32 -Wall -Werror -Wextra
LINUX_FLAG = -L /usr/local/lib -lmlx -lX11 -lXext -D BUFFER_SIZE=32 -lm
all: $(NAME)
$(NAME) : 
			@sh srcs/artwork.sh
			@echo "\033[0;33mMaking LIBFT"
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) -C $(LIBFT) bonus
			@echo "\033[0;33mCompiling MiniRT"
			@gcc $(MLX) $(FLAG) main.c $(LIBFT)libft.a $(SRC) $(GNL) -o $(NAME)
			@echo "\033[0;32mReady to use.\n\033[0;33mDo ./MiniRT scenename.rt"
clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo "\033[0;32mDone."
fclean: clean
	@/bin/rm -f MiniRT
	@$(MAKE) -C $(LIBFT) fclean
	@echo "\033[0;32mEverything is cleaned"

re : fclean all

linux :
			@gcc  -g  main.c $(SRC) $(LIBFT)libft.a $(MLX) $(LINUX_FLAG) $(GNL) -o $(NAME)	
.PHONY: all clean fclean re