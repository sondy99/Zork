#ifndef __Item__
#define __Item__

#include "Entity.h"


class Item : public Entity
{
public:
	Item();
	Item(string pName, string pDescription);
	~Item();

private:
};

#endif //__Item__