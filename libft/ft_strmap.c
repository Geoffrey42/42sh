/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:10:57 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 08:11:22 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		i;

	i = -1;
	if (!s || !f || !(new = ft_strdup(s)))
		return (NULL);
	while (new && new[++i])
		new[i] = (f)(new[i]);
	new[i] = '\0';
	return (new);
}
