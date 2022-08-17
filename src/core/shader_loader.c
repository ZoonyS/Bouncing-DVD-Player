#include "core/shader_loader.h"

static GLuint loadShaderFromFile(GLchar* shaderPath, GLenum shaderType);
static GLchar *readFile(GLchar* filePath);

GLuint loadShaderProgramFromFile(GLchar* vertexPath, GLchar* fragmentPath)
{
    GLuint vertexShader;
    if (!(vertexShader = loadShaderFromFile(vertexPath, GL_VERTEX_SHADER)))
    {
        return 0;
    }
    
    GLuint fragmentShader;
    if (!(fragmentShader = loadShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER)))
    {
        glDeleteShader(vertexShader);
        return 0;
    }

    GLuint program;
    if (!(program = glCreateProgram()))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program); // link compiled shaders to program object

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar *infoLog = (GLchar *) malloc(maxLength);
        if (infoLog)
        {
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
            printf("%s\n", infoLog);
            free(infoLog);
        }
        else
        {
            printf("Failed to allocate memory for info log\n");
        }
        
        glDeleteProgram(program);
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}



static GLuint loadShaderFromFile(GLchar* shaderPath, GLenum shaderType)
{
    GLchar *shaderSource = readFile(shaderPath);
    if (!shaderSource)
    {
        return 0;
    }

    GLuint shader;
    if (!(shader = glCreateShader(shaderType)))
    {
        free(shaderSource);
        return 0;
    }

    glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);
    glCompileShader(shader);
    free(shaderSource);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar *infoLog = (GLchar *) malloc(maxLength);
        if (infoLog)
        {
            glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);
            printf("%s\n", infoLog);
            free(infoLog);
        }
        else
        {
            printf("Failed to allocate memory for info log\n");
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLchar *readFile(GLchar* filePath)
{
    FILE *file = fopen(filePath, "r");
    if (!file)
    {
        perror("Failed to open file");
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0)
    {
        perror("Failed to seek to end of file");
        fclose(file);
        return NULL;
    }

    long fileSize = ftell(file);
    if (fileSize == -1)
    {
        perror("Failed to get file size");
        fclose(file);
        return NULL;
    }
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        perror("Failed to seek to start of file");
        fclose(file);
        return NULL;
    }

    GLchar *fileSource = (GLchar *) malloc(fileSize + 1);
    if (!fileSource)
    {
        printf("Failed to allocate memory for shader source\n");
        fclose(file);
        return NULL;
    }

    int totalRead = 0;
    while (totalRead < fileSize)
    {
        int read = fread(fileSource + totalRead, 1, fileSize - totalRead, file);
        if (ferror(file) && errno != EINTR)
        {
            perror("Failed to read file");
            fclose(file);
            free(fileSource);
            return NULL;
        }
        
        totalRead += read;
    }
    fileSource[fileSize] = '\0';
    fclose(file);

    return fileSource;
}
