#version 330 core
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

const float gamma = 5.2;

vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0., -1./3., 2./3., -1.);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.*d+e)), d/(q.x+e), q.x);
}

vec3 hsv2rgb(vec3 c) {
    vec3 p = abs(fract(c.xxx + vec3(0., 2./3., 1./3.)) * 6. - 3.);
    return c.z * mix(vec3(1.), clamp(p - 1., 0., 1.), c.y);
}

void main()
{
    vec3 col = texture(texture0, fragTexCoord).rgb * colDiffuse.rgb * fragColor.rgb;
    col = pow(col, vec3(1.0 / gamma)); // gamma-correct to linear

    vec3 hsv = rgb2hsv(col);

    // Shift hue toward purple/pink (~300°)
    float targetHue = 300.0 / 360.0; 
    hsv.x = mix(hsv.x, targetHue, 0.25);

    // Desaturate highlights
    hsv.y *= mix(1.0, 0.6, hsv.z);

    // Slightly boost midtone contrast
    hsv.z = smoothstep(0.2, 0.8, hsv.z);

    col = hsv2rgb(hsv);
    col = pow(col, vec3(gamma)); // back to sRGB

    // Optional: subtle vignette to darken edges
    vec2 uv = fragTexCoord * 2.0 - 1.0;
    float v = smoothstep(1.3, 0.7, dot(uv, uv));
    col *= mix(1.0, 0.85, v);

    finalColor = vec4(col, 1.0);
}
