//=====================================
//
//�v���C���[�I�u�U�[�o�[�w�b�_[PlayerObserver.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYEROBSERVER_H_
#define _PLAYEROBSERVER_H_

#include "main.h"

#include "IStateMachine.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "PlayerModel.h"
#include "PlayerTrail.h"

#include <map>
#include <functional>
#include <vector>

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
PlayerState�񋓎q
***************************************/
enum class PlayerState
{
	Move,
	Wait,
	Idle,
	Return,
	Max
};

/**************************************
�N���X��`
***************************************/
class PlayerObserver
{
public:
	PlayerObserver();
	~PlayerObserver();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void PushInput(int num);
	void SetMoveTargetPosition(int i, D3DXVECTOR3 pos);

private:
	Player *player;
	std::vector<PlayerBullet*> bulletContainer;
	PlayerTrail* trailEffect;

	PlayerState current, prevState;
	std::map<PlayerState, IStateMachine<Player>*> fsm;

	PlayerModel *model;
	int moveTarget;
	std::vector<D3DXVECTOR3> targetPos;

	void ChangeStatePlayer(PlayerState next);

	void OnFinishPlayerMove();
	void OnFinishPlayerWait();
	void OnFinishPlayerReturn();
	void SetPlayerBullet(PlayerTrailModel trail);
	void OnPlayerStateFinish();
};


#endif