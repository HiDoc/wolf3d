/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:32:02 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/07 18:46:08 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "doom.h"

typedef struct s_parsefile	t_parsefile;
typedef struct s_parseline	t_parseline;
typedef struct s_token		t_token;

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

t_token		*new_token(char c, unsigned pos);
t_parseline	*new_line(unsigned nline);

int			reader(int fd, t_parsefile *file, unsigned *nvtx, unsigned *nsct);

void		print_line(t_parseline *line);
void		print_file(t_parsefile *file);
int			free_file(t_parsefile *file);


#endif
