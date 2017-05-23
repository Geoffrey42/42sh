/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:51:23 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:56:24 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_supp_space(char *s)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	ft_init_supp(&ret, s, &i, &j);
	while (s[i] != '\0')
	{
		if ((s[i] == '\'' || s[i] == '\"') && (k = i + 1) > -1)
		{
			while (s[k] && s[k] != s[i])
				k++;
			while (i < k)
				ret[j++] = s[i++];
		}
		while (s[i] == ' ' && s[i + 1] == ' ')
			i++;
		if (s[i] == ' ' && s[i + 1] == '\0')
			break ;
		ret[j++] = s[i++];
	}
	ret[j] = '\0';
	free(s);
	return (ret);
}

int		ft_next_pv(char *s, int begin)
{
	int	i;
	int	k;

	i = begin - 1;
	while (s[++i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			k = i + 1;
			while (s[k] && s[k] != s[i])
				k++;
			while (i < k)
				i++;
		}
		else if (s[i] == ';' && s[i - 1] != '\\')
			return (i);
	}
	return (i);
}

void	ft_nb_word_pv(char *s, int *i, int *word)
{
	int	k;

	while (s[++(*i)] != '\0')
		if (s[*i] == ';' && s[*i - 1] != '\\')
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

char	**ft_strsplit_pv(char *s)
{
	char	**ret;
	int		i;
	int		j;
	int		end;
	int		word;

	i = -1;
	word = 1;
	ft_nb_word_pv(s, &i, &word);
	ret = (char **)malloc(sizeof(char *) * (word + 1));
	i = -1;
	j = 0;
	while (++i < word)
	{
		end = ft_next_pv(s, j);
		ret[i] = ft_strsub(s, j, end - j);
		j = end + 1;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_split_cmd(t_var *var)
{
	int	i;

	i = -1;
	var->cmd = ft_strsplit_pv(var->line);
	while (var->cmd && var->cmd[++i])
		var->cmd[i] = ft_supp_space(var->cmd[i]);
}
