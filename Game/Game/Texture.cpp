#include "Texture.h"

#include "direct.h"
#include "GameObject.h"




LPD3DXSPRITE Texture::m_pSprite;

void Texture::Draw(wstring spriteName, int frame)
{
	m_pSprite->Draw(m_pTexture, mapSprite[spriteName]->GetRect(frame), mapSprite[spriteName]->GetCenter(), &(m_pGameInfo->vecPos), DEFAULT_COLOR);

}


D3DXVECTOR3 Texture::GetSize()
{
	return m_vecSize;
}

void Texture::SetInfo(ObjectInfo* pObjectInfo)
{
	m_pGameInfo = pObjectInfo;
}

void Texture::SetColorKey(D3DCOLOR color)
{
	m_ColorKey = color;
}

void Texture::Update()
{
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale,
		m_pGameInfo->vecRenderRatio.x,
		m_pGameInfo->vecRenderRatio.y,
		m_pGameInfo->vecRenderRatio.z);


	D3DXMATRIX matRotate;

	D3DXMATRIX matTempMove;
	D3DXMatrixTranslation(&matTempMove,
		-m_pGameInfo->vecPos.x,
		-m_pGameInfo->vecPos.y,
		-m_pGameInfo->vecPos.z);

	matRotate = matTempMove;

	D3DXMATRIX matTempRotate;
	D3DXMatrixRotationZ(&matTempRotate, m_pGameInfo->fDirection * DEGREE_TO_RADIAN);

	matRotate *= matTempRotate;
	D3DXMatrixTranslation(&matTempMove,
		m_pGameInfo->vecPos.x,
		m_pGameInfo->vecPos.y,
		m_pGameInfo->vecPos.z);

	matRotate *= matTempMove;

	D3DXMATRIX matMove;
	D3DXMatrixTranslation(&matMove, 0, 0, 0);

	matWorld = matRotate * matMove * matScale;


	
}

void Texture::Render()
{
	Update();
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTexture, NULL, &(m_vecSize / 2), &(m_pGameInfo->vecPos), DEFAULT_COLOR);
	D3DXMatrixIdentity(&matWorld);
	m_pSprite->SetTransform(&matWorld);
}


void Texture::Release()
{
	if(m_pTexture)
		m_pTexture->Release();
}

Texture::Texture(wstring fileName)
{

	SetDevice(fileName);

	bMultiFrame = false;
}

Texture::Texture(wstring fileName, int frameX, int frameY)
{
	SetDevice(fileName);

	if (frameX == 1 && frameY == 1)
		bMultiFrame = false;
	else
		bMultiFrame = true;

	iFrameX = frameX;
	iFrameY = frameY;
}

Texture::~Texture()
{
	map<wstring, CSprite*>::iterator iter= mapSprite.begin();
	for (; iter != mapSprite.end(); iter++)
	{
		if (iter->second)
		{
			delete iter->second;
		}
	}
	mapSprite.clear();
}

void Texture::SetDevice(wstring fileName)
{
	HRESULT hr;

	D3DXIMAGE_INFO ImageInfo;

	hr = D3DXGetImageInfoFromFile(fileName.c_str(), &ImageInfo);


	m_vecSize = { (float)ImageInfo.Width, (float)ImageInfo.Height, 0 };

	if (FAILED(hr))
	{
		return;
	}
	hr = D3DXCreateTextureFromFileEx(CDirect::GetInstance()->GetDevice(),
		fileName.c_str(),
		ImageInfo.Width,
		ImageInfo.Height,
		1, 0,
		ImageInfo.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		m_ColorKey,
		NULL,
		NULL,
		&m_pTexture);

	if (FAILED(hr))
	{
		MessageBox(g_hWnd, L"이미지 파일을 찾을수 없습니다!", fileName.c_str(), MB_OK);
		return;
	}

	m_pSprite = CDirect::GetInstance()->GetSprite();
}
