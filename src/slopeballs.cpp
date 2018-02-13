#include "slopeballs.h"
#include "main.h"

Slopeballs::Slopeballs(float x, float y, color_t color,double rad,double spd ) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = -rand()%90;
    this->speed = spd;//((double)rand()/RAND_MAX)*0.05;
//    speedY = 0.3;
    accY = -0.1;
    static GLfloat g_vertex_buffer_data[18];
     int p=0;
 //    float pi=3.14;
//     double r = ((double) rand() / (RAND_MAX)) + 1;
     this->r = rad;
     g_vertex_buffer_data[p++]=(-r*sqrt(2)-0.1/sqrt(2));
     g_vertex_buffer_data[p++]=0.1/sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=-0.1/sqrt(2);
     g_vertex_buffer_data[p++]=(r*sqrt(2)+0.1/sqrt(2));
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=0;
     g_vertex_buffer_data[p++]=r*sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=0;
     g_vertex_buffer_data[p++]=r*sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=-r*sqrt(2);
     g_vertex_buffer_data[p++]=0;
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=(-r*sqrt(2)-0.1/sqrt(2));
     g_vertex_buffer_data[p++]=0.1/sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;

    this->object = create3DObject(GL_TRIANGLES, 18, g_vertex_buffer_data, color, GL_FILL);
}

void Slopeballs::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Slopeballs::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slopeballs::tick() {
    this->position.x += this->speed;
//    if(this->position.x>6)
//        this->set_position(rand()%5-12,rand()%5);
//    else if(this->position.x<-4)
//        this->speed = -this->speed;
}

bounding_box_t Slopeballs::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float rad = this->r;
    bounding_box_t bbox = { x, y, rad };
    return bbox;
}
