/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:46:16 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:32:34 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_quotes	*ft_init_quotes(void)
{
	t_quotes	*qu;

	qu = (t_quotes *)malloc(sizeof(t_quotes));
	qu->acc = 0;
	qu->par = 0;
	qu->bra = 0;
	qu->bac = 0;
	return (qu);
}

int			ft_quotes(char **s)
{
	int	begin;
	int	end;

	begin = 0;
	while ((*s)[begin] != '\0')
	{
		if ((*s)[begin] == '\"' || (*s)[begin] == '\'')
		{
			end = begin + 1;
			while ((*s)[end] != '\0' && (*s)[begin] != (*s)[end])
				end++;
			if (begin == end || (*s)[end] == '\0')
				return (0);
			while (begin <= end)
			{
				(*s)[begin] = '.';
				begin++;
			}
			begin = 0;
		}
		begin++;
	}
	return (1);
}

int			ft_no_quotes(char **s, char **cpy)
{
	while (!ft_quotes(cpy))
	{
		free(*cpy);
		*s = ft_loop_quotes(*s);
		if (*s == NULL)
		{
			miniprintf(STDOUT_FILENO, "\n");
			return (0);
		}
		*cpy = ft_strdup(*s);
	}
	return (1);
}
