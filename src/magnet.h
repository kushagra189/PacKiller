#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color,double r);
    glm::vec3 position;
    float rotation;
    double rad;
    int onn=1;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    void set_position(float x, float y);
//    void tick();
//    void tickPlayer();
private:
    VAO *object;
};

#endif // MAGNET_H
