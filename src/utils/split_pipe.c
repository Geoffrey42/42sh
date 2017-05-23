/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:51:04 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:54:16 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_next_pipe(char *s, int begin)
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
		else if (s[i] == '|' && s[i - 1] != '\\')
			return (i);
	}
	return (i);
}

void	ft_nb_word_pipe(char *s, int *i, int *word)
{
	int	k;

	while (s[++(*i)] != '\0')
		if (s[*i] == '|' && s[*i - 1] != '\\')
			(*word)++;
		else if (s[*i] == '\'' || s[*i] == '\"')
		{
			k = *i + 1;
			while (s[k] && s[k] != s[*i])
				k++;
			while (*i < k)
				(*i)++;
		}
}

char	**ft_strsplit_pipe(char *s)
{
	char	**ret;
	int		i;
	int		j;
	int		end;
	int		word;

	i = -1;
	word = 1;
	ft_nb_word_pipe(s, &i, &word);
	ret = (char **)malloc(sizeof(char *) * (word + 1));
	i = -1;
	j = 0;
	while (++i < word)
	{
		end = ft_next_pipe(s, j);
		ret[i] = ft_strsub(s, j, end - j);
		j = end + 1;
	}
	ret[i] = NULL;
	return (ret);
}

int		ft_search_pipe(t_var *var)
{
	int		i;
	char	*s;

	i = -1;
	while (var->pipe[0][++i] != '\0')
		if (var->pipe[0][i] == '|')
			break ;
	if (var->pipe[0][i] == '\0')
		return (0);
	s = ft_strdup(var->pipe[0]);
	free(var->pipe[0]);
	free(var->pipe);
	var->pipe = ft_strsplit_pipe(s);
	free(s);
	return (1);
}
