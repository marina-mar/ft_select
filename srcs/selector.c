/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:40:34 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/22 13:40:35 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int get_node_mouse(t_term *term)
{
    int w;
    int h;
    int place;

    w = (term->cursor_w) / (term->node_size + 1);
    h = term->cursor_h;
    place = ((term->total_c - 1) * (h - 2)) + w;
    return (place);
}

void move_the_cursor(t_term *term)
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
}

void selector(t_term *term, t_input *input)
{
	t_input *tmp;
    int mouse_on;
    int i;

    i = 0;
    mouse_on = get_node_mouse(term);
    tmp = input;
    while (i < mouse_on)
    {
        input = input->next;
        i++;
    }
    if (input == NULL)
	{
    	ft_printf("%RHey! How did your cursor went there?? Quit and try again!%E\n");
    	return ;
	}
	if (input->is_selected == 1)
    	input->is_selected = 0;
	else
		input->is_selected = 1;
	if (input->is_selected == 1)
		move_the_cursor(term);
    sprint(tmp, term->col_num, term);
    tputs(tgoto(term->cursor, term->cursor_w, term->cursor_h), 1, ft_sputchar);
}