#version 330 core

precision highp float;
precision highp sampler2D;

in vec3 fragPos;
in vec2 uv;
in vec3 normal;

uniform sampler2D texture0;
out vec4 color;

#define MINECRAFT_LIGHT_POWER   (0.6)
#define MINECRAFT_AMBIENT_LIGHT (0.4)

vec4 minecraft_mix_light(vec3 lightDir0, vec3 normal, vec4 color) {
  lightDir0 = normalize(lightDir0);
  float light0 = max(0.0, dot(lightDir0, normal));
  float lightAccum = min(1.0, (light0) * MINECRAFT_LIGHT_POWER + MINECRAFT_AMBIENT_LIGHT);
  return vec4(color.rgb * lightAccum, color.a);
}

vec3 lightDir = normalize(vec3(-0.4,1,-0.2));

void main() {
  vec4 objectColor =  texture(texture0, uv);
  color = minecraft_mix_light(lightDir, normal, objectColor);
}
