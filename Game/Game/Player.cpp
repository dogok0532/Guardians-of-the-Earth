
#include "Player.h"
#include "SpriteResource.h"
#include "direct.h"


void CPlayer::Update(float deltaTime)
{
	Move(deltaTime);


}

void CPlayer::Render()
{
	
	
		
	m_pSprite->Draw(m_vecImage[0].pTexture, NULL, &m_vecCenter, &m_vecPos, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		
	
}

bool CPlayer::Fire(float deltaTime)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (bFired == false)
		{
			bFired = true;
			return true;
		}
  		if (fCurrentCycle >= fFireCycle)
		{
			fCurrentCycle =0;
			bFired = true;
          	return true;
		}


		fCurrentCycle += deltaTime;

   		return false;
		
	}
	else
	{
		bFired = false;
	}



	fCurrentCycle = 0;
	return false;
}

void CPlayer::Move(float deltaTime)
{
	{		//이동관련 알고리즘
		if (GetAsyncKeyState(VK_LEFT))
			m_vecPos.x -= 500 * deltaTime;
		if (GetAsyncKeyState(VK_RIGHT))
			m_vecPos.x += 500 * deltaTime;
		if (GetAsyncKeyState(VK_UP))
			m_vecPos.y -= 500 * deltaTime;
		if (GetAsyncKeyState(VK_DOWN))
			m_vecPos.y += 500 * deltaTime;
	}
}

CPlayer::CPlayer()
{
	m_vecImage.push_back(CSpriteResource::GetInstance()->GetTextureInfo(L"User_Center"));
	m_vecImage.push_back(CSpriteResource::GetInstance()->GetTextureInfo(L"User_Left"));
	m_vecImage.push_back(CSpriteResource::GetInstance()->GetTextureInfo(L"User_Right"));

	if(m_vecImage.size()!=0)
		SetSizeToTextureSize();
	
	m_vecPos = { 400,400,0 };

	fFireCycle = 0.1f;
	fCurrentCycle = 0;
	bFired = false;
}


CPlayer::~CPlayer()
{
	
}
