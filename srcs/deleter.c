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

static t_input	*delete_it(t_input *input, int i, t_input *tmp)
{
	t_input	*next;

	if (input->next != NULL)
		next = input->next;
	if (i == 0 && input->next == NULL)
		sclean_close(input);
	else if (i > 0 && input->next == NULL)
		(input->before)->next = NULL;
	else if (i == 0)
	{
		next->before = NULL;
		tmp = input->next;
	}
	else
	{
		next->before = input->before;
		(input->before)->next = input->next;
	}
	return (tmp);
}

t_input			*deleter(t_input *input)
{
	int		i;
	int		mouse_on;
	t_input	*tmp;

	i = 0;
	tmp = input;
	mouse_on = get_node_mouse();
	while (i < mouse_on)
	{
		input = input->next;
		i++;
	}
	tmp = delete_it(input, i, tmp);
	s_input_cleaner(input);
	g_term.c_w = 0;
	g_term.c_h = 2;
	sprint(tmp, g_term.col_num);
	tputs(tgoto(g_term.cursor, 0, 2), 1, ft_sputchar);
	return (tmp);
}
