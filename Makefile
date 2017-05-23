# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggane <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/21 11:27:27 by ggane             #+#    #+#              #
#    Updated: 2017/04/27 03:00:52 by lprunier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC =	tilde.c\

CORE =	create_file.c\
		ft_enter.c\
		ft_enter_bis.c\
		loop.c\
		executable.c\
		find_exec.c\
		path.c\
		main.c\

INIT =	environment.c\
		environment_2.c\
		init_term.c\

PIPE =	gift_pipe.c\
		gift_pipe_one.c\
		gift_pipe_two.c\
		gift_pipe_der.c\
		where_redir.c\
		all_redir.c\

SHELLREDIR =	search_redir.c\
				shell_multi_cmd.c\
				shell_redir.c\
				shell_redir_in.c\
				shell_redir_nopipe.c\
				shell_redir_nopipe_bis.c\
				shell_redir_out.c\
				shell_redir_split.c\
				shell_redir_tools.c\
				no_pipe.c\
				no_pipe_bis.c\
				aggregateur.c\
				heredoc.c\
				hdc.c\
				heredoc_bis.c\

SIGNAUX =	signaux.c\
			signaux_parents.c\
			signaux_parents_bis.c\

UTILS =	lst_to_tab.c\
		join.c\
		split.c\
		split_logic.c\
		split_pipe.c\
		split_pv.c\
		split_pv_bis.c\
		split_quote.c\
		strjoin_char.c\
		miniprintf.c\
		ft_str_space.c\
		ft_outc.c\
		len_space.c\
		tab_to_str.c\
		free.c\
		error.c\

EDITLINE=	term.c\
			print_line.c\
			insert.c\
			supp_del.c\
			copy.c\
			mouve.c\
			paste.c\
			prompt.c\

LINEINTEGRITY =	check.c\
				check_sep.c\
				check_brace.c\
				check_quotes.c\

GLOB =	acollade.c\
		add_double_char.c\
		add_lst.c\
		cmp.c\
		cmp_bis.c\
		complete_glob.c\
		globbing.c\
		globbing_bis.c\
		make_bracket.c\
		parsing.c\
		quit.c\
		split_targuet.c\
		tools.c\

BULT =	builtins.c\
		is_builtins.c\
		cd.c\
		cd_replace.c\
		echo.c\
		env.c\
		env_2.c\
		env_copy.c\
		exit.c\
		ft_strsplit_spe.c\
		lst_env.c\
		lst_env_2.c\
		verif_opt.c\
		setenv.c\
		unsetenv.c\
		export.c\
		history.c\

AUTOCOM	=	auto_completion.c\
			auto_completion_bis.c\
			autocompletion_tool.c\
			auto_mouve.c\
			auto_split.c\
			auto_print.c\
			auto_print_results.c\
			auto_tab.c\
			auto_init.c\
			auto_len.c\
			auto_lst.c\
			auto_ret.c\
			auto_ret_supp.c\
			auto_clean.c\
			auto_warning.c\
			auto_placecursor.c\

REPLACE =	replace_point.c\
			find_point.c\
			concact.c\
			dollar.c\
			glob.c\
			list_point.c\
			del_quotes.c\
			kill_quotes.c\
			loop_quotes.c

INCLUDE = -I include/

FLAG = -Wall -Werror -Wextra

LIBRARIES = -L libft/  -lft  -ltermcap

CGLOB = $(addprefix src/globing/, $(GLOB))
CFILES = $(addprefix src/, $(SRC))
CBULT = $(addprefix src/builtins/, $(BULT))
CAUTOCOM = $(addprefix src/autocompletion/, $(AUTOCOM))
CPIPE = $(addprefix src/shell_redir/pipe/, $(PIPE))
CSHELLREDIR = $(addprefix src/shell_redir/, $(SHELLREDIR))
CSIGNAUX = $(addprefix src/signaux/, $(SIGNAUX))
CUTILS = $(addprefix src/utils/, $(UTILS))
CEDITLINE = $(addprefix src/edit_line/, $(EDITLINE))
CLINEINTEGRITY = $(addprefix src/line_integrity/, $(LINEINTEGRITY))
CREPLACE = $(addprefix src/replace/, $(REPLACE))
CCORE = $(addprefix src/core/, $(CORE))
CINIT = $(addprefix src/core/init/, $(INIT))

OBJ = $(SRC:.c=.o)
OBJ1 = $(GLOB:.c=.o)
OBJ2 = $(BULT:.c=.o)
OBJ3 = $(AUTOCOM:.c=.o)
OBJ4 = $(SHELLREDIR:.c=.o)
OBJ5 = $(SIGNAUX:.c=.o)
OBJ6 = $(UTILS:.c=.o)
OBJ7 = $(EDITLINE:.c=.o)
OBJ8 = $(LINEINTEGRITY:.c=.o)
OBJ9 = $(REPLACE:.c=.o)
OBJ10 = $(CORE:.c=.o)
OBJ11 = $(PIPE:.c=.o)
OBJ12 = $(INIT:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c $(FLAG) $(INCLUDE) $(CFILES) $(CGLOB) $(CBULT) $(CAUTOCOM) $(CSHELLREDIR) $(CSIGNAUX) $(CUTILS) $(CEDITLINE) $(CLINEINTEGRITY) $(CREPLACE) $(CCORE) $(CPIPE) $(CINIT)
	@make -C libft/ fclean && make -C libft && make -C libft/ clean
	@gcc -o $(NAME) $(LIBRARIES) $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8) $(OBJ9) $(OBJ10) $(OBJ11) $(OBJ12)
	@mkdir obj && mv $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8) $(OBJ9) $(OBJ10) $(OBJ11) $(OBJ12) obj/

clean:
	@/bin/rm -rf obj
	@/bin/rm -rf $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8) $(OBJ9) $(OBJ10) $(OBJ11) $(OBJ12)

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all
