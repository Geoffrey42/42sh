/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:51:25 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:43:54 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_one_result(char *line, t_var *var, char buf[BSIZE])
{
	char	*ret;

	print_result(line, var);
	ret = loop_tab(buf, line, var);
	ft_free_comp(var);
	return (ret);
}

void	ft_print_tab_up(t_var *var, char *line)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("cd", NULL), 0, 0), 0, ft_outc);
	ft_prompt(var);
	ft_putstr(line);
	ft_tab_to_space(var->comp->array[var->comp->i]);
	ft_putstr(var->comp->array[var->comp->i]);
	ft_space_to_tab(var->comp->array[var->comp->i]);
	(var->comp->split) ? ft_putstr(var->comp->end) : (0);
	tputs(tgoto(tgetstr("do", NULL), 0, 0), 0, ft_outc);
	print_tabulation(var, var->comp->i);
}

void	print_tab(char *line, t_var *var, int i, int j)
{
	struct winsize	ws;
	int				len;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	(var->comp->split) ? i = ft_strlen(var->comp->end) : (0);
	j = ft_strlen(line) + ft_prompt_len(var) +
		ft_strlen(var->comp->array[var->comp->prec]) - 1;
	j = j / ws.ws_col;
	while (--var->comp->ligne)
		tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
	while (--j >= 0)
		tputs(tgetstr("up", NULL), 0, ft_outc);
	ft_print_tab_up(var, line);
	while (var->comp->ligne++ <= var->nb_line)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	len = len_last_line(line, var) + ft_strlen(var->comp->array[var->comp->i]);
	while (len > ws.ws_col)
		len -= ws.ws_col;
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 0, ft_outc);
	while (--i >= 0)
		tputs(tgoto(tgetstr("le", NULL), 0, 0), 0, ft_outc);
	var->comp->prec = var->comp->i;
}

void	print_first_line(char *line, t_var *var)
{
	int	i;

	ft_tab_to_space(var->comp->array[0]);
	(!var->comp->split) ? i = 0 : (0);
	(var->comp->split) ? i = ft_strlen(var->comp->end) : (0);
	tputs(tgoto(tgetstr("ce", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, len_begin_last_line(line, var)), 0,
			ft_outc);
	ft_putstr(var->comp->array[0]);
	(var->comp->split) ? ft_putstr(var->comp->end) : (0);
	tputs(tgoto(tgetstr("do", NULL), 0, 0), 0, ft_outc);
	print_tabulation(var, 0);
	while (var->comp->ligne++ <= var->nb_line)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, len_last_line(line, var) +
				ft_strlen(var->comp->array[0])), 0, ft_outc);
	while (--i >= 0)
		tputs(tgoto(tgetstr("le", NULL), 0, 0), 0, ft_outc);
}

void	print_tabulation(t_var *var, int video)
{
	struct winsize	ws;
	struct stat		s;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	ft_init_tabulation(var, &i, ws.ws_col);
	while (var->comp->array[++i] && var->comp->nb_word--)
	{
		var->comp->array[i] = ft_tab_space(var->comp->array[i]);
		lstat(var->comp->array[i], &s);
		var->comp->array[i] = ft_strdup_spaces(var->comp->array[i]);
		tputs(tgetstr("me", NULL), 0, ft_outc);
		(i == video) ? tputs(tgetstr("mr", NULL), 0, ft_outc) : (0);
		if (S_ISDIR(s.st_mode))
			ft_dir_or_usr(0, var, i, video);
		else if (s.st_mode & S_IXUSR)
			ft_dir_or_usr(1, var, i, video);
		else if (S_ISLNK(s.st_mode))
			ft_lnk_or_else(0, var, i, video);
		else
			ft_lnk_or_else(1, var, i, video);
		while ((var->comp->space-- >= 0) && var->comp->nb_word > 0)
			write(1, " ", 1);
		(var->comp->nb_word == 0) ? ft_no_word(ws.ws_col, var) : (0);
	}
}
