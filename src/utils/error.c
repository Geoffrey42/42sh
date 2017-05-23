/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:16:58 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_error(char *s)
{
	miniprintf(STDERR_FILENO, "%s : invalid. No arguments accepted.\n", s);
	return (0);
}

void	ft_error_malloc(void)
{
	miniprintf(STDERR_FILENO, "ERROR: out of memory! malloc() failed.\n");
	exit(1);
}
