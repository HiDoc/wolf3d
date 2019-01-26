/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 11:13:50 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/26 16:43:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		ft_parsing_exit(t_env *env, int fd, char *msg)
{
	(void)env; // to remove
	if (fd > -1)
		close(fd);
	//ft_err_exit(msg, data); // return to an exit function
	if (msg)
		ft_putendl(msg); // to remove
	exit(EXIT_FAILURE); // to remove
}

static int	convert(char c, int base)
{
	int ret;

	if (c >= '0' && c <= '9')
		ret = c - 48;
	else if (c >= 'a' && c <= 'z')
		ret = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		ret = c - 65 + 10;
	else
		ret = -1;
	if (ret < base && ret != -1)
		return (ret);
	else
		return (-1);
}

static int	nbr_digits(const char *str, int base)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (convert(str[i], base) < 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_atoibase(const char *str, int base)
{
	int	ret;
	int	len;
	int	i;

	if (base == 10)
		return (ft_atoi(str));
	while (*str == ' ' || *str == '\t')
		str++;
	ret = 0;
	len = nbr_digits(str, base) - 1;
	i = 0;
	while (str[i] && len >= 0 && convert(str[i], base) >= 0)
	{
		ret += convert(str[i], base) * pow(base, len);
		len--;
		i++;
	}
	return (ret);
}

static int		ft_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int		ft_strdigit(char *line)
{
	while (*line)
	{
		if (!(ft_isdigit(*line)) && *line != ',')
			return (0);
		line++;
	}
	return (1);
}

static void		ft_get_mapsize(t_env *env, int fd, char *line)
{
	char	**split;
	int		i;

	i = 0;
	if (!(split = ft_strsplit(line, ',')))
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: out of memory");
	if (ft_tablen(split) != 3 || !ft_strdigit(line))
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");

	if ((env->map_w = ft_atoi(split[0])) == 0)
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");
	if ((env->map_h = ft_atoi(split[1])) == 1)
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");
	if ((env->nb_bots = ft_atoi(split[2])) == 0)
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");

	while (split[i])
		ft_strdel(&split[i++]);
	ft_memdel((void **)split);
}

static void		ft_parse_line(t_env *env, int fd, int index, char *line)
{
	static int	bot_index = 0;
	char		**split;
	int			i;

	i = 0;
	if (!(split = ft_strsplit(line, ',')))
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: out of memory");
	if (ft_tablen(split) != env->map_w)
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");
	while (split[i])
	{
		env->w_map[index][i] = ft_atoibase(split[i], 16);
		if ((env->w_map[index][i] & 0xa0) == 0xa0) // add fc to check if double spawn
		{
			env->player.pos = (t_point){(index + 0.5), (i + 0.5)};
			env->w_map[index][i] = 0;
		}
		else if ((env->w_map[index][i] & 0xc0) == 0xc0)
		{
			if (!(env->bots[bot_index] = (t_bot *)ft_memalloc(sizeof(t_bot))))
				exit(EXIT_FAILURE); // to recup exit
			ft_bzero(env->bots[bot_index], sizeof(t_bot));
			env->bots[bot_index]->init_pos.x = i + 0.5;
			env->bots[bot_index]->init_pos.y = index + 0.5;
			env->bots[bot_index]->position.x = i + 0.5;
			env->bots[bot_index]->position.y = index + 0.5;
			env->bots[bot_index]->health = 100;
			bot_index++;
		}
		ft_strdel((void *)&(split[i]));
		i++;
	}
	ft_memdel((void *)split);
}

void			parse_map(t_env *env, char *filename)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_parsing_exit(env, -1, "doom_nukem: parsing error: can't open the map");
	if ((get_next_line(fd, &line)) < 1)
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");
	ft_get_mapsize(env, fd, line);
	ft_strdel(&line);

	printf("nb_bots : %d\n", env->nb_bots);
	if (!(env->bots = (t_bot **)ft_memalloc(sizeof(t_bot *) * (env->nb_bots + 1))))
		exit(EXIT_FAILURE); // to recup exit

	printf("map_w : %d\nmap_h : %d\n", env->map_w, env->map_h);

	if (!(env->w_map = (int **)(ft_memalloc(sizeof(int *) * (env->map_h)))))
		ft_parsing_exit(env, fd, "doom_nukem: parsing error: out of memory");
	while ((get_next_line(fd, &line)) > 0)
	{
		if (i >= env->map_h)
			ft_parsing_exit(env, fd, "doom_nukem: parsing error: bad map format");
		if (!(env->w_map[i] = (int *)(ft_memalloc(sizeof(int) * (env->map_w)))))
			ft_parsing_exit(env, fd, "doom_nukem: parsing error: out of memory");
		ft_parse_line(env, fd, i, line);
		ft_strdel(&line);
		i++;
	}
	//if (i != env->map_h || env->player.position.x == -1)
	//	ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
	close(fd);
}
