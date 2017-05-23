/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:55:49 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:36:19 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_lnk_or_else(int opt, t_var *var, int i, int video)
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
			miniprintf(STDOUT_FILENO, "\e[1;35;40m%s"FIN, tmp);
		var->comp->space = max - ft_strlen_tab(tmp);
	}
	else
	{
		ft_tab_to_space(tmp);
		miniprintf(STDOUT_FILENO, "%s", tmp);
		var->comp->space = max - ft_strlen_tab(tmp);
	}
	free(tmp);
}

int		find_dollar(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*loop_tab(char *buf, char *line, t_var *var)
{
	int		len;
	char	*ret;

	len = len_array(var->comp->array);
	var->comp->i = 0;
	while (1)
	{
		(ENTER) ? (ret = ft_enter_tab(var, line)) : (0);
		if (ENTER)
			return (ret);
		if (!var->comp->array[var->comp->i])
			var->comp->i = 0;
		if ((GAUCHE || DROITE || BAS || HAUT || TAB) && var->comp->len > 1)
			print_tab(line, var, 0, 0);
		if ((GAUCHE || DROITE || BAS || HAUT || TAB) && var->comp->len == 1)
			var->comp->i = 0;
		ft_bzero(buf, BSIZE);
		read(1, buf, BSIZE);
		(GAUCHE && len > 1) ? ft_move_le_ri(0, var, len) : (0);
		(DROITE && len > 1) ? ft_move_le_ri(1, var, len) : (0);
		(BAS && len > 1) ? ft_move_down(var, len) : (0);
		(HAUT && len > 1) ? ft_move_up(var, len) : (0);
		(TAB && len > 1) ? var->comp->i++ : (0);
	}
	return ("erreur");
}

char	*ft_tab_estula(t_var *var, char **line)
{
	struct winsize	ws;
	char			*ret;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	tputs(tgoto(tgetstr("dl", NULL), 0, 0), 0, ft_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	ft_prompt(var);
	ret = replace_glob(*line, var);
	ft_putstr(ret);
	var->index = ft_strlen(ret);
	var->multiline = (ft_strlen(ret) + ft_prompt_len(var)) / ws.ws_col;
	return (ret);
}

char	*tabulation(char *line, t_var *var)
{
	char			buf[BSIZE];
	struct winsize	ws;
	int				backup;
	char			*ret;

	ft_bzero(buf, BSIZE);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	if ((backup = var->index) > -2 && estula(line) == 1)
		return (ft_tab_estula(var, &line));
	(!line[0]) ? tputs(tgetstr("bl", NULL), 0, ft_outc) : (0);
	if (!line[0])
		return (line);
	ft_initial_tab(line, var, &ws);
	if (!var->comp->array || !var->comp->array[0])
		return (ft_no_tab(line, var));
	if (count_line_tab(var->comp->array) >= 1)
		return (ft_tab_to_small(var));
	line = check_and_clean(line, var);
	(var->comp->len != 1) ? print_first_line(line, var) : (0);
	if (var->comp->len == 1)
		return (ft_one_result(line, var, buf));
	ft_place_for_tab(line, var);
	ret = loop_tab(buf, line, var);
	ft_free_comp(var);
	return (ret);
}
