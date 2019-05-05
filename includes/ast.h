/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:02 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 19:36:34 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define TOKEN_VALUE 0x01
# define TOKEN_VERIF 0x02
# define TOKEN_STRING 0x04
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
int			is_plr(int c);
int			is_cmt(int c);
int			is_dgt(int c);
int			is_ptn(int c);
int			is_mus(int c);
int			is_sky(int c);
int			no_op_int(int c);

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
	unsigned	absolute;
};

struct	s_parsefile
{
	int			nvertex;
	int			nsector;
	t_parseline	*first;
};

enum e_op_next
{
	SPACE,
	TAB,
	INT,
	MINUS,
	POINT,
	NEND,
	NNONE,
	TOKEN_NEXT_MAX
};

enum e_op_first
{
	SECTOR,
	VERTEX,
	PLAYER,
	OBJECT,
	SKYBOX,
	ENTITY,
	COMMNT,
	TXTURE,
	MUSIC,
	END,
	NONE,
	ERROR,
	TOKEN_FRST_MAX
};

t_token		*new_token(char c, unsigned pos);
t_parseline	*new_line(unsigned nline, unsigned absolute);

int			reader(int fd, t_parsefile *file, unsigned *nvtx, unsigned *nsct);
int			parser(t_env *env, char *filename);
void		print_line(t_parseline *line);
void		print_file(t_parsefile *file);
int			free_file(t_parsefile *file);
int			verify_token_first(int iter, char c, unsigned which);
int			verify_token_next(int iter, char c, unsigned which);
unsigned	token_count_until(t_token *start, unsigned type, unsigned until);
unsigned	token_count(t_parseline *line, unsigned type);

void		load_sector(t_env *e, t_parseline *line, t_vtx *vert);
void		load_vertex(t_env *e, t_parseline *line, t_vtx *vert);
void		load_player(t_env *e, t_parseline *line, t_vtx *vert);
void		load_object(t_env *e, t_parseline *line, t_vtx *vert);
void		load_skybox(t_env *e, t_parseline *line, t_vtx *vert);
void		load_entity(t_env *e, t_parseline *line, t_vtx *vert);
void		load_texture(t_env *e, t_parseline *line, t_vtx *vert);
void		load_comment(t_env *e, t_parseline *line, t_vtx *vert);
void		load_music(t_env *e, t_parseline *line, t_vtx *vert);
void		no_op_ft(t_env *e, t_parseline *line, t_vtx *vert);
#endif
