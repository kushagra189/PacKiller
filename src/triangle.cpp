#include "triangle.h"
#include "main.h"

Triangle::Triangle(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed=0.05;
//    this->length = l;
//    this->width = b;
    GLfloat g_vertex_buffer_data[]{

        1,-1.5,0,
        0.5*2*cos(M_PI*5/12)+1,-1.5,0,
        1+0.5*cos(M_PI*5/12),-1.5+0.5*sin(M_PI*5/12),0,

        0.5*2*cos(M_PI*5/12)+1,-1.5,0,
        0.5*2*cos(M_PI*5/12)+1+0.5*cos(M_PI*5/12),-1.5+0.5*sin(M_PI*5/12),0,
        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12),-1.5,0,

        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12),-1.5,0,
        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12)+0.5*cos(M_PI*5/12),-1.5+0.5*sin(M_PI*5/12),0,
        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12)+0.5*2*cos(M_PI*5/12),-1.5,0,

        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12)+0.5*2*cos(M_PI*5/12),-1.5,0,
        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12)+0.5*2*cos(M_PI*5/12)+0.5*cos(M_PI*5/12),-1.5+0.5*sin(M_PI*5/12),0,
        0.5*2*cos(M_PI*5/12)+1+0.5*2*cos(M_PI*5/12)+0.5*2*cos(M_PI*5/12)+0.5*2*cos(M_PI*5/12),-1.5,0,
//        0,0,0,
//        3/3,0,0,
//        0,4/3,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Triangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Triangle::tick() {
    this->position.x += this->speed;
    if(this->speed>0)
    {
        if(this->position.x>10 || (this->position.x>-4.2 && this->position.x<-1))
            this->speed=-this->speed;
    }
    else
    {
        if(this->position.x<-10 || (this->position.x>-4 && this->position.x<-0.5))
            this->speed=-this->speed;
    }
//    else if(this->position.x<-4)
//        this->speed = -this->speed;
}

bounding_box_tri Triangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float side = 1;
    bounding_box_tri bbox = { x, y, side };
    return bbox;
}
