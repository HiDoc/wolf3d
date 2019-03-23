
#ifndef DOOM_S_TGA_READER
# define DOOM_S_TGA_READER

typedef struct		s_pixel
{
	unsigned char 	a;
	unsigned char 	r;
	unsigned char 	g;
	unsigned char 	b;
}					t_pixel;

typedef struct		s_tga
{
	t_pixel			*cm;
	t_pixel			*pxl;
	t_pixel			*done;
	char			*str;
	unsigned char	*colormap;
	unsigned char	*file;
	int				xorigin;
	int				yorigin;
	int				nb_elem;
	int				cm_begin;
	int				w;
	int				h;
	int				bits_cm;	//number of bits per palette entry 15,16,24,32
	int				color_type; // type of colour map 0=none, 1=has palette
	int				compress; 	//type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
	int				bitspix;	// image bits per pixel 8,16,24,32
	int				alpha;
	int				len_cm;		// number of colours in palette
}					t_tga; 

#endif
