/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:10:03 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 16:52:47 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_built		*ft_init_struct_built(char **s, int *i)
{
	t_built	*built;

	built = (t_built *)malloc(sizeof(t_built));
	built->name = ft_strdup(s[0]);
	built->first = 0;
	built->error = 0;
	built->cd_racine = 0;
	built->noarg = 0;
	*i = 0;
	return (built);
}

void		ft_init_opt(int *i, char **s, t_built *built)
{
	int	j;

	j = -1;
	while (s[++(*i)] && s[*i][0] == '-' && built->error == 0)
	{
		j = 0;
		if (s[*i][1] == '\0')
			break ;
		while (s[*i][++j])
			if (built->first == 0)
				built->first = s[*i][j];
			else if (built->first != 0 && built->first != s[*i][j])
				built->error = s[*i][j];
	}
}

t_built		*ft_init_built(char **s)
{
	t_built	*built;
	int		i;

	built = ft_init_struct_built(s, &i);
	if (ft_is_in(s[0], '='))
	{
		free(built->name);
		built->name = ft_strdup("export");
		i = -1;
	}
	if (!ft_strcmp(built->name, "echo") && (s[++i] && s[i][0] == '-' &&
	s[i][1] == 'n' && s[i][2] == '\0'))
	{
		built->first = 'n';
		i++;
	}
	else if (ft_strcmp(built->name, "echo"))
		ft_init_opt(&i, s, built);
	(s[i] == NULL) ? built->noarg = 1 : (0);
	(s[i] != NULL) ? built->arg = ft_cpy_tab_i(s, i) : (0);
	return (built);
}

int			ft_built_two(t_built *built, t_var *var)
{
	if (!ft_strcmp(built->name, "unsetenv"))
		return (ft_unsetenv(built, var));
	if (!ft_strcmp(built->name, "unset"))
		return (ft_unsetenv(built, var));
	if (!ft_strcmp(built->name, "history"))
	{
		ft_built_free(built);
		return (ft_history(var->h));
	}
	return (F);
}

int			builtins(char **arg, t_var *var)
{
	t_built *built;

	built = ft_init_built(arg);
	if (ft_verif_opt(built) == F)
	{
		ft_built_free(built);
		return (F);
	}
	if (built->noarg == 0 && ft_strcmp(built->name, "env"))
		ft_kill_quotes(&(built->arg));
	if (!ft_strcmp(built->name, "exit"))
		return (ft_exit(built, var));
	if (!ft_strcmp(built->name, "cd"))
		return (ft_cd(built, var));
	if (!ft_strcmp(built->name, "echo"))
		return (ft_echo(built, var));
	if (!ft_strcmp(built->name, "env"))
		return (ft_env(built, var, 0));
	if (!ft_strcmp(built->name, "setenv"))
		return (ft_setenv(built, var));
	if (!ft_strcmp(built->name, "export"))
		return (ft_export(built, var));
	return (ft_built_two(built, var));
}
