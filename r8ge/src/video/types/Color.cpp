#include "Color.h"

namespace r8ge {
    ColorRGBA::ColorRGBA(float _r, float _g, float _b, float _a) : ColorRGB(_r, _g, _b), a(_a) {}

    ColorRGB::ColorRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

}