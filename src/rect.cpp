#include "rect.h"
#include "main.h"

Rect::Rect(float x, float y, float l, float b, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = l;
    this->width = b;
    GLfloat g_vertex_buffer_data[]{
        x,y,0,
        x+l,y,0,
        x,y+b,0,
        x+l,y,0,
        x,y+b,0,
        x+l,y+b,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Rect::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rect::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
