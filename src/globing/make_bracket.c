/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:25:46 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	get_size_bracket(const char *s2, int y)
{
	int	n;

	n = 0;
	while (s2[y] != ']')
	{
		y++;
		n++;
	}
	return (n);
}

static char	*make_bracket_without_minus(const char *s2, int y)
{
	char	*bracket;
	int		i;

	i = 0;
	bracket = (char*)malloc((get_size_bracket(s2, y) + 1) * sizeof(char));
	if (bracket == NULL)
		return (NULL);
	while (s2[y] != ']')
	{
		bracket[i] = s2[y];
		i++;
		y++;
	}
	bracket[i] = '\0';
	return (bracket);
}

static char	*make_bracket_with_minus(const char *s2, int y)
{
	char	*bracket;
	int		i;
	char	c;

	i = 0;
	if ((s2[y + 2] - s2[y]) >= 0)
		bracket = (char*)malloc(((s2[y + 2] - s2[y]) + 2) * sizeof(char));
	else
		bracket = NULL;
	if (bracket == NULL)
		return (NULL);
	c = s2[y];
	while (c != s2[y + 2])
	{
		bracket[i] = c;
		c++;
		i++;
	}
	bracket[i] = c;
	bracket[i + 1] = '\0';
	return (bracket);
}

static char	*make_inverted_bracket(const char *s2, int y)
{
	char	*contenu;
	char	*bracket;
	int		i;
	int		z;

	i = 0;
	z = 0;
	contenu = ft_strdup(&(s2[y]));
	while (contenu[i] && contenu[i] != ']')
		i++;
	contenu[i] = '\0';
	i = 33;
	bracket = (char*)malloc(94 * sizeof(char));
	while (i < 127)
	{
		if (ft_strchr(contenu, i) == NULL)
		{
			bracket[z] = i;
			z++;
		}
		i++;
	}
	bracket[z] = '\0';
	free(contenu);
	return (bracket);
}

char		*make_bracket(const char *s2, int y)
{
	if (s2[y] == '!')
		return (make_inverted_bracket(s2, y));
	else if (s2[y + 1] == '-')
		return (make_bracket_with_minus(s2, y));
	else
		return (make_bracket_without_minus(s2, y));
}
