/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scursor_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:01:25 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/25 19:01:26 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int	cursorleft(t_input *input)
{
	if ((g_term.c_w == 0) && (g_term.c_h == 2) && (g_term.total_c > 1))
	{
		g_term.c_w = ((g_term.node_size + 1) * (g_term.last_line - 1));
		g_term.c_h = g_term.total_l;
	}
	else if (g_term.c_w == 0)
	{
		g_term.c_w = ((g_term.node_size + 1) * (g_term.total_c - 2));
		g_term.c_h -= 1;
	}
	else if (g_term.total_l > 1)
		g_term.c_w -= (g_term.node_size + 1);
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.c_w, g_term.c_h), 1, ft_sputchar);
	return (0);
}

static int	cursorright(t_input *input)
{
	if (g_term.c_w >= (g_term.node_size * (g_term.total_c - 2)) &&
	(g_term.total_c > 1) && (g_term.c_h != g_term.total_l))
	{
		g_term.c_w = 0;
		g_term.c_h += 1;
	}
	else if ((g_term.c_h == g_term.total_l) &&
	(g_term.c_w == ((g_term.last_line - 1) * (g_term.node_size + 1))))
	{
		g_term.c_w = 0;
		g_term.c_h = 2;
	}
	else if (g_term.total_l > 1)
		g_term.c_w += (g_term.node_size + 1);
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.c_w, g_term.c_h), 1, ft_sputchar);
	return (0);
}

static int	cursorup(t_input *input)
{
	int up_line;

	up_line = (g_term.c_h - 1);
	if ((g_term.c_h == 2) && (g_term.total_l > 2) &&
	(g_term.c_w < ((g_term.last_line) * (g_term.node_size + 1))))
		g_term.c_h = g_term.total_l;
	else if ((g_term.c_h == 2) &&
	(g_term.c_w >= ((g_term.last_line) * (g_term.node_size + 1))))
		g_term.c_h = (g_term.total_l - 1);
	else if (g_term.total_l > 2)
		(g_term.c_h)--;
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.c_w, g_term.c_h), 1, ft_sputchar);
	return (0);
}

static int	cursordown(t_input *input)
{
	int down_line;

	down_line = (g_term.c_h + 1);
	if ((g_term.c_h == g_term.total_l) && (g_term.total_l > 2))
		g_term.c_h = 2;
	else if ((g_term.c_h == (g_term.total_l - 1)) &&
	(g_term.c_w >= ((g_term.last_line) * (g_term.node_size + 1))))
		g_term.c_h = 2;
	else if (g_term.total_l > 2)
		(g_term.c_h)++;
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.c_w, g_term.c_h), 1, ft_sputchar);
	return (0);
}

void		cursor_move(long cursor, t_input *input)
{
	if (cursor == UP)
		cursorup(input);
	else if (cursor == DOWN)
		cursordown(input);
	else if (cursor == RIGHT)
		cursorright(input);
	else if (cursor == LEFT)
		cursorleft(input);
}
