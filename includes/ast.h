/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:02 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 13:02:26 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define TOKEN_VALUE 0x01
# define TOKEN_VERIF 0x02
# define TOKEN_NEXT_MAX 7
# define TOKEN_FRST_MAX	12

/*
** AST function to assign token
*/
int			is_spc(int c);
int			is_tab(int c);
int			is_min(int c);
int			is_end(int c);
int			is_sec(int c);
int			is_vtx(int c);
int			is_obj(int c);
int			is_txt(int c);
int			is_ent(int c);
int			is_wob(int c);
int			is_spe(int c);
int			is_plr(int c);
int			is_cmt(int c);
int			is_dgt(int c);
int			is_ptn(int c);

typedef struct s_parsefile	t_parsefile;
typedef struct s_parseline	t_parseline;
typedef struct s_token		t_token;
typedef struct s_op			t_op;

struct	s_op
{
	unsigned	val;
	const char	*name;
	int			(*verify)(int);
	unsigned	max_token;
};

struct	s_token
{
	int			value;
	unsigned	type;
	unsigned	pos;
	t_token		*next;
};

struct	s_parseline
{
	t_token		*first;
	t_parseline	*next;
	unsigned	len;
	unsigned	nline;
};

struct	s_parsefile
{
	int			nvertex;
	int			nsector;
	t_parseline	*first;
};

enum e_op_first{
	SECTOR,
	VERTEX,
	PLAYER,
	OBJECT,
	WOJECT,
	SPECIA,
	ENTITY,
	COMMNT,
	TXTURE
};

t_token		*new_token(char c, unsigned pos);
t_parseline	*new_line(unsigned nline);

int			reader(int fd, t_parsefile *file, unsigned *nvtx, unsigned *nsct);
int			parser(t_env *env, char *filename);
void		print_line(t_parseline *line);
void		print_file(t_parsefile *file);
int			free_file(t_parsefile *file);

#endif
