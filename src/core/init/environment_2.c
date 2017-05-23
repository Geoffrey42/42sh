/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:07:26 by ggane             #+#    #+#             */
/*   Updated: 2017/04/27 00:19:45 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**ft_no_env(void)
{
	char	**env;
	char	*s;

	env = (char **)malloc(sizeof(char *) * 3);
	s = (char *)malloc(sizeof(char) * 400);
	env[0] = ft_strdup("SHLVL=2");
	s = getcwd(s, 2048);
	env[1] = ft_strjoin("PWD=", s);
	free(s);
	env[2] = NULL;
	return (env);
}

void	open_fd(void)
{
	if ((isatty(STDIN_FILENO) == 0) || (isatty(STDOUT_FILENO) == 0) ||
		(isatty(STDERR_FILENO) == 0))
		exit(0);
}
