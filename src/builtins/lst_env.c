/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 20:41:55 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:59:02 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*delete_quote(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i] != '\0')
		if (str[i] == 34)
			break ;
		else
			i++;
	if (i == (int)ft_strlen(str))
		return (str);
	ret = (char *)malloc(sizeof(char) * ft_strlen(str) - i + 1);
	i++;
	while (str[i] != '\0')
	{
		ret[j] = str[i];
		j++;
		i++;
		if (str[i] == 34)
			i++;
	}
	ret[j] = '\0';
	return (ret);
}

void	ft_verif_link(t_lenv *new)
{
	new->aft = delete_quote(new->aft);
	if (ft_is_in(new->aft, '$'))
	{
		free(new->aft);
		new->aft = ft_strdup("\0");
	}
	new->next = NULL;
}

t_lenv	*ft_new_link(char *env, char c)
{
	t_lenv	*new;
	int		i;

	i = 0;
	new = (t_lenv *)malloc(sizeof(t_lenv));
	new->c = c;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	if (!(new->bef = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	new->bef = ft_memcpy(new->bef, env, i);
	new->bef[i] = '\0';
	if (env[i] == '\0')
		new->aft = ft_strdup("\0");
	else if (i++ > -1)
	{
		if (!(new->aft = (char *)malloc(sizeof(char)
			* (ft_strlen(env) - i + 1))))
			return (NULL);
		new->aft = ft_memcpy(new->aft, &(env[i]), ft_strlen(env) - i);
		new->aft[ft_strlen(env) - i] = '\0';
	}
	ft_verif_link(new);
	return (new);
}

char	*check_bef(char *env)
{
	int		i;
	char	*ret;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret = ft_memcpy(ret, env, i);
	ret[i] = '\0';
	return (ret);
}

int		update_value(t_lenv **lenv, char *env, char c)
{
	t_lenv	*begin_list;
	char	*lorette;

	lorette = check_bef(env);
	begin_list = (*lenv);
	while ((*lenv))
	{
		if (ft_strcmp((*lenv)->bef, lorette) == 0 && (*lenv)->bef)
		{
			free((*lenv)->aft);
			(*lenv)->aft = ft_strdup(&(env[ft_strlen((*lenv)->bef) + 1]));
			(*lenv)->aft = delete_quote((*lenv)->aft);
			(*lenv)->c = c;
			(*lenv) = begin_list;
			free(lorette);
			return (1);
		}
		(*lenv) = (*lenv)->next;
	}
	free(lorette);
	(*lenv) = begin_list;
	return (0);
}
