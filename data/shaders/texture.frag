// Disegno di texture
uniform sampler2D texture_image;

void main()
{
	vec4 tex	= texture2D( texture_image, gl_TexCoord[0].st );
	vec4 color	= tex * gl_Color;

	/*
	vec2 light = vec2( 320, 240 );
	float intensity = distance( gl_FragCoord.xy, light.xy );
	gl_FragColor = vec4( color.rgb * ( 1.5 - intensity / 200 ), color.a );
	*/

	gl_FragColor = color;
}
