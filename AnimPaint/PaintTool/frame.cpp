#include "frame.h"

Frame::Frame()
{

}
Frame::~Frame()
{
	//Delete and empty the vectors in the frame
	/*while (!m_shapes.empty())
	{
		IShape* delShape = (m_shapes.back());
		delete delShape;
		m_shapes.pop_back();
	}
	while (!m_redo.empty())
	{
		IShape* delShape = (m_redo.back());
		delete delShape;
		m_redo.pop_back();
	}*/
}

std::vector<IShape*> &Frame::GetShapeVector()
{
	if (this != nullptr)
	{
		return (m_shapes);
	}
}

std::vector<IShape*> &Frame::GetRedoVector()
{
	if (this != nullptr)
	{
		return (m_redo);
	}
}