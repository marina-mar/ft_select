/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:30:59 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/19 17:31:00 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <curses.h>
#include <term.h>
void window_size_val(int *col, int *lin)
{
	*col = tgetnum("co");
	*lin = tgetnum("li");
}