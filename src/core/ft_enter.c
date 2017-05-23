/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:17:36 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:10:26 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_add_space(char **s, int i)
{
	char	*new;
	int		j;

	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(*s) + 2));
	while (j <= i)
	{
		new[j] = (*s)[j];
		j++;
	}
	new[j++] = ' ';
	while ((*s)[++i])
	{
		new[j] = (*s)[i];
		j++;
	}
	new[j] = '\0';
	free(*s);
	*s = new;
}

int		ft_check_redir(char **s)
{
	int	i;
	int	j;

	i = 0;
	while ((*s)[i] == ' ')
		i++;
	if ((*s)[i] == '>' || (*s)[i] == '<' || (*s)[i] == '|' || (*s)[i] == '&')
		return (ft_return_check((*s)[i]));
	while ((*s)[i])
	{
		if ((*s)[i] == '(' || (*s)[i] == ')')
			return (ft_return_check((*s)[i]));
		if (((*s)[i] == '>' || (*s)[i] == '<') && (ft_is_redir(s, &i, &j) == F))
			return (F);
		else if ((*s)[i] == '|' || ((*s)[i] == '&' && (*s)[i - 1] != '>'
		&& (*s)[i - 1] != '<'))
		{
			if (ft_is_redir(s, &i, &j) == F)
				return (F);
		}
		i++;
	}
	return (V);
}

int		ft_verif_enter(t_var *var, int i)
{
	var->nodol = 0;
	var->cmd[i] = replace_d_point(var->cmd[i]);
	var->cmd[i] = replace_glob(var->cmd[i], var);
	var->cmd[i] = replace_dol(var->cmd[i], var);
	if (var->nodol == 1)
	{
		var->var_ret = F;
		return (F);
	}
	if (ft_check_redir(&(var->cmd[i])) == F)
	{
		var->var_ret = F;
		return (F);
	}
	var->logic = ft_split_logic(var->cmd[i]);
	if (!ft_strcmp(var->line, "$?"))
		miniprintf(STDOUT_FILENO, "%d\n", var->var_ret);
	ft_no_pipe(var);
	ft_free_logic(var);
	return (V);
}

int		ft_enter(char *line, t_var *var)
{
	int	i;

	i = -1;
	var->line = ft_strdup(line);
	(!var->line) ? ft_prompt(var) : (0);
	if (!var->line)
		return (0);
	miniprintf(STDOUT_FILENO, "\n");
	if (var->echo != NULL)
	{
		free(var->echo);
		var->echo = NULL;
	}
	if (ft_str_space(var->line) == 1 && ft_check_line(&(var->line)) > 0
	&& (ft_check_sep(var) > 0))
	{
		ft_split_cmd(var);
		while (var->cmd[++i])
			ft_verif_enter(var, i);
		ft_free_cmd(var);
	}
	free(var->line);
	var->index = 0;
	return (0);
}
