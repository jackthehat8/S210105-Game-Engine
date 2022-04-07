#include "PlayButton.h"
#include "SceneManager.h"

void PlayButton::ButtonPressed()
{
	//move to the next screen
	SceneManager::GetInstance()->setScene(ObjectManager::GetInstance()->currentScene+ 1);
}
