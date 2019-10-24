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

void	set_noncanonical(t_term *term)
{
	term->orig_attr = term->new_attr;
	(term->new_attr).c_lflag &= ~(ICANON | ECHO);
	(term->new_attr).c_cflag &= ~(CREAD);
	(term->new_attr).c_cc[VMIN] = 0;
	(term->new_attr).c_cc[VTIME] = 0;
	if (tcsetattr(term->t_desc, TCSAFLUSH, &(term->new_attr)) == -1)
		exit_suc("Can't set noncanonical mode!");
}

void	unset_noncanonical(t_term *term)
{
	ft_printf("%s", term->clean_screen);
	if (tcsetattr(term->t_desc, TCSAFLUSH, &(term->orig_attr)) == -1)
		exit_suc("Can't unset noncanonical mode!");
}

void	get_term_info(t_term *term)
{
	char buffer[1024];
	char *tmp;

	if (!(term->t_name = getenv("TERM")))
		exit_suc("Terminal type not found! Set type with: seotenv TERM [type]");
	term->t_desc = tgetent(buffer, term->t_name);
	if (term->t_desc < 0)
		exit_suc("Could not access the termcap database!!");
	window_size_val(&(term->col_num), &(term->line_num));
	if (tcgetattr(term->t_desc, &(term->new_attr)) == -1)
		exit_suc("Could not get Terminal attributes");
	term->buffer = ft_strnew(1024);
	term->clean_screen = tgetstr("cl", &(term->buffer));
	term->cursor = tgetstr("cm", &(term->buffer));
	term->c_up = tgetstr("up", &(term->buffer));
	term->c_down = tgetstr("do", &(term->buffer));
	term->autowrap = tgetflag("am");
	tmp = tgetstr("pc", &(term->buffer));
	term->pc = tmp ? *tmp : 0;
	term->bc = tgetstr("le", &(term->buffer));
}

void	managesignals(t_term *term, t_input *input)
{
	if (signal(SIGWINCH, sig_handlr(SIGWINCH)) == SIG_ERR)
	{
		ft_printf("%s", term->clean_screen);
		ft_printf("%R%s%E\n", strerror(errno));
	}
	else
	{
		window_size_val(&(term->col_num), &(term->line_num));
		sprinter(term, term->col_num, input);
	}
	//signal(SIGINT, sig_handlr(SIGINT));
}

int		main (int argc, char **argv)
{
	t_term	term;
	t_input	*input;

	input = NULL;
	if (argc < 2 || argv[1] == NULL)
		exit_suc("USAGE: ft_select argument 1 [argument 2] [argument ...]");
	else
	{
		get_term_info(&term);
		set_noncanonical(&term);
		//managesignals();
		input = sparser(argv, input);
		term.total_l = 2;
		sprint(input, term.col_num, &term);
		tputs(tgoto(term.cursor, 0, 2), 1, ft_sputchar);
		term.cursor_h = 2;
		term.cursor_w = 0;
		s_moving(&term, input);
		unset_noncanonical(&term);
	}
}