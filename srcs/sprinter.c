/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprinter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:37:03 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/20 17:37:04 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		maxstr(t_input *input)
{
	int size;

	size = 0;
	while (input != NULL)
	{
		if (size < input->str_len)
			size = input->str_len;
		input = input->next;
	}
	return (size);
}

int		count_str(t_input *input)
{
	int total;

	total = 0;
	while (input != NULL)
	{
		total++;
		input = input->next;
	}
	return (total);
}

int		get_total_l(int total_c, t_input *input)
{
	int total;
	int i;

	i = 1;
	total = 2;
	while (input != NULL)
	{
		if (i == total_c)
		{
			total++;
			i = 1;
		}
		i++;
		input = input->next;
	}
	return (total);
}
/*
int		get_pad(t_input *input, int width, int height)
{
	int how_many_str;
	int total;
	int max;

	total = get_total(input);
	how_many_str = count_str(input);
	max = maxstr(input);
	if ()
}*/

int	check_size(t_input *input)
{
	int w_need;
	int h_need;
	int orig_w;
	int orig_h;

	w_need = g_term.node_size * g_term.total_c;
	h_need = (g_term.total_l + 2);
	orig_w = g_term.col_num;
	orig_h = g_term.line_num;
	if (orig_w < w_need || orig_h < h_need)
	{
		while (g_term.col_num == orig_h && orig_h == g_term.line_num)
			;
		g_term.total_c = (g_term.col_num / g_term.node_size) - 1;
		w_need = g_term.node_size * g_term.total_c;
		g_term.total_l = get_total_l(g_term.total_c, input);
		h_need = g_term.total_l + 2;
		if (g_term.col_num >= w_need && g_term.line_num >= h_need)
			return (0);
		else
			return (-1);
	}
	return (0);
}

void	sprint(t_input *input, int width)
{
	int i;
	int j;
	int mouse_on;

	i = 1;
	j = 0;
	mouse_on = get_node_mouse();
	g_term.node_size = maxstr(input);
	g_term.total_c = (width / g_term.node_size) - 1;
	ft_printf("%s", g_term.clean_screen);
	g_term.total_l = get_total_l(g_term.total_c, input);
	if (check_size(input) == -1)
	{
		ft_printf("%RHey! We need a little more space to print!\n Can you [[r e s i z e]] your terminal??%E");
		while (check_size(input) == -1)
			;
		ft_printf("%s", g_term.clean_screen);
	}
	begin_screen(width);
	while (input != NULL)
	{
		if (i == g_term.total_c)
		{
			ft_printf("\n");
			i = 1;
		}
		if (j == mouse_on && input->is_selected == 1)
			ft_printf("%R%-*s%E ", g_term.node_size, input->element);
		else if (j == mouse_on)
			ft_printf("%G%-*s%E ", g_term.node_size, input->element);
		else if (input->is_selected == 1)
		    ft_printf("%I%-*s%E ", g_term.node_size, input->element);
		else
			ft_printf("%C%-*s %E", g_term.node_size, input->element);
		input = input->next;
		i++;
		j++;
	}
    g_term.last_line = i - 1;
	end_screen(width);
}
