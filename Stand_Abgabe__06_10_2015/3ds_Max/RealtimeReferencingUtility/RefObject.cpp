#include "RefObject.h"


RefObject::RefObject()
{
}


RefObject::~RefObject()
{
	if (parent != nullptr && !childs.empty() ) {
		parent->childs.insert(parent->childs.end(), childs.begin(), childs.end());
		for (std::vector<RefObject*>::iterator iter = childs.begin(); iter != childs.end(); ++iter)
		{
			(*iter)->parent = parent;
		}
		for (std::vector<RefObject*>::iterator iter = parent->childs.begin(); iter != parent->childs.end(); ++iter)
		{
			if (*iter == this)
			{
				parent->childs.erase(iter);
				break;
			}
		}
	}
}


