/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:19:29 by ggane             #+#    #+#             */
/*   Updated: 2017/04/25 16:22:44 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_rapids_terms(t_var *var, char buf[BSIZE], int len)
{
	if (GAUCHE && var->index > 0)
		ft_left(var);
	if (DROITE && (var->index < len))
		ft_right(var);
	if (HOME)
		while (var->index > 0)
			ft_left(var);
	if (END)
		while (var->index < len)
			ft_right(var);
}

void	ft_multimove(t_var *var, char buf[BSIZE], char *line)
{
	int		i;

	i = 0;
	if (MULTIUP)
		while (i < var->col && var->index > 0)
		{
			ft_left(var);
			i++;
		}
	if (MULTIDO)
		while (i < var->col && var->index < (int)ft_strlen(line))
		{
			ft_right(var);
			i++;
		}
}

char	*ft_termcaps(t_var *var, char *line, char buf[BSIZE])
{
	int				len;
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	var->col = ws.ws_col;
	len = ft_strlen(line);
	if (TAB)
		line = tabulation(line, var);
	if (CL)
	{
		tputs(tgetstr("cl", NULL), 0, ft_outc);
		ft_prompt(var);
		miniprintf(STDOUT_FILENO, "%s", line);
		var->multiline = (ft_prompt_len(var) + ft_strlen(line)) / var->col;
	}
	(HAUT) ? ft_history_move('u', var, &line) : (0);
	(BAS) ? ft_history_move('d', var, &line) : (0);
	(GAUCHE || DROITE || HOME || END) ? ft_rapids_terms(var, buf, len) : (0);
	(UP) ? ft_prev_word(var, line) : (0);
	(DOWN) ? ft_next_word(var, line, len) : (0);
	(MULTIUP || MULTIDO) ? ft_multimove(var, buf, line) : (0);
	(COPY && ft_strcmp(line, "\0")) ? ft_copy(var, &line) : (0);
	(PASTE) ? line = ft_paste(var, line) : (0);
	return (line);
}
