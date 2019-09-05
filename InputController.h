#pragma once
//=============================================================================
//
// InputControllerèàóù [InputController.cpp]
// Author : ìnÁ≥ó«ë•
//
//=============================================================================
#ifndef _INPUTCONTROLLER_H_
#define _INPUTCONTROLLER_H_

#define INPUTBUTTON_MAX		(5)

class GameSceneUIManager;

int GetMoveInput();
bool GetBomberInput();

void SetInstanceUIManager(GameSceneUIManager* instance);

#endif