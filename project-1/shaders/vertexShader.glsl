#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 rot;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

mat3 u_tModel;
vec3 pos;
const float rx = rot.x;
const float ry = rot.y;
mat3 scale = mat3(
   0.2, 0.0, 0.0, // first column (not row!)
   0.0, 0.2, 0.0, // second column
   0.0, 0.0, 0.2  // third column
);
mat3 rotationx = mat3(
    1,    0,       0,
    0, cos(rx), sin(rx),
	0, -sin(rx),  cos(rx)
);

mat3 rotationy = mat3(
    cos(ry),   0, -sin(ry),
       0,      1,     0,
    sin(ry),   0,   cos(ry)
);

void main(void)
{
    u_tModel = rotationx * rotationy * scale;
    FragPos = vec3( u_tModel * position );
    pos = u_tModel * position;
    gl_Position = vec4( pos, 1.0 );
    Normal = mat3( transpose( inverse( u_tModel ) ) ) * aNormal;
}
