#pragma once
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"
#include "Texture.hpp"
#include <glimac/Image.hpp>

class Model 
{
    public:
        Model();
        Model(string path, string shader_name, float rotate_angle, float rotate_x, float rotate_y, float rotate_z, float translate_x, float translate_y, float translate_z, float scale);
        void Draw(Shader shader);   
        string shader_name;
        float rotate_angle, rotate_x, rotate_y, rotate_z;
        float translate_x, translate_y, translate_z;
        float scale;
        vector<Mesh> meshes;
        vector<Texture> textures_loaded;

    private:
        
        string directory;
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        GLint TextureFromFile(const char* path, string directory);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
