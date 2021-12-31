#version 330 core

out highp vec4 FragColor;

in highp vec3 ourColor;
in highp vec2 TexCoord;

uniform sampler2D texture0;

void main() {
  FragColor = texture(texture0, TexCoord);
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
