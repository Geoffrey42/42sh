/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:23:58 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:34:05 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_change_quotes(char *s)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = -1;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[++i] != '\0')
		if ((s[i] == '\'' || s[i] == '\"') && (k = i + 1))
		{
			while (s[k] != '\0' && s[k] != s[i])
				k++;
			(i != k) ? s[i] = '	' : (0);
			(i != k) ? s[k] = '	' : (0);
		}
	i = -1;
	while (s[++i] != '\0')
		if (s[i] != '	' && s[i] != '\\')
			new[j++] = s[i];
	new[j] = '\0';
	return (new);
}

void	ft_del_quotes(char ***arg)
{
	int		i;
	char	*tmp;

	i = -1;
	while ((*arg)[++i] != NULL)
	{
		tmp = ft_strdup((*arg)[i]);
		free((*arg)[i]);
		(*arg)[i] = ft_change_quotes(tmp);
		free(tmp);
	}
}
