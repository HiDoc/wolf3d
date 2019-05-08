/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:54:47 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 20:52:56 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	musics_pack(char *name, Mix_Music **pack, int limit, const char **str)
{
	int			i;
	char		*file;
	const char	*wav = ".wav";
	const char	*rsrc = "./rsrc/sound/";
	char		*prefix;

	i = -1;
	while (++i < limit)
	{
		prefix = ft_strjoin((char*)rsrc, name);
		prefix = ft_strljoin(prefix, (char *)str[i]);
		file = ft_itoa(i + 1);
		file = ft_strrjoin(prefix, file);
		file = ft_strljoin(file, (char*)wav);
		if (!(pack[i] = lt_push(Mix_LoadMUS(file), &msc_del)))
			doom_error_exit("Doom_nukem error on Mix_LoadMUS");
		lt_release((void**)&prefix);
		lt_release((void**)&file);
	}
}

void	chunks_pack(char *name, Mix_Chunk **pack, int limit)
{
	int			i;
	char		*file;
	char		*prefix;
	const char	*wav = ".wav";
	const char	*rsrc = "./rsrc/sound/";

	i = -1;
	while (++i < limit)
	{
		prefix = ft_strjoin((char*)rsrc, name);
		file = ft_itoa(i + 1);
		file = ft_strrjoin(prefix, file);
		file = ft_strljoin(file, (char*)wav);
		if (!(pack[i] = lt_push(Mix_LoadWAV(file), &chk_del)))
			doom_error_exit("Doom_nukem error on Mix_LoadWAV");
		lt_release((void**)&prefix);
		lt_release((void**)&file);
	}
}

void	ld_sound(t_env *e)
{
	t_sound		*s;
	const char	*names[SD_AMBIANCE] = {"menu+", "first_room+", "gameover+",
	"inspace+", "cyberdmroom+", "bossroom+", "deadroom+", "metallic+", "drama+",
	"stress_undrgrd+", "underwater+", "stressaction+", "loadinpage+", "dark+",
	"tension+", "epicloop+", "cavewater+", "cinematik+", "actionloop+",
	"factory+"};

	s = &e->sound;
	ft_bzero(s, sizeof(t_sound));
	musics_pack("ambiance/", s->ambiance, SD_AMBIANCE, names);
	chunks_pack("hud/", s->hud, SD_HUD);
	chunks_pack("effect/", s->s_effect, SD_EFFECT);
	chunks_pack("wpn/shot/", s->shot, WORLD_NB_WEAPONS);
	chunks_pack("wpn/reload/", s->reload, GAME_NB_WPN);
	chunks_pack("player/", s->p_sound, SD_PLAYER);
	chunks_pack("player/gem/", s->rp_gem, SD_RAND_GEM);
	chunks_pack("player/impass/", s->rp_impass, SD_RAND_IMPASS);
	chunks_pack("player/kill/", s->rp_kill, SD_RAND_KILL);
	chunks_pack("player/hit/", s->rp_hit, SD_RAND_HIT);
	chunks_pack("enemies/voice/", s->e_voice, WORLD_NB_ENEMIES);
	chunks_pack("enemies/shot/", s->e_shot, WORLD_NB_ENEMIES);
	chunks_pack("enemies/death/", s->e_death, WORLD_NB_ENEMIES);
	Mix_AllocateChannels(32);
}
