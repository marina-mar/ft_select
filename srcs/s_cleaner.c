/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cleaner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:10:34 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/22 16:10:38 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	s_input_cleaner(t_input *input)
{
	ft_memdel((void**)&input);
}

void	get_selected(t_input *input)
{
	int	has_it;

	has_it = 0;
	while (input != NULL)
	{
		if (input->is_selected == 1)
		{
			if (has_it > 0)
				ft_putstr(" ");
			ft_putstr(input->element);
			has_it++;
		}
		input = input->next;
	}
}

void	sclean_close(t_input *input)
{
	t_input	*tmp;

	ft_printf("%E");
	ft_printf("%s", g_term.clean_screen);
	unset_noncanonical();
	if (g_term.print == 1)
		get_selected(input);
	while (input != NULL)
	{
		tmp = input;
		input = input->next;
		s_input_cleaner(tmp);
	}
	exit(EXIT_SUCCESS);
}
