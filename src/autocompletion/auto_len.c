/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:00:50 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:40:42 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		len_begin_last_line(char *line, t_var *var)
{
	int	len;

	len = (int)ft_strlen(line) + ft_prompt_len(var);
	while (len > var->col)
		len -= var->col;
	return (len);
}

int		len_last_line(char *line, t_var *var)
{
	int	len;

	len = (int)ft_strlen_tab(line) + ft_prompt_len(var);
	(var->comp->split) ? len += ft_strlen_tab(var->comp->end) : (0);
	while (len > var->col)
		len -= var->col;
	return (len);
}

int		len_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
