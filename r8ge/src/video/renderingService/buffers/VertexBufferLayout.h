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
            enum Entry : uint8_t {
                POS_XY,         // Basic 2 x FLOAT, should be used for 2D games and 2D rendering (like GUI)
                POS_XYZ,        // Basic 3 x FLOAT, should be used for 3D games and 3D rendering (like 3D models: .obj, .fbx, etc.)
                COLOUR_RGB,     // Basic 3 x FLOAT, should be used for RGB colours, !0.0 - 1.0 values only!
                COLOUR_RGBA,    // Basic 4 x FLOAT, should be used for RGBA colours, !0.0 - 1.0 values only!, Alpha channel is used for transparency
                TEXTURE_XY,     // Basic 2 x FLOAT, should be used for texture coordinates, !0.0 - 1.0 values only!
                NORMAL_XYZ,     // Basic 3 x FLOAT, should be used for normal attributes -> TBN matrix
                TANGENT_XYZ,    // Basic 3 x FLOAT, should be used for tangent attributes -> TBN matrix
                BITANGENT_XYZ   // Basic 3 x FLOAT, should be used for bitangent attributes -> TBN matrix
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
