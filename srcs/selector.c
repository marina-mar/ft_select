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

int			get_node_mouse(void)
{
	int w;
	int h;
	int place;

	w = (g_term.c_w) / (g_term.node_size + 1);
	h = g_term.c_h;
	place = ((g_term.total_c - 1) * (h - 2)) + w;
	return (place);
}

static void	move_the_cursor(void)
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
}

void		selector(t_input *input)
{
	t_input	*tmp;
	int		mouse_on;
	int		i;

	i = 0;
	mouse_on = get_node_mouse();
	tmp = input;
	while (i < mouse_on)
	{
		input = input->next;
		i++;
	}
	if (input == NULL)
	{
		ft_printf("%RHey! Where is your cursor?? Quit and try again!%E\n");
		return ;
	}
	if (input->is_selected == 1)
		input->is_selected = 0;
	else
		input->is_selected = 1;
	if (input->is_selected == 1)
		move_the_cursor();
	sprint(tmp, g_term.col_num);
	tputs(tgoto(g_term.cursor, g_term.c_w, g_term.c_h), 1, ft_sputchar);
}
