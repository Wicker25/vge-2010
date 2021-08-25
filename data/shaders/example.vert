// Simple vertex shader
varying float intensity;

void main()
{
	gl_Position	= ftransform();

	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;

	vec2 light = gl_Position.xy + vec2( 50, 50 );

	intensity = distance( gl_Position.xy * gl_Vertex.xy, light.xy );

	gl_TexCoord[0] = gl_MultiTexCoord0;
}

/*
void main()
{
	gl_Position	= gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
*/

