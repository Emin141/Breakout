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

void Scene::AddActor(Actor& actor) {
	mActorList.push_back(&actor);
}

void Scene::RemoveActor(Actor& actor) {
	for (auto a : mActorList) {
		if (a->GetID() == actor.GetID()) {
			mActorList.remove(a);
			delete a;
		}
	}
}

void Scene::Draw(SDL_Surface* windowSurface) {
	for (auto actor : mActorList) {
		actor->Draw(windowSurface);
	}
}

