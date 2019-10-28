/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:45:00 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/20 18:45:01 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void	first_line(int width)
{
	while (width > 1)
	{
		ft_printf("%C_");
		width--;
	}
	ft_printf("\n");
}

void		begin_screen(int width)
{
	int spaces;
	int print;

	spaces = ((width - 9) / 2);
	print = 1;
	first_line(width);
	while (print < spaces)
	{
		ft_printf("%C_");
		print++;
	}
	print = 0;
	ft_printf("%Yft_select");
	while (print < spaces)
	{
		ft_printf("%C_");
		print++;
	}
	if (((width - 9) % 2) != 0)
		ft_printf("_");
	ft_printf("\n");
}

void		end_screen(int width)
{
	int print;

	print = 1;
	ft_printf("%C\n");
	while (print < width)
	{
		ft_printf("_");
		print++;
	}
	ft_printf("\n");
}
