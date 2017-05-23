/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:23:35 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:14:21 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	ft_print_multiline(t_var *var, char **line, char buf[BSIZE])
{
	if (var->index > (int)ft_strlen(*line) - 1)
	{
		if (((var->index + ft_prompt_len(var) - 1) % (var->col) == 0)
		&& !DEL && !SUPP)
			var->multiline++;
		if (((var->index + ft_prompt_len(var)) % (var->col) == 0)
		&& (DEL || SUPP))
			var->multiline--;
	}
	else
	{
		if (((var->index + ft_prompt_len(var)) % (var->col) == 0) && !DEL
		&& !SUPP)
			var->multiline++;
		if (((var->index + ft_prompt_len(var) + 1) % (var->col) == 0) &&
		(DEL || SUPP))
			var->multiline--;
	}
}

void		ft_print_line(t_var *var, char **line, char buf[BSIZE])
{
	int				i;
	struct winsize	ws;
	int				j;
	int				l;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	var->col = ws.ws_col;
	(!DEL && !SUPP) ? *line = ft_insert_char(*line, buf, &var->index) : (0);
	(SUPP) ? *line = ft_supp_char(*line, &var->index) : (0);
	(DEL) ? *line = ft_del_char(*line, &var->index) : (0);
	(!DEL && !SUPP) ? var->index++ : (0);
	j = -1;
	while (++j < var->multiline)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	l = -1;
	while (++l <= (ft_prompt_len(var) + (int)ft_strlen(*line)))
		write(1, "\b", 2);
	ft_prompt(var);
	miniprintf(STDOUT_FILENO, "%s", *line);
	ft_print_multiline(var, line, buf);
	i = ft_strlen(*line);
	while (--i >= var->index)
		tputs(tgetstr("le", NULL), 0, ft_outc);
}
