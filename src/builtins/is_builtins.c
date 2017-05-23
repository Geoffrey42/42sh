/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:57:15 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:58:45 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			ft_is_builtin(char *s)
{
	if (CMP("exit") || CMP("cd") || CMP("env") || CMP("export") ||
			CMP("setenv") || CMP("unsetenv") || CMP("unset") || CMP("echo") ||
			ft_is_in(s, '=') || CMP("history"))
		return (V);
	return (F);
}

char		**ft_cpy_tab_i(char **s, int beg)
{
	int		i;
	char	**ret;

	i = beg;
	while (s[i] != NULL)
		i++;
	ret = (char **)malloc(sizeof(char *) * (i - beg + 1));
	i = 0;
	while (s[beg] != NULL)
	{
		ret[i] = ft_strdup(s[beg]);
		i++;
		beg++;
	}
	ret[i] = NULL;
	return (ret);
}
