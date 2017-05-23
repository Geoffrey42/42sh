/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:14:09 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:56:52 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_strjoin_char(char *s1, char c, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = ft_strlen(s1) + ft_strlen(s2) + 2;
	ret = (char *)malloc(sizeof(char) * i);
	i = -1;
	j = -1;
	while (s1[++j])
		ret[++i] = s1[j];
	ret[++i] = c;
	j = -1;
	while (s2[++j])
		ret[++i] = s2[j];
	ret[++i] = '\0';
	return (ret);
}

char	*ft_strjoin_int(char *s1, int c, char *s2)
{
	int		i;
	int		j;
	char	*ret;
	char	*nb;

	nb = ft_itoa(c);
	i = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(nb) + 2;
	ret = (char *)malloc(sizeof(char) * i);
	i = -1;
	j = -1;
	while (s1[++j])
		ret[++i] = s1[j];
	j = -1;
	while (nb[++j])
		ret[++i] = nb[j];
	j = -1;
	while (s2[++j])
		ret[++i] = s2[j];
	ret[++i] = '\0';
	free(nb);
	return (ret);
}
