#include "parser.h"

int	is_spc(int c) { return c == ' '; }
int	is_tab(int c) { return c == '\t'; }
int	is_min(int c) { return c == '-'; }
int	is_end(int c) { return c == '\n'; }
int	is_sec(int c) { return c == 's'; }
int	is_vtx(int c) { return c == 'v'; }
int	is_plr(int c) { return c == 'p'; }
