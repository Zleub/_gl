uniform sampler2D tex;

varying vec3 color;
varying vec2 fragTexCoord;

void main()
{
	float dst = sqrt(
		pow(color.x, 2.) +
		pow(color.y, 2.)
	);

	gl_FragColor = vec4(1., 1., 1., 1.);
}
