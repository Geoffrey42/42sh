/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:41:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:53:42 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_next_sp(char *s, int begin)
{
	int	i;
	int	k;

	i = begin - 1;
	while (s[++i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			k = i + 1;
			while (s[k] != '\0' && s[k] != s[i])
				k++;
			while (i < k)
				i++;
		}
		else if (s[i] == ' ' && s[i - 1] != '\\')
			return (i);
	}
	return (i);
}

int		ft_nb_word(char *s, int i)
{
	int	word;
	int	k;

	word = 1;
	while (s[++i] != '\0')
		if (s[i] == ' ' && s[i - 1] != '\\')
			word++;
		else if (s[i] == '\'' || s[i] == '\"')
		{
			k = i + 1;
			while (s[k] != '\0' && s[k] != s[i])
				k++;
			while (i < k)
				i++;
		}
	return (word);
}

char	**ft_strsplit_sp(char *s)
{
	char	**ret;
	int		i;
	int		j;
	int		word;
	int		k;

	i = -1;
	word = ft_nb_word(s, i);
	ret = (char **)malloc(sizeof(char *) * (word + 1));
	i = -1;
	j = 0;
	while (++i < word)
	{
		k = ft_next_sp(s, j);
		ret[i] = ft_strsub(s, j, k - j);
		j = k + 1;
	}
	ret[i] = NULL;
	return (ret);
}
