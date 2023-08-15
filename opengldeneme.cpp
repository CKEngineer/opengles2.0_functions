#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
/*https://www.youtube.com/watch?v=XpBGwZNyUh0&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-*/
/*OpenGL Victor Gordan*/

#define SCR_WIDTH 512
#define SCR_HEIGTH 512

/*Pencere küçültülüp büyütüldüğünde içindeki yapıda buna adapte olacaktır (Basic seviye)*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Diğer gerekli adaptasyon işlemleri burada yapılabilir.
}

int main() {
    /*Pencerenin oluşturulması*/
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGTH, "OpenGL ES 2.0 Texture Örneği", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*Dikdörtgenin köşeleri pencerinin üst ve alt köşelerinde birer tane var*/
    GLfloat vertices[] = {
        -0.7f, -0.7f,   // Sol alt köşe
         0.7f, -0.7f,   // Sağ alt köşe
         0.7f,  0.7f,   // Sağ üst köşe
         -0.7f,  0.7f    // Sol üst köşe
    };

    GLuint indices[] = {
        0, 1, 2,   // İlk üçgen
        0, 2, 3    // İkinci üçgen
    };

    GLfloat texCoord[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint texCoordBuffer;
    glGenBuffers(1, &texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    const char* vertexShaderCode =
        "attribute vec2 aPosition;\n"
        "attribute vec2 aTexCoord;\n"
        "varying vec2 vTexCoord;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "    vTexCoord = aTexCoord;\n"
        "}";

    const char* fragmentShaderCode =
        "precision mediump float;\n"
        "varying vec2 vTexCoord;\n"
        "uniform sampler2D uTexture;\n"
        "void main() {\n"
        "    gl_FragColor = texture2D(uTexture, vTexCoord);\n"
        "}";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint aPosition = glGetAttribLocation(shaderProgram, "aPosition");
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(aPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(aPosition);

    GLint aTexCoord = glGetAttribLocation(shaderProgram, "aTexCoord");
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(aTexCoord);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    /*
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    */

    /*Texture oluşturmak için farklı yollar var*/
    /*1.YOL kütüphane stb_image.h başlık dosyasının kullanılması*/

   /*2. YOL Raw data kullanılarak (resmin convert edilmiş hali) kullanılması*/
    unsigned char pixels_of_texture[] = {
255,0,0,0,
255,0,0,1,
255,0,0,2,
255,0,0,3,
255,0,0,4,
255,0,0,5,
255,0,0,6,
255,0,0,7,
255,0,0,8,
255,0,0,9,
255,0,0,10,
255,0,0,11,
255,0,0,12,
255,0,0,13,
255,0,0,14,
255,0,0,15,

255,0,0,16,
255,0,0,17,
255,0,0,18,
255,0,0,19,
255,0,0,20,
255,0,0,21,
255,0,0,22,
255,0,0,23,
255,0,0,24,
255,0,0,25,
255,0,0,26,
255,0,0,27,
255,0,0,28,
255,0,0,29,
255,0,0,30,
255,0,0,31,
255,0,0,32,
255,0,0,33,
255,0,0,34,
255,0,0,35,
255,0,0,36,
255,0,0,37,
255,0,0,38,
255,0,0,39,
255,0,0,40,
255,0,0,41,
255,0,0,42,
255,0,0,43,
255,0,0,44,
255,0,0,45,
255,0,0,46,
255,0,0,47,
255,0,0,48,
255,0,0,49,
255,0,0,50,
255,0,0,51,
255,0,0,52,
255,0,0,53,
255,0,0,54,
255,0,0,55,
255,0,0,56,
255,0,0,57,
255,0,0,58,
255,0,0,59,
255,0,0,60,
255,0,0,61,
255,0,0,62,
255,0,0,63,
255,0,0,64,
255,0,0,65,
255,0,0,66,
255,0,0,67,
255,0,0,68,
255,0,0,69,
255,0,0,70,
255,0,0,71,
255,0,0,72,
255,0,0,73,
255,0,0,74,
255,0,0,75,
255,0,0,76,
255,0,0,77,
255,0,0,78,
255,0,0,79,
255,0,0,80,
255,0,0,81,
255,0,0,82,
255,0,0,83,
255,0,0,84,
255,0,0,85,
255,0,0,86,
255,0,0,87,
255,0,0,88,
255,0,0,89,
255,0,0,90,
255,0,0,91,
255,0,0,92,
255,0,0,93,
255,0,0,94,
255,0,0,95,
255,0,0,96,
255,0,0,97,
255,0,0,98,
255,0,0,99,
255,0,0,100,
255,0,0,101,
255,0,0,102,
255,0,0,103,
255,0,0,104,
255,0,0,105,
255,0,0,106,
255,0,0,107,
255,0,0,108,
255,0,0,109,
255,0,0,110,
255,0,0,111,
255,0,0,112,
255,0,0,113,
255,0,0,114,
255,0,0,115,
255,0,0,116,
255,0,0,117,
255,0,0,118,
255,0,0,119,
255,0,0,120,
255,0,0,121,
255,0,0,122,
255,0,0,123,
255,0,0,124,
255,0,0,125,
255,0,0,126,
255,0,0,127,
255,0,0,128,
255,0,0,129,
255,0,0,130,
255,0,0,131,
255,0,0,132,
255,0,0,133,
255,0,0,134,
255,0,0,135,
255,0,0,136,
255,0,0,137,
255,0,0,138,
255,0,0,139,
255,0,0,140,
255,0,0,141,
255,0,0,142,
255,0,0,143,
255,0,0,144,
255,0,0,145,
255,0,0,146,
255,0,0,147,
255,0,0,148,
255,0,0,149,
255,0,0,150,
255,0,0,151,
255,0,0,152,
255,0,0,153,
255,0,0,154,
255,0,0,155,
255,0,0,156,
255,0,0,157,
255,0,0,158,
255,0,0,159,
255,0,0,160,
255,0,0,161,
255,0,0,162,
255,0,0,163,
255,0,0,164,
255,0,0,165,
255,0,0,166,
255,0,0,167,
255,0,0,168,
255,0,0,169,
255,0,0,170,
255,0,0,171,
255,0,0,172,
255,0,0,173,
255,0,0,174,
255,0,0,175,
255,0,0,176,
255,0,0,177,
255,0,0,178,
255,0,0,179,
255,0,0,180,
255,0,0,181,
255,0,0,182,
255,0,0,183,
255,0,0,184,
255,0,0,185,
255,0,0,186,
255,0,0,187,
255,0,0,188,
255,0,0,189,
255,0,0,190,
255,0,0,191,
255,0,0,192,
255,0,0,193,
255,0,0,194,
255,0,0,195,
255,0,0,196,
255,0,0,197,
255,0,0,198,
255,0,0,199,
255,0,0,200,
255,0,0,201,
255,0,0,202,
255,0,0,203,
255,0,0,204,
255,0,0,205,
255,0,0,206,
255,0,0,207,
255,0,0,208,
255,0,0,209,
255,0,0,210,
255,0,0,211,
255,0,0,212,
255,0,0,213,
255,0,0,214,
255,0,0,215,
255,0,0,216,
255,0,0,217,
255,0,0,218,
255,0,0,219,
255,0,0,220,
255,0,0,221,
255,0,0,222,
255,0,0,223,
255,0,0,224,
255,0,0,225,
255,0,0,226,
255,0,0,227,
255,0,0,228,
255,0,0,229,
255,0,0,230,
255,0,0,231,
255,0,0,232,
255,0,0,233,
255,0,0,234,
255,0,0,235,
255,0,0,236,
255,0,0,237,
255,0,0,238,
255,0,0,239,
255,0,0,240,
255,0,0,241,
255,0,0,242,
255,0,0,243,
255,0,0,244,
255,0,0,245,
255,0,0,246,
255,0,0,247,
255,0,0,248,
255,0,0,249,
255,0,0,250,
255,0,0,251,
255,0,0,252,
255,0,0,253,
255,0,0,254
    };


    

    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, 16,16, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels_of_texture);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    

    glGenerateMipmap(GL_TEXTURE_2D);

    GLint uTexture = glGetUniformLocation(shaderProgram, "uTexture");
    glUniform1i(uTexture, 0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Ekran beyaza boyanır
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &texCoordBuffer);
    glDeleteBuffers(1, &elementBuffer);

    glfwTerminate();
    return 0;
}
