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

void

int sig_handler(int sig)
{
	int okay;

	okay = 0;
	if (sig == SIGINT)
		okay = sigint_hand();
	else if (sig == SIGWINCH)
		okay = sigwin_hand();
	return (okay);
}
