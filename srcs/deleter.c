/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:58:17 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/22 15:58:19 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

/*void deleter(t_term *term, t_input **input_loc)
{
	t_input *tmp;
	t_input *input;
	int mouse_on;
	int i;

	i = 0;
	input = *input_loc;
	mouse_on = get_node_mouse(term);
	tmp = input;
	while (i < mouse_on)
	{
		input = input->next;
		i++;
	}
	if (i == 0)
	{
		(input->next)->before = NULL;
		tmp = input->next;
	}
	else
	{
		(input->before)->next = input->next;
		(input->next)->before = input->before;
	}
	if (i == 0)
		input_loc = &(input->next);
	s_input_cleaner(input);
	sprint(tmp, g_term.col_num, term);
	tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
	g_term.cursor_w = 0;
	g_term.cursor_h = 2;
}*/

t_input *deleter(t_input *input)
{
	int i;
	int mouse_on;
	t_input *next;
	t_input *tmp;

	i = 0;
	tmp = input;
	mouse_on = get_node_mouse();
	while (i < mouse_on)
	{
		input = input->next;
		i++;
	}
	if (input->next != NULL)
		next = input->next;
	if (i == 0)
	{
		next->before = NULL;
		tmp = input->next;
	}
	else if (input->next == NULL)
	{
		//CLEAN AND DELETE EVERYTHING AND EXIT AS ESC, AND ENTER CANONICAL MODE!!
	}
	else
	{
		next->before = input->before;
		(input->before)->next = input->next;
	}
	s_input_cleaner(input);
	sprint(tmp, g_term.col_num);
	tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
	g_term.cursor_w = 0;
	g_term.cursor_h = 2;
	return (tmp);
}