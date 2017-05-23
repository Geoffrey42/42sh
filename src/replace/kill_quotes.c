/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:37:41 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:35:07 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_change(char *s, int i, int j)
{
	char	*new;
	char	c;

	new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[++i] != '\0')
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] != c)
				new[j++] = s[i++];
		}
		else if (s[i] == '\\')
		{
			i++;
			if (s[i] == '	')
				new[j++] = ' ';
			else
				new[j++] = s[i];
		}
		else
			new[j++] = s[i];
	new[j] = '\0';
	free(s);
	return (new);
}

void	ft_kill_quotes(char ***arg)
{
	int	i;

	i = -1;
	if (!*arg || (*arg && *(arg[0]) == NULL))
		return ;
	while (*arg && (*arg)[++i])
		if (ft_is_in((*arg)[i], '\'') || ft_is_in((*arg)[i], '\"') ||
		ft_is_in((*arg)[i], '\\'))
			(*arg)[i] = ft_change((*arg)[i], -1, 0);
}
