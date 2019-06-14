#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include <GL/glew.h>
#include <chrono>

#include <chrono>
#include <thread>

#include "game.h"
#include "key_event_manager.h"

#define M_PI       3.14159265358979323846
#define WIDTH 320 
#define HEIGHT 180

 
// Data for triangle 1
float vertices1[] = {   -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0, 1.0f,
            -1.0f, -1.0f, 0, 1.0f};
 
float colors1[] = { 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f,0.0f, 1.0f, 1.0f};
 
// Data for triangle 2
float vertices2[] = {   1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 1.0f};
 
float colors2[] = { 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f,0.0f, 0.0f, 1.0f};
            
            
// Program and Shader Identifiers
GLuint p,v,f;
 
// Vertex Attribute Locations
GLuint vertexLoc, colorLoc;
 
// Vertex Array Objects Identifiers
GLuint vao[2];

GLuint tex;
 

int width = WIDTH;
int height = HEIGHT;

struct run_info{
    bool exited = false;
    bool allow_draw = true;
} run_state;
pthread_t raytracerThread;

int frame=0, timebase=0;
game g(WIDTH,HEIGHT);

// ----------------------------------------------------
 
void changeSize(int w, int h) {
 
    //float ratio;
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;
 
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    //ratio = (1.0f * w) / h;
    width = w;
    height = h;
}
 
void setup_buffers() {
 
    GLuint buffers[2];
 
    glGenVertexArrays(2, vao);
    //
    // VAO for first triangle
    //
    glBindVertexArray(vao[0]);
    // Generate two slots for the vertex and color buffers
    glGenBuffers(2, buffers);
    // bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
 
    // bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
 
    //
    // VAO for second triangle
    //
    glBindVertexArray(vao[1]);
    // Generate two slots for the vertex and color buffers
    glGenBuffers(2, buffers);
 
    // bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
 
    // bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
 
    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}
 
void update_buffer(void) {
    //Has updated since last draw?
    if(!run_state.allow_draw){
        return;
    }
    
//     frame++;
// 	int time=glutGet(GLUT_ELAPSED_TIME);
// 	if (time - timebase > 1000) {
// 		printf(" FPS:%4.2f\n",
// 			frame*1000.0/(time-timebase));
// 		timebase = time;
// 		frame = 0;
// 	}
 
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, WIDTH, HEIGHT, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, g.get_framebuffer());
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glUseProgram(p);
    int uniform_ScreenDim = glGetUniformLocation(p, "ScreenDim");
    glUniform2f(uniform_ScreenDim, width, height);
    //setUniforms();
 
    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
    glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
    glutSwapBuffers();
    //Wait for game update before drawing again
    run_state.allow_draw = false;
}
 
void processNormalKeys(unsigned char key, int x, int y) {
    (void) x;
    (void) y;
 
    if (key == 27) {
        glDeleteVertexArrays(3,vao);
        glDeleteProgram(p);
        glDeleteShader(v);
        glDeleteShader(f);
        exit(0);
    }
    key_event_manager::get_instance()->set_key_press(key);
}


void processNormalKeysUp(unsigned char key, int x, int y) {
    key_event_manager::get_instance()->reset_key_press(key);
    (void) x;
    (void) y;
}
 
#define printOpenGLError() printOglError(__FILE__, __LINE__)
 
int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;
 
    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}
 
void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 
void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 
GLuint setup_shaders() {
 
    std::string vs,fs;
 
    GLuint p,v,f;
 
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
 
    vs =    "#version 150\n"
            "uniform mat4 viewMatrix, projMatrix;\n"
            "in vec4 position;\n"
            "in vec3 color;\n"
            "out vec3 Color;\n"
            "void main()\n"
            "{\n"
            "Color = color;\n"
            "gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
            "}";
    fs =    "#version 150\n"
            "uniform vec2 ScreenDim;\n"
            "uniform isampler2D textureSampler;\n"
            "out vec4 outputColour;\n"
            "void main()\n"
            "{\n"
            "vec2 texCoord;\n"
            "texCoord.x = gl_FragCoord.x/ScreenDim.x;\n"
            "texCoord.y = gl_FragCoord.y/ScreenDim.y;\n"
            "ivec4 red = texture(textureSampler, texCoord);\n"
            "float rc = float((red.r >> 5) & 7) / 7.0;"
            "float gc = float((red.r >> 2) & 7) / 7.0;"
            "float bc = float((red.r >> 0) & 3) / 3.0;"
            "outputColour = vec4(rc,gc,bc,1.0);\n"
           // "outputColour = vec4(texCoord.x, texCoord.y, 0.0f, 1.0f);\n"
            "}";
/*    fs =    "#version 150\n"
            "in vec3 Color;\n"
            "out vec4 outputF;\n"
            "void main()\n"
            "{\n"
            "outputF = vec4(Color,1.0);\n"
            "}";
 */
    const char * vv = vs.data();
    const char * ff = fs.data();
 
    glShaderSource(v, 1, &vv,NULL);
    glShaderSource(f, 1, &ff,NULL);
 
    //free(vs);free(fs);
 
    glCompileShader(v);
    glCompileShader(f);
 
    printShaderInfoLog(v);
    printShaderInfoLog(f);
 
    p = glCreateProgram();
    glAttachShader(p,v);
    glAttachShader(p,f);
 
    glBindFragDataLocation(p, 0, "outputF");
    glLinkProgram(p);
    printProgramInfoLog(p);
 
    vertexLoc = glGetAttribLocation(p,"position");
    colorLoc = glGetAttribLocation(p, "color"); 
 
//     projMatrixLoc = glGetUniformLocation(p, "projMatrix");
//     viewMatrixLoc = glGetUniformLocation(p, "viewMatrix");
 
    return(p);
}

void *start_renderer(void *run_state){
    typedef std::chrono::high_resolution_clock Clock;
    int counter = 0;
    int msCounter = 0;
    int deltaTime = 0;
    run_info *state = ((run_info*) run_state);
    while(!state->exited){
        std::this_thread::sleep_for(std::chrono::milliseconds(33 - deltaTime/1000));
        auto t1 = Clock::now();
		//UPDATE AND RENDER HERE
        g.tic();
        //Allow rendering
        state->allow_draw = true;
        auto t2 = Clock::now();
        
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        msCounter += deltaTime;
        counter++;
        if(counter == 30){
            counter++;
            std::cout << "fps: " << 1000000/((float) msCounter/(float)counter) << "fps"<< std::endl;
            counter = 0;
            msCounter = 0;
        }
    }
    pthread_exit(NULL);
}

void end_renderer(void){
    run_state.exited = true;
    printf("Trying to exit application now.\n");
    pthread_join(raytracerThread, NULL);
    printf("Renderer exited.\n");
}
 
int main(int argc, char **argv) {
    
    int threadC = pthread_create(&raytracerThread, NULL, start_renderer, (void*) &run_state);
    if(threadC){
        printf("Failed to create rendering thread, exiting.\n");
        exit(-1);
    }
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitContextVersion(3,3);
    glutCreateWindow("SimpleGame");
    glutFullScreen();
 
    glutDisplayFunc(update_buffer);
    glutIdleFunc(update_buffer);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(processNormalKeysUp);
    glutWMCloseFunc(end_renderer);
 
    glewInit();
    if (glewIsSupported("GL_VERSION_3_3"))
        printf("Ready for OpenGL 3.3\n");
    else {
        printf("OpenGL 3.3 not supported\n");
        exit(1);
    }
 
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
 
    p = setup_shaders(); 
    setup_buffers();

    
    glutMainLoop();
    return(0); 
}
