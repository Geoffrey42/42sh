/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enter_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:07:10 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:08:15 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ft_check_red(char **s, int *i, int *j)
{
	if ((*s)[*i - 1] != ' ' && (*s)[*i - 1] != (*s)[*i] &&
	!ft_isdigit((*s)[*i - 1]))
	{
		ft_add_space(s, *i - 1);
		(*i)++;
	}
	if ((*s)[*i] == '<' && (*s)[*i + 1] != ' ' && (*s)[*i + 1] != '<')
	{
		ft_add_space(s, *i);
		(*i)++;
	}
	*j = *i + 1;
	while ((*s)[*j] == (*s)[*i])
		(*j)++;
	if (ft_isalnum((*s)[*j]) || (*s)[*j] == '/')
		ft_add_space(s, *j - 1);
}

int			ft_return_check(char c)
{
	miniprintf(STDERR_FILENO, "42sh: Parse error near `%c'\n", c);
	return (F);
}

int			ft_is_redir(char **s, int *i, int *j)
{
	ft_check_red(s, i, j);
	if ((*j - *i) > 2 || ((*s)[*j] != (*s)[*i] && (*s)[*j] != '&' &&
	(*s)[*j] != ' '))
		return (ft_return_check((*s)[*i]));
	while ((*s)[*j] == ' ')
		(*j)++;
	if (!ft_isalnum((*s)[*j]) && (*s)[*j] != '&' && (*s)[*j] != '/')
		return (ft_return_check((*s)[*i]));
	if ((*s)[*i] == '>' && (*s)[(*i) - 1] == '1' && (*s)[(*i) + 1] != '&')
		(*s)[(*i) - 1] = ' ';
	return (V);
}

int			ft_is_sep(char **s, int *i, int *j)
{
	*j = *i + 1;
	while ((*s)[*j] == (*s)[*i])
		(*j)++;
	if ((*j - *i) > 2 || ((*s)[*i] == '&' && (*s)[*i + 1] != '&'))
		return (ft_return_check((*s)[*i]));
	while ((*s)[*j] == ' ')
		(*j)++;
	if ((*s)[*j] == '\0')
		return (ft_return_check((*s)[*i]));
	*i = *j;
	return (V);
}
