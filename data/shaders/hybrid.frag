// Disegno ibrido
uniform int type;
uniform int mode;
uniform sampler2D texture_image;

void main()
{
	vec4 tex	= texture2D( texture_image, gl_TexCoord[0].st );
	vec4 color	= tex * gl_Color;

	if ( type == 0 )

		gl_FragColor = gl_Color;

	else if ( type == 1 ) {

		/*
		vec2 light = vec2( 320, 240 );
		float intensity = distance( gl_FragCoord.xy, light.xy );
		gl_FragColor = vec4( color.rgb * ( 1.5 - intensity / 200 ), color.a );
		*/

		gl_FragColor = color;
	}
}
