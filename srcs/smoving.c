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

static int cursorleft(t_input *input)
{
	if ((g_term.cursor_w == 0) && (g_term.cursor_h == 2) && (g_term.total_c > 1))
	{
		g_term.cursor_w = ((g_term.node_size + 1) * (g_term.last_line - 1));
		g_term.cursor_h = g_term.total_l;
	}
	else if (g_term.cursor_w == 0)
	{
		g_term.cursor_w = ((g_term.node_size + 1) * (g_term.total_c - 2));
		g_term.cursor_h -= 1;
	}
	else if (g_term.total_l > 1)
		g_term.cursor_w -= (g_term.node_size + 1);
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.cursor_w, g_term.cursor_h), 1, ft_sputchar);
	return (0);
}

static int cursorright(t_input *input)
{
	if (g_term.cursor_w >= (g_term.node_size * (g_term.total_c - 2)) && (g_term.total_c > 1) && (g_term.cursor_h != g_term.total_l))
	{
		g_term.cursor_w = 0;
		g_term.cursor_h += 1;
	}
	else if ((g_term.cursor_h == g_term.total_l) && (g_term.cursor_w == ((g_term.last_line - 1)  * (g_term.node_size + 1))))
	{
		g_term.cursor_w = 0;
		g_term.cursor_h = 2;
	}
	else if (g_term.total_l > 1)
		g_term.cursor_w += (g_term.node_size + 1);
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.cursor_w, g_term.cursor_h), 1, ft_sputchar);
	return (0);
}

static int cursorup(t_input *input)
{
	int up_line;

	up_line = (g_term.cursor_h - 1);
	if ((g_term.cursor_h == 2) && (g_term.total_l > 2) && (g_term.cursor_w < ((g_term.last_line) * (g_term.node_size + 1))))
		g_term.cursor_h = g_term.total_l;
    else if ((g_term.cursor_h == 2) && (g_term.cursor_w >= ((g_term.last_line) * (g_term.node_size + 1))))
        g_term.cursor_h = (g_term.total_l - 1);
	else if (g_term.total_l > 2)
		(g_term.cursor_h)--;
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.cursor_w, g_term.cursor_h), 1, ft_sputchar);
	return (0);
}

static int cursordown(t_input *input)
{
	int down_line;

	down_line = (g_term.cursor_h + 1);
	if ((g_term.cursor_h == g_term.total_l) && (g_term.total_l > 2))
		g_term.cursor_h = 2;
    else if ((g_term.cursor_h == (g_term.total_l - 1)) && (g_term.cursor_w >= ((g_term.last_line)  * (g_term.node_size + 1))))
        g_term.cursor_h = 2;
	else if (g_term.total_l > 2)
		(g_term.cursor_h)++;
	ft_printf("%s", g_term.clean_screen);
	sprint(input, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.cursor_w, g_term.cursor_h), 1, ft_sputchar);
	return (0);
}

int		s_moving(t_input *input)
{
	long	cursor;
	int		ret;
	int orig_w;
	int orig_h;

	orig_w = g_term.col_num;
	orig_h = g_term.line_num;
	while (1)
	{
		if (g_term.col_num != orig_w || g_term.line_num != orig_h)
		{
			g_term.cursor_w = 0;
			g_term.cursor_h = 2;
			sprint(input, g_term.col_num);
			tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
			orig_w = g_term.col_num;
			orig_h = g_term.line_num;
		}
		ret = read(g_term.t_desc, &cursor, 4);
		if (cursor == UP)
			cursorup(input);
		else if (cursor == DOWN)
			cursordown(input);
		else if (cursor == RIGHT)
			cursorright(input);
		else if (cursor == LEFT)
			cursorleft(input);
		else if (cursor == SPACE)
		    selector(input);
		else if (cursor == DELETE || cursor == BSPACE)
			input = deleter(input);
		cursor = 0;
	}
	return (0);
}
