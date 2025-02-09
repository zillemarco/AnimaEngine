#version 150 core

in vec3 _position;

uniform mat4 CAM_ProjectionViewMatrix;
uniform mat4 MOD_AModelMatrix;

void main()
{          
    gl_Position = CAM_ProjectionViewMatrix * MOD_AModelMatrix * vec4(_position, 1.0);
}