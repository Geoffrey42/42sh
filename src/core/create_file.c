/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:03:31 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:07:27 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_create_file(char *s)
{
	int		i;
	int		len;
	char	*word;

	i = -1;
	if (s[0] == '$')
		return ;
	while (s[++i] != '\0')
	{
		if (s[i] == '>' && (ft_isalpha(s[i + 1]) || (s[i + 1] == ' ' &&
			ft_isalpha(s[i + 2]))))
		{
			while (s[i] == '>' || s[i] == ' ')
				i++;
			len = i + 1;
			while (s[len] != ' ' && s[len] != '\0')
				len++;
			word = ft_strsub(s, i, len - i);
			if (access(word, F_OK) == -1)
				open(word, O_WRONLY | O_CREAT, 0644);
			i = len;
			free(word);
		}
	}
}
