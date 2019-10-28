/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:11:20 by mcouto            #+#    #+#             */
/*   Updated: 2019/10/19 16:11:25 by mcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_FT_SELECT_H
# define FT_SELECT_FT_SELECT_H

# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <stdlib.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <signal.h>
# include <limits.h>
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/includes/binary_tree.h"
# include "../libft/includes/ft_printf.h"

# define UP 4283163
# define DOWN 4348699
# define RIGHT 4414235
# define LEFT 4479771
# define DELETE 2117294875L
# define ESC 27
# define SPACE 32
# define ENTER 10
# define BSPACE 127

typedef struct		s_term
{
	char			*t_name;
	char			*clean_screen;
	char			*cursor;
	int				hold;
	int				node_size;
	int				total_l;
	int				total_c;
	int				t_desc;
	int				c_w;
	int				c_h;
	int				col_num;
	int				line_num;
	int				last_line;
	int				close;
	int				print;
	int				orig_w;
	int				orig_h;
	struct termios	orig_attr;
	struct termios	new_attr;

}					t_term;

typedef struct		s_input
{
	char			*element;
	short			is_selected;
	int				str_len;
	struct s_input	*next;
	struct s_input	*before;
}					t_input;

t_term				g_term;

int					main (int argc, char **argv);
int					get_node_mouse();
void				s_input_cleaner(t_input *input);
void				selector(t_input *input);
void				window_size_val(int *col, int *lin);
void				exit_suc(char *error);
t_input				*sparser(char **argv, t_input *input);
t_input				*deleter(t_input *input);
t_input				*s_moving(t_input *input);
void				set_noncanonical(void);
void				sprint(t_input *input, int width);
void				end_screen(int width);
void				begin_screen(int width);
void				sig_handler(int sig);
void				sclean_close(t_input *input);
void				unset_noncanonical(void);
void				get_selected(t_input *input);
void				cursor_move(long cursor, t_input *input);

#endif
