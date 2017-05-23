/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:57:34 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:14:11 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	ft_loop_paste(t_var *var, char *s)
{
	if ((var->index > (int)ft_strlen(s) - 1) && ((var->index +
					ft_prompt_len(var) - 1) % (var->col) == 0))
		var->multiline++;
	else if (((var->index + ft_prompt_len(var)) % (var->col) == 0))
		var->multiline++;
	var->index++;
}

static void	ft_replace_paste(int *i, int *j, t_var *var, char *s)
{
	*j = -1;
	*i = -1;
	while (++(*j) < var->multiline)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	ft_prompt(var);
	write(1, s, ft_strlen(s));
}

char		*ft_paste(t_var *var, char *line)
{
	char	*s;
	int		i;
	int		j;

	s = (char *)malloc(sizeof(char) *
	(ft_strlen(line) + ft_strlen(var->copy) + 1));
	i = -1;
	j = -1;
	while (++i < var->index)
		s[i] = line[i];
	while (var->copy[++j])
		s[i++] = var->copy[j];
	j = var->index - 1;
	while (line[++j])
		s[i++] = line[j];
	s[i] = '\0';
	free(line);
	ft_replace_paste(&i, &j, var, s);
	while (++i < (int)ft_strlen(var->copy))
		ft_loop_paste(var, s);
	i = ft_strlen(s);
	while (--i >= var->index)
		tputs(tgetstr("le", NULL), 0, ft_outc);
	return (s);
}
