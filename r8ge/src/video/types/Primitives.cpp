#include "Primitives.h"

#include <cstdint>

namespace r8ge {
    std::string to_string(Primitive type) {
        switch (type) {
            case UINT8: return "UINT8";
            case UINT16: return "UINT16";
            case UINT32: return "UINT32";
            case UINT64: return "UINT64";
            case INT8: return "INT8";
            case INT16: return "INT16";
            case INT32: return "INT32";
            case INT64: return "INT64";
            case FLOAT: return "FLOAT";
            case DOUBLE: return "DOUBLE";
        }

        return "UNKNOWN";
    }

    size_t size(Primitive type) {
        switch (type) {
            case UINT8: return sizeof(uint8_t);
            case UINT16: return sizeof(uint16_t);
            case UINT32: return sizeof(uint32_t);
            case UINT64: return sizeof(uint64_t);
            case INT8: return sizeof(int8_t);
            case INT16: return sizeof(int16_t);
            case INT32: return sizeof(int32_t);
            case INT64: return sizeof(int64_t);
            case FLOAT: return sizeof(float);
            case DOUBLE: return sizeof(double);
        }

        return 0;
    }
}
