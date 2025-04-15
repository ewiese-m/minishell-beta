NAME	= 	libft.a
SRC		= 	ft_atoi.c \
			ft_atoll.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memset.c \
			ft_memcmp.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strnstr.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_calloc.c \
			ft_split.c \
			ft_strcat.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			gc_add.c \
			gc_close_all_fds.c \
			gc_close_fd.c \
			gc_free_all.c \
			gc_free.c \
			gc_init.c \
			gc_malloc.c \
			gc_memory_wrappers.c \
			gc_remove.c \
			gc_track_fd.c \
			get_next_line.c \
			get_next_line_utils.c

BONUS	=	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJ 	=	$(SRC:.c=.o)

OBJS 	=	${OBJ} ${BONUS:.c=.o}

HEAD 	=	libft.h

AR 		= 	ar -rcs

GCC 	= 	gcc

FLAGS 	= 	-Wall -Werror -Wextra


all: ${NAME}

$(NAME): ${OBJ}
	${AR} ${NAME} ${OBJ}

.c.o:
	${GCC} ${FLAGS} -I ./ -c $< -o ${<:.c=.o}

bonus: ${OBJS}
	${AR} ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}



fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
