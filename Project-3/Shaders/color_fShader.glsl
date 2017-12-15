/*****************************
 * File: fshader42.glsl
 *       A simple fragment shader
 *****************************/

#version 120  // YJC: Comment/un-comment this line to resolve compilation errors
                 //      due to different settings of the default GLSL version

vec4 fogColor = vec4(0.7, 0.7, 0.7, 0.5);
float FogDensity = 0.09;
float fogFactor, dist;
uniform int fogOption;
uniform bool ground;
uniform sampler2D texture;

in vec4 color;
in vec4 fragPos;
in vec2 texCoord;

varying out vec4 fColor;

void main()
{
    dist = length(fragPos);
    fColor = color;
    if(ground)
        fColor = fColor * texture2D( texture, texCoord );
    if(fogOption == 1)//linear fog
    {
       fogFactor = (0 - dist)/(0 - 18);
       fogFactor = clamp( fogFactor, 0.0, 1.0 );

       fColor = mix(fogColor, fColor, 1.0 -fogFactor);
    }
    else if(fogOption == 2)// exponential fog
    {
        fogFactor = 1.0 /exp(dist * FogDensity);
        fogFactor = clamp( fogFactor, 0.0, 1.0 );

        fColor = mix(fogColor, fColor, fogFactor);
    }
    else if(fogOption == 3)
    {
       fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity));
       fogFactor = clamp( fogFactor, 0.0, 1.0 );

       fColor = mix(fogColor, fColor, fogFactor);
    }
}
