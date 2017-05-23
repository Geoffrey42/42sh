/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 16:01:22 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:56:37 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	nbtab(char const *s, char c, char d)
{
	int	i;
	int	nbr;

	i = 0;
	while ((s[i] == c && s[i]) || (s[i] == d && s[i]))
		i++;
	nbr = 0;
	while (s[i])
	{
		while (s[i] && s[i] != c && s[i] != d)
			i++;
		nbr++;
		while ((s[i] && s[i] == c) || (s[i] && s[i] == d))
			i++;
	}
	return (nbr);
}

void		loop_split_pipe(char const *s, char **str, int *j, int *index)
{
	int		booleen;
	int		k;
	char	car;

	booleen = 0;
	k = 0;
	while ((s[*j] == ' ') || (s[*j] == '\t'))
		*j = *j + 1;
	str[*index] = ft_strnew(ft_strlen(s));
	while ((s[*j] && s[*j] != ' ' && s[*j] != '\t') || (booleen == 1))
	{
		if (((s[*j] == '\"' && booleen == 0) ||
					(s[*j] == '\'' && booleen == 0)))
		{
			booleen = 1;
			car = s[*j];
		}
		else if ((booleen == 1 && s[*j] == car))
			booleen = 0;
		else
			str[*index][k++] = s[*j];
		*j = *j + 1;
	}
	str[*index][k] = '\0';
	*index = *index + 1;
}

char		**split_qte(char const *s)
{
	int		len;
	int		j;
	int		index;
	char	**str;

	j = 0;
	index = 0;
	len = nbtab(s, ' ', '\t');
	if ((!s) || (!(str = (char**)malloc(sizeof(char*) * (len + 2)))))
		return (NULL);
	while (s[j] && (index < len))
		loop_split_pipe(s, str, &j, &index);
	str[index] = NULL;
	return (str);
}
