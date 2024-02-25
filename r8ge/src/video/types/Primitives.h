#ifndef R8GE_PRIMITIVES_H
#define R8GE_PRIMITIVES_H

#include <string>


namespace r8ge {

    // TODO: move to core
    enum Primitive {
        UINT8,UINT16,UINT32,UINT64,
        INT8,INT16,INT32,INT64,
        FLOAT, DOUBLE
    };

    std::string to_string(Primitive type);
    size_t size(Primitive type);
}

#endif//!R8GE_PRIMITIVES_H
