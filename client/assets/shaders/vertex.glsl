#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 ChunkOffset;

out highp vec3 fragPos;
out highp vec2 uv;
out highp vec3 normal;

void main()
{
  vec3 pos = aPos + ChunkOffset;

  gl_Position = projection * view * model * vec4(pos, 1.0);
  fragPos = vec3(model * vec4(pos, 1.0));
  uv = aTexCoord;
  normal = aNormal;
}
