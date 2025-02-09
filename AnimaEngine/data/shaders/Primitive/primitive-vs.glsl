#version 150 core

in vec3 _position;

uniform mat4 _projectionViewMatrix;
uniform mat4 _modelMatrix;

void main()
{
    gl_Position = _projectionViewMatrix *  _modelMatrix * vec4(_position, 1.0);
}
