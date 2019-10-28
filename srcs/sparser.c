/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:13:11 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/20 18:13:13 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static t_input		*new(t_input *input)
{
	input = ft_memalloc(sizeof(t_input));
	input->before = NULL;
	input->next = NULL;
	return (input);
}

t_input				*sparser(char **argv, t_input *input)
{
	t_input	*first;
	t_input	*before;
	int		i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (i == 1)
		{
			input = new(input);
			first = input;
		}
		else
		{
			input->next = ft_memalloc(sizeof(t_input));
			before = input;
			input = input->next;
			input->before = before;
		}
		input->element = argv[i];
		input->str_len = ft_strlen(argv[i]);
		input->is_selected = 0;
		i++;
	}
	return (first);
}
