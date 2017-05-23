/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:19:02 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:24:44 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	open_directory(DIR **mydir, char **str, char **save)
{
	int		i;

	i = 0;
	*mydir = NULL;
	if ((ft_strchr(*str, '/') == NULL) && (*save = ft_strdup(".")) != NULL)
	{
		if ((*mydir = opendir("./")) == NULL)
			return (free_and_quit(*save));
	}
	else
	{
		*save = ft_strdup(*str);
		while (save[0][i])
			i++;
		while (save[0][i] != '/')
			i--;
		if (i == 0)
			*mydir = opendir("/");
		save[0][i] = '\0';
		if ((*mydir == NULL) && ((*mydir = opendir(*save)) == NULL))
			return (free_and_quit(*save));
		free(*str);
		*str = ft_strdup(&(save[0][i + 1]));
	}
	return (1);
}

static void	recollage(char **splitted, char *save)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	if (ft_strcmp(save, ".") != 0)
	{
		while (splitted[i] != NULL)
		{
			temp = ft_strjoin(save, "/");
			temp2 = ft_strjoin(temp, splitted[i]);
			free(splitted[i]);
			free(temp);
			splitted[i] = ft_strdup(temp2);
			free(temp2);
			i++;
		}
	}
	free(save);
}

char		*ft_tab_space(char *old)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	j = 0;
	while (old[++i] != '\0')
		(old[i] == '	' && old[i - 1] == '\\') ? j++ : (0);
	s = (char *)malloc(sizeof(char) * (ft_strlen(old) - j + 1));
	i = 0;
	j = 0;
	while (old[i] != '\0')
	{
		(old[i] == '\\') ? i++ : (0);
		if (old[i] == '	')
			s[j] = ' ';
		else
			s[j] = old[i];
		j++;
		i++;
	}
	s[j] = '\0';
	if (ft_strlen(old) > 0)
		free(old);
	return (s);
}

void		ft_free_lst_glob(t_list_glob *lst)
{
	t_list_glob	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->name);
		free(tmp);
	}
}

char		**globing(char *old)
{
	t_dir_ext	direc;
	t_list_glob	*lst;
	char		**splitted;
	char		*str;
	int			i;

	str = ft_tab_space(old);
	kill_star_in_brackets(&str);
	lst = NULL;
	if (open_directory(&(direc.dir), &str, &(direc.save)) == 0)
		return (free_and_quit_null(str));
	splitted = split_accolades(str);
	while ((direc.lecture = readdir(direc.dir)) != NULL)
		globbing_loop(direc, &lst, splitted);
	closedir(direc.dir);
	free_double_char(splitted);
	splitted = conversion(&lst);
	ft_free_lst_glob(lst);
	recollage(splitted, direc.save);
	i = -1;
	while (splitted[++i])
		splitted[i] = ft_strdup_spaces(splitted[i]);
	free(str);
	return (splitted);
}
