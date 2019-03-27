
#ifndef DOOM_S_TGA_READER
# define DOOM_S_TGA_READER

typedef struct		s_tga
{
	unsigned char	*cm;// DONE
	unsigned char	*data;// DONE
	unsigned char	*done;// DONE
	unsigned char	*info;
	int				id_len;// =>
	int				datatype;
	int				compress;
	int				cm_start;
	int				cm_len;
	int				cm_bpp;
	int				xorigin;
	int				yorigin;
	int				w;
	int				h;
	int				data_bpp;
	int				descriptor;// <=
	int				data_len;
	int				fd;
	int				data_i;
	int				new_i;
	int				truevision;
}					t_tga;

#endif
