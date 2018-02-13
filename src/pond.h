#include "main.h"

#ifndef POND_H
#define POND_H


class Pond {
public:
    Pond() {}
    Pond(float x, float y, color_t color,double r);
    glm::vec3 position;
    float rotation;
    double rad;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    void set_position(float x, float y);
//    void tick();
//    void tickPlayer();
private:
    VAO *object;
};

#endif // POND_H
