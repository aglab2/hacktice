#pragma once

#define vec2_quot_val(dst, src, x) {    \
    (dst)[0] = ((src)[0] / (x));        \
    (dst)[1] = ((src)[1] / (x));        \
}
#define vec3_quot_val(dst, src, x) {    \
    vec2_quot_val((dst), (src), (x));   \
    (dst)[2] = ((src)[2] / (x));        \
}

#define vec2_copy(dst, src) {           \
    (dst)[0] = (src)[0];                \
    (dst)[1] = (src)[1];                \
}
#define vec3_copy(dst, src) {           \
    vec2_copy((dst), (src));            \
    (dst)[2] = (src)[2];                \
}

#define vec2_prod_val(dst, src, x) {    \
    (dst)[0] = ((src)[0] * (x));        \
    (dst)[1] = ((src)[1] * (x));        \
}
#define vec3_prod_val(dst, src, x) {    \
    vec2_prod_val((dst), (src), (x));   \
    (dst)[2] = ((src)[2] * (x));        \
}

#define vec2_c(v)           (   (v)[0] + (v)[1])
#define vec3_c(v)           (vec2_c(v) + (v)[2])

#define vec2_average(v)     (vec2_c(v) / 2.0f)
#define vec3_average(v)     (vec3_c(v) / 3.0f)

#define vec2_same(v, s)     (((v)[0]) = ((v)[1])                       = (s))
#define vec3_same(v, s)     (((v)[0]) = ((v)[1]) = ((v)[2])            = (s))
