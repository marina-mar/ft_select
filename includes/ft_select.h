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
#define FT_SELECT_FT_SELECT_H

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
	char 			*buffer;
	char			*t_name;
	char 			*clean_screen;
	char 			*cursor;
	char 			*c_up;
	char 			*c_down;
	char 			*bc;
	char 			pc;
	int				node_size;
	int				total_l;
	int				total_c;
	int				t_desc;
	int				cursor_w;
	int				cursor_h;
	int				col_num;
	int				line_num;
	int				autowrap;
	int             last_line;
	struct termios	orig_attr;
	struct termios	new_attr;

}					t_term;

typedef struct		s_input
{
	char			*element;
	short 			is_selected;
	int				str_len;
	struct s_input	*next;
	struct s_input	*before;
}					t_input;

typedef struct 		s_signal
{
	short			sigint;
	short			window;
}					t_signal;

t_term				g_term;

int					main (int argc, char **argv);
int                 s_moving(t_input *input);
int					get_node_mouse();
int					s_input_cleaner(t_input *input);
void				selector(t_input *input);
void				window_size_val(int *col, int *lin);
void				exit_suc(char *error);
t_input				*sparser(char **argv, t_input *input);
t_input 			*deleter(t_input *input);
void				sprint(t_input *input, int width);
void				end_screen(int width);
void				begin_screen(int width);
void				sig_handler(int sig);



#endif
