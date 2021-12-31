#version 330 core

layout (location = 0) in highp vec3 aPos;
layout (location = 1) in highp vec2 aTexCoord;

out highp vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  UV = vec2(aTexCoord.x, aTexCoord.y);
}
