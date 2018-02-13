#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color,double r) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;
    this->rad = r;
    static GLfloat g_vertex_buffer_data[45000];
     int p=0;
     for(int i=0;i<5000;i++)
     {
         double a = -(2*i+1)*(double)M_PI/10000;
         for(int j=0;j<3;j++)
             g_vertex_buffer_data[p++]=0.0f;
         g_vertex_buffer_data[p++]=rad*(float)cos(a);
         g_vertex_buffer_data[p++]=rad*(float)sin(a);
         g_vertex_buffer_data[p++]=0.0f;
         a-=(double)M_PI/5000;
         g_vertex_buffer_data[p++]=rad*(float)cos(a);
         g_vertex_buffer_data[p++]=rad*(float)sin(a);
         g_vertex_buffer_data[p++]=0.0f;
     }

    this->object = create3DObject(GL_TRIANGLES, 45000, g_vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float rad = this->rad;
    bounding_box_t bbox = { x, y, rad };
    return bbox;
}
