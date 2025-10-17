#pragma once
#include "Camera.h"

namespace threshold
{
	void init();
	void update();
	void draw();
	void destroy();
	void SetCamera(Camera* cam);
}
