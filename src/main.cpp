#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "pond.h"
#include "slopeballs.h"
#include "rect.h"
#include "triangle.h"
#include "magnet.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
/**************************
* Customizable functions *
**************************/

Ball ball[15];
Ball player;
Ground ground;
Ground grass;
Pond pond;
Pond tramp;
Magnet mag[2];
Rect t1,t2,m1,m2;
Triangle tri[2];
Slopeballs slopeball[5];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
char scorput[1000];
Timer t60(1.0 / 60);
int mag_vis_time = 600;
int mag_non_time = 400;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
//    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP = Matrices.projection * Matrices.view * glm::scale(glm::vec3(exp(camerazoom)));
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    ball1.draw(VP);
//    ball2.draw(VP);
    if(mag[1].onn==1 && mag[0].onn==1){
        mag[1].draw(VP);
        mag[0].draw(VP);
        m1.draw(VP);
        m2.draw(VP);
    }
    for(int i=0;i<5;i++){
        slopeball[i].draw(VP);
//        ball[i].draw(VP);
    }
    for(int i=0;i<15;i++){
        ball[i].draw(VP);
    }
    grass.draw(VP);
    ground.draw(VP);
    pond.draw(VP);
    player.draw(VP);
    tramp.draw(VP);
    t1.draw(VP);
    t2.draw(VP);
    tri[0].draw(VP);
    tri[1].draw(VP);
}

void magPos(){
    if(mag[0].onn==1 && mag[1].onn==1)
    {
        mag_vis_time-=1;
        if(mag_vis_time<=0)
        {
            mag_vis_time=600;
            mag[0].onn=0;
            mag[1].onn=0;
        }
        if(player.position.y>=1.5 && player.position.y<=4.5){
            if(player.position.x>4) player.position.x-=0.01;
            else player.position.x+=0.01;
        }
    }
    else
    {
        mag_non_time-=1;
        if(mag_non_time<=0){
            mag[0].onn=1;
            mag[1].onn=1;
            mag_non_time=400;
        }
    }
}

void position(){
    for(int i=0;i<5;i++)
    {
        if(ball[i].position.x>8){
            float x = (rand()%5)-12;
            float y = rand()%5;
            slopeball[i].set_position(x,y);
            ball[i].set_position(x,y);
        }
    }
    for(int i=5;i<15;i++)
    {
        if(ball[i].position.x>8){
            float x = (rand()%5)-12;
            float y = rand()%5;
            ball[i].set_position(x,y);
//            slopeball[i].set_position(x,y);
        }
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int key_a = glfwGetKey(window, GLFW_KEY_A);
    int key_s = glfwGetKey(window, GLFW_KEY_S);
    int key_d = glfwGetKey(window, GLFW_KEY_D);
    int key_w = glfwGetKey(window, GLFW_KEY_W);
    int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (left) {
            // Do something
    //        ball1.rotation+=45;
            player.position.x-=player.speed;
        }
        if(right){
            player.position.x+=player.speed;
        }
        if(up && player.fl==1){
//            if(player.position.x < 0.7 && player.position.x > -2.3){
//                player.speedY = 0.5;
//                player.fl = 0;
//            }
//            printf("%f",player.speedY);
//            else{
            player.speedY+=0.8;
            player.fl=0;
//            }
//            if(player.position.y>=-3 && player.position.y<=-1.5)
//                player.speedY+=player.accY+player.by;
        }
        if (key_a && screen_center_x - 4/screen_zoom > -4) {
                screen_center_x -= 0.07;
                reset_screen();
            }
            if (key_s && screen_center_y - 4/screen_zoom > -4) {
                screen_center_y -= 0.07;
                reset_screen();
            }
            if (key_d && screen_center_x + 4/screen_zoom < 4) {
                screen_center_x += 0.07;
                reset_screen();
            }
            if (key_w && screen_center_y + 4/screen_zoom < 4) {
                screen_center_y += 0.07;
                reset_screen();
            }

            if (mouse_clicked) {
                if (drag_oldx == -1 && drag_oldy == -1) {
                    glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
                }
                else {
                    int w, h;
                    double new_x, new_y;
                    glfwGetCursorPos(window, &new_x, &new_y);
                    glfwGetWindowSize(window, &w, &h);
                    float pos_x, pos_y;
                    pos_x = 8 * (new_x - drag_oldx) / (w * screen_zoom);
                    player.position.x = pos_x;
                    // drag_oldx = new_x;
                    // drag_oldy = new_y;
                }
            }
}

void tick_elements() {
    for(int i=0;i<5;i++){
        ball[i].tick();
        slopeball[i].tick();
        if(detect_collision(player.bounding_box(),slopeball[i].bounding_box()) && player.speedY<0)
        {
            player.position.x=-player.speedY;
            player.speedY=0.2;
        }
    }
    for(int i=5;i<15;i++){
        ball[i].tick();
        if (detect_collision(ball[i].bounding_box(), player.bounding_box())) {
            float a = rand()%5-12;
            float b = rand()%5;
            if(player.speedY<0){
                ball[i].set_position(a,b);
                player.speedY += 0.8;
                if(ball[i].color==1)player.score+=100;
                if(ball[i].color==2)player.score+=300;
//                printf("%d\n",player.score);
             }
//          ball2.speed = -ball2.speed;
        }
    }
    if(detect_collision_tp(player.bounding_box(),tramp.bounding_box()))
    {
        player.speedY=-player.speedY;
    }
    if(detect_collision_tri(tri[0].bounding_box(),player.bounding_box()))
    {
//        printf("%lf",player.position.x);
//        printf("%lf",player.position.y);
        tri[0].set_position(2*0.5*cos(M_PI*5/12)-12,-1.47+2*0.5*sin(M_PI*5/12));
        player.set_position(0,-1);
        player.score-=50;
    }
    if(detect_collision_tri(tri[1].bounding_box(),player.bounding_box()))
    {
//        printf("%lf",player.position.x);
//        printf("%lf",player.position.y);
        tri[1].set_position(2*0.5*cos(M_PI*5/12)+8,-1.47+2*0.5*sin(M_PI*5/12));
        player.set_position(0,-1);
        player.score-=50;
    }
//    if((player.position.y-player.r)==-1)
//    {
//        if(player.position.x>0.6 && player.position.x<1.35)
//        {
//            player.speedY=-player.speedY;
//        }
//    }
    player.tickPlayer();
    tri[0].tick();
    tri[1].tick();

    magPos();

    sprintf(scorput,"Score: %d",player.score);
    glfwSetWindowTitle(window,scorput);
//    ball1.tick();
//    ball2.tick();
//    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    for(int i=5;i<15;i++){

        double randomRad = ((double) rand() / (RAND_MAX))*0.5+0.2;
        float x = (rand()%5)-12;
        float y = rand()%5;
        color_t temp;
        int z = rand()%2+1;
//        if(z==1)temp = COLOR_RED;
        if (z==1)temp = COLOR_GREEN;
        else if(z==2)temp = COLOR_BLUE;
        double spd = ((double)rand()/RAND_MAX)*0.05;
        ball[i]  = Ball(x, y, temp,randomRad,spd);
        ball[i].color=z;
    }
    for(int i=0;i<5;i++){

        double randomRad = ((double) rand() / (RAND_MAX))*0.5+0.2;
        float x = (rand()%5)-12;
        float y = rand()%5;
        color_t temp;
        int z = rand()%2+1;
        double spd =((double)rand()/RAND_MAX)*0.05;
//        if(z==1)temp = COLOR_RED;
        if (z==1)temp = COLOR_YELLOW;
        else if(z==2)temp = COLOR_BLUE;
        ball[i]  = Ball(x, y, temp,randomRad,spd);
//        ball[i].color=z;
        slopeball[i] = Slopeballs(x, y, COLOR_BROWN,randomRad,spd);
//        ball[i]  = Ball(x, y, temp,randomRad);
    }
    player = Ball(-3,-1.5, COLOR_RED,0.5,0.05);
//    player.speed = 0.05;
    grass = Ground(0,0,COLOR_GRASS);
    ground = Ground(0,-1,COLOR_BROWN);
    pond = Pond(-0.8,-2,COLOR_POND,1.5);
    tramp = Pond(3,-1,COLOR_RED,0.8);
    t1 = Rect(1.1,-1,0.1,1,COLOR_RED);
    t2 = Rect(1.85,-1,0.1,1,COLOR_RED);
    tri[0] = Triangle(2*0.5*cos(M_PI*5/12)-5,-1.47+2*0.5*sin(M_PI*5/12),COLOR_YELLOW);
    tri[1] = Triangle(2*0.5*cos(M_PI*5/12),-1.47+2*0.5*sin(M_PI*5/12),COLOR_YELLOW);
    mag[1] = Magnet(4,4,COLOR_ORANGE,1.5);
    mag[0] = Magnet(4,4,COLOR_BACKGROUND,0.75);
    m1 = Rect(1.5,2.4,0.75,0.75,COLOR_ORANGE);
    m2 = Rect(1.5,1.25,0.75,0.75,COLOR_ORANGE);
//    randomRad = ((double) rand() / (RAND_MAX)) + 1;
//    ball2       = Ball(-2, 0, COLOR_RED,randomRad);
//    ball2.speed = -ball2.speed;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            position();
            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    float p = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    if(p <= a.rad + b.rad)
        return 1;
    else
        return 0;
}

bool detect_collision_tp(bounding_box_t a, bounding_box_t b) {
    if((a.x>=b.x-b.rad && a.x<=b.x+b.rad) && ((a.y-a.rad)<=b.y))
        return 1;
    else
        return 0;
}

bool detect_collision_pl(bounding_box_t a, bounding_box_t b) {
    if((a.x>(b.x-b.rad*sqrt(2)) && a.x<b.x) && (a.y<(b.y+b.rad*sqrt(2)) && a.y>b.y))
        return 1;
    else
        return 0;
}

bool detect_collision_tri(bounding_box_tri a, bounding_box_t b) {
       if(((b.y-(-1.5+2*0.5*sin(M_PI*5/12)))<=b.rad) && (b.x>=(a.x+1+2*0.5*cos(M_PI*5/12)) && b.x<=(a.x+1+8*0.5*cos(M_PI*5/12)))){
           return 1;
       }
       else return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4*3/2 / screen_zoom;
    float bottom = screen_center_y - 4*3/2 / screen_zoom;
    float left   = screen_center_x - 4*3/2 / screen_zoom;
    float right  = screen_center_x + 4*3/2 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
