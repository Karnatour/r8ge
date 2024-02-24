//
// Created by karnatour on 28.1.24.
//

#include "Model.h"

namespace r8ge {
    namespace video {
        Model::Model(const std::string &path) {
            Assimp::Importer importer;
            const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                           aiProcess_FlipUVs |
                                                           aiProcess_CalcTangentSpace);
            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
                R8GE_LOG_ERROR("Assimp Error: {}", importer.GetErrorString());
                return;
            }
            m_directory = path.substr(0, path.find_last_of('/'));
            m_nameVector.emplace_back(path.substr(path.find_last_of('/')));
            connectNodes(scene->mRootNode, scene);
        }

        void Model::connectNodes(aiNode *node, const aiScene *scene) {
            for (unsigned int i = 0; i < node->mNumMeshes; i++) {
                aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                m_meshes.push_back(processMesh(mesh, scene));
            }

            for (unsigned int i = 0; i < node->mNumChildren; i++) {
                connectNodes(node->mChildren[i], scene);
            }
        }

        Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
            std::vector<VertexColorTexture3D> vertices;
            std::vector<unsigned int> indices;
            std::vector<GLTexture> textures;

            for (int i = 0; i < mesh->mNumVertices; ++i) {
                VertexColorTexture3D temp(0.0f, 0.0f, 0.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f),
                                          0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

                temp.x = mesh->mVertices[i].x;
                temp.y = mesh->mVertices[i].y;
                temp.z = mesh->mVertices[i].z;

                if (mesh->HasNormals()) {
                    temp.normal_x = mesh->mNormals[i].x;
                    temp.normal_y = mesh->mNormals[i].y;
                    temp.normal_z = mesh->mNormals[i].z;
                }

                if (mesh->mTextureCoords[0]) {
                    temp.tex_x = mesh->mTextureCoords[0][i].x;
                    temp.tex_y = mesh->mTextureCoords[0][i].y;

                    if (mesh->HasTangentsAndBitangents()) {
                        temp.tangent_x = mesh->mTangents[i].x;
                        temp.tangent_y = mesh->mTangents[i].y;
                        temp.tangent_z = mesh->mTangents[i].z;

                        temp.bitangent_x = mesh->mBitangents[i].x;
                        temp.bitangent_y = mesh->mBitangents[i].y;
                        temp.bitangent_z = mesh->mBitangents[i].z;
                    }
                }


                vertices.push_back(temp);
            }

            for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                aiFace face = mesh->mFaces[i];
                for (unsigned int j = 0; j < face.mNumIndices; j++) {
                    indices.push_back(face.mIndices[j]);
                }
            }

            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<GLTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE,
                                                                      "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<GLTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR,
                                                                       "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            std::vector<GLTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT,
                                                                     "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

            std::vector<GLTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT,
                                                                     "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

            m_nameVector.emplace_back(mesh->mName.C_Str());

            return Mesh(vertices, indices, textures,mesh->mName.C_Str());

        }

        std::vector<GLTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                           const std::string &typeName) {
            std::vector<GLTexture> textures;

            for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
                aiString path;
                mat->GetTexture(type, i, &path);
                if (m_loadedTextureHashSet.count(path.C_Str()) > 0) {

                }
                else {
                    GLTexture tempGLTex(m_directory + '/' + path.C_Str(), true);
                    tempGLTex.setType(typeName);
                    textures.push_back(tempGLTex);
                    m_loadedTextureHashSet.insert(path.C_Str());
                }
            }
            return textures;
        }

        void Model::render(Program &shader,Transformation &transformation) {
            for (unsigned int i = 0; i < m_meshes.size(); i++)
                m_meshes[i].render(shader,transformation);
        }

        std::vector<std::string> Model::m_getNameVector() {
            return m_nameVector;
        }

    } // r8ge
} // video