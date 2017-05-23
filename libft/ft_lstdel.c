/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 07:49:22 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 15:34:24 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *list;
	t_list *new_list;

	list = *alst;
	while (list)
	{
		new_list = list->next;
		del(list->content, list->content_size);
		free(list);
		list = new_list;
	}
	*alst = NULL;
}
