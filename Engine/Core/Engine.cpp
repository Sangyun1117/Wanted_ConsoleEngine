#include "Engine.h"
#include <iostream>
#include "Level/Level.h"
#include <Windows.h>
//#include <chrono>

// 2가지.
// 윈도우즈.
// 단순 입력 처리(키보드).
// 타이머(시간 계산).

Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;
	//콘솔 커서 끄기
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

Engine::~Engine()
{
	if (mainLevel) {
		delete mainLevel;
		mainLevel = nullptr;
	}
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 현재 시간을 알려줌.
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도(주파수) 가져오기.
	// 나중에 초로 변환하기 위해.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임.
	float targetFrameRate = 60.0f;

	// 타겟 한 프레임 시간.
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop.
	while (true)
	{
		// 엔진 종료 여부 확인.
		if (isQuit)
		{
			// 루프 종료.
			break;
		}

		// 프레임 시간 계산.
		// (현재 시간 - 이전 시간) / 주파수 = 초단위.
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간.
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		// 입력은 최대한 빨리.
		ProcessInput();

		// 고정 프레임.
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트.
			previousTime = currentTime;

			//현재 프레임의 입력을 기록
			for (int i = 0; i < 255; ++i) {
				keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
			}
		}
	}
	//프로그램 종료 후 정리
	//텍스트 색상 원상태
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);//비트연산 결과 7 = 하얀색
}

void Engine::AddLevel(Level* newLevel)
{
	//기존에 있던 레벨은 제거.
	if (mainLevel) {
		delete mainLevel;
	}
	mainLevel = newLevel;
}

bool Engine::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode)
{
	return !keyStates[keyCode].previousKeyDown && keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyUp(int keyCode)
{
	return keyStates[keyCode].previousKeyDown && !keyStates[keyCode].isKeyDown;
}

void Engine::Quit()
{
	// 종료 플래그 설정.
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::ProcessInput()
{
	//키 입력 확인
	for (int i = 0; i < 255; ++i) {
		keyStates[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000);
	}
	// ESC키 눌림 확인.
	//if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	//{
	//	// 종료.
	//	Quit();
	//}
}

void Engine::BeginPlay() {
	if (mainLevel) {
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	//std::cout
	//	<< "DeltaTime: " << deltaTime
	//	<< ", FPS: " << (1.0f / deltaTime)
	//	<< "\n";
	//if (GetKeyDown('A')) { //소문자는 안됨.
	//	std::cout << "KeyDown\n";
	//}
	//if (GetKey('A')) {
	//	std::cout << "Key\n";
	//}
	//if (GetKeyUp('A')) {
	//	std::cout << "KeyUp\n";
	//}

	//레벨 업데이트
	if (mainLevel) {
		mainLevel->Tick(deltaTime);
	}

	//if (GetKeyDown(VK_ESCAPE)) {
	//	Quit();
	//}
}

void Engine::Render()
{
	//프레임 시작 시점 하얀색으로 설정 후 각자 지정
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);//비트연산 결과 7 = 하얀색
	if (mainLevel) {
		mainLevel->Render();
	}
}