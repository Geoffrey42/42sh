/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:41:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 17:05:36 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_next_logic(char *s, int beg)
{
	int	i;
	int	k;

	i = beg;
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
		else if ((s[i] == '|' && s[i + 1] == '|') ||
			(s[i] == '&' && s[i + 1] == '&'))
			return (i);
	}
	return (i);
}

void	ft_nb_word_logic(char *s, int *i, int *word)
{
	int	k;

	while (s[++(*i)] != '\0')
	{
		if ((s[*i] == '|' && s[*i + 1] == '|') ||
			(s[*i] == '&' && s[*i + 1] == '&'))
		{
			*word += 2;
			(*i)++;
		}
		else if (s[*i] == '\'' || s[*i] == '\"')
		{
			k = *i + 1;
			while (s[k] != '\0' && s[k] != s[*i])
				k++;
			while (*i < k)
				(*i)++;
		}
	}
}

char	**ft_split_logic(char *s)
{
	int		i;
	int		j;
	int		end;
	char	**ret;
	int		word;

	i = -1;
	word = 1;
	ft_nb_word_logic(s, &i, &word);
	ret = (char **)malloc(sizeof(char *) * (word + 1));
	i = -1;
	j = 0;
	while (++i < word)
	{
		end = ft_next_logic(s, j);
		ret[i] = ft_strsub(s, j, end - j);
		(s[end] == '|') ? ret[++i] = ft_strdup("||") : (0);
		(s[end] == '&') ? ret[++i] = ft_strdup("&&") : (0);
		j = end + 2;
	}
	ret[i] = NULL;
	i = -1;
	while (ret[++i])
		ret[i] = ft_supp_space(ret[i]);
	return (ret);
}
