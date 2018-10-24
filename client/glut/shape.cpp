#include "shape.h"

#include <iostream>

shape *shape::make_cube()
{
    auto cube = new shape;

    cube->vertices.reserve(24);

    cube->vertices.push_back(vec3 { 1.0f, 1.0f, -1.0f }); // Top Right Of The Quad (Top)
    cube->vertices.push_back(vec3 { -1.0f, 1.0f, -1.0f }); // Top Left Of The Quad (Top)
    cube->vertices.push_back(vec3 { -1.0f, 1.0f, 1.0f }); // Bottom Left Of The Quad (Top)
    cube->vertices.push_back(vec3 { 1.0f, 1.0f, 1.0f }); // Bottom Right Of The Quad (Top)

    cube->vertices.push_back(vec3 { 1.0f, -1.0f, 1.0f }); // Top Right Of The Quad (Bottom)
    cube->vertices.push_back(vec3 { -1.0f, -1.0f, 1.0f }); // Top Left Of The Quad (Bottom)
    cube->vertices.push_back(vec3 { -1.0f, -1.0f, -1.0f }); // Bottom Left Of The Quad (Bottom)
    cube->vertices.push_back(vec3 { 1.0f, -1.0f, -1.0f }); // Bottom Right Of The Quad (Bottom)

    cube->vertices.push_back(vec3 { 1.0f, 1.0f, 1.0f }); // Top Right Of The Quad (Front)
    cube->vertices.push_back(vec3 { -1.0f, 1.0f, 1.0f }); // Top Left Of The Quad (Front)
    cube->vertices.push_back(vec3 { -1.0f, -1.0f, 1.0f }); // Bottom Left Of The Quad (Front)
    cube->vertices.push_back(vec3 { 1.0f, -1.0f, 1.0f }); // Bottom Right Of The Quad (Front)

    cube->vertices.push_back(vec3 { 1.0f, -1.0f, -1.0f }); // Top Right Of The Quad (Back)
    cube->vertices.push_back(vec3 { -1.0f, -1.0f, -1.0f }); // Top Left Of The Quad (Back)
    cube->vertices.push_back(vec3 { -1.0f, 1.0f, -1.0f }); // Bottom Left Of The Quad (Back)
    cube->vertices.push_back(vec3 { 1.0f, 1.0f, -1.0f }); // Bottom Right Of The Quad (Back)

    cube->vertices.push_back(vec3 { -1.0f, 1.0f, 1.0f }); // Top Right Of The Quad (Left)
    cube->vertices.push_back(vec3 { -1.0f, 1.0f, -1.0f }); // Top Left Of The Quad (Left)
    cube->vertices.push_back(vec3 { -1.0f, -1.0f, -1.0f }); // Bottom Left Of The Quad (Left)
    cube->vertices.push_back(vec3 { -1.0f, -1.0f, 1.0f }); // Bottom Right Of The Quad (Left)

    cube->vertices.push_back(vec3 { 1.0f, 1.0f, -1.0f }); // Top Right Of The Quad (Right)
    cube->vertices.push_back(vec3 { 1.0f, 1.0f, 1.0f }); // Top Left Of The Quad (Right)
    cube->vertices.push_back(vec3 { 1.0f, -1.0f, 1.0f }); // Bottom Left Of The Quad (Right)
    cube->vertices.push_back(vec3 { 1.0f, -1.0f, -1.0f }); // Bottom Right Of The Quad (Right)

    return cube;
}

void shape::draw() const
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

    glTranslatef(translation[0], translation[1], translation[2]);
    glRotatef(rotation[0], rotation[1], rotation[2], rotation[3]);
	glScalef(scaling[0], scaling[1], scaling[2]);

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    for (const auto & vertex : vertices)
    {
        glVertex3f(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();

    glPopMatrix();
}

void shape::print() const
{
	for (const auto & vec : vertices)
	{
		vec.print();
	}
}

//void shape::compute_center()
//{
//	center = vec3();
//	for (const auto & vertex : vertices)
//	{
//		center += vertex;
//	}
//	center /= static_cast<float>(vertices.size());
//}
