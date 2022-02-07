#include "Scene.h"

Scene::Scene() {
	mActorList = {};
}

Scene::~Scene() {
	for (auto actor : mActorList) {
		delete actor;
	}
}

void Scene::Load(const std::vector<std::string>& resources,
	const std::vector<sf::Vector2f>& positions) {
	for (int index = 0; index < resources.size(); index++) {
		Actor* actorPtr = new Actor;
		actorPtr->Load(resources.at(index), positions.at(index));
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

