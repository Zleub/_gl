__kernel void square(
	global uint * width,
	global double3 * mouse,
	global float3 * dPobj,
	global float3 * dCobj,
	global float3 * dVel
) {
	int Xindex = get_global_id(0);
	int Yindex = get_global_id(1);
	int index = Xindex + Yindex * (int)(*width);

	// printf("%f %f\n", mouse[0], mouse[1]);

	float pos = dPobj[index].x ;
	float col = dCobj[index].x ;
	float vel = dVel[index].x ;

	float att = (*mouse).x ;
	float dst = distance(pos, att);
	float speed = 0.0001;

	dVel[index].x += (att - pos) * dst;
	dCobj[index].x = dst ;
	dPobj[index].x += vel * speed ;

}
