#version 150
// A texture is expected as program attribute
uniform sampler2D Texture;
uniform float Offset;

// The vertex shader fill feed this input
in vec2 FragTexCoord;

// The final color
out vec4 FragmentColor;

vec3 h_color_top = vec3(-0.5, 0.1, 1);
vec3 h_color_bottom = vec3(0.7, 0.7, 1);

void main() {
  // Lookup the color in Texture on coordinates given by fragTexCoord
  //FragmentColor = texture(Texture, FragTexCoord+vec2(0, Offset));
  //FragmentColor = texture(Texture, FragTexCoord+vec2(Offset,0));
  FragmentColor = vec4(h_color_top * (gl_FragCoord.y / 1080), 1) + vec4(h_color_bottom * (1.4 - (gl_FragCoord.y / 1080)), 1);
}
