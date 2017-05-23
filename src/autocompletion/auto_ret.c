/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:05:27 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:44:41 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_part_ret_single(int *i, t_var *var, char *line)
{
	char	*tmp;

	while (--(*i) >= 0)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	ft_prompt(var);
	tmp = begin_clean(line);
	miniprintf(STDOUT_FILENO, "%s%s", tmp, var->comp->array[var->comp->i]);
	free(tmp);
}

char	*ret_single_line(char *line, t_var *var)
{
	int				i;
	char			*tmp;
	char			*tmpl;
	int				len;
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	ft_tab_to_space(var->comp->array[var->comp->i]);
	i = (ft_strlen(line) + ft_prompt_len(var) +
			ft_strlen(var->comp->array[var->comp->i])) / var->col;
	ft_part_ret_single(&i, var, line);
	len = len_last_line(line, var) + ft_strlen(var->comp->array[var->comp->i]);
	while (len > ws.ws_col)
		len -= ws.ws_col;
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 0, ft_outc);
	var->index = ft_strlen(line) + ft_strlen(var->comp->array[var->comp->i]);
	var->multiline = var->index / ws.ws_col;
	tmpl = begin_clean(line);
	tmp = ft_strjoin(tmpl, var->comp->array[var->comp->i]);
	free(line);
	free(tmpl);
	free(var->comp->new);
	return (tmp);
}

void	ft_split_tmp_one(char **s, t_var *var)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(var->comp->array[var->comp->i], var->comp->end);
	tmp1 = begin_clean(var->comp->begin);
	*s = ft_strjoin(tmp1, tmp);
	free(tmp);
	free(tmp1);
	ft_prompt(var);
}

char	*ft_split_tmp_two(char **s, t_var *var, char **line)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(var->comp->array[var->comp->i], var->comp->end);
	tmp1 = ft_strjoin(*line, tmp);
	free(*line);
	free(*s);
	free(tmp);
	return (tmp1);
}

char	*ret_join_split(char *line, t_var *var)
{
	int				i;
	char			*s;
	int				len;
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	ft_tab_to_space(var->comp->array[var->comp->i]);
	i = (ft_strlen(line) + ft_prompt_len(var) +
			ft_strlen(var->comp->array[var->comp->i])) / var->col;
	while (--i >= 0)
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	ft_split_tmp_one(&s, var);
	ft_putstr(s);
	len = len_last_line(line, var) + ft_strlen(var->comp->array[var->comp->i]);
	while (len > ws.ws_col)
		len -= ws.ws_col;
	tputs(tgoto(tgetstr("ch", NULL), 0, len), 0, ft_outc);
	var->index = ft_strlen(s) - ft_strlen(var->comp->end);
	var->multiline = var->index / ws.ws_col;
	i = ft_strlen(s);
	while (--i >= var->index)
		tputs(tgetstr("le", NULL), 0, ft_outc);
	free(var->comp->new);
	return (ft_split_tmp_two(&s, var, &line));
}
