/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:35:34 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:17:48 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	ft_printf_string(va_list pa, int fd)
{
	char	*s;

	s = va_arg(pa, char *);
	if (s == NULL)
	{
		ft_putstr_fd("NULL", fd);
		return (0);
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}

int	ft_printf_nb(va_list pa, int fd)
{
	int	i;
	int	len;

	len = 0;
	i = va_arg(pa, int);
	ft_putnbr_fd(i, fd);
	while (i)
	{
		i = i / 10;
		len++;
	}
	return (len);
}

int	miniprintf(int fd, char *str, ...)
{
	va_list	pa;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	va_start(pa, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == 's' && ++i)
			ret += ft_printf_string(pa, fd);
		else if (str[i] == '%' && str[i + 1] == 'd' && ++i)
			ret += ft_printf_nb(pa, fd);
		else if (str[i] == '%' && str[i + 1] == 'c' && ++i && ++ret)
			ft_putchar_fd(va_arg(pa, int), fd);
		else if (++ret)
			ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(pa);
	return (ret);
}
