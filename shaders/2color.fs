#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

// 4x4 Bayer ordered dithering matrix
float bayer4x4(vec2 p)
{
    ivec2 ip = ivec2(mod(p, 4.0));
    int idx = ip.y * 4 + ip.x;
    const float M[16] = float[16](
         0.0,  8.0,  2.0, 10.0,
        12.0,  4.0, 14.0,  6.0,
         3.0, 11.0,  1.0,  9.0,
        15.0,  7.0, 13.0,  5.0
    );
    return (M[idx] + 0.5) / 16.0;
}

void main()
{
    vec2 texSize = vec2(textureSize(texture0, 0));
    
    // Sample original color
    vec3 col = texture(texture0, fragTexCoord).rgb * colDiffuse.rgb * fragColor.rgb;

    // Convert to luminance (perceived brightness)
    float lum = dot(col, vec3(0.299, 0.587, 0.114));

    // Ordered dithering threshold
    float threshold = bayer4x4(fragTexCoord * texSize);

    // Decide black or white based on dither threshold
    float bw = (lum > threshold) ? 1.0 : 0.0;
    if(bw == 1.0){
        finalColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
    else{
        finalColor = vec4(0.1, 0.1, 0.1, 1.0);
    }
    
}
