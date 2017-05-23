/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 09:32:44 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:08:46 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	ft_init_loop(t_var *var, int *i, char **line)
{
	struct winsize	ws;

	*i = 0;
	var->lenv = NULL;
	var->h = NULL;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	var->col = ws.ws_col;
	*line = ft_strdup("\0");
	init_termios(var);
	var->index = 0;
	ft_tab_to_lst(var->env, &var->lenv, 'e');
	var->name = ft_find_name(var->lenv);
	var->addr = ft_find_addr(var->lenv);
	var->multiline = ft_prompt_len(var) / var->col;
	ft_prompt(var);
}

static void	ft_loop_enter(char **line, t_var *var)
{
	if (var->echo != NULL)
	{
		free(var->echo);
		var->echo = NULL;
	}
	if (ft_strcmp(*line, "\0") != 0)
	{
		if (ft_str_space(*line) == 1)
			ft_add_history(*line, &(var->h));
		while (var->index < (int)ft_strlen(*line))
			ft_right(var);
		var->multiline = ft_prompt_len(var) / var->col;
		ft_enter(*line, var);
	}
	else
		miniprintf(STDOUT_FILENO, "\n");
	ft_prompt(var);
	free(*line);
	*line = ft_strdup("\0");
}

static void	ft_control_loop(char (*buf)[BSIZE], char **line, t_var *var)
{
	ft_bzero(*buf, BSIZE);
	free(*line);
	*line = ft_strdup("\0");
	var->index = 0;
	var->multiline = 0;
	miniprintf(STDIN_FILENO, "\n");
	ft_prompt(var);
}

static void	ft_cd_loop(char (*buf)[BSIZE], char **line)
{
	if ((*buf)[0] == 4 && (*buf)[1] == 0 && (*line)[0] == '\0')
	{
		miniprintf(STDOUT_FILENO, "exit\n");
		ft_bzero(*buf, BSIZE);
		free(*line);
		exit(V);
	}
	else if ((*buf)[0] == 4 && (*buf)[1] == 0)
	{
		ft_bzero(buf, BSIZE);
		(*buf)[0] = 9;
		(*buf)[1] = 0;
	}
}

void		ft_loop(t_var *var)
{
	char	*line;
	char	buf[BSIZE];
	int		i;

	ft_init_loop(var, &i, &line);
	ft_bzero(buf, BSIZE);
	while (1)
	{
		signal_handler(SETSIG, SIGINT_REGULAR);
		ft_bzero(buf, BSIZE);
		read(STDIN_FILENO, buf, BSIZE);
		ft_cd_loop(&buf, &line);
		(buf[0] == 3 && buf[1] == 0) ? ft_control_loop(&buf, &line, var) : (0);
		if (!HAUT && !BAS)
			while (var->h && var->h->prev)
				var->h = var->h->prev;
		if (ENTER)
			ft_loop_enter(&line, var);
		else if (buf[0] != '\0' && !BAD && !HOME && !END && !UP && !DOWN &&
				!HAUT && !BAS && !GAUCHE && !DROITE && !CL && !CD && !TAB &&
				!MULTIUP && !MULTIDO && !COPY && !PASTE)
			ft_print_line(var, &line, buf);
		else if (!BAD)
			line = ft_termcaps(var, line, buf);
	}
}
