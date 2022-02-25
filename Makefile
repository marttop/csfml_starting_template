##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

NAME	=	game

SRC	=	main.c \

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-Wall -Wextra
CFLAGS	+=	-l csfml-system
CFLAGS	+=	-l csfml-graphics
CFLAGS	+=	-l csfml-audio
CFLAGS	+=	-l csfml-window

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
