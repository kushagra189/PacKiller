#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color,double rad,double spd);
    glm::vec3 position;
    float rotation;
    int score=0;
    int color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int inW=0;
    void tickPlayer();
    double speed;
    double by;
    double r;
    double speedY;
    double accY;
    int fl=1;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
