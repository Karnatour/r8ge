#ifndef R8GE_VERTEX_H
#define R8GE_VERTEX_H

#include "Color.h"
#include "../renderingService/buffers/VertexBufferLayout.h"

#include <vector>

namespace r8ge {
    struct Vertex {
        Vertex(coord_float x, coord_float y);

        virtual ~Vertex() = default;

        [[nodiscard]] virtual video::VertexBufferLayout getLayout() const;

        [[nodiscard]] virtual std::vector<uint8_t> getRawData() const;

        [[nodiscard]] virtual size_t getSize() const;

        coord_float x, y;
    };

    struct Vertex3D : public Vertex {
        Vertex3D(coord_float x, coord_float y, coord_float z);

        ~Vertex3D() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        coord_float z;
    };

    struct VertexTexture : public Vertex {
        VertexTexture(coord_float x, coord_float y, texture_coord tex_x, texture_coord tex_y);

        ~VertexTexture() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        texture_coord tex_x, tex_y;
    };

    struct VertexTexture3D : public Vertex {
        VertexTexture3D(coord_float x, coord_float y, coord_float z, texture_coord tex_x, texture_coord tex_y);

        ~VertexTexture3D() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        coord_float z;
        texture_coord tex_x, tex_y;
    };

    struct VertexColor : public Vertex {
        VertexColor(coord_float x, coord_float y, ColorRGBA rgba);

        ~VertexColor() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        ColorRGBA rgba;
    };

    struct VertexColor3D : public Vertex {
        VertexColor3D(coord_float x, coord_float y, coord_float z, ColorRGBA rgba);

        ~VertexColor3D() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        ColorRGBA rgba;
        coord_float z;
    };

    struct VertexColorTexture : public Vertex {
        VertexColorTexture(coord_float x, coord_float y, ColorRGBA rgba, texture_coord tex_x,
                           texture_coord tex_y);

        ~VertexColorTexture() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        ColorRGBA rgba;
        texture_coord tex_x, tex_y;

    };
    //This is main structure of video
    struct VertexColorTexture3D : public Vertex {
        VertexColorTexture3D(coord_float x, coord_float y, coord_float z, ColorRGBA rgba, texture_coord tex_x,
                             texture_coord tex_y,normal_float normal_x, normal_float normal_y,
                             normal_float normal_z,tangent_float tangent_x, tangent_float tangent_y,
                             tangent_float tangent_z,bitangent_float bitangent_x,bitangent_float bitangent_y,
                             bitangent_float bitangent_z);

        ~VertexColorTexture3D() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        coord_float z;
        ColorRGBA rgba;
        texture_coord tex_x, tex_y;
        normal_float normal_x,normal_y,normal_z;
        tangent_float tangent_x,tangent_y,tangent_z;
        bitangent_float bitangent_x,bitangent_y,bitangent_z;
    };

}

#endif//!R8GE_VERTEX_H
