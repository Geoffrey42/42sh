/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_explode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:24:10 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	number_str(char const *s, char *delimiter)
{
	int	result;
	int	i;
	int	len;

	i = 0;
	result = 1;
	len = ft_strlen(delimiter);
	while (s[i] != 0)
	{
		if (ft_strncmp(delimiter, &s[i], len) == 0)
		{
			result++;
			i += len;
		}
		else
			i++;
	}
	return (result);
}

static int	next_size(char const *s, char *delimiter, int i)
{
	int	result;
	int	len;

	len = ft_strlen(delimiter);
	result = 0;
	while (ft_strncmp(&s[i + result], delimiter, len) && s[i + result] != '\0')
		result++;
	return (result);
}

static char	*next_word(char const *s, char *delimiter, int *i)
{
	char	*result;
	int		size;
	int		j;
	int		len;

	len = ft_strlen(delimiter);
	size = next_size(s, delimiter, *i);
	result = ft_strnew(size + 1);
	if (result == NULL)
		return (NULL);
	j = 0;
	while (ft_strncmp(&s[*i], delimiter, len) && s[*i] != '\0')
	{
		result[j] = s[*i];
		j++;
		*i += 1;
	}
	if (ft_strncmp(&s[*i], delimiter, len) == 0)
		*i += len;
	return (result);
}

char		**ft_explode(char const *s, char *delimiter)
{
	int		size;
	int		n;
	int		i;
	char	**result;

	if (s == NULL)
		size = 0;
	else
		size = number_str(s, delimiter);
	result = ft_memalloc(sizeof(char*) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	i = 0;
	n = 0;
	while (n < size)
	{
		result[n] = next_word(s, delimiter, &i);
		if (result[n] == NULL)
			return (NULL);
		n++;
	}
	return (result);
}
