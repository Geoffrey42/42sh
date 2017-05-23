/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:26:03 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 15:49:30 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include "libft.h"

# define SYNTAX "!$\\`;|&*?[]{}()'\"<>- \n\t"
# define GLOB "*?[]{}"
# define DIRECT "\033[1;36;40m"

typedef struct			s_list_glob
{
	char				*name;
	struct s_list_glob	*next;
	struct s_list_glob	*prec;
}						t_list_glob;

typedef struct			s_dir_ext
{
	DIR					*dir;
	struct dirent		*lecture;
	char				*save;
}						t_dir_ext;

/*
** globing pour l'autocompletion
*/
char					**ft_glob(char *str);

/*
** fonction tool glob_autocompletion
*/
int						detect_double(char *str);
void					recursion_recollage(char **files, char *str);
char					**destroy_empty(char **str);

/*
** glob_tab recursion
*/
char					**glob_recursion(char *str);

/*
** lauch
*/

char					**launch(char *str);
/*
** insert tab
*/
char					*ft_insert(char *str);
char					*ft_replace(char *str, char *to_delete, char *to_put);
char					**ft_explode(char const *s, char *delimiter);
char					*ft_implode(char **split, char *inter);

/*
** fonction ci-dessous pour le globing general !!!
*/

char					*complete_glob(char *str);
/*
** fonction similaire a la fonction glob(3) sans
** la gestion du regex.
*/
char					*ft_strdup_spaces(char *s);
char					*ft_tab_space(char *old);
char					**globing(char *str);

/*
** fichier utilitaire
*/
void					kill_star_in_brackets(char **str);
int						find(char *str);

/*
** gestion des sorties d erreiur
*/
int						free_and_quit(char *str);
char					**free_and_quit_null(char *str);

/*
** gestion des acolades
*/
char					**split_accolades(char *str);

/*
** parsin for find
*/
char					*parsing(char *str, int pos);

/*
** add_double_char to line
*/
void					free_double_char(char **str);
int						get_size_double_char(char **str);
char					**add_double_char(char **l1, char **l2);
/*
** make_braket.c
*/
char					*make_bracket(const char *s2, int y);

/*
** add to list
*/
int						size_list(t_list_glob *lst);
int						check_existence(t_list_glob *lst, char *str);
void					add_lst(t_list_glob **lst, char *name);
/*
**fonction de comparaison pour matching
*/
int						free_bracket(char *bracket);
int						glob_cmp(char *wild, char *str);
int						meta_glob_cmp(char *wild, char *str);

/*
** cmp_bis.c
*/
int						glob_strncmp(char *s1, char *s2, size_t n);
char					*glob_strstr(char *s1, char *s2);
int						glob_strlen(char *str);
int						init_strncmp(size_t *i, size_t *y, char *s1, char *s2);
/*
** fonction principale globbing
*/
void					globbing_loop(t_dir_ext direc, t_list_glob **lst,
						char **splitted);
char					**conversion(t_list_glob **lst);
char					**globing(char *str);

/*
** fonction pour split en fonction de la cible
*/
char					**split_targuet(char const *s, char *delimiter);

#endif
