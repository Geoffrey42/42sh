/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:51:20 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:37:30 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_last_slash(char *s)
{
	char	*ret;
	int		i;

	i = ft_strlen(s) - 1;
	if (s[i] == '/')
		i--;
	while (i > 0 && s[i] != '/')
		i--;
	if (i == 0)
		ret = ft_strdup(s);
	else
		ret = ft_strdup(&(s[i + 1]));
	return (ret);
}

void	ft_dir_or_usr(int opt, t_var *var, int i, int video)
{
	int		max;
	char	*tmp;

	max = max_len(var->comp->array);
	tmp = ft_last_slash(var->comp->array[i]);
	if (opt == 0)
	{
		ft_tab_to_space(tmp);
		if (i == video)
			miniprintf(STDOUT_FILENO, "%s", tmp);
		else
			miniprintf(STDOUT_FILENO, DIRECT"%s"FIN, tmp);
		var->comp->space = max - ft_strlen_tab(tmp);
	}
	else
	{
		ft_tab_to_space(tmp);
		if (i == video)
			miniprintf(STDOUT_FILENO, "%s", tmp);
		else
			miniprintf(STDOUT_FILENO, "\e[1;31;40m%s"FIN, tmp);
		var->comp->space = max - ft_strlen_tab(tmp);
	}
	free(tmp);
}
