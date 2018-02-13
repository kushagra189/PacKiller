#include "main.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle {
public:
    Triangle() {}
    Triangle(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speed;
    bounding_box_tri bounding_box();
//    float length;
//    float width;
    void set_position(float x, float y);
//    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TRIANGLE_H
