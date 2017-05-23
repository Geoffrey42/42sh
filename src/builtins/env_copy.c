/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:01:22 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:55:33 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_copy_env(t_var **var_cpy, t_var *var, t_built *built, int *i)
{
	*i = -1;
	*var_cpy = (t_var *)malloc(sizeof(t_var));
	(*var_cpy)->copy = ft_strdup(var->copy);
	(*var_cpy)->opt_quo = var->opt_quo;
	(*var_cpy)->var_ret = var->var_ret;
	(*var_cpy)->addr = ft_strdup(var->addr);
	(*var_cpy)->name = ft_strdup(var->name);
	(*var_cpy)->env = NULL;
	(built->first == 0) ? (*var_cpy)->lenv = ft_copy_lst(var->lenv, NULL) : (0);
	(built->first == 'i') ? (*var_cpy)->lenv = NULL : (0);
}

char	**ft_copy_var(t_built *built, t_var **var_cpy, t_var *var)
{
	int		egal;
	char	**str;
	int		i;
	int		j;
	char	*tmp;

	egal = 0;
	j = -1;
	ft_copy_env(var_cpy, var, built, &i);
	str = (char **)malloc(sizeof(char *) * (ft_len_array(built->arg) + 1));
	while (built->arg[++i] && ft_is_in(built->arg[i], '=') == 1)
		str[++j] = ft_strdup(built->arg[i]);
	(built->arg[i] && built->arg[i + 1]) ? str[++j] = ft_strdup("\0") : (0);
	if (built->arg[i] && built->arg[i + 1])
		while (built->arg[i])
		{
			tmp = ft_strjoin(str[j], " ");
			free(str[j]);
			str[j] = ft_strjoin(tmp, built->arg[i++]);
			free(tmp);
		}
	else if (built->arg[i])
		str[++j] = built->arg[i++];
	str[++j] = NULL;
	return (str);
}
