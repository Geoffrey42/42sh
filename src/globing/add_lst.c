/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:19:02 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:22:56 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int		size_list(t_list_glob *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	while (lst->prec != NULL)
		lst = lst->prec;
	return (i);
}

int		check_existence(t_list_glob *lst, char *str)
{
	while (lst)
	{
		if (ft_strcmp(lst->name, str) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	add_lst(t_list_glob **lst, char *name)
{
	t_list_glob	*new;

	if (check_existence(*lst, name) == 1)
		return ;
	new = (t_list_glob*)malloc(sizeof(t_list_glob));
	new->name = ft_strdup(name);
	new->next = NULL;
	new->prec = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		(*lst)->next = new;
		new->prec = (*lst);
		while ((*lst)->prec != NULL)
			*lst = (*lst)->prec;
	}
}
