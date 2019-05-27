#ifndef ECS_RENDERING_SHADER_H
#define ECS_RENDERING_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>

#include "system/common.hpp"
#include "dataStructures.hpp"

class Shader
{
public:
    Shader();
    Shader(const String& name);
    virtual ~Shader();
    
    void initShader(const String& name);

    void use();

    void setBool(const String& name, bool v0);
    void setInt(const String& name, int v0);
    void setFloat(const String& name, float v0);

    void setVec2(const String& name, float v0, float v1);
    void setVec3(const String& name, float v0, float v1, float v2);
    void setVec4(const String& name, float v0, float v1, float v2, float v3);

    void setVec2(const String& name, const glm::vec2& v);
    void setVec3(const String& name, const glm::vec3& v);
    void setVec4(const String& name, const glm::vec4& v);

    void setMat3(const String& name, const glm::mat3& m0);
    void setMat4(const String& name, const glm::mat4& m0);

private:
    enum
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        NUM_SHADERS
    };

    uint32 program;
    uint32 shaders[NUM_SHADERS];

    uint32 createShader(const String& name, GLenum type);
    String loadShader(const String& path);

    // Private Functions
    void checkErrors(uint32 program, bool type);
};

#endif // ECS_RENDERING_SHADER_H
