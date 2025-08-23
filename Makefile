NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

CFLAGS += -I include


LIBFT_DIR = libft/
LIBFT_A = $(LIBFT_DIR)libft.a

SRCS = 	src/main.c \
		src/setter.c \
		src/clear_all.c \
		src/first_pars.c \
		src/first_pars_bis.c \
		src/parsing.c \
		src/parsing_bis.c \
		src/parsing_content.c \
		src/parsing_content_tab.c \
		src/parsing_content_tab_bis.c \
		src/parsing_env.c \
		src/parsing_env_bis.c \
		src/parsing_env_bis2.c \
		src/parsing_env_bis2_utils.c \
		src/parsing_env_utils.c \
		src/parsing_here_doc.c \
		src/parsing_here_doc_utils.c \
		src/parsing_here_doc_env.c \
		src/parsing_here_doc_clear.c \
		src/utils.c \
		src/utils_bis.c \
		src/pars_lstnew.c \
		src/pars_lstadd_back.c \
		src/pars_lstclear.c \
		src/pars_lstlast.c \
		src/pars_lstsize.c \
		src/print_debug_lst.c \
		src/convert_type_to_str.c \
		src/interpreter.c \
		src/command_utils.c \
		src/debug_command_print.c \
		src/executor.c \
		src/executor_bis.c \
		src/path_finder.c \
		src/executor_utils.c \
		src/signals.c \
		src/builtins/pwd.c \
		src/builtins/builtins.c \
		src/builtins/echo.c \
		src/builtins/cd.c \
		src/builtins/env.c \
		src/environment.c \
		src/builtins/unset.c \
		src/builtins/export.c \
		src/builtins/export_bis.c \
		src/builtins/exit.c


OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline


$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "Fichiers objets de Minishell nettoyés."

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@echo "Nettoyage complet effectué."

re: fclean all

.PHONY: all clean fclean re
