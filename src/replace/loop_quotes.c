/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:37:41 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:35:30 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_var	*ft_init_loop_qte(char **line)
{
	struct winsize	ws;
	t_var			*var;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	miniprintf(STDOUT_FILENO, RED">"FIN);
	*line = ft_strdup("\0");
	var = ft_init_env(NULL);
	var->col = ws.ws_col;
	var->index = 0;
	var->copy = ft_strdup("\0");
	var->opt_quo = 1;
	var->multiline = 1 / var->col;
	init_termios(var);
	return (var);
}

char	*ft_enter_quotes(char *s, char *line, t_var *var)
{
	char	*ret;

	ret = ft_strjoin(s, line);
	free(s);
	free(line);
	line = ft_strjoin(ret, "\n");
	free(ret);
	free(var->copy);
	ft_free_struct(var);
	miniprintf(STDOUT_FILENO, "\n");
	return (line);
}

void	ft_free_ctrlc(char *s, char *line, t_var *var)
{
	free(line);
	free(s);
	free(var->copy);
	ft_free_struct(var);
}

char	*ft_loop_quotes(char *s)
{
	t_var	*var;
	char	*line;
	char	buf[BSIZE];

	var = ft_init_loop_qte(&line);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		ft_bzero(buf, BSIZE);
		read(STDIN_FILENO, buf, BSIZE);
		if (ENTER)
			return (ft_enter_quotes(s, line, var));
		else if (buf[0] == 3 && buf[1] == 0)
		{
			ft_free_ctrlc(s, line, var);
			return (NULL);
		}
		else if (!HOME && !END && !UP && !DOWN && !HAUT && !BAS && !GAUCHE
				&& !DROITE && !CL && !CD && !TAB && !MULTIUP && !MULTIDO &&
				!COPY && !PASTE)
			ft_print_line(var, &line, buf);
		else
			line = ft_termcaps(var, line, buf);
	}
}
