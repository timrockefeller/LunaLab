#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace LUNA {
class Shader {
   public:
    Shader(const std::string& vertexShaderPath,
           const std::string& fragmentShaderPath);
    ~Shader();
    void Use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3f(const std::string& name, float v1, float v2, float v3);
    void setVec3f(const std::string& name, glm::vec3 vec);
    void setMat4f(const std::string& name, const float* matValue) const;
    void setMat4f(const std::string& name, glm::mat4 mat4) const;
    unsigned int GetID() const;
    bool isValid() const;

   private:
    unsigned int ID;
};
}  // namespace LOGL
