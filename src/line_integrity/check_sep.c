/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 20:41:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:32:51 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_init_sep(t_var *var)
{
	var->sep = (t_sep *)malloc(sizeof(t_sep));
	var->sep->pv = 0;
	var->sep->et = 0;
	var->sep->ou = 0;
	var->sep->pip = 0;
	var->sep->in = 0;
	var->sep->out = 0;
}

void	ft_sep_next(int *i, t_var *var)
{
	char	c;

	c = var->line[*i];
	(*i)++;
	while (var->line[*i] != c)
		(*i)++;
}

int		ft_check_sep(t_var *var)
{
	int		i;

	i = -1;
	ft_init_sep(var);
	while (var->line[++i] != '\0')
		if (var->line[i] == '\'' || var->line[i] == '\"')
			ft_sep_next(&i, var);
		else if (var->line[i] == '&' && i > 0 && var->line[i - 1] == ' ' &&
				(var->line[i + 1] == ' ' || var->line[i + 1] == '\0'))
		{
			miniprintf(STDERR_FILENO, "42sh: parse error near `&'\n");
			free(var->sep);
			return (0);
		}
		else if (var->line[i] == ';' && var->line[i + 1] == ';')
		{
			miniprintf(STDERR_FILENO, "42sh: parse error near `;'\n");
			free(var->sep);
			return (0);
		}
		else if (var->line[i] == ';')
			var->sep->pv = 1;
	free(var->sep);
	return (1);
}
