/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:34:13 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:25:33 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	globbing_loop(t_dir_ext direc, t_list_glob **lst, char **splitted)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (direc.lecture)->d_name;
	while (splitted[++i] != NULL)
	{
		if (meta_glob_cmp(splitted[i], tmp) == 1)
			add_lst(lst, tmp);
	}
	if (tmp != (direc.lecture)->d_name)
		ft_strdel(&tmp);
}

char	*ft_strdup_spaces(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	while (s[++i] != '\0')
		(s[i] == ' ' && s[i - 1] != '\\') ? j++ : (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + j + 1));
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == ' ' && s[i - 1] != '\\')
		{
			str[j] = '\\';
			str[++j] = '	';
		}
		(!(s[i] == ' ' && s[i - 1] != '\\')) ? str[j] = s[i] : (0);
		j++;
	}
	str[j] = '\0';
	if (ft_strlen(s) > 0)
		free(s);
	return (str);
}

char	**conversion(t_list_glob **lst)
{
	char		**ret;
	int			i;
	t_list_glob *temp;

	ret = (char**)malloc((size_list(*lst) + 1) * sizeof(char*));
	i = 0;
	while ((*lst) != NULL)
	{
		temp = *lst;
		ret[i] = ft_strdup_spaces((*lst)->name);
		*lst = (*lst)->next;
		free(temp);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
