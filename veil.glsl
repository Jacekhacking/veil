uniform sampler2D sampler;
uniform vec2 resolution;
uniform float hue;
uniform float intensity;

// sRGB to linear
float linearize(float c) {
    return c <= 0.04045 ? c / 12.92 : pow((c + 0.055) / 1.055, 2.4);
}

// linear to sRGB
float delinearize(float c) {
    return c <= 0.0031308 ? c * 12.92 : 1.055 * pow(c, 1.0/2.4) - 0.055;
}

vec3 srgbToOklab(vec3 c){
    vec3 lin = vec3(linearize(c.r), linearize(c.g), linearize(c.b));

    // linear sRGB to LMS
       vec3 lms = mat3(
           0.4122214708, 0.5363325363, 0.0514459929,
           0.2119034982, 0.6806995451, 0.1073969566,
           0.0883024619, 0.2817188376, 0.6299787005
       ) * lin;

       // LMS cube root
       vec3 lms_ = pow(lms, vec3(1.0 / 3.0));

       // LMS to OKLAB
          return mat3(
              0.2104542553, 0.7936177850, -0.0040720468,
              1.9779984951, -2.4285922050, 0.4505937099,
              0.0259040371, 0.7827717662, -0.8086757660
          ) * lms_;
}

vec3 oklabToSrgb(vec3 lab) {
    // OKLAB to LMS
    vec3 lms_ = mat3(
        1.0000000000,  0.3963377774,  0.2158037573,
        1.0000000000, -0.1055613458, -0.0638541728,
        1.0000000000, -0.0894841775, -1.2914855480
    ) * lab;

    // cube
    vec3 lms = lms_ * lms_ * lms_;

    // LMS to linear sRGB
    vec3 lin = mat3(
         4.0767416621, -3.3077115913,  0.2309699292,
        -1.2684380046,  2.6097574011, -0.3413193965,
        -0.0041960863, -0.7034186147,  1.7076147010
    ) * lms;

    // delinearize
    return vec3(delinearize(lin.r), delinearize(lin.g), delinearize(lin.b));
}


void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
       uv.y = 1.0 - uv.y; // flip Y for OpenGL
       vec4 color = texture2D(sampler, uv);

       // convert to OKLAB
       vec3 lab = srgbToOklab(color.rgb);

       // convert to OKLCh
       float L = lab.x;
       float C = sqrt(lab.y * lab.y + lab.z * lab.z);
       float h = atan(lab.z, lab.y);

       // shift hue
       h += radians(hue);

       // convert back to OKLAB
       lab = vec3(L, C * cos(h), C * sin(h));

       // back to sRGB
       vec3 result = oklabToSrgb(lab);

       // blend with original based on intensity
       result = mix(color.rgb, result, intensity);

       gl_FragColor = vec4(clamp(result, 0.0, 1.0), color.a);
}