#include "Scene.h"

Scene::Scene() {
	mActorList = {};
}

Scene::~Scene() {
	for (auto actor : mActorList) {
		delete actor;
	}
}

void Scene::Load(const std::list<std::string>& resources) {
	for (auto resource : resources) {
		Actor* actorPtr = new Actor;
		actorPtr->Load(resource);
		mActorList.push_back(actorPtr);
	}
}

//void Scene::AddActor(Actor& actor) {
//	mActorList.push_back(&actor);
//}
//
//void Scene::RemoveActor(Actor& actor) {
//	for (auto Actor : mActorList) {
//		mActorList.remove_if(Actor->ToBeRemoved);
//		delete Actor;
//	}
//}

void Scene::Draw(sf::RenderWindow& window) {
	for (auto actor : mActorList) {
		actor->Draw(window);
	}
}

