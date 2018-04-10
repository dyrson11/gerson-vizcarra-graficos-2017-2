#version 120

attribute  vec3 vPosition;
attribute  vec3 vColor;
attribute  vec3 vNormal;
attribute  vec2 vTexCoord;

//varying out vec4 color;
varying vec3 Normal;
varying vec3 FragPos;
varying vec2 texCoord;

uniform mat4 model;
uniform mat4 imodel;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    vec4 vPosition4 = vec4(vPosition, 1.0);
    FragPos = -vec3(view * model * vPosition4);
    Normal = mat3(transpose(imodel)) * vNormal;
    gl_Position = projection * view * model * vec4(vPosition, 1.0);
    texCoord = vTexCoord;
}
