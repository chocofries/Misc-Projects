/***********************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2018 Media Design School

File Name   :   AnimPaint
Description :   Painting & Animation Software
Author      :   John (Zheng Yu) Bu
Mail        :   zheng.yu5315@mediadesign.school.nz
********************/

#ifndef __FRAME_H__
#define __FRAME_H__

#include <Windows.h>
#include <vector>
#include "shape.h"

class Frame
{
public:
	Frame();
	~Frame();

	std::vector<IShape*> &GetShapeVector();
	std::vector<IShape*> &GetRedoVector();

private:
	std::vector<IShape*> m_shapes;
	std::vector<IShape*> m_redo;
};

#endif