#include "Level.h"
#include "Actor/Actor.h"
Level::Level() {

}
Level::~Level() {

}

//레벨에 액터를 추가할 때 사용
void Level::AddActor(Actor* newActor) {
	//예외처리(중복 여부 확인) 필요함

	//push_back/emplace_back()
	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

//엔진 이벤트 함수
void Level::BeginPlay() {
	for (Actor* const actor : actors) {
		if (actor->HasBeginPlay()) {
			continue;
		}
		actor->BeginPlay();
	}
}
void Level::Tick(float deltaTime) {
	for (Actor* const actor : actors) {
		actor->Tick(deltaTime);
	}
}
void Level::Render() {
	for (Actor* const actor : actors) {
		actor->Render();
	}
}