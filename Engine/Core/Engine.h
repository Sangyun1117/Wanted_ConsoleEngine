#pragma once
#include "Core.h"
#include <Windows.h>
/*
*Todo:  
	- RTTI ����
	- Engine �߰� (SingleTon).
*
*/
class Level;

class Engine_API Engine
{
public:

	//Ű �Է� Ȯ�� ����ü
	struct KeyState
	{
		//���� �����ӿ� Ű�� ���ȴ���
		bool isKeyDown = false;
		//���� �����ӿ� Ű�� ���ȴ���
		bool previousKeyDown = false;
	};

	// ������.
	Engine();

	// �Ҹ���.
	~Engine();

	// ���� ���� �Լ�.
	void Run();

	//���� �߰� �Լ�
	void AddLevel(Level* newLevel);

	//Ű Ȯ�� �Լ�
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// ���� �Լ�.
	void Quit();

	//�̱��� ���� �Լ�
	static Engine& Get();

private:
	void ProcessInput();
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

private:
	// ���� ���� �÷���.
	bool isQuit = false;

	//Ű �Է� ���� ���� ����
	KeyState keyStates[255] = { };

	// ���� ����
	Level* mainLevel = nullptr;
	
	//��Ŭ�� ����
	static Engine* instance;
};

