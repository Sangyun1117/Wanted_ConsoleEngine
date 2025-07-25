#include <iostream>
#include "Engine.h"
#include "DemoLevel.h"
//#include "Math/Vector2.h"
int main() {

	//Vector2 a(10, 20);
	//Vector2 b(20, 30);
	//std::cout << (a + b).ToString() << "\n";

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine engine;
	engine.AddLevel(new DemoLevel());
	engine.Run();
}
