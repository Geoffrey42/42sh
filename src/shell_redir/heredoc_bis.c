/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 06:19:35 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:46:21 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_verif_buf(char buf[BSIZE], char **ret, int *index, t_var *term)
{
	char *tmp;

	if (buf[0] != 4 && buf[0] != 127 && !BAD)
	{
		miniprintf(STDOUT_FILENO, "%s", buf);
		tmp = ft_strjoin(*ret, buf);
		free(*ret);
		*ret = ft_strdup(tmp);
		free(tmp);
	}
	if (buf[0] == 4)
	{
		term->cd = 1;
		miniprintf(STDIN_FILENO, "\n");
	}
	if (buf[0] == 127 && ft_strlen(*ret) > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 0, 0), 0, ft_outc);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 0, ft_outc);
		*index = ft_strlen(*ret);
		*ret = ft_supp_char(*ret, index);
	}
}

char	*loop_loop_heredoc(t_var *term)
{
	char	buf[BSIZE];
	char	*ret;
	int		index;
	char	*tmp;

	index = 0;
	term->cd = 0;
	ret = ft_strdup("\0");
	ft_putstr("heredoc > ");
	while (!ENTER || buf[0] != 4)
	{
		init_termios(term);
		ft_bzero(buf, BSIZE);
		read(STDIN_FILENO, buf, BSIZE);
		buf[1] = '\0';
		ft_verif_buf(buf, &ret, &index, term);
		if (buf[0] == 10 || term->cd)
		{
			tmp = ft_strjoin(ret, "\0");
			free(ret);
			return (tmp);
		}
	}
	return (ret);
}

int		loop_heredoc(t_var *term, char **tmp, char *key)
{
	char	*tmp1;
	char	*tmp2;

	(void)tmp;
	tmp1 = NULL;
	tmp1 = loop_loop_heredoc(term);
	if (ft_strcmp(tmp1, key) == 0)
	{
		free(tmp1);
		return (1);
	}
	else if (term->cd)
	{
		free(tmp1);
		return (1);
	}
	else
	{
		tmp2 = ft_strjoin(term->tmp, tmp1);
		free(term->tmp);
		term->tmp = ft_strdup(tmp2);
		free(tmp2);
		free(tmp1);
	}
	return (0);
}

char	*loop_init_heredoc(t_var *term, int *j)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	term->tmp = ft_free(term->tmp);
	term->tmp = ft_strdup("\0");
	i = *j;
	while (term->redir[i] && ft_valid(term, i) != 1 && ft_valid(term, i) != 2)
	{
		if (ft_strcmp(term->redir[i], "<<") == 0)
		{
			*j = i + 1;
			tmp = ft_free(tmp);
			term->key = ft_strjoin(term->redir[i + 1], "\n");
			while (loop_heredoc(term, &tmp, term->key) == 0)
			{
			}
			term->key = ft_free(term->key);
		}
		i++;
	}
	return (term->tmp);
}

void	ft_init_heredoc(t_var *term)
{
	init_std(term);
	term->red = 0;
	term->cd = 0;
	term->her = 0;
	term->truc = 0;
}
