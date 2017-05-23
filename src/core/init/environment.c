/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:23:35 by ggane             #+#    #+#             */
/*   Updated: 2017/04/27 00:20:01 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_lvl_shell(char *str)
{
	char	*nb;

	nb = ft_itoa(ft_atoi(&(str[6])) + 1);
	free(str);
	str = ft_strjoin("SHLVL=", nb);
	free(nb);
	return (str);
}

char	**ft_copy_tab(char **from)
{
	char	**dest;
	int		len;

	len = 0;
	while (from[len])
		len++;
	dest = (char **)malloc(sizeof(char *) * len + 1);
	len = 0;
	while (from[len])
	{
		dest[len] = ft_strdup(from[len]);
		if (!ft_strncmp(from[len], "SHLVL=", 6))
			dest[len] = ft_lvl_shell(dest[len]);
		len++;
	}
	dest[len] = NULL;
	return (dest);
}

char	*ft_search_env(char *to_find, char **env)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(to_find);
	while (env[i])
	{
		if (!ft_strncmp(to_find, env[i], len) && env[i][len] == '=')
		{
			str = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	if (!env[i])
	{
		str = (char *)malloc(sizeof(char) * (len + 2));
		str = ft_memcpy(str, to_find, len);
		str[len] = '=';
		str[len + 1] = '\0';
	}
	return (str);
}

t_var	*ft_init_env(char **basic)
{
	t_var	*var;

	open_fd();
	var = (t_var *)malloc(sizeof(t_var));
	if (basic && *basic != NULL)
		var->env = ft_copy_tab(basic);
	else
		var->env = ft_no_env();
	var->echo = NULL;
	var->multiline = 0;
	var->opt_quo = 0;
	var->linefile = NULL;
	return (var);
}

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		miniprintf(STDOUT_FILENO, "%s\n", env[i]);
		i++;
	}
}
