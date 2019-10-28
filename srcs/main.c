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

void	set_noncanonical(void)
{
	g_term.orig_attr = g_term.new_attr;
	(g_term.new_attr).c_lflag &= ~(ICANON | ECHO);
	(g_term.new_attr).c_cflag &= ~(CREAD);
	(g_term.new_attr).c_cc[VMIN] = 0;
	(g_term.new_attr).c_cc[VTIME] = 0;
	if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &(g_term.new_attr)) == -1)
		exit_suc("Can't set noncanonical mode!");
	ft_printf("%s", tgetstr("te", NULL));
}

void	unset_noncanonical(void)
{
	ft_printf("%s", tgetstr("ti", NULL));
	if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &(g_term.orig_attr)) == -1)
		exit_suc("Can't unset noncanonical mode!");
}

void	get_term_info(void)
{
	char buffer[1024];

	if (!(g_term.t_name = getenv("TERM")))
		exit_suc("Terminal type not found! Set type with: seotenv TERM [type]");
	if ((g_term.t_desc = tgetent(buffer, g_term.t_name)) == -1)
		exit_suc("Terminfo database not found!!");
	if (g_term.t_desc < 0)
		exit_suc("Could not access the termcap database!!");
	if (tcgetattr(STDERR_FILENO, &(g_term.new_attr)) == -1)
		exit_suc("Could not get Terminal attributes");
	g_term.col_num = tgetnum("co");
	g_term.line_num = tgetnum("li");
	g_term.clean_screen = tgetstr("cl", NULL);
	g_term.cursor = tgetstr("cm", NULL);
}

void	managesignals(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSTOP, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGQUIT, sig_handler);
}

int		main(int argc, char **argv)
{
	t_input	*input;

	input = NULL;
	if (argc < 2 || argv[1] == NULL)
		exit_suc("USAGE: ft_select argument 1 [argument 2] [argument ...]");
	else
	{
		g_term.print = 1;
		g_term.close = 0;
		g_term.hold = 0;
		get_term_info();
		set_noncanonical();
		input = sparser(argv, input);
		g_term.c_h = 2;
		g_term.c_w = 0;
		managesignals();
		sprint(input, g_term.col_num);
		tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
		input = s_moving(input);
		sclean_close(input);
	}
}
