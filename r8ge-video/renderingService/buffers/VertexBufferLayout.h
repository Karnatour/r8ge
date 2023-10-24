#ifndef R8GE_VERTEXBUFFERLAYOUT_H
#define R8GE_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <string>
#include <cstdint>

#include "../../types/Primitives.h"

namespace r8ge
{
    namespace video {
        class VertexBufferLayout final {
        public:
            // Each entry in the layout is a type,
            // which is used to determine the size of the data
            // and how to interpret it, normalize it, etc.
            // Rendering API then uses this information to
            // determine how to interpret the data in the program (shader).
            // f.e.: - POS_XYZ is 3 x FLOAT, so it is 3 x 4 bytes = 12 bytes,
            //         but the position is in world space coordinates, it is not normalized,
            //         position is converted to screen space coordinates by the shader program
            //         using the projection matrix in shader program passed from uniforms (great
            //         for performance)
            //
            //       - COLOUR_RGB is 3 x U8CHAR, so it is 3 x 1 byte = 3 bytes,
            //         data is then normalized to 0.0 - 1.0 range, so it is
            //         0 - 255 range, and then it is converted to 0.0 - 1.0 range
            //         by the renderingAPI program
            //
            // NOTE: Most game data should have similar layout, because
            //       every layout uses different shader program.
            //       This is not a problem, but it may result in smaller FPS
            //       because of the need to switch between programs and thus
            //       more draw calls.
            //
            // TODO: Add more types, like: POS_XYZW, COLOUR_RGBF, COLOUR_RGBAF, etc.
            enum Entry : uint8_t {
                POS_XY,      // Basic 2 x FLOAT, should be used for 2D games and 2D rendering (like GUI)
                POS_XYZ,     // Basic 3 x FLOAT, should be used for 3D games and 3D rendering (like 3D models: .obj, .fbx, etc.)
                COLOUR_RGB,  // Basic 3 x U8CHAR, should be used for RGB colours, !0-255 values only!,
                COLOUR_RGBA, // Basic 4 x U8CHAR, should be used for RGBA colours, !0-255 values only!, Alpha channel is used for transparency
                TEXTURE_UV   // Basic 2 x FLOAT, should be used for texture coordinates, !0.0 - 1.0 values only!
            };

            // Layout is a vector of LayoutEntryType
            // f.e.: Vector: { POS_XYZ, COLOUR_RGB, COLOUR_RGBA, ... }
            using Layout = std::vector<Entry>;

            VertexBufferLayout();

            VertexBufferLayout(const Layout &layout);

            VertexBufferLayout(Layout &&layout);

            // Returns the layout
            [[nodiscard]] Layout getLayout() const;

            // Set the layout by copy
            void setLayout(const Layout &layout);

            // Set the layout, with move semantics
            void setLayout(Layout &&layout);

            // Returns the size of the layout in bytes
            [[nodiscard]] uint32_t getStride() const;

            // Returns string representation of the type
            static std::string EntryTypeToString(Entry type);

            // Returns size of the type in bytes
            static uint8_t EntryTypeSize(Entry type);

            // Returns number of components of the type
            static uint8_t EntryTypeComponents(Entry type);

            // Returns wheter the type shlould be normalized
            static bool EntryTypeShouldBeNormalized(Entry type);

            // Returns the data type of the entry
            static Primitive EntryTypeToDataType(VertexBufferLayout::Entry type);
        protected:
            Layout m_layout;
        };
    }
} // R8GE

#endif//!R8GE_VERTEXBUFFERLAYOUT_H
