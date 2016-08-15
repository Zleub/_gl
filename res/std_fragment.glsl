varying vec3 color;
varying vec3 texture;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture2D(tex, vec2(texture.x, texture.y)) ; //* vec4(color, 1.);
}
