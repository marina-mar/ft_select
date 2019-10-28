/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:23:02 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/21 17:23:05 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void		reset_select(t_input *input)
{
	set_noncanonical();
	ft_printf("%s", g_term.clean_screen);
	g_term.hold = 0;
	g_term.c_w = 0;
	g_term.c_h = 2;
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
}

void		resize_select(t_input *input)
{
	g_term.c_w = 0;
	g_term.c_h = 2;
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
}

t_input		*actions(long cursor, t_input *input)
{
	if (cursor == SPACE)
		selector(input);
	else
		input = deleter(input);
	return (input);
}

void		change_term(t_input *input)
{
	if (g_term.hold == 1)
		reset_select(input);
	if (g_term.col_num != g_term.orig_w || g_term.line_num != g_term.orig_h)
	{
		resize_select(input);
		g_term.orig_w = g_term.col_num;
		g_term.orig_h = g_term.line_num;
	}
}

t_input		*s_moving(t_input *input)
{
	long	cursor;

	g_term.orig_w = g_term.col_num;
	g_term.orig_h = g_term.line_num;
	while (g_term.close == 0)
	{
		read(STDERR_FILENO, &cursor, 4);
		if (g_term.hold == 1 || g_term.col_num != g_term.orig_w ||
		g_term.line_num != g_term.orig_h)
			change_term(input);
		if (cursor == UP || cursor == DOWN || cursor == RIGHT || cursor == LEFT)
			cursor_move(cursor, input);
		else if (cursor == SPACE || cursor == DELETE || cursor == BSPACE)
			input = actions(cursor, input);
		else if (cursor == ENTER)
		{
			g_term.print = 1;
			break ;
		}
		else if (cursor == ESC)
			break ;
		cursor = 0;
	}
	return (input);
}
