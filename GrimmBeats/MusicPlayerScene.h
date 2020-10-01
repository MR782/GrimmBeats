#include"Scene.h"
#include"Animation.h"
#include<memory>

class MusicPlayerScene : public Scene {
	std::unique_ptr<Animation> _uiBoard;
public:
	MusicPlayerScene();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};