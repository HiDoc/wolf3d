/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:27:29 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/11 03:10:24 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static SDL_Surface	**enemy_fill(char *path, int size)
{
	SDL_Surface	**enemy;
	int i;

	i = -1;
	enemy = ft_memalloc(sizeof(SDL_Surface*) * size);
	while (++i < size)
		enemy[i] = ui_img(path, i);
	return (enemy);
}

static void			enemy_sprite(t_character *enemy, char *name)
{
	char	*w_path;
	char	*s_path;
	char	*d_path;

	w_path = ft_strjoin(name, "/walk/");
	s_path = ft_strjoin(name, "/shoot/");
	d_path = ft_strjoin(name, "/death/");
	enemy->walk = enemy_fill(w_path, enemy->time_walk);
	enemy->shoot = enemy_fill(s_path, enemy->time_shoot);
	enemy->death = enemy_fill(d_path, enemy->time_death);
	lt_release(w_path);
	lt_release(s_path);
	lt_release(d_path);
}

static void			enemy_set(char *name, t_character *enemy, t_brain b)
{
	long	ref;

	ref = enemy->ref;
	enemy->type = (ref & 0xF);
	enemy->damage = ((ref >> (1 << 2)) & 0xFF);
	enemy->time_shoot = ((ref >> (3 << 2)) & 0xFF);
	enemy->time_walk = ((ref >> (5 << 2)) & 0xFF);
	enemy->time_death = ((ref >> (7 << 2)) & 0xFF);
	enemy->cadence_shoot = ((ref >> (9 << 2)) & 0xFF);
	enemy->brain = b;
	enemy_sprite(enemy, name);
}

void				init_enemies(t_env *env, t_brain b, int i)
{
	const long	ref[WORLD_NB_ENEMIES] = {L_MONSTER, L_SOLDIER, L_ROGER,
	L_LOSTSOUL, L_PAIN_ELEM, L_PINKBOY, L_CYBERDEMON, L_BOSS, L_BOSS_MIDL};
	t_character	*e;

	e = env->world.enemies;
	while (++i < WORLD_NB_ENEMIES)
		env->world.enemies[i].ref = ref[i];
	b = (t_brain){100, 0, 0, 5, 700, 400, 200, 0.15f, {3, 10}};
	enemy_set("enemies/monster", &e[MONSTER], b);
	b = (t_brain){100, 0, 0, 50, 700, 300, 100, 0.1f, {3, 10}};
	enemy_set("enemies/soldier", &e[SOLDIER], b);
	b = (t_brain){200, 0, 0, 50, 700, 500, 100, 0.1f, {2, 12}};
	enemy_set("enemies/roger", &e[ROGER], b);
	b = (t_brain){70, 0, 0, 3, 800, 800, 500, 0.25f, {3, 10}};
	enemy_set("enemies/lostsoul", &e[LOSTSOUL], b);
	b = (t_brain){250, 0, 0, 20, 900, 700, 400, 0.2f, {4, 10}};
	enemy_set("enemies/painelemental", &e[PAIN_ELEM], b);
	b = (t_brain){400, 0, 0, 7, 1000, 400, 100, 0.1f, {2, 15}};
	enemy_set("enemies/pinkboy", &e[PINKBOY], b);
	b = (t_brain){1000, 0, 0, 100, 700, 700, 300, 0.05f, {2, 20}};
	enemy_set("enemies/cyberdemon", &e[CYBERDEMON], b);
	b = (t_brain){1000, 0, 0, 100, 600, 300, 300, 0.1f, {2, 15}};
	enemy_set("enemies/boss", &e[BOSS], b);
	b = (t_brain){1000, 0, 0, 50, 600, 300, 200, 0.2f, {2, 10}};
	enemy_set("enemies/boss/midlife", &e[BOSS_MIDL], b);
}