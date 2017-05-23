/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_multi_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:15:45 by ggane             #+#    #+#             */
/*   Updated: 2017/04/13 16:51:29 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	message_err_redir(char *str, t_var *term)
{
	ft_print_str_endl(1, str);
	term->red = 0;
	return (0);
}

int	search_redir(t_var *term, int i)
{
	int	j;

	j = 0;
	term->red = 0;
	while (term->pipe[i][j])
	{
		if (term->pipe[i][j] == '>' || term->pipe[i][j] == '<')
			term->red = 1;
		if (term->pipe[i][j] == '>' && term->pipe[i][j + 1] == '>' &&
				term->pipe[i][j + 2] == '>')
			return (message_err_redir("42sh: parse error near `>'\n", term));
		if (term->pipe[i][j] == '<' && term->pipe[i][j + 1] == '<' &&
				term->pipe[i][j + 2] == '<')
			return (message_err_redir("42sh: parse error near `<'\n", term));
		j++;
	}
	return (1);
}
