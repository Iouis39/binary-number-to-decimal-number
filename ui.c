
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "./include/nuklear.h"
#include "./include/nuklear_glfw_gl3.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024


static void error_callback(int e, const char *d)
{
  printf("Error %d: %s\n", e, d);
}


int calcPower(int base, int exp) {
    int result = 1;

    if (exp < 0) {
        return -1;
    }
    
    while(exp) {
        if(exp & 1) {
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    
    return result;
}

int convertBinaryToDecimal(int input[], int numberOfInputElements, int* result) {
    int i = 0;
    int exp;
    *result = 0;
    
    for (i = 0; i < numberOfInputElements; i++) {
        exp = numberOfInputElements - i - 1;
        *result += input[i] * calcPower(2, exp);
    }
        
    return 0;
}

int stringToIntArr(char* string, int** intArrayResult) {
    int size = 0;
    int i = 0;
    while (string[size] != 0) {
        size++;
    }
    *intArrayResult = malloc(sizeof(int)*size);
    while (string[i] != 0) {
        if (string[i] == '0') {
            (*intArrayResult)[i] = 0;
        } else if (string[i] == '1') {
            (*intArrayResult)[i] = 1;
        } else {
            return -1;
        }        
        i++;
    }
    return size;
}

int main(void)
{
    /* Platform */
    struct nk_glfw glfw = {0};
    static GLFWwindow *win;
    int width = 0, height = 0;
    struct nk_context *ctx;
    struct nk_colorf bg;
    char buf[256] = {0};
    char outBuff[50] = {0};
    int* intArrayResult;
    int size;
    int decimal;

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bin to Dec Converter", NULL, NULL);
    glfwMakeContextCurrent(win);
    glfwGetWindowSize(win, &width, &height);

    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }

    ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);
    {
      struct nk_font_atlas *atlas;
      nk_glfw3_font_stash_begin(&glfw, &atlas);
      nk_glfw3_font_stash_end(&glfw);
    }

    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    while (!glfwWindowShouldClose(win))
    {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame(&glfw);

        /* GUI */
        if (nk_begin(ctx, "Bin to Dec Converter", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
          nk_layout_row_static(ctx, 30, 180, 1);
          nk_edit_string_zero_terminated (ctx, NK_EDIT_FIELD, buf, sizeof(buf) - 1, nk_filter_default);
          if (nk_button_label (ctx, "Convert")) {
            size = stringToIntArr(buf, &intArrayResult);
            if(size < 0) {
              sprintf (outBuff, "Result: ERROR");
            } else {
              convertBinaryToDecimal(intArrayResult, size, &decimal);
              sprintf (outBuff, "Result: %d", decimal);
            }
          }
          nk_label(ctx, outBuff, NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_BOTTOM);

        }
        nk_end(ctx);

        /* Draw */
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(win);
    }
    nk_glfw3_shutdown(&glfw);
    glfwTerminate();
    return 0;
}

