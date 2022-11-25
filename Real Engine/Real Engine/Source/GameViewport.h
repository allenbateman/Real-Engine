#include "Panel.h"
#include "Renderer.h"
class GameViewport : public Panel
{
public:

	GameViewport(int _id, bool isActive);
	~GameViewport();
	void Init();
	void Update();
	bool CleanUp();
};