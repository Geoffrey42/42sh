/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 09:45:36 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:56:34 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	ft_nb_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*ft_dup_word(char const *s, char c)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (!(word = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = -1;
	while (++i < len)
		word[i] = s[i];
	word[i] = '\0';
	return (word);
}

char		**ft_strsplit_spe(char const *s, char c)
{
	char	**array;
	int		len;
	int		i;
	int		quote;

	quote = -1;
	if (!s || !c)
		return (NULL);
	len = ft_nb_word(s, c);
	if (!(array = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	i = -1;
	while (*s)
	{
		if (*s == '"')
			quote += 1;
		while (*s && *s == c && quote == 0)
			s++;
		if (*s && *s != c && quote)
			array[++i] = ft_dup_word(s, c);
		while (*s && *s != c)
			s++;
	}
	array[++i] = NULL;
	return (array);
}
