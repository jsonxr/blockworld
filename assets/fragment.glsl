#version 330 core

out highp vec4 FragColor;

uniform highp vec4 ourColor;

void main() {
  //  FragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);
  FragColor = ourColor;
}
