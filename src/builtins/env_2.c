/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:16:56 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:01:43 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_free_var_cpy(t_var *var)
{
	t_lenv	*tmp;
	int		i;

	free(var->name);
	free(var->addr);
	free(var->copy);
	if (var->lenv)
	{
		while (var->lenv)
		{
			tmp = var->lenv;
			var->lenv = var->lenv->next;
			free(tmp->bef);
			free(tmp->aft);
			free(tmp);
		}
	}
	i = -1;
	if (var->logic)
	{
		if (ft_is_in(var->logic[0], ' ') || ft_is_in(var->logic[0], '='))
			free(var->logic[0]);
		free(var->logic);
	}
	free(var);
}

void	ft_lst_env(t_lenv *lst, t_lenv *cpy)
{
	cpy->bef = ft_strdup(lst->bef);
	cpy->aft = ft_strdup(lst->aft);
	cpy->c = lst->c;
	cpy->next = NULL;
}

t_lenv	*ft_copy_lst(t_lenv *lst, t_lenv *begin_lst)
{
	t_lenv	*cpy;
	t_lenv	*begin_cpy;

	begin_lst = lst;
	if (lst == NULL)
		return (NULL);
	cpy = (t_lenv *)malloc(sizeof(t_lenv));
	ft_lst_env(lst, cpy);
	begin_cpy = cpy;
	while (lst && lst->next)
	{
		if (lst->next->c == 'e')
		{
			cpy->next = (t_lenv *)malloc(sizeof(t_lenv));
			cpy->next->bef = ft_strdup(lst->next->bef);
			cpy->next->aft = ft_strdup(lst->next->aft);
			cpy->next->c = lst->next->c;
			cpy->next->next = NULL;
			cpy = cpy->next;
		}
		lst = lst->next;
	}
	cpy = begin_cpy;
	lst = begin_lst;
	return (cpy);
}

int		ft_is_in(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}
