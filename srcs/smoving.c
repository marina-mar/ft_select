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

int cursorleft(t_term *term, t_input *input)
{
	if ((term->cursor_w == 0) && (term->cursor_h == 2) && (term->total_c > 1))
	{
		term->cursor_w = ((term->node_size + 1) * (term->last_line - 1));
		term->cursor_h = term->total_l;
	}
	else if (term->cursor_w == 0)
	{
		term->cursor_w = ((term->node_size + 1) * (term->total_c - 2));
		term->cursor_h -= 1;
	}
	else if (term->total_l > 1)
		term->cursor_w -= (term->node_size + 1);
	ft_printf("%s", term->clean_screen);
	sprint(input, term->col_num, term);
	tputs(tgoto(term->cursor, term->cursor_w, term->cursor_h), 1, ft_sputchar);
	return (0);
}

int cursorright(t_term *term, t_input *input)
{
	if (term->cursor_w >= (term->node_size * (term->total_c - 2)) && (term->total_c > 1) && (term->cursor_h != term->total_l))
	{
		term->cursor_w = 0;
		term->cursor_h += 1;
	}
	else if ((term->cursor_h == term->total_l) && (term->cursor_w == ((term->last_line - 1)  * (term->node_size + 1))))
	{
		term->cursor_w = 0;
		term->cursor_h = 2;
	}
	else if (term->total_l > 1)
		term->cursor_w += (term->node_size + 1);
	ft_printf("%s", term->clean_screen);
	sprint(input, term->col_num, term);
	tputs(tgoto(term->cursor, term->cursor_w, term->cursor_h), 1, ft_sputchar);
	return (0);
}

int cursorup(t_term *term, t_input *input)
{
	int up_line;

	up_line = (term->cursor_h - 1);
	if ((term->cursor_h == 2) && (term->total_l > 2) && (term->cursor_w < ((term->last_line) * (term->node_size + 1))))
		term->cursor_h = term->total_l;
    else if ((term->cursor_h == 2) && (term->cursor_w >= ((term->last_line) * (term->node_size + 1))))
        term->cursor_h = (term->total_l - 1);
	else if (term->total_l > 2)
		(term->cursor_h)--;
	ft_printf("%s", term->clean_screen);
	sprint(input, term->col_num, term);
	tputs(tgoto(term->cursor, term->cursor_w, term->cursor_h), 1, ft_sputchar);
	return (0);
}

int cursordown(t_term *term, t_input *input)
{
	int down_line;

	down_line = (term->cursor_h + 1);
	if ((term->cursor_h == term->total_l) && (term->total_l > 2))
		term->cursor_h = 2;
    else if ((term->cursor_h == (term->total_l - 1)) && (term->cursor_w >= ((term->last_line)  * (term->node_size + 1))))
        term->cursor_h = 2;
	else if (term->total_l > 2)
		(term->cursor_h)++;
	ft_printf("%s", term->clean_screen);
	sprint(input, term->col_num, term);
	tputs(tgoto(term->cursor, term->cursor_w, term->cursor_h), 1, ft_sputchar);
	return (0);
}

int		s_moving(t_term *term, t_input *input)
{
	long	cursor;
	int		ret;

	while (1)
	{
		ret = read(term->t_desc, &cursor, 4);
		if (cursor == UP)
			cursorup(term, input);
		else if (cursor == DOWN)
			cursordown(term, input);
		else if (cursor == RIGHT)
			cursorright(term, input);
		else if (cursor == LEFT)
			cursorleft(term, input);
		else if (cursor == SPACE)
		    selector(term, input);
		else if (cursor == SPACE)
			selector(term, input);
		else if (cursor == DELETE || cursor == BSPACE)
			input = deleter(term, input);
		cursor = 0;
	}
	return (0);
}
