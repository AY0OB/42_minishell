#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	// hop hop on évite le trigger "unused parameter" :x
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);

	// fonctions magiques de readline:
	// 1. rl_on_new_line() : prévient readline qu'on est sur une nouvelle ligne
	rl_on_new_line();
	// 2. rl_replace_line("", 0) : efface le contenu du buffer de ligne actuel
	rl_replace_line("", 0);
	// 3. rl_redisplay() : ré-affiche le prompt et le buffer (qui est maintenant vide)
	rl_redisplay();
}