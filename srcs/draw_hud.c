#include "doom.h"

int print_hud(t_env *env)
{
    char *tmp;

    if (!(tmp = ft_strljoin(ft_itoa(env->player.shield), "%")))
        return (0);
    draw_img(env, (t_edge){{50, H - 50 - env->player.hud.health->h},
    {50 + env->player.hud.health->w, H - 50}}, env->player.hud.health, (t_ixy){0, 0});
    text_font(env, tmp, (t_vctr){85, H - 133, 36}, (SDL_Color){242, 248, 42, 255});
    free(tmp);
    tmp = NULL;
    return (0);
}