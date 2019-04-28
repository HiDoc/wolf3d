/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_rc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:44:41 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 17:36:55 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		*tga_read(void *tga_p, t_tga data)
{
	int		*pixels;
	int 	(*tga_sum)(t_tga *);
	int 	(*tga_parse)(int (*)(t_tga *), t_tga, int *);

	pixels = (int *)malloc(4 * data.width * data.height);
	tga_sum = get_ft_index(&data);
	tga_parse = tga_p;
	while (data.i < data.height)
	{
		while (data.j < data.width)
		{
			tga_parse(tga_sum, data, pixels);
			data.j++;
		}
		data.i++;
	}
	return (pixels);
}

SDL_Surface		*tga_start(const unsigned char *buffer)
{
	t_tga	tga;
	int		*pixels;

	pixels = NULL;
	tga.type = buffer[2] & 0xFF;
	tga.origin = (buffer[3] & 0xFF) | (buffer[4] & 0xFF) << 8;
	tga.length = (buffer[5] & 0xFF) | (buffer[6] & 0xFF) << 8;
	tga.depth = buffer[7] & 0xFF;
	tga.width = tga_width(buffer);
	tga.height = tga_height(buffer);
	tga.depth = buffer[16] & 0xFF;
	tga.descriptor = buffer[17] & 0xFF;
	tga.bytes = buffer;
	tga.order = (t_order){24, 16, 8, 0};
	tga.index = 0;
	tga.i = 0;
	tga.j = 0;
	// OFFSET FOR COLORMAP
	if (tga.type == COLORMAP_RLE || tga.type == COLORMAP)
		tga.offset = 18 + (tga.depth / 8) * tga.length;
	else
		tga.offset = 18;
	// BUFFER FOR PARSING
	if (tga.type == COLORMAP || tga.type == RGB | tga.type == GRAYSCALE)
		tga.palette = buffer;
	else
	{
		tga.palette = tga_rle(tga);
		tga.offset = 0;
	}

	// FUNCTION FOR PARSING
	if (tga.type == GRAYSCALE || tga.type == GRAYSCALE_RLE)
		pixels = tga_read(&tga_greyscale, tga);
	else
		pixels = tga_read(&tga_map, tga);
	return (SDL_CreateRGBSurfaceFrom((void *)pixels, tga.width, tga.height,
		tga.depth, (tga.width * sizeof(int)),
		(Uint32)(0xFF << tga.order.rs), (Uint32)(0xFF << tga.order.gs),
		(Uint32)(0xFF << tga.order.bs), (Uint32)(0xFF << tga.order.as)));
}



#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(void) {
	SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;
	SDL_Surface		*surface = NULL;
	SDL_Texture		*texture = NULL;
	SDL_Event		event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	FILE *file = fopen("large_ol.tga", "rb");

	int size;
	size = 0;
	if (file) {
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
		unsigned char *buffer = (unsigned char *)malloc(size);
		fread(buffer, 1, size, file);
		fclose(file);
		surface = tga_start(buffer);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	}
	int quit = 0;
	while (quit == 0)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
        		quit = 1;
        		break;
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}