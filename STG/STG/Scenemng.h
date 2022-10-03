#pragma once
class AbstractScene {
public:
	virtual ~AbstractScene() {};
	virtual AbstractScene* Update() = 0;
	virtual void Draw() const = 0;
};

class SceneManager :public AbstractScene {
private:
	AbstractScene* mScene;

public:
	SceneManager(AbstractScene* scene) :mScene(scene) {}

	~SceneManager() {
		delete mScene;
	}

	AbstractScene* Update() override;

	void Draw() const override;
};


