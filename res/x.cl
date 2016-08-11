__kernel void square(
	global uint * width,
	global float * dt,
	global float4 * mouse,

	global float4 * dPobj,
	global float4 * dVel,
	global float4 * dCobj,

	global float3 * iPos
) {
	int Xindex = get_global_id(0);
	int Yindex = get_global_id(1);
	int index = Xindex + Yindex * (int)(*width);

	float pos = dPobj[index].x ;
	float vel = dVel[index].x ;

	float att = (*mouse).x ;
	float dst = sqrt(
		pow(dPobj[index].x - (*mouse).x, 2) +
		pow(dPobj[index].y - (*mouse).y, 2)
		// pow(dPobj[index].z - (*mouse).z, 2)
	);

	dVel[index].x += (att - pos) * (dst / 2) ;
	dPobj[index].x += vel * (*dt) ;
	dCobj[index].x = 1 ; //pow(dst / 2, 2);

	dPobj[index].w -= 0.0001;
	if (dPobj[index].w < 0) {
		dPobj[index] = (float4){ iPos[index], 1 } ;
	}
}
