NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs

SRC =	ft_isascii.c ft_memset.c ft_memcmp.c ft_memchr.c ft_strlcpy.c ft_substr.c\
	ft_bzero.c ft_isdigit.c ft_strchr.c ft_strnstr.c ft_strlen.c ft_tolower.c\
	ft_calloc.c ft_isprint.c ft_strdup.c ft_strncmp.c ft_toupper.c ft_isalnum.c\
	ft_memcpy.c ft_strjoin.c ft_strrchr.c ft_isalpha.c ft_memmove.c ft_strlcat.c\
	ft_strtrim.c ft_split.c ft_itoa.c ft_atoi.c ft_strmapi.c ft_striteri.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstsize.c\
	ft_lstnew.c ft_lstadd_back.c ft_lstclear.c ft_lstlast.c\
\
	ft_lstadd_front.c  \
	ft_lstdelone.c  ft_lstiter.c\
\
	ft_printf.c ft_put_c_to_i.c ft_put_u_to_none.c\
\
	get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $@ $(OBJ)
#	$(AR) $@ $^

#---------------------
# relink ie : Si un .c est modifié alors on recompile tous les autes

#$(OBJ) : $(SRC)
#	$(CC) $(CFLAGS) -c $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#---------------------

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus so pfgnl
