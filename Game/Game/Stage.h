#pragma once
#include <list>
#include <vector>
#include "Scene.h"

using namespace std;

class CGameObject;
class CStage :public CScene
{
private:
	CGameObject * m_pPlayer[2] = { NULL, NULL};
	list<CGameObject*> m_pEnemyList;
	list<CGameObject*> m_pPlayerBulletList;
	list<CGameObject*> m_pEnmeyBulletList;


	

public:
	virtual void Update(float deltaTime);
	virtual void Render();

	void PlayerFire(float deltaTime);


public:
	CStage();
	virtual ~CStage();
};
