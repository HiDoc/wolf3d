#include "wolf.h"

static float  yaw(float p_yaw, float y, float z)
{
	return (y + z * p_yaw);
}

t_projec    curr_projection(float p_yaw, t_ylevel l, t_edge t, t_edge scale)
{
	t_projec	projection;
	
	projection = (t_projec)
	{
		H/2 - (int)(yaw(p_yaw, l.yceil, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, l.yfloor, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, l.yceil, t.y2) * scale.y2),
		H/2 - (int)(yaw(p_yaw, l.yfloor, t.y2) * scale.y2)
	};
	return (projection);	
}

t_projec	next_projection(float p_yaw, t_ylevel l, t_edge t, t_edge scale)
{
	t_projec	projection;

	projection = (t_projec)
	{
		H/2 - (int)(yaw(p_yaw, l.nyceil, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, l.nyfloor, t.y1) * scale.y1),
		H/2 - (int)(yaw(p_yaw, l.nyceil, t.y2) * scale.y2),
		H/2 - (int)(yaw(p_yaw, l.nyfloor, t.y2) * scale.y2)
	};
	return (projection);
}