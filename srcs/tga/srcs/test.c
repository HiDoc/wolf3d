#include "tga.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void print_tga_data(t_tga *img)
{
    int x = 0, y = 0;
    printf("TGA VERSION: %d\n", img->version);
    printf("WIDTH: %d, HEIGHT: %d, DEPTH: %d\n", img->meta.width,
            img->meta.height, img->meta.pixel_depth);
    printf("IMAGE TYPE: ");
    switch(img->meta.image_type)
    {
        case TGA_COLOR_MAPPED:
            printf("Color Mapped\n");
            break;
        case TGA_TRUECOLOR:
            printf("Truecolor\n");

            break;
        case TGA_MONOCHROME:
            printf("Monochrome\n");
            break;
        default:
            printf("Unsupported\n");
    }
    printf("C_MAP_START: %d\n", img->meta.c_map_start);
    printf("C_MAP_DEPTH: %d\n", img->meta.c_map_depth);
    printf("C_MAP_LENGTH: %d\n", img->meta.c_map_length);
    printf("Attribute Bits: %d\n", (img->meta.image_descriptor & (uint8_t)15));

    uint8_t *pixel = NULL;
    uint8_t depth = (uint8_t)((img->meta.pixel_depth + 7) / 8);
    uint16_t width = img->meta.width;
    printf("FIRST 8 x 8 Pixel Values (Assuming 24-bit Pixels):\n");
    for(y = 0; y < 50; y++)
    {
        for(x = 0; x < 50; x++)
        {
            pixel = img->data + (y*width*depth) + (depth * x);
            printf("#%02x%02x%02x ", pixel[2], pixel[1], pixel[0]);
        }
        printf("\n");
    }
}
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void		setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = pixel;
}

Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	int				bpp;
	Uint8			*p;

	if (!surface)
		return (0xffff0000);
	x = ft_abs(--x);
	y = ft_abs(--y);
	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	return (*(Uint32 *)p);
}

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
	int fd = open("/Users/fmadura/doom/srcs/tga/large_ol.tga", O_RDONLY);
	if (fd > -1)
	{
		t_tga *image;
		image = malloc(sizeof(t_tga));
		bzero(image, sizeof(t_tga));
		printf("%d\n", read_tga_image(fd, image));
		print_tga_data(image);
		surface = SDL_CreateRGBSurfaceFrom((void *)image->data, image->meta.width,
            image->meta.height, image->meta.pixel_depth, image->meta.width * image->meta.pixel_depth / 8,
			0xFF0000, 0xFF00, 0xFF, 0xFF000000);
		SDL_Surface *tmp = SDL_CreateRGBSurface(0, image->meta.width,
            image->meta.height, 32, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);
		int i = 0;
		int j = 0;
		while (i < image->meta.width)
		{
			j = 0;
			while (j < image->meta.height)
			{
				Uint32 color = getpixel(surface, i, j);
				setpixel(tmp, i, j, (0xFF000000 | color));
				j++;
			}
			i++;
		}
		texture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
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
				SDL_RenderCopy(renderer, texture, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
		}
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	return 0;
}
