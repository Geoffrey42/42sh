/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:24:07 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 15:53:18 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_put_in_array(char **array, char *s1, char *s2)
{
	int	i;
	int	j;

	*array = ft_memcpy(*array, s1, ft_strlen(s1));
	i = ft_strlen(s1) + 1;
	j = 0;
	(*array)[i - 1] = '=';
	while (s2[j] != '\0')
	{
		(*array)[i] = s2[j];
		i++;
		j++;
	}
	(*array)[i] = '\0';
}

char	**ft_lst_to_tab(t_lenv **lst)
{
	t_lenv	*begin_list;
	char	**env;
	int		i;

	i = 0;
	begin_list = *lst;
	while (*lst && i++ >= 0)
		*lst = (*lst)->next;
	*lst = begin_list;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*lst)
	{
		env[i] = (char *)malloc(sizeof(char) * (ft_strlen((*lst)->bef) +
					ft_strlen((*lst)->aft) + 2));
		ft_put_in_array(&(env[i]), (*lst)->bef, (*lst)->aft);
		i++;
		*lst = (*lst)->next;
	}
	env[i] = NULL;
	*lst = begin_list;
	return (env);
}
