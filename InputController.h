#pragma once
//=============================================================================
//
// InputController���� [InputController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _INPUTCONTROLLER_H_
#define _INPUTCONTROLLER_H_

#define INPUTBUTTON_MAX		(5)

class GameSceneUIManager;

int GetMoveInput();
int GetStickInput(int currentStar);
bool GetBomberInput();

void SetInstanceUIManager(GameSceneUIManager* instance);
bool IsAnyKeyTriggered();
bool IsAnyButtonTriggerd();

#endif