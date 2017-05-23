/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_warning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:16:28 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:46:22 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_no_word(int col, t_var *var)
{
	var->nb_line++;
	tputs(tgetstr("do", NULL), 0, ft_outc);
	var->comp->nb_word = col / (max_len(var->comp->array) + 1);
}

char	*ft_tab_to_small(t_var *var)
{
	char	*ret;

	tputs(tgetstr("bl", NULL), 0, ft_outc);
	miniprintf(STDOUT_FILENO, PURPLE"\n42sh: Window too small for print\n"
	"Try with more letters\n"FIN);
	ft_prompt(var);
	ft_free_comp(var);
	ret = ft_strdup("\0");
	var->index = 0;
	return (ret);
}

char	*ft_no_tab(char *line, t_var *var)
{
	tputs(tgetstr("bl", NULL), 0, ft_outc);
	free(var->comp->new);
	ft_free_comp(var);
	return (line);
}
