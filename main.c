/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:10:13 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/19 16:10:17 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

void	set_noncanonical()
{
	g_term.orig_attr = g_term.new_attr;
	(g_term.new_attr).c_lflag &= ~(ICANON | ECHO);
	(g_term.new_attr).c_cflag &= ~(CREAD);
	(g_term.new_attr).c_cc[VMIN] = 0;
	(g_term.new_attr).c_cc[VTIME] = 0;
	if (tcsetattr(g_term.t_desc, TCSAFLUSH, &(g_term.new_attr)) == -1)
		exit_suc("Can't set noncanonical mode!");
}

void	unset_noncanonical()
{
	ft_printf("%s", g_term.clean_screen);
	if (tcsetattr(g_term.t_desc, TCSAFLUSH, &(g_term.orig_attr)) == -1)
		exit_suc("Can't unset noncanonical mode!");
}

void	get_term_info()
{
	char buffer[1024];
	char *tmp;

	if (!(g_term.t_name = getenv("TERM")))
		exit_suc("Terminal type not found! Set type with: seotenv TERM [type]");
	g_term.t_desc = tgetent(buffer, g_term.t_name);
	if (g_term.t_desc < 0)
		exit_suc("Could not access the termcap database!!");
	if (tcgetattr(g_term.t_desc, &(g_term.new_attr)) == -1)
		exit_suc("Could not get Terminal attributes");
	g_term.col_num = tgetnum("co");
	g_term.line_num = tgetnum("li");
	g_term.buffer = ft_strnew(1024);
	g_term.clean_screen = tgetstr("cl", &(g_term.buffer));
	g_term.cursor = tgetstr("cm", &(g_term.buffer));
	g_term.c_up = tgetstr("up", &(g_term.buffer));
	g_term.c_down = tgetstr("do", &(g_term.buffer));
	g_term.autowrap = tgetflag("am");
	tmp = tgetstr("pc", &(g_term.buffer));
	g_term.pc = tmp ? *tmp : 0;
	g_term.bc = tgetstr("le", &(g_term.buffer));
}

void	managesignals()
{
	if (signal(SIGWINCH, sig_handler) == SIG_ERR)
	{
		ft_printf("%s", g_term.clean_screen);
		ft_printf("%R%s%E\n", strerror(errno));
	}

	//signal(SIGINT, sig_handlr(SIGINT));
}

int		main (int argc, char **argv)
{
	t_input	*input;

	input = NULL;
	if (argc < 2 || argv[1] == NULL)
		exit_suc("USAGE: ft_select argument 1 [argument 2] [argument ...]");
	else
	{
		get_term_info();
		set_noncanonical();
		input = sparser(argv, input);
		g_term.cursor_h = 2;
		g_term.cursor_w = 0;
		managesignals();
		sprint(input, g_term.col_num);
		tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
		s_moving(input);
		unset_noncanonical();
	}
}