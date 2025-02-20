#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Rendercomponent.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Rendercomponent>("background.tga",0.f,0.f);
	
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Rendercomponent>("logo.tga",216.f,180.f);
	
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("here", font);
	go->GetComponent<dae::TextComponent>()->SetPosition(5,50);
	go->AddComponent<dae::FPSComponent>();
	
	
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	go->SetPosition(80, 20);

	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}