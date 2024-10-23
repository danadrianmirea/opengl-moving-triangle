#pragma once

namespace engine::math
{
    struct vec3
    {
        void add(vec3 v2) { x += v2.x;  y += v2.y, z += v2.z; }
        void h_product(vec3 v2) { x *= v2.x;  y *= v2.y, z *= v2.z; }
        float x;
        float y;
        float z;
    };
}