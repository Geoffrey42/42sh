/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gift_pipe_der.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 06:31:21 by ggane             #+#    #+#             */
/*   Updated: 2017/04/25 01:35:16 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ft_free_loop_cmd(char ***cmd, int *i)
{
	while ((*cmd)[*i])
	{
		free((*cmd)[*i]);
		(*cmd)[*i] = NULL;
		(*i)++;
	}
}

void		ft_hdc_pipe(t_var *var, int p[2])
{
	int	file;

	write(p[1], var->hdc_result, ft_strlen(var->hdc_result));
	if (var->numredir == 1)
	{
		file = open(var->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(file, var->hdc_result, ft_strlen(var->hdc_result));
		free(var->filename);
		close(file);
	}
	if (var->numredir == 2)
	{
		file = open(var->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		write(file, var->hdc_result, ft_strlen(var->hdc_result));
		free(var->filename);
		close(file);
	}
	free(var->hdc_result);
}
