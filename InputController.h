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
bool GetBomberInput();

void SetInstanceUIManager(GameSceneUIManager* instance);

#endif