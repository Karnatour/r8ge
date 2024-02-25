#include "GLConvertor.h"

namespace r8ge {
    namespace video {

        GLenum GLConvertor::convertToGLType(Primitive type) {
            switch(type) {
                case Primitive::UINT8: return GL_UNSIGNED_BYTE;
                case Primitive::UINT16: return GL_UNSIGNED_SHORT;
                case Primitive::UINT32: return GL_UNSIGNED_INT;
                case Primitive::UINT64: return GL_UNSIGNED_INT64_ARB;
                case Primitive::INT8: return GL_BYTE;
                case Primitive::INT16: return GL_SHORT;
                case Primitive::INT32: return GL_INT;
                case Primitive::INT64: return GL_INT64_ARB;
                case Primitive::FLOAT: return GL_FLOAT;
                case Primitive::DOUBLE: return GL_DOUBLE;
            }
            return GL_NONE;
        }

        GLenum GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat format) {
            switch(format){
                case ImageFormat::RGB8: return GL_RGB8;
                case ImageFormat::RGBA8: return GL_RGBA8;
            }
            return GL_NONE;
        }

        GLenum GLConvertor::convertImageFormatToGLFormat(Format format) {
            switch(format){
                case Format::RGB: return GL_RGB;
                case Format::RGBA: return GL_RGBA;
            }
            return GL_NONE;
        }
    }
}