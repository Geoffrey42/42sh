/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:41:24 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:32:11 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	ft_end_of_par(char c)
{
	if (c == '(')
		return (')');
	if (c == '{')
		return ('}');
	if (c == '[')
		return (']');
	if (c == '`')
		return ('`');
	return (0);
}

void	ft_check_par(char c, t_quotes *qu)
{
	(c == '(') ? qu->par++ : (0);
	(c == ')') ? qu->par-- : (0);
	(c == '{') ? qu->acc++ : (0);
	(c == '}') ? qu->acc-- : (0);
	(c == '[') ? qu->bra++ : (0);
	(c == ']') ? qu->bra-- : (0);
	(c == '`' && qu->acc % 2 == 0) ? qu->acc++ : (0);
	(c == '`' && qu->acc % 2 == 1) ? qu->acc-- : (0);
}

int		ft_return_syntax(char c)
{
	miniprintf(STDERR_FILENO, "42sh: syntax error `%c'\n", c);
	return (0);
}

int		ft_return_brace(t_quotes *qu, char c)
{
	free(qu);
	return (ft_return_syntax(c));
}

int		ft_check_line(char **s)
{
	int		i;
	char	*cpy;

	if (!s)
		return (0);
	i = -1;
	cpy = ft_strdup(*s);
	if (ft_no_quotes(s, &cpy) == 0)
		return (0);
	while (cpy[++i] != '\0')
		if ((cpy[i] == '(' || cpy[i] == '{' || cpy[i] == '[' || cpy[i] == '`')
		&& ft_check_brace('a', &i, &cpy, 0) == 0)
		{
			free(cpy);
			return (0);
		}
		else if (cpy[i] == ')' || cpy[i] == '}' || cpy[i] == ']')
		{
			miniprintf(STDERR_FILENO, "42sh: syntax error `%c'\n", cpy[i]);
			free(cpy);
			return (0);
		}
	free(cpy);
	return (1);
}
