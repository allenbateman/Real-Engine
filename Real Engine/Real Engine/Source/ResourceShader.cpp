#include "ResourceShader.h"

ResourceShader::ResourceShader(UID uid) : Resource(uid)
{
    type = Resource::Type::Shader;
}
ResourceShader::~ResourceShader()
{
}

void ResourceShader::SaveData()
{
}

void ResourceShader::LoadData()
{
}

void ResourceShader::Load()
{
    if(!IsLoaded)
     Load(vertex.string().c_str(), fragment.string().c_str());
}
void ResourceShader::UnLoad()
{
}

bool ResourceShader::Load(const char* vertexPath, const char* fragmentPath)
{
    bool ret = true;
    this->vertex = vertexPath;
    this->fragment = fragmentPath;

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
    IsLoaded = true;
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

std::unordered_map<std::string, float> ResourceShader::GetShaderUniforms(GLuint shaderProgram)
{
    std::unordered_map<std::string, float> uniforms;

    GLint uniformCount;
    GLint uniformMaxLength;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniformCount);
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);

    for (int i = 0; i < uniformCount; i++) {
        GLsizei length;
        GLint size;
        GLenum type;
        char* uniformName = new char[uniformMaxLength];
        glGetActiveUniform(shaderProgram, i, uniformMaxLength, &length, &size, &type, uniformName);

        // Get the location of the uniform
        GLint uniformLocation = glGetUniformLocation(shaderProgram, uniformName);
        if (uniformLocation == -1) {
            std::cerr << "Error: uniform " << uniformName << " not found in shader program" << std::endl;
            continue;
        }
        // Get the value of the uniform
        float value = 0;
        switch (type) {
        case GL_FLOAT: {
            glGetUniformfv(shaderProgram, uniformLocation, &value);
            break;
        }
        case GL_INT: {
            int ivalue;
            glGetUniformiv(shaderProgram, uniformLocation, &ivalue);
            value = (float)ivalue;
            break;
        }
        case GL_UNSIGNED_INT: {
            unsigned int uivalue;
            glGetUniformuiv(shaderProgram, uniformLocation, &uivalue);
            value = (float)uivalue;
            break;
        }
        default:
            std::cerr << "Error: uniform " << uniformName << " has unsupported type" << std::endl;
            continue;
        }
        uniforms[uniformName] = value;
    }
    return uniforms;
}
