#include "VertexBufferLayout.h"


namespace r8ge {
    namespace video {
        VertexBufferLayout::VertexBufferLayout() : m_layout({}) {}

        VertexBufferLayout::Layout VertexBufferLayout::getLayout() const { return m_layout; }

        VertexBufferLayout::VertexBufferLayout(const Layout& layout) : m_layout(layout) {}
        VertexBufferLayout::VertexBufferLayout(VertexBufferLayout::Layout &&layout) : m_layout(std::move(layout)) {}

        void VertexBufferLayout::setLayout(const Layout& layout){ m_layout = layout; }
        void VertexBufferLayout::setLayout(Layout&& layout){ m_layout = std::move(layout); }

        std::string VertexBufferLayout::EntryTypeToString(VertexBufferLayout::Entry type) {
            switch (type) {
                // TODO: Document, important for shader creation
                case VertexBufferLayout::Entry::COLOUR_RGB: return "colourRGB";
                case VertexBufferLayout::Entry::COLOUR_RGBA: return "colourRGBA";
                case VertexBufferLayout::Entry::POS_XY: return "positionXY";
                case VertexBufferLayout::Entry::POS_XYZ: return "positionXYZ";
                case VertexBufferLayout::Entry::TEXTURE_XY: return "textureXY";
                case VertexBufferLayout::Entry::NORMAL_XYZ: return "normalXYZ";
                case VertexBufferLayout::Entry::TANGENT_XYZ: return "tangentXYZ";
                case VertexBufferLayout::Entry::BITANGENT_XYZ: return "bitangentXYZ";
            }

            R8GE_LOG_ERROR("Unknown layout entry type to string");
            return "Unknown";
        }

        uint8_t VertexBufferLayout::EntryTypeSize(VertexBufferLayout::Entry type) {
            uint8_t size = EntryTypeComponents(type) * r8ge::size(EntryTypeToDataType(type));
            return size;
        }

        uint8_t VertexBufferLayout::EntryTypeComponents(VertexBufferLayout::Entry type) {
            switch (type) {
                case VertexBufferLayout::Entry::COLOUR_RGB: return 3;
                case VertexBufferLayout::Entry::COLOUR_RGBA: return 4;
                case VertexBufferLayout::Entry::POS_XY: return 2;
                case VertexBufferLayout::Entry::POS_XYZ: return 3;
                case VertexBufferLayout::Entry::TEXTURE_XY: return 2;
                case VertexBufferLayout::Entry::NORMAL_XYZ: return 3;
                case VertexBufferLayout::Entry::TANGENT_XYZ: return 3;
                case VertexBufferLayout::Entry::BITANGENT_XYZ: return 3;

            }

            R8GE_LOG_ERROR("Unknown layout component count in entry type");
            return 0;
        }


        uint32_t VertexBufferLayout::getStride() const {
            uint32_t stride = 0;
            for(auto& entry : m_layout) {
                stride += EntryTypeSize(entry);
            }
            return stride;
        }

        bool VertexBufferLayout::EntryTypeShouldBeNormalized(VertexBufferLayout::Entry type) {
            switch (type) {
                case VertexBufferLayout::Entry::COLOUR_RGB: return false;
                case VertexBufferLayout::Entry::COLOUR_RGBA: return false;
                case VertexBufferLayout::Entry::POS_XY: return false;
                case VertexBufferLayout::Entry::POS_XYZ: return false;
                case VertexBufferLayout::Entry::TEXTURE_XY: return false;
                case VertexBufferLayout::Entry::NORMAL_XYZ: return false;
                case VertexBufferLayout::Entry::TANGENT_XYZ: return false;
                case VertexBufferLayout::Entry::BITANGENT_XYZ: return false;
            }

            R8GE_LOG_ERROR("Unknown layout entry type normalization");
            return false;
        }

        Primitive VertexBufferLayout::EntryTypeToDataType(VertexBufferLayout::Entry type) {
            switch (type) {
                case VertexBufferLayout::Entry::COLOUR_RGB: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::COLOUR_RGBA: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::POS_XY: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::POS_XYZ: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::TEXTURE_XY: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::NORMAL_XYZ: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::TANGENT_XYZ: return Primitive::FLOAT;
                case VertexBufferLayout::Entry::BITANGENT_XYZ: return Primitive::FLOAT;
            }

            R8GE_LOG_ERROR("Unknown layout entry type data type");
        }
    }
}