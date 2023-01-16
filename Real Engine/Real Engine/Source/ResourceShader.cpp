#include "ResourceShader.h"

ResourceShader::ResourceShader(UID uid) : Resource(uid)
{
    type = Resource::Type::Shader;
}
ResourceShader::ResourceShader()
{
    type = Resource::Type::Shader;
}
ResourceShader::~ResourceShader()
{
}

void ResourceShader::SaveData()
{
    std::ofstream out;
    out.open(libraryPath);
    if (out.is_open())
    {
        nlohmann::json shader;
        shader["vertex"] = vertex;
        shader["fragment"] = fragment;
        std::string dump = shader.dump();

        out << dump.c_str();
    }
    out.close();
}

void ResourceShader::LoadData()
{
    std::ifstream in;
    in.open(libraryPath);
    if (in.is_open())
    {
        nlohmann::json shader;
        in >> shader;
        vertex = shader["vertex"].get<std::string>();
        fragment = shader["fragment"].get<std::string>();
    }
    in.close();
}

void ResourceShader::Load()
{
     Load(vertex.string().c_str(), fragment.string().c_str());
}
void ResourceShader::UnLoad()
{
}

bool ResourceShader::Load(const char* vertexPath, const char* fragmentPath)
{
    if (IsLoaded)return true;
    bool ret = true;
    vertex = vertexPath;
    fragment = fragmentPath;

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        ret = false;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        ret = false;
    };

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    //print complie errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
        ret = false;
    }

    // shader Program binding
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
         ret = false;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (ret)
    {
        IsLoaded = true;
    }
    else
    {
        IsLoaded = true;
        std::cout << "Error loading shader" << name.c_str() << "\n\n";
    }

    return ret;
}

void ResourceShader::Use()
{
    glUseProgram(ID);
}

void ResourceShader::StopUse()
{
    glUseProgram(0);
}

void ResourceShader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ResourceShader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ResourceShader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ResourceShader::SetVec3(const std::string& name, vec3& value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void ResourceShader::SetMat4(const std::string& name, float* mat4) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &*mat4);
}

void ResourceShader::SetShaderUniform(GLuint shaderProgram, const char* uniformName, float value)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgram, uniformName);
    if (uniformLocation == -1) {
        std::cerr << "Error: uniform " << uniformName << " not found in shader program" << std::endl;
        return;
    }

    glUseProgram(shaderProgram);
    glUniform1f(uniformLocation, value);
}



void ResourceShader::LoadActiveUniforms()
{
    GLint uniformCount;
    GLint uniformMaxLength;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &uniformCount);
    glGetProgramiv(ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);
    for (int i = 0; i < uniformCount; i++) {
        GLint nameLen, size;
        GLenum type;
        char* uniformName = new char[uniformMaxLength];

        glGetActiveUniform(ID, i, uniformMaxLength, &nameLen, &size, &type, uniformName);
        // Get the location of the uniform
        GLint uniformLocation = glGetUniformLocation(ID, uniformName);
        if (uniformLocation == -1) {
            std::cerr << "Error: uniform " << uniformName << " not found in shader program" << std::endl;
            continue;
        }
        switch (type) {
        case GL_FLOAT:
        {
            float tmp;
            glGetUniformfv(ID, uniformLocation, &tmp);
            SetUniformValue(uniformName, tmp, uniformLocation, type);
        }break;
        case GL_INT:
        {
            int tmp;
            glGetUniformiv(ID, uniformLocation, &tmp);
            SetUniformValue(uniformName, tmp, uniformLocation, type);
        }break;
        case GL_UNSIGNED_INT:
        {
            unsigned int tmp;
            glGetUniformuiv(ID, uniformLocation, &tmp);
            SetUniformValue(uniformName, tmp, uniformLocation, type);
        }break;
        case GL_BOOL:
        {
    
        } break;
        case GL_FLOAT_VEC2:
        {
            vec2 tmp;
            glGetUniformfv(ID, uniformLocation, &tmp);
            SetUniformValue(uniformName, tmp, uniformLocation, type);
        }break;
        case GL_FLOAT_VEC3:
        {
            vec3 tmp;
            glGetUniformfv(ID, uniformLocation, &tmp);
            SetUniformValue(uniformName, tmp, uniformLocation, type);
        }break;
        default:
            std::cerr << "Error: uniform " << uniformName << " has unsupported type" << std::endl;
            break;
        }
    }
}

void ResourceShader::UpdateUniformValues()
{
    for (auto uniform : uniforms)
    {
        ImGui::Text(uniform.name.c_str());
        switch (uniform.type)
        {
        case GL_FLOAT:
        {

          if (ImGui::SliderFloat(uniform.name.c_str(), &std::get<float>(uniform.value), 0.0f, 1.0f))
          {
              glUniform1f(uniform.location, std::get<float>(uniform.value));
          }
        }break;
        case GL_INT:
        {

           if (ImGui::SliderInt(uniform.name.c_str(), &std::get<int>(uniform.value), 0.0f, 100.0f))
           {
               glUniform1i(uniform.location, std::get<int>(uniform.value));
           }
        }break;   
        case GL_FLOAT_VEC3:
        {   
           //if (ImGui::SliderFloat3("##X", &std::get<vec3>(uniform.value), 0.0f, 1.0f))
           //{
           //    glUniform3f(uniform.location, std::get<vec3>(uniform.value).r, std::get<vec3>(uniform.value).g, std::get<vec3>(uniform.value).b);
           //    std::cout << "value: " << std::get<vec3>(uniform.value).r << " " << std::get<vec3>(uniform.value).g << " " << std::get<vec3>(uniform.value).b << "\n";
           //}
           if (ImGui::SliderFloat3("##X", &color, 0.0f, 1.0f))
           {
             
               SetVec3(uniform.name, color);
             
           }

        }break;
        case GL_UNSIGNED_INT:
        {
            //ImGui::SliderInt(uniform.name.c_str(), (float)&uniform.value, 0.0f, 1.0f);
        }break;
        case GL_BOOL:
        {
        } break;
        }
    }
   

}

void ResourceShader::LoadUniform(std::string location)
{
    GLint uniformLocation = glGetUniformLocation(ID, location.c_str());
    if (uniformLocation != -1) {
        GLint size;
        GLenum type;
        GLchar name[64];
        GLsizei nameLength;
        glGetActiveUniform(ID, uniformLocation, sizeof(name), &nameLength, &size, &type, name);

        // Check the type of the uniform
        switch (type) {
        case GL_FLOAT:
        {
            GLfloat tmp;
            glGetUniformfv(ID, uniformLocation, &tmp);
            SetUniformValue(location, tmp, uniformLocation, type);
        }break;
        case GL_INT:
        {
            GLint tmp;
            glGetUniformiv(ID, uniformLocation, &tmp);
            SetUniformValue(location, tmp, uniformLocation, type);
        }break;
        case GL_UNSIGNED_INT:
        { 
            unsigned int tmp;
            glGetUniformuiv(ID, uniformLocation, &tmp);
            SetUniformValue(location, tmp, uniformLocation, type);
        }break;
        case GL_BOOL:
        {  
            //unsigned int tmp;
            //glUniform1i(uniformLocation,tmp);
            //SetUniformValue(location, tmp, type);
        } break;
        case GL_FLOAT_VEC3:
            vec3 tmp;
            glGetUniformfv(ID, uniformLocation, &tmp);
            SetUniformValue(location, tmp, uniformLocation, type);
            break;
        }
    }
}
