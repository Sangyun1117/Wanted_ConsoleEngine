#pragma once
#include "Core.h"
#include "RTTI.h"
#include <vector>

class Actor;
class Engine_API Level : public RTTI{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();


	//������ ���͸� �߰��� �� ���
	void AddActor(Actor* newActor);

	//���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();
private:
	//������ ��ġ�� ��� ���͸� �����ϴ� �迭
	std::vector<Actor*> actors;
};
