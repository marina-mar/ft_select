/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:43:40 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/21 16:43:41 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void	sigwin_hand(void)
{
	char buffer[1024];

	g_term.t_desc = tgetent(buffer, g_term.t_name);
	g_term.col_num = tgetnum("co");
	g_term.line_num = tgetnum("li");
}

void		sig_handler(int sig)
{
	if (sig == SIGWINCH)
		sigwin_hand();
	else if (sig == SIGCONT)
		g_term.hold = 1;
	else
		g_term.close = 1;
}
