#version 330 core

out highp vec4 color;

in highp vec2 UV;

uniform sampler2D texture0;

void main() {
  color = texture(texture0, UV);
}


//out highp vec4 FragColor;
//
//in highp vec3 ourColor;
//in highp vec2 TexCoord;
//
//// texture sampler
//uniform sampler2D texture1;
//
//void main()
//{
//  FragColor = texture(texture1, TexCoord);
//}
