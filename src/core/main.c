/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by ggane             #+#    #+#             */
/*   Updated: 2017/04/26 23:15:16 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	main(int ac, char **av, char **env)
{
	t_var	*var;
	int		ret;

	if (ac >= 2)
		return (ft_error(av[1]));
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	var = ft_init_env(env);
	var->copy = ft_strdup("\0");
	ft_loop(var);
	ret = var->var_ret;
	ft_free_struct(var);
	return (ret);
}
