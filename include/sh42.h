/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:11:48 by ggane             #+#    #+#             */
/*   Updated: 2017/04/26 23:27:00 by lprunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H
# include "libft.h"
# include "globbing.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <term.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdarg.h>
# include <stdint.h>
# define RET "\e[1;37;41m"
# define STR "\e[8;30;42m"
# define BUFF_SIZE 1
# define FD_SIZE 10
# define ENTER ((buf[0] == 10 && buf[1] == 0 )|| (buf[0] == 13 && buf[1] == 0))
# define SPACE (buf[0] == 32 && buf[1] == 0)
# define SUPP (buf[0] == 127 && buf[1] == 0)
# define DEL (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
# define HOME (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
# define END (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
# define UP (buf[0] == 27 && buf[1] == 91 && buf[2] == 53 && buf[3] == 126)
# define DOWN (buf[0] == 27 && buf[1] == 91 && buf[2] == 54 && buf[3] == 126)
# define HAUT (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
# define BAS (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
# define GAUCHE (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
# define DROITE (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
# define CL (buf[0] == 12 && buf[1] == 0)
# define CD (buf[0] == 4 && buf[1] == 0)
# define TAB (buf[0] == 9 && buf[1] == 0)
# define MULTIUP (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 65)
# define MULTIDO (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 66)
# define COPY (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 68)
# define PASTE (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 67)
# define ONE (buf[2] == 90 || buf[2] == 49)
# define TWO (buf[0] == 27 && buf[1] == 91)
# define THR (buf[3] == 59 && buf[4] == 50)
# define FOU (buf[5] == 67 || buf[5] == 68 || buf[5] == 65 || buf[5] == 66)
# define FIV (buf[0] == 8 || buf[0] == 11 || buf[0] == 27)
# define BAD (TWO && (ONE && THR && FOU) || (FIV && buf[1] == 0) || buf[0] < 0)
# define CTRLR (buf[0] == 18 && buf[1] == 0)
# define BSIZE 1000
# define YES (buf[0] == 121)
# define NO (buf[0] == 110)
# define V 0
# define F 1
# define CMP(X) (!ft_strcmp(s, X))
# define SETSIG (0)
# define GETSIG (1)
# define SIGINT_IGNORE (0)
# define SIGINT_REGULAR (1)
# define SIGNALS_CHILD (65)

typedef struct		s_signal_ptr
{
	int				signal;
	char			*err;
}					t_signal_ptr;

typedef struct		s_exec
{
	char			*clef;
	char			*path;
	char			*exec;
	struct s_exec	*next;
}					t_exec;

typedef struct		s_lenv
{
	char			*bef;
	char			*aft;
	char			c;
	struct s_lenv	*next;
}					t_lenv;

typedef struct		s_point
{
	char			*s;
	struct s_point	*next;
}					t_point;

typedef struct		s_sep
{
	int				pv;
	int				et;
	int				ou;
	int				pip;
	int				in;
	int				out;
}					t_sep;

typedef struct		s_comp
{
	int				space;
	int				nb_word;
	char			**array;
	char			buf[BSIZE];
	int				i;
	int				ligne;
	char			*new;
	char			*end;
	char			*begin;
	int				col;
	int				j;
	int				split;
	int				res;
	int				prec;
	int				len;
}					t_comp;

typedef struct		s_hist
{
	char			*s;
	int				end;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_var
{
	int				file;
	char			**linefile;
	char			*otion;
	char			**env;
	char			*home;
	char			*name;
	char			*addr;
	int				index;
	char			*line;
	int				nb_line;
	int				col;
	int				multiline;
	char			*copy;
	char			**cmd;
	char			**logic;
	struct s_comp	*comp;
	struct s_lenv	*lenv;
	struct s_exec	*exec;
	struct s_sep	*sep;
	char			*echo;
	int				opt_quo;
	int				var_ret;
	char			**redir;
	int				aggreg;
	char			**command;
	char			**pipe;
	int				ifpipe;
	int				count_redir;
	int				i;
	int				fd_out;
	int				fd_in;
	int				fd_err;
	int				out;
	int				in;
	int				err;
	int				red;
	int				ctl_c;
	int				acces;
	char			*tmp;
	char			*key;
	int				cd;
	int				from;
	int				to;
	int				old_stderr;
	int				oui;
	int				nodol;
	int				her;
	int				hdc;
	int				truc;
	char			*filename;
	int				numredir;
	char			*hdc_result;
	int				repeat;
	int				error_hdc;
	char			*pipe_out;
	char			*pipe_end;
	char			**pipe_in;
	int				test;
	struct termios	termios;
	struct s_hist	*h;
}					t_var;

typedef struct		s_built
{
	char			*name;
	char			first;
	char			error;
	char			cd_racine;
	int				noarg;
	char			**arg;
}					t_built;

typedef struct		s_quotes
{
	int				acc;
	int				par;
	int				bra;
	int				bac;
}					t_quotes;

/*
**	get_next_line.c
*/
int					get_next_line(int const fd, char **line);
/*
**	read_file.c
*/
void				read_file(t_var *var, char *file);
/*
**	tilde.c
*/
void				loop_tilde(t_var *term, char ***tebl, int i);
void				tilde(t_var *term, char ***tabl);

/*
*******************************************************************************
************************* autocompletion ** ***********************************
*******************************************************************************
*/

/*
** auto_mouve.c
*/
void				ft_move_up(t_var *var, int len);
void				ft_move_down(t_var *var, int len);
void				ft_move_le_ri(int opt, t_var *var, int len);
char				*ft_enter_tab(t_var *var, char *line);

/*
** auto_split.c
*/
void				split_line(char *line, t_var *var);
void				split_to_line(char *line, t_var *var);
void				ft_loop_split(t_var *var);

/*
** auto_print.c
*/
char				*ft_one_result(char *line, t_var *var, char buf[BSIZE]);
void				print_result(char *line, t_var *var);
void				print_tabulation(t_var *var, int video);
void				print_first_line(char *line, t_var *var);
void				print_tab(char *line, t_var *var, int i, int j);

/*
** auto_print_results.c
*/
void				print_result(char *line, t_var *var);

/*
** auto_tab.c
*/
int					count_tab(char **array);
int					count_line_tab(char **array);
void				ft_space_to_tab(char *s);
void				ft_tab_to_space(char *s);

/*
** auto_init.c
*/
void				ft_initial_tab(char *line, t_var *var, struct winsize *ws);
void				init_tab(char *line, t_var *var);
void				ft_init_tabulation(t_var *var, int *i, int col);

/*
** auto_len.c
*/
int					len_begin_last_line(char *line, t_var *var);
int					len_last_line(char *line, t_var *var);
int					len_array(char **array);

/*
** auto_lst.c
*/
char				*lst_to_str(char *line, t_var *var);
void				ft_line_in_lst(t_var *var, char **new_line, char *clef);

/*
** auto_ret.c
*/
char				*ret_del_supp(char *line, t_var *var);
char				*ret_single_line(char *line, t_var *var);
char				*ret_join_split(char *line, t_var *var);

/*
** auto_ret_supp.c
*/
char				*ret_del_supp(char *line, t_var *var);

/*
** auto_clean.c
*/
void				ft_free_comp(t_var *var);
void				clean_enter(t_var *var);
char				*check_and_clean(char *line, t_var *var);

/*
** auto_warning.c
*/
char				*ft_no_tab(char *line, t_var *var);
char				*ft_tab_to_small(t_var *var);
void				ft_no_word(int col, t_var *var);

/*
** auto_placecursor.c
*/
void				ft_place_for_tab(char *line, t_var *var);
void				place_cursor(t_var *var);

/*
** auto_completion.c
*/
void				ft_dir_or_usr(int opt, t_var *var, int i, int video);
void				ft_lnk_or_else(int opt, t_var *var, int i, int video);
int					find_dollar(char *line);
char				*loop_tab(char *buf, char *line, t_var *var);
char				*tabulation(char *line, t_var *var);

/*
** auto_completion_bis.c
*/
char				*ft_last_slash(char *s);
void				ft_dir_or_usr(int opt, t_var *var, int i, int video);

/*
**	autocompletion_tool.c
*/
int					ft_strlen_tab(char *s);
int					max_len(char **array);
char				*clean_addr(char *s);
char				*begin_clean(char *begin);
/*
******************************************************************
*/

/*
******************************************************************
************************* core ***********************************
******************************************************************
*/

/*
** Init------>	environment.c
**recuperation de l'environnement avant de passer en mode canonique,
**augmentation du shlvl et initialisation de variables
*/
char				*ft_lvl_shell(char *str);
char				**ft_copy_tab(char **from);
char				*ft_search_env(char *to_find, char **env);
t_var				*ft_init_env(char **basic);
void				ft_print_env(char **env);

/*
**Init ----> environment_2.c
*/
char				**ft_no_env(void);
void				open_fd(void);

/*
** Init ------> init_term.c\
*/
void				init_termios(t_var *var);
void				init_std(t_var *var);

/*
**	create_file.c
*/
void				ft_create_file(char *s);

/*
**	executable.c
*/
int					ft_execution(t_var *var, char **arg, int ret);
int					ft_exec(char **cmd, t_var *var);

/*
**	find_exec.c
**fonction permettant de retrouver si un "mot" est executable ou non
*/
char				*ft_search_lenv(t_lenv *lst, char *s);
int					ft_find_exec(char **s, t_var *var);

/*
** ft_enter.c\
*/
int					ft_verif_enter(t_var *var, int i);
int					ft_check_redir(char **s);
void				ft_add_space(char **s, int i);
int					ft_enter(char *line, t_var *var);

/*
** ft_enter_bis.c
*/
int					ft_return_check(char c);
int					ft_is_redir(char **s, int *i, int *j);
int					ft_is_sep(char **s, int *i, int *j);
void				ft_check_red(char **s, int *i, int *j);

/*
**	loop.c
**boucle infinie qui permettra a l'utilisateur de lancer des commandes a
**l'infini, il suffiera de lancer la commande exit pour sortir du programme
*/
void				ft_loop(t_var *var);

/*
** path.c
*/
void				ft_write_path(char *tmp, char **path, int i);
int					ft_path_finded(char **s, char *tmp);
int					ft_path_inacess(char *tmp, char **s);
/*
******************************************************************
*/

/*
******************************************************************
************************* line_integrity *************************
******************************************************************
*/
/*
**	check.c
**fonctions permettant de verifier si la ligne entree par l'utilisatuer est
**correcte et utilisable par le programme
*/
char				ft_end_of_par(char c);
int					ft_return_syntax(char c);
void				ft_check_par(char c, t_quotes *qu);
int					ft_return_brace(t_quotes *qu, char c);
int					ft_check_line(char **s);

/*
** check_brace.c
*/
int					ft_check_brace(char c, int *i, char **cpy, int begin);

/*
** check_quotes.c
*/
int					ft_quotes(char **s);
t_quotes			*ft_init_quotes(void);
int					ft_no_quotes(char **s, char **cpy);
/*
**	check_sep.c
*/
void				ft_init_sep(t_var *var);
int					ft_check_sep(t_var *var);
/*
******************************************************************
*/

/*
******************************************************************
************************* edit_line ******************************
******************************************************************
*/

/*
**	copy.c
**edition de ligne, fonctions de copie et collage d'une portion de ligne
*/
char				*ft_print_mr(char *line, int index, int i);
void				ft_copy(t_var *var, char **line);

/*
**	paste.c
*/
char				*ft_paste(t_var *var, char *line);

/*
** mouve.c
*/
void				ft_left(t_var *var);
void				ft_right(t_var *var);
void				ft_prev_word(t_var *var, char *line);
void				ft_next_word(t_var *var, char *line, int len);

/*
** insert.c
*/
char				*ft_insert_char(char *line, char buf[BSIZE], int *index);

/*
**	print_line.c
**fonctions d'insertions et deletions de char dans la ligne
*/
void				ft_print_line(t_var *var, char **line, char buf[BSIZE]);

/*
**	prompt.c
*/
char				*ft_find_addr(t_lenv *lst);
char				*ft_find_name(t_lenv *lst);
void				ft_prompt(t_var *var);
int					ft_prompt_len(t_var *var);

/*
** supp_del.c
*/
char				*ft_supp_char(char *line, int *index);
char				*ft_del_char(char *line, int *index);

/*
**	term.c
**fonctions de deplacements du prompt (mots suivants/precedents,
**debut/fin de ligne, haut/bas, etc...)
*/
void				ft_rapids_terms(t_var *var, char buf[BSIZE], int len);
void				ft_multimove(t_var *var, char buf[BSIZE], char *line);
char				*ft_termcaps(t_var *var, char *line, char buf[BSIZE]);

/*
********************** replace ***********************************
*/

/*
** concat.c
*/
void				ft_concat(t_point *p);
void				ft_concat_nbr(t_point *p);

/*
**	del_quotes.c
*/
char				*ft_change_quotes(char *s);
void				ft_del_quotes(char ***arg);

/*
** dollar.c
*/
char				*replace_dol_find(char *value, t_var *var);
char				*replace_dol(char *line, t_var *var);

/*
** find_point.c
*/
int					ft_find_point(char *s);
int					ft_find_nbr(char *s, int i);

/*
** glob.c
*/
int					estula(char *s);
char				*replace_glob(char *line, t_var *var);

/*
**	kill_quotes.c
*/
char				*ft_change(char *s, int i, int j);
void				ft_kill_quotes(char ***arg);

/*
**	loop_quotes.c
*/
char				*ft_loop_quotes(char *s);

/*
**	list_point.c
*/
void				ft_add_end(t_point *p, char *s);

/*
**	replace_point.c
*/
void				ft_sep_point(t_point *p);
int					find_number(char *line);
char				*replace_d_point(char *line);

/*
********************** shell_redir *******************************
*/

/*
**	PIPE ----->  gift_pipe.c
*/
void				ft_pid_null(t_var *var, char ***cmd, int *fd_in, int p[2]);
void				ft_pid_positif(t_var *var,
						int p[2], int *fd_in, char ****cmd);
void				ft_init_loopipe(int *j, int *status, int *fd_in);
int					loop_pipe2(char	***cmd, t_var *var);
int					gift_pipe(t_var *term);

/*
** gift_pipe_one.c
*/
void				ft_loop_redir_spe(t_var *var, char ***cmd, int *i);
void				ft_aggreg_close(t_var *var, int *fd);
void				ft_init_loop_red(t_var *var);
void				ft_free_next_cmd(char ***cmd, int i);
int					is_file(char **s, char **cmd);

/*
** gift_pipe_two.c
*/
void				ft_heredoc_pipe(t_var *var, int p[2]);
void				ft_pid_rep(t_var *var, int p[2]);
void				ft_pid_repeat(t_var *var, int file, int p[2]);
void				ft_loop_red(t_var *var, int j, char ***cmd);
void				ft_free_loop_cmd(char ***cmd, int *i);

/*
** gift_pipe_der.c
*/
void				ft_free_loop_cmd(char ***cmd, int *i);
void				ft_hdc_pipe(t_var *var, int p[2]);

/*
**	where_redir.c
*/
void				ft_free_where(t_var *var, int *i, int *to, int *in);
void				ft_alloc_in(t_var *var, int in, int to, char *s);
void				ft_alloc_out(t_var *var, int *i, int *j, char *s);
void				ft_where_redir(t_var *var, char *s);
void				ft_redir_in_out(t_var *var, char ***cmd, int *i, char *tmp);

/*
**	all_redir.c
*/
void				ft_redir_in_pipe(t_var *var, int *i, int p[2], char ***cmd);
void				ft_rediroutpipe(t_var *var, char ***cmd);
void				ft_pipehdc(t_var *var, char ***cmd);
void				ft_choose_redir_pipe(t_var *var, char ***cmd, int p[2]);

/*
**	aggregateur.c
*/
void				ft_return_aggreg(int *i);
void				ft_aggreg(char *s, int *aggreg, t_var *term);

/*
**	hdc.c
*/
int					ft_multiple_opt(char **text, t_var *term, int *j);
void				ft_hdc_out(t_var *term, int fd_tab[2], char *text);

/*
** heredoc.c
*/
int					heredoc(t_var *term, int *j);
void				ft_pid_null_hdc(t_var *term, int fd_tab[2], char *text);
void				ft_hdc_read(t_var *term, int fd_tab[2]);
void				ft_err_direct(int opt, DIR *rep, char *s);
void				ft_fd_neg(t_var *term, int fd);

/*
** heredoc_bis.c
*/
void				ft_init_heredoc(t_var *term);
char				*loop_init_heredoc(t_var *term, int *j);
int					loop_heredoc(t_var *term, char **tmp, char *key);
char				*loop_loop_heredoc(t_var *term);
void				ft_verif_buf(char buf[BSIZE],
						char **ret, int *index, t_var *term);

/*
**	no_pipe.c
*/
int					ft_no_pipe(t_var *var);
void				ft_redir_ret(t_var *var, int *res, int i);

/*
** no_pipe_bis.c
*/
void				ft_no_red(t_var *var, int *res);
/*
**	search_redir.c
*/
void				ft_print_str_endl(int nb, ...);
char				*ft_free(char *str);
void				ft_init_redir(t_var *var, char *s);
int					ft_search_redir(char *s);
int					ft_if_pipe(char *s);

/*
**	shell_multi_cmd.c
*/
int					message_err_redir(char *str, t_var *term);
int					search_redir(t_var *term, int i);

/*
**	shell_redir.c
*/
void				ft_count_tab(t_var *term, int index);
int					ft_valid(t_var *term, int i);
int					more_tall(int out, int in, int err);
void				redir_pipe(t_var *term, int i);

/*
**	shell_redir_in.c
*/
void				loop_init_redir_in(t_var *term, int *j);
void				fork_redir_in(t_var *term, int j);
void				open_file_in(char **tabl, int *fd, int i);
void				redir_in(t_var *term, int *j);

/*
**	shell_redir_nopipe.c
*/
char				**ft_free_tab(char **str);
int					ft_redir(t_var *term, int i, int j);

/*
** shell redir_nopipe_bis.c
*/
char				**ft_free_tab(char **str);

/*
**	shell_redir_out.c
*/
int					fd_dup(char *str);
void				fork_redir_out(t_var *term, int j);
void				loop_init_redir(t_var *term, int *j);
void				open_file_out(char **tabl, int *fd, int i, int flag);
void				redir_out(t_var *term, int *j);

/*
**	shell_redir_split.c
*/
void				suite_loop_redir(t_var *term, int *i, int *a, int *b);
void				condition_redir(t_var *term, int *i, int *a, int *b);
void				loop_redir(t_var *term, int index, int i);
int					loop_back_redir(t_var *term, int index, int i);
void				split_redir(t_var *term, int i);

/*
** tools.c
*/
void				condition_loop(t_var *term, int *a, int *b);

/*
********************** signaux ***********************************
*/
/*
**	signaux.c
*/
void				free_sig_handler(t_signal_ptr **sig_handler);
void				alloc_sig_handler(t_signal_ptr **sig_handler);
void				init_sig_handler(t_signal_ptr **sig_handler);
/*
**	signaux_parents.c
*/
void				signal_catcher(int catched_signal);
int					signal_handler(char mode, int sigint_behavior);

/*
** signaux_parents_bis.c
*/
int					parent_exec(pid_t pid, int *status, t_var *var);
void				signal_catcher_bis(int catched_signal);
int					signal_handler_bis(char mode, int sigint_behavior,
					int pid);
/*
********************** utils *************************************
*/

/*
**	error.c
*/
int					ft_error(char *s);
void				ft_error_malloc(void);

/*
**	free.c
*/
void				ft_free_struct(t_var *var);
void				ft_free_cmd(t_var *var);
void				ft_free_logic(t_var *var);

/*
** ft_str_space.c
*/
int					ft_str_space(char *s);

/*
** ft_outc.c
*/
int					ft_outc(int c);

/*
**	lst_to_tab.c
*/
void				ft_put_in_array(char **array, char *s1, char *s2);
char				**ft_lst_to_tab(t_lenv **lst);

/*
** len_space.c
*/
int					len_space(char *s);

/*
**	miniprintf.c
**un printf utilisable avec les option s,c et d
*/
int					ft_printf_string(va_list pa, int fd);
int					ft_printf_nb(va_list pa, int fd);
int					miniprintf(int fd, char *str, ...);

/*
** join.c\
*/
int					ft_join_error(int i, char **path, char **s,
					char *tmp);
int					ft_join_path(int i, char **path, char **s,
					char *tmp);

/*
**	split.c
*/
int					ft_next_sp(char *s, int begin);
char				**ft_strsplit_sp(char *s);

/*
**	split_logic.c
*/
int					ft_next_logic(char *s, int beg);
char				**ft_split_logic(char *s);

/*
**	split_pipe.c
*/
int					ft_next_pipe(char *s, int begin);
char				**ft_strsplit_pipe(char *s);
int					ft_search_pipe(t_var *var);

/*
**	split_pv.c
*/
char				*ft_supp_space(char *s);
int					ft_next_pv(char *s, int begin);
char				**ft_strsplit_pv(char *s);
void				ft_split_cmd(t_var *var);

/*
** split_pv_bis.c
*/
void				ft_init_supp(char **ret, char *s, int *i, int *j);

/*
**	split_quote.c
*/
void				loop_split_pipe(char const *s, char **str, int *j,
					int *index);
char				**split_qte(const char *s);

/*
**	strjoin_char.c
*/
char				*ft_strjoin_char(char *s1, char c, char *s2);
char				*ft_strjoin_int(char *s1, int c, char *s2);

/*
** tab_to_str.c
*/
char				*tab_to_str(char **array, char *line);
/*
********************************************************************
*/

/*
*******************************************************************************
***********************************BUILTINS************************************
*******************************************************************************
*/

/*
** builtins.c
*/
int					ft_is_builtin(char *s);
char				**ft_cpy_tab_i(char **s, int beg);
t_built				*ft_init_built(char **s);
int					builtins(char **arg, t_var *var);

/*
** is_builtins.c
*/
int					ft_is_builtin(char *s);
char				**ft_cpy_tab_i(char **s, int beg);

/*
**	cd.c
*/
char				*ft_go_home(char *arg, t_var *var);
int					ft_go_cd(t_var *var, char *buf);
int					ft_cd(t_built *built, t_var *var);

/*
** cd_replace.c
*/
void				ft_no_pwd(char *buf, t_lenv **begin, char **old);
void				ft_no_oldpwd(char *old, t_lenv **begin);
void				ft_replace_old(t_var *var, char *old);
void				ft_replace_cd(t_var *var, char *s);

/*
**	echo.c
*/
char				*ft_tab_to_str(char **arg);
int					ft_echo(t_built *built, t_var *var);

/*
**	env.c
*/
void				ft_copy_env(t_var **var_cpy, t_var *var, t_built *built,
					int *i);
char				**ft_copy_var(t_built *built, t_var **var_cpy, t_var *var);
int					ft_print_environment(t_var *var, int i);
void				ft_init_var_logic(char **exec, t_var *var_cpy, int *i);
int					ft_env(t_built *built, t_var *var, int i);

/*
** env_copy.c
*/
char				**ft_copy_var(t_built *built, t_var **var_cpy,
					t_var *var);
void				ft_copy_env(t_var **var_cpy, t_var *var,
					t_built *built, int *i);

/*
** env_2.c
*/

void				ft_free_var_cpy(t_var *var);
t_lenv				*ft_copy_lst(t_lenv *lst, t_lenv *begin_lst);
void				ft_lst_env(t_lenv *lst, t_lenv *cpy);
int					ft_is_in(char *s, char c);
/*
**	exit.c
*/
void				ft_built_free(t_built *built);
int					ft_exit(t_built *built, t_var *var);

/*
**	export.c
*/
int					ft_export(t_built *built, t_var *var);

/*
**	history.c
*/
void				ft_add_history(char *s, t_hist **h);
int					ft_history(t_hist *h);
void				ft_history_move(char way, t_var *var, char **line);

/*
** lst_env.c
*/
void				ft_replace_spaces(char *str);
t_lenv				*ft_new_link(char *env, char c);
char				*check_bef(char *env);
int					bult_export(t_built *built);
char				*check_bef(char *env);
int					update_value(t_lenv **lenv, char *env, char c);

/*
** lst_env_2.c
*/
int					ft_insert_link(t_lenv **lst, char *env, char c,
					char *test);
void				ft_tab_to_lst(char **env, t_lenv **lst, char c);
void				ft_sort_insert(t_lenv **lst, char *env, char c);

/*
**	setenv.c
*/
int					ft_line_alphabetic(char *s);
int					ft_error_print(char *s);
int					ft_setenv(t_built *built, t_var *var);

/*
**	unsetenv.c
*/
int					ft_unsetenv(t_built *built, t_var *var);

/*
**	verif_opt.c
*/
int					ft_print_usage(char cmd, char opt);
int					ft_verif_opt(t_built *built);
/*
********************************************************************
*/
#endif
