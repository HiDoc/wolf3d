/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 11:13:50 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/27 11:41:25 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		check_line(char *line, int cnt, int *nbr)
{
	while (line[cnt])
	{
		if (!ft_isdigit(line[cnt]) || !(line[cnt] != '-') || !(line[cnt] != ' '))
			return (0);
		if (line[cnt + 1] && line[cnt] == '-' && !(ft_isdigit(line[cnt + 1])))
			return (0);
		if (line[cnt + 1] && ft_isdigit(line[cnt]) && line[cnt + 1] == ' ')
			++(*nbr);
	}
	return (1);
}

t_env	*parse_line(t_env *env, char *line, int **map, int nline)
{
	int		cnt;
	int		nbr;
    char    *tmp;

    tmp = line;
 	cnt = 0;
	nbr = 0;
	if (!check_line(line, cnt, &nbr))
		return (NULL);
	if ((*map = malloc(sizeof(int) * nbr)) == NULL)
		return (NULL);
	cnt = 0;
	nbr = 0;
	while (tmp[cnt])
	{
		map[nline][nbr] = ft_atoi(&tmp[cnt]);
		while (tmp[cnt] && tmp[cnt] != ' ')
			cnt++;
		while (tmp[cnt] && tmp[cnt] == ' ')
			cnt++;
		nbr++;
	}
	free(line);
	line = NULL;
	return (env);
}

 t_env	*parse(t_env *env, char *filename)
{
	int		fd;
	char	*line;
	int		**map;
	int		count;
 	if (!(fd = open(filename, S_IROTH)))
		return (NULL);
	line = NULL;
	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		line = NULL;
		count++;
	}
	free(line);
	line = NULL;
	lseek(fd, 0, SEEK_SET);
	if ((map = (int **)malloc(sizeof(int *) * count)) == NULL)
		return (NULL);
	env->w_map = map;
    count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(env, line, map, count);
		++map;
        count++;
	}
	return (env);
}
