/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:43:27 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:59:14 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_insert_link(t_lenv **lst, char *env, char c, char *test)
{
	t_lenv	*temp;

	if (!(*lst)->next)
	{
		(*lst)->next = ft_new_link(env, c);
		return (1);
	}
	else if (ft_strcmp((*lst)->bef, test) < 0 &&
	ft_strcmp((*lst)->next->bef, test) > 0)
	{
		temp = (*lst)->next;
		(*lst)->next = ft_new_link(env, c);
		(*lst)->next->next = temp;
		return (1);
	}
	*lst = (*lst)->next;
	return (0);
}

void	ft_sort_insert(t_lenv **lst, char *env, char c)
{
	char	*test;
	t_lenv	*begin_list;

	begin_list = *lst;
	if (!(*lst))
	{
		(*lst) = ft_new_link(env, c);
		return ;
	}
	if (update_value(lst, env, c))
		return ;
	test = check_bef(env);
	if (ft_strcmp((*lst)->bef, test) > 0)
	{
		(*lst) = ft_new_link(env, c);
		(*lst)->next = begin_list;
		free(test);
		return ;
	}
	while ((*lst))
		if (ft_insert_link(lst, env, c, test) == 1)
			break ;
	free(test);
	*lst = begin_list;
}

void	ft_tab_to_lst(char **env, t_lenv **lst, char c)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_sort_insert(lst, env[i], c);
}
