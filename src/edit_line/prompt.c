/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprunier <lprunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:17:31 by lprunier          #+#    #+#             */
/*   Updated: 2017/04/25 15:10:00 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_find_addr(t_lenv *lst)
{
	t_lenv	*begin;
	char	*addr;
	int		i;
	char	*tmp;

	begin = lst;
	addr = NULL;
	while (lst)
	{
		if (!ft_strcmp(lst->bef, "PWD"))
			addr = ft_strdup(lst->aft);
		lst = lst->next;
	}
	if (addr == NULL)
	{
		tmp = ft_strdup(".");
		return (tmp);
	}
	lst = begin;
	i = ft_strlen(addr);
	while (i > 0 && addr[i] != '/')
		i--;
	tmp = ft_strdup(&(addr[i]));
	free(addr);
	return (tmp);
}

char	*ft_find_name(t_lenv *lst)
{
	t_lenv	*begin;
	char	*name;

	begin = lst;
	name = NULL;
	while (lst)
	{
		if (!ft_strcmp(lst->bef, "LOGNAME"))
			name = ft_strdup(lst->aft);
		lst = lst->next;
	}
	lst = begin;
	if (name == NULL)
		name = ft_strdup(".");
	return (name);
}

void	ft_prompt(t_var *var)
{
	int	i;

	tputs(tgetstr("me", NULL), 0, ft_outc);
	if (var->opt_quo == 1)
	{
		miniprintf(STDOUT_FILENO, RED">"FIN);
		return ;
	}
	if (var->echo != NULL)
	{
		i = -1;
		while (var->echo[++i])
			if (var->echo[i] != '	')
				miniprintf(STDOUT_FILENO, "%c", var->echo[i]);
	}
	miniprintf(STDOUT_FILENO, SHINE"42sh [");
	miniprintf(STDOUT_FILENO, SHINE"%s] "FIN RED">"FIN, var->addr);
}

int		ft_prompt_len(t_var *var)
{
	int	i;
	int	len;

	if (var->opt_quo == 1)
		return (1);
	len = 0;
	if (var->echo != NULL)
	{
		i = -1;
		while (var->echo[++i])
			if (var->echo[i] != '	')
				len++;
	}
	i = 6 + len - 4 + 6;
	i += ft_strlen(var->addr);
	if (var->echo != NULL)
		i += ft_strlen(var->echo);
	return (i);
}
