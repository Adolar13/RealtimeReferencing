#pragma once

#include "RefObject.h"

class RefScene
{
	static RefScene * m_instance;
	RefScene();

public:

	RefObject * root;

	static RefScene * Instance() {
		if (!m_instance)
			m_instance = new RefScene;
		return m_instance;
	}
};

