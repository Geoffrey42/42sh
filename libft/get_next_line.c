/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:57 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 15:41:38 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_special_malloc(char *s1, char *s2, int i, int j)
{
	char	*tmp;
	int		len;
	char	*t;

	t = s1;
	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(tmp = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s1[j])
		tmp[i++] = s1[j++];
	j = 0;
	while (s2[j])
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	free(t);
	return (tmp);
}

int		ft_check(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_stock_in_static(char **line, char *src, int i)
{
	char	*tmp;

	*line = ft_strdup(src);
	tmp = ft_strdup(src);
	while (*src)
	{
		if (*src == '\n' || *(src + 1) == '\0')
		{
			if (*src != '\n' && *(src + 1) == '\0')
				line[0][i++] = *src;
			line[0][i] = '\0';
			i = 0;
			src++;
			while (*src)
				tmp[i++] = *src++;
			tmp[i] = '\0';
			return (tmp);
		}
		line[0][i++] = *src++;
	}
	return (tmp);
}

char	*ft_end(char **line, char *mem[FD_SIZE], int fd)
{
	char	*t;

	t = mem[fd];
	mem[fd] = ft_stock_in_static(line, mem[fd], 0);
	free(t);
	return (mem[fd]);
}

int		get_next_line(int const fd, char **line)
{
	static char	*mem[FD_SIZE];
	char		*mem1;
	int			ret;

	if (line == NULL || fd < 0 || BUFF_SIZE < 1 || fd >= FD_SIZE)
		return (-1);
	while ((ft_check(mem[fd])) != 1)
	{
		if (!(mem1 = (char *)malloc(BUFF_SIZE + 1)))
			return (-1);
		if ((ret = read(fd, mem1, BUFF_SIZE)) == -1)
			return (-1);
		mem1[ret] = '\0';
		mem[fd] = ft_special_malloc(mem[fd], mem1, 0, 0);
		free(mem1);
		if (ret == 0 && (*mem[fd] == '\0' || !mem[fd]))
		{
			*line = NULL;
			return (0);
		}
		else if (ret == 0)
			break ;
	}
	mem[fd] = ft_end(line, mem, fd);
	return (1);
}
