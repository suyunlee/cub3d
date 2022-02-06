# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suylee <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 16:49:41 by suylee            #+#    #+#              #
#    Updated: 2021/05/14 11:10:15 by suylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS_DIR	= ./srcs
SRCS_NAME	= bmp.c init.c draw.c key.c main.c parsing.c parsing2.c \
	   raycasting.c sprite.c sprite2.c texture.c utils.c verifymap.c \
	   get_next_line.c
SRCS	= $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS	= $(SRCS:.c=.o)
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
LIBS	= -Lminilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit\
		  ./libft/libft.a

all		: $(NAME)

$(NAME) : $(OBJS)
			@(make re -C ./libft/)
			gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				@(make clean -C ./libft/)
				$(RM) $(OBJS)

fclean:			clean
				@(make fclean -C ./libft/)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
