#ifndef R8GE_COLOR_H
#define R8GE_COLOR_H

#include <cstdint>
#include <string>

namespace r8ge {
    using coord_pixel = uint16_t;
    using coord_float = float;
    using texture_coord = float;
    using normal_float = float;
    using tangent_float = float;
    using bitangent_float = float;

#ifdef _MSC_VER
#pragma pack(push, 1)
    struct ColorRGB {
        float r;
        float g;
        float b;

        ColorRGB(float _r, float _g, float _b);
    };

    struct ColorRGBA : public ColorRGB {
        ColorRGBA(float _r, float _g, float _b, float _a);

        float a;
    };
}


#pragma pack(pop)
#elif
    struct ColorRGB {
    float r;
    float g;
    float b;

    ColorRGB(float _r, float _g, float _b);
}__attribute__((packed));

    struct ColorRGBA : public ColorRGB {
        ColorRGBA(float _r, float _g, float _b, float _a);

        float a;
    }__attribute__((packed));
}
#endif

#endif//!R8GE_COLOR_H
