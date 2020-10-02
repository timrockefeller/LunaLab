#pragma once
#include <Core/OpenGL/Shader.h>
#include <Core/OpenGL/Texture.h>
#include <Core/OpenGL/VAO.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

namespace LUNA {
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
   public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(std::vector<Vertex> &vertices,
         std::vector<unsigned int>& indices,
         std::vector<Texture> &textures);
    void Draw(Shader shader);
    ~Mesh();

   private:
    // VAO vao;
    unsigned int meshVAO;
    unsigned int meshVBO;
    unsigned int meshEBO;
    
    void setupMesh();
};

}  // namespace LOGL
