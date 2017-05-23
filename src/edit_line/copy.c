/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:57:33 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:13:34 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*ft_print_mr(char *line, int index, int i)
{
	int		max;
	char	*s;
	int		j;

	max = index;
	(i > index) ? max = i : (0);
	(i > index) ? i = index : (0);
	index = 0;
	s = (char *)malloc(sizeof(char) * (max - i + 1));
	j = -1;
	while (line[index])
	{
		if (index == i)
			tputs(tgetstr("mr", NULL), 0, ft_outc);
		write(STDOUT_FILENO, &(line[index]), 1);
		if (index == max)
			tputs(tgetstr("me", NULL), 0, ft_outc);
		if (index >= i && index <= max)
			s[++j] = line[index];
		index++;
	}
	s[j + 1] = '\0';
	tputs(tgetstr("me", NULL), 0, ft_outc);
	return (s);
}

static void	ft_select_copy(char buf[BSIZE], int *i, char **line, t_var *var)
{
	int	j;

	if (DROITE && *i < (int)ft_strlen(*line))
		(*i)++;
	if (GAUCHE && *i > 0)
		(*i)--;
	tputs(tgetstr("vi", NULL), 0, ft_outc);
	j = -1;
	while (++j < var->multiline)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	ft_prompt(var);
	free(var->copy);
	var->copy = ft_print_mr(*line, var->index, *i);
	j = ft_strlen(*line);
	while (--j >= var->index)
		tputs(tgetstr("le", NULL), 0, ft_outc);
}

void		ft_copy(t_var *var, char **line)
{
	char	buf[BSIZE];
	int		i;
	int		j;

	free(var->copy);
	var->copy = ft_strdup("\0");
	ft_bzero(buf, BSIZE);
	i = var->index;
	while (!COPY)
	{
		ft_bzero(buf, BSIZE);
		read(1, buf, BSIZE);
		ft_select_copy(buf, &i, line, var);
	}
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	j = -1;
	while (++j < var->multiline)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	ft_prompt(var);
	write(1, *line, ft_strlen(*line));
	i = ft_strlen(*line);
	while (--i >= var->index)
		tputs(tgetstr("le", NULL), 0, ft_outc);
}
