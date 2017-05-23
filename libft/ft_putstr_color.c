/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:03:06 by ggane             #+#    #+#             */
/*   Updated: 2017/02/02 00:47:45 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_color(char *color, char *text_back, char *text,
		char *text_suite)
{
	ft_putstr("\033[");
	ft_putstr(color);
	ft_putstr("m");
	ft_putstr(text_back);
	ft_putstr(text);
	ft_putstr(text_suite);
	ft_putstr("\033[0m");
}
