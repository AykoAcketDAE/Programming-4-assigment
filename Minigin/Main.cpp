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
#include "RotatorComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Rendercomponent>("background.tga");
	
	go->SetPosition(0, 0);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Rendercomponent>("logo.tga");
	go->SetPosition(200,100);
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
	
	go = std::make_shared<dae::GameObject>();
	go->SetPosition(200, 200);

	auto go1 = std::make_shared<dae::GameObject>();
	go1->AddComponent<dae::Rendercomponent>("Boss.png");
	go1->SetParent(go.get(), false);
	go1->AddComponent<dae::RotatorComponent>();
	

	auto go2 = std::make_shared<dae::GameObject>();
	go2->AddComponent<dae::Rendercomponent>("Boss.png");
	go2->SetParent(go1.get(), false);
	go2->AddComponent<dae::RotatorComponent>();
	
	scene.Add(go);
	
	scene.Add(go1);
	scene.Add(go2);
	
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}