#ifndef TUNEL_H
#define TUNEL_H


#include <random>
#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

float DIST_INTER = 0.4f;
float DEG_INTER = 4.f;

float prob(){
    return   rand() / float(RAND_MAX);
}

float d2rad(float d){
    return d * (M_PI / 180.f);
}

struct TunelSeg{

    glm::vec3 start;
    glm::vec3 dir;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec3> vertex;

    float dist;

    constexpr  static glm::vec3 p0{0.f,1.f,0.f};
    float radious = 2;

    TunelSeg(glm::vec3 start_, glm::vec3 dir_, float dist_, float  radious_, int &offset){
        start = start_;
        dir = glm::normalize(dir_);
        dist = dist_;
        radious = radious_;

        generate_points();
        generate_vertex(offset);
    }

    void generate_points(){
        int c = 0;
        for (float d = 0; d < dist; d += DIST_INTER) {
            auto p = start + d * dir;
            auto p1 = glm::normalize(glm::cross(p0, dir));
            auto p2 = glm::normalize(glm::cross(p1, dir));
            for (float theta = 0.f; theta < 360.f; theta += DEG_INTER) {
                glm::vec3 new_dot = p + radious * cosf(d2rad(theta)) * p1 + radious * sinf(d2rad(theta)) * p2;
                auto test = glm::vec3(1, 1, 1);
                auto surface_norm = normalize(test);
                points.emplace_back(new_dot);
                normal.emplace_back(surface_norm);
            }
            c++;
        }
    }

    void generate_vertex(int &offset){
        int rings = ceilf( 360.f / DEG_INTER);
        int ppr = ceilf( dist / DIST_INTER);
        for(int ring = 0; ring < rings - 1; ring++){
            for(int point = 1; point <  ppr - 1;point++){

                glm::vec3  t1( ring * ppr + point + offset,
                               (ring + 1) * ppr + point + offset,
                               (ring + 1) * ppr + point + 1 + offset);
                glm::vec3  t2( ring * ppr + point + offset,
                              (ring + 1) * ppr + point + offset,
                              ring * ppr  + point - 1 + + offset);
                vertex.emplace_back(t1);
                vertex.emplace_back(t2);
            }
        }
        offset += (int) points.size();
    }
};


struct Tunnel{
    std::vector<TunelSeg> path;
    Tunnel* alt;
    const static int max_depth = 5, min_dist = 2, max_dist = 4;
    constexpr static float thresh = 0.2, min_rad = 0.5f, max_rad = 1.5f;
    glm::vec3 dir;

    Tunnel(glm::vec3 start, glm::vec3 dir = glm::sphericalRand(1.0f)  ,bool first = true, int offset = 0){
        alt = nullptr;

        for(int depth = 0; depth < max_depth;depth++){
            float dist = glm::linearRand((float) min_dist, (float) max_dist);
            float r = glm::linearRand(min_rad, max_rad);
            TunelSeg s {start, dir, dist, r, offset};

            path.push_back(s);
            auto stay = glm::linearRand(0.0f, 1.0f);
            start += dir * dist;
            if( stay < thresh) break;
        }

        std::cout<<offset<<'\n';
        if(glm::linearRand(0.0f, 1.0f) < thresh ||  first){
            alt = new Tunnel(path[rand() % path.size()].start, glm::normalize(glm::cross(dir, TunelSeg::p0) ),false, offset );
        }
    }
};




#endif