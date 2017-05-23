/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:54:12 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:46:06 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_tab_to_space(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		(s[i] == '	' && s[i - 1] == '\\') ? s[i] = ' ' : (0);
	s[i] = '\0';
}

void	ft_space_to_tab(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		(s[i] == ' ' && s[i - 1] == '\\') ? s[i] = '	' : (0);
	s[i] = '\0';
}

int		count_line_tab(char **array)
{
	struct winsize	ws;
	int				max;
	int				word;
	int				line;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	max = max_len(array) + 1;
	word = count_tab(array);
	if (max > ws.ws_col)
		return (word * 2);
	line = ws.ws_col / max;
	line = word / line;
	line++;
	if (line >= ws.ws_row)
		return (line);
	return (0);
}

int		count_tab(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
