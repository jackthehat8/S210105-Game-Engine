#include "PlayButton.h"
#include "SceneManager.h"

void PlayButton::ButtonPressed()
{
	SceneManager::GetInstance()->setScene(1);
}
