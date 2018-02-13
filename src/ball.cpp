#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color,double rad ,double spd) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->by=0.03;
    speed = spd;//((double)rand()/RAND_MAX)*0.05;
//    speedY = 0.3;
    accY = -0.05;
    static GLfloat g_vertex_buffer_data[9000];
     int p=0;
 //    float pi=3.14;
//     double r = ((double) rand() / (RAND_MAX)) + 1;
     this->r = rad;
     for(int i=0;i<1000;i++)
     {
         double a = (2*i+1)*(double)M_PI/1000;
         for(int j=0;j<3;j++)
             g_vertex_buffer_data[p++]=0.0f;
         g_vertex_buffer_data[p++]=this->r*(float)cos(a);
         g_vertex_buffer_data[p++]=this->r*(float)sin(a);
         g_vertex_buffer_data[p++]=0.0f;
         a+=(double)M_PI/500;
         g_vertex_buffer_data[p++]=this->r*(float)cos(a);
         g_vertex_buffer_data[p++]=this->r*(float)sin(a);
         g_vertex_buffer_data[p++]=0.0f;
     }

    this->object = create3DObject(GL_TRIANGLES, 9000, g_vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += this->speed;
//    if(this->position.x>6)
//        this->set_position(rand()%5-12,rand()%5);
//    else if(this->position.x<-4)
//        this->speed = -this->speed;
}

void Ball::tickPlayer() {
//    this->position.x += speed;
    // this->position.y -= speed;
    this->position.y += this->speedY;
    if((this->position.x>=-2.3 && this->position.x<=0.7) && (this->position.y<=-1.5 && this->position.y>=-3)){
//        if(this->position.x<0.2 && this->position.x>0.1)
//            this->position
        this->inW=1;
        this->speedY=0;
//        this->position.y += this->speedY;
//        this->accY=-0.01;
        if(this->position.x>=-2.3 && this->position.x<=-1.8){
            this->position.x=-1.8;
            this->position.y = -2;
        }
        else if(this->position.x>=0.2 && this->position.x<=0.7){
            this->position.x=0.2;
            this->position.y = -2;
        }

        if(this->position.y>-3)
        {
            this->fl=1;
            if(this->position.x<-0.8){
                this->position.x+=0.01;
                this->position.y = -(sqrt(1*1-(this->position.x+0.8)*(this->position.x+0.8)))-2;
            }
            else
            {
                this->position.x-=0.01;
                this->position.y = -(sqrt(1*1-(this->position.x+0.8)*(this->position.x+0.8)))-2;
            }
//            this->speedY += this->accY;
        }

//        this->speedY+=this->by;
//        this->position.y += this->speedY;
    }
    else{
        this->inW=0;
    }
    if(this->inW==0){
        if(this->position.y>-1.5)// || (this->position.x>-2.3 && this->position.x<0.7 && this->position.y<-1.5))
        {
            this->speedY += this->accY;
    //        printf("haha");
        }
        else
        {
            this->position.y=-1.5;
            this->speedY = 0;
            this->fl=1;
    //        flag=0;
        }
    }

//    if(this->position.y>=1.5 && this->position.y<=4.5){
//        if(this->position.x>4)
//            this->position.x-=0.1;
//        else
//            this->position.x+=0.1;
//    }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float rad = this->r;
    bounding_box_t bbox = { x, y, rad };
    return bbox;
}
