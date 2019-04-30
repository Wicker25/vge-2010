// Simple fragment shader
uniform sampler2D texture_image;
uniform bool image_;
varying float intensity;

void main()
{
	vec4 tex	= texture2D( texture_image, gl_TexCoord[0].st );
	vec4 color	= tex * gl_Color;

	//gl_FragColor = vec4( color.rgb * ( 1.0 - intensity / 200 ), color.a );

	if ( image_ )

		gl_FragColor = color;
	else
		gl_FragColor = gl_Color;
}


/*
void main()
{
	vec4 tex	= texture2D( textureImage, gl_TexCoord[0].st );
	vec4 color	= vec4( ( tex + gl_Color ) / 2.0 );

	gl_FragColor = color;
}
*/
