#include <d3dx9.h>
#include <dinput.h>
#include <d3d9.h>
#include "resource.h"

#include <dshow.h>

#define WM_GRAPHNOTIFY  WM_APP + 1


#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "Winmm.lib")




//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND						g_hWnd = NULL;
LPDIRECT3D9					g_pD3D = NULL;
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;

LPDIRECTINPUT8			g_pDin;							// the pointer to our DirectInput interface
LPDIRECTINPUTDEVICE8	g_pDinKeyboard;					// the pointer to the keyboard device
BYTE					g_Keystate[256];				// the storage for the key-information

LPDIRECT3DVERTEXBUFFER9		g_pSkyboxVertexBuffer = NULL;
LPDIRECT3DTEXTURE9			g_SkyTextures[6];
D3DLIGHT9					g_pLight;

const int					SCREEN_WIDTH = 800;
const int					SCREEN_HEIGHT = 600;
LPD3DXMESH              g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*           g_pMeshMaterials = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9*     g_pMeshTextures = NULL; // Textures for our mesh
DWORD                   g_dwNumMaterials = 0L;   // Number of mesh materials

IGraphBuilder *pGraph = NULL;
IMediaControl *pControl = NULL;
IMediaEventEx *pEvent = NULL;

HRESULT InitDInput(HINSTANCE hInstance, HWND hWnd);

VOID DetectInput();
VOID CleanDInput();

typedef struct _TVertex
{
	// Default ctor
	_TVertex() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; tu = 0.0f; tv = 0.0f; }

	_TVertex(float fX, float fY, float fZ, float fW, float fTu, float fTv)
	{
		x = fX; y = fY; z = fZ; w = fW; tu = fTu; tv = fTv;
	}

	float x, y, z, w;	// Screen-space position
	float tu, tv;		// Texture coordinates
}TVertex;

// ----------------
double						g_dCurTime;
double						g_dLastTime;

float						g_fYaw = 0;
float						g_fZaw = 0;
float						g_fXaw = 0;
float						g_fPitch;

// Vectors used for simple "camera"
D3DXVECTOR3	g_vecLook(0.0f, 0.0f, 100.0f);		// Look Vector
D3DXVECTOR3	g_vecUp(0.0f, 1.0f, 0.0f);    // Up Vector
D3DXVECTOR3	g_vecRight(1.0f, 0.0f, 0.0f);    // Right Vector
D3DXMATRIX  g_matView;

// We need a vertex structure.  Typically you may want to create a separate Vertex
// class for this but in this simple example we will just create a global structure.

// ----------------
// SKYBOX VERTEX DEFINITION
// This little vertex structure follows the Flexible Vertex Flags: D3DFVF_XYZ | D3DFVF_TEX1
struct TTexVertex
{
	float x, y, z;		// 3D world position
	float tu, tv;		// Texture coordinates
};

// 24 vertices = 6 faces (cube) * 4 vertices per face
//
// Example diagram of "front" quad
// The numbers are vertices
// 
// 2  __________ 4
//   |\         |
//	 |  \       |
//   |    \     |
//   |      \   |
// 1 |        \ | 3
//	  ----------	 

TTexVertex g_SkyboxMesh[24] =
{
	// Front quad, NOTE: All quads face inward
	{ -20.0f, -20.0f,  20.0f,  0.0f, 1.0f },
	{ -20.0f,  20.0f,  20.0f,  0.0f, 0.0f },
	{ 20.0f, -20.0f,  20.0f,  1.0f, 1.0f },
	{ 20.0f,  20.0f,  20.0f,  1.0f, 0.0f },

	// Back quad
	{ 20.0f, -20.0f, -20.0f,  0.0f, 1.0f },
	{ 20.0f,  20.0f, -20.0f,  0.0f, 0.0f },
	{ -20.0f, -20.0f, -20.0f,  1.0f, 1.0f },
	{ -20.0f,  20.0f, -20.0f,  1.0f, 0.0f },

	// Left quad
	{ -20.0f, -20.0f, -20.0f,  0.0f, 1.0f },
	{ -20.0f,  20.0f, -20.0f,  0.0f, 0.0f },
	{ -20.0f, -20.0f,  20.0f,  1.0f, 1.0f },
	{ -20.0f,  20.0f,  20.0f,  1.0f, 0.0f },

	// Right quad
	{ 20.0f, -20.0f,  20.0f,  0.0f, 1.0f },
	{ 20.0f,  20.0f,  20.0f,  0.0f, 0.0f },
	{ 20.0f, -20.0f, -20.0f,  1.0f, 1.0f },
	{ 20.0f,  20.0f, -20.0f,  1.0f, 0.0f },

	// Top quad
	{ -20.0f,  20.0f,  20.0f,  0.0f, 1.0f },
	{ -20.0f,  20.0f, -20.0f,  0.0f, 0.0f },
	{ 20.0f,  20.0f,  20.0f,  1.0f, 1.0f },
	{ 20.0f,  20.0f, -20.0f,  1.0f, 0.0f },

	// Bottom quad
	{ -20.0f, -20.0f, -20.0f,  0.0f, 1.0f },
	{ -20.0f, -20.0f,  20.0f,  0.0f, 0.0f },
	{ 20.0f, -20.0f, -20.0f,  1.0f, 1.0f },
	{ 20.0f, -20.0f,  20.0f,  1.0f, 0.0f }
};

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void 	Initialize();
void 	ShutDown();
void 	RenderFrame();
bool 	BuildSkybox();
void	ProcessInput(float fElapsedTime);


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	WNDCLASSEX winClass;
	MSG        uMsg;
	float	fElpasedTime;

	memset(&uMsg, 0, sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hIconSm = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;

	if (!RegisterClassEx(&winClass))
		return E_FAIL;

	g_hWnd = CreateWindowEx(NULL, "MY_WINDOWS_CLASS",
		"Proiect - StatieSpatiala - Grigorciuc Bogdan Andrei",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600, NULL, NULL, hInstance, NULL);


	if (g_hWnd == NULL)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);


	Initialize();
	InitDInput(hInstance, g_hWnd);

	// Construct a skybox mesh.
	// Load skybox texture images
	if (!BuildSkybox())
		return 0;		// stop application on failure to build the skybox


	// ---------
	// Main Loop
	// ---------
	while (uMsg.message != WM_QUIT)
	{
		if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		else
		{
			// Goofy little timer
			g_dCurTime = timeGetTime();
			fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
			g_dLastTime = g_dCurTime;

			// Process the keyboard presses
			DetectInput();    // update the input data before rendering
			ProcessInput(fElpasedTime);

			// Render the current frame
			RenderFrame();


		}
	}

	// -------------------------
	// Release directx resources
	// -------------------------
	//ShutDown();

	UnregisterClass("MY_WINDOWS_CLASS", winClass.hInstance);

	return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND   hWnd,
	UINT   msg,
	WPARAM wParam,
	LPARAM lParam)
{
	// Matrix used for rotation
	D3DXMATRIX matRotation;

	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}

	case WM_DESTROY:
	{
		CleanDInput();
		ShutDown();
		PostQuitMessage(0);

	}
	break;

	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: Initialize()
// Desc: Create DirectX interface objects
//		 Initialize the view matrix.
//-----------------------------------------------------------------------------
void Initialize()
{


	// Create a direct 3D interface object
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		// TO DO: Respond to failure of Direct3DCreate8
		return;
	}

	D3DDISPLAYMODE d3ddm;

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		// TO DO: Respond to failure of GetAdapterDisplayMode
		return;
	}

	//HRESULT hr;
	IGraphBuilder *pGraph = NULL;
	IMediaControl *pControl = NULL;
	IMediaEventEx *pEvent = NULL;
	//Create filter graph
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	//Create media control and events
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);
	//Load a file
	hr = pGraph->RenderFile(L"houston_apollo13_problem.mp3", NULL);
	//Set window for events
	//pEvent->SetNotifyWindow((OAHWND)g_hwnd, WM_GRAPHNOTIFY, 0);
	//Play media control
	pControl->Run();
	// 
	if (FAILED(hr = g_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		d3ddm.Format, D3DUSAGE_DEPTHSTENCIL,
		D3DRTYPE_SURFACE, D3DFMT_D16)))
	{
		if (hr == D3DERR_NOTAVAILABLE)
			// POTENTIAL PROBLEM: We need at least a 16-bit z-buffer!
			return;
	}

	//
	// Do we support hardware vertex processing? if so, use it. 
	// If not, downgrade to software.
	//

	D3DCAPS9 d3dCaps;

	if (FAILED(g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &d3dCaps)))
	{
		// TO DO: Respond to failure of GetDeviceCaps
		return;
	}

	DWORD dwBehaviorFlags = 0;

	if (d3dCaps.VertexProcessingCaps != 0)
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//
	// Everything checks out - create a simple, windowed device.
	//

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		dwBehaviorFlags, &d3dpp, &g_pD3DDevice)))
	{
		// TO DO: Respond to failure of CreateDevice
		return;
	}

	// ------------------------
	// Setup View Matrix Values
	D3DXMatrixIdentity(&g_matView);
	D3DXMatrixLookAtLH(&g_matView, &D3DXVECTOR3(0.0f, 0.0f, 0.1f),
		&D3DXVECTOR3(0.0f, 0.0f, -20.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));





	LPD3DXBUFFER pD3DXMtrlBuffer;

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX("esspresor.x", D3DXMESH_SYSTEMMEM,
		g_pD3DDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX("..\\esspresor.x", D3DXMESH_SYSTEMMEM,
			g_pD3DDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
			&g_pMesh)))
		{
			MessageBox(NULL, "Could not find esspresor.x", "Meshes.exe", MB_OK);
			return;// E_FAIL;
		}
	}

	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];

	for (DWORD i = 0; i<g_dwNumMaterials; i++)
	{
		// Copy the material
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

		g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// Create the texture
			if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice,
				d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[i])))
			{
				// If texture is not in current folder, try parent folder
				const TCHAR* strPrefix = TEXT("..\\");
				const int lenPrefix = lstrlen(strPrefix);
				TCHAR strTexture[MAX_PATH];
				lstrcpyn(strTexture, strPrefix, MAX_PATH);
				lstrcpyn(strTexture + lenPrefix, d3dxMaterials[i].pTextureFilename, MAX_PATH - lenPrefix);
				// If texture is not in current folder, try parent folder
				if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice,
					strTexture,
					&g_pMeshTextures[i])))
				{
					MessageBox(NULL, "Could not find texture map", "Statie.exe", MB_OK);
				}
			}
		}
	}

	// Done with the material buffer
	pD3DXMtrlBuffer->Release();

	//Shows you how to compute a bounding sphere
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer = NULL;
	D3DXVECTOR3* Vertices = NULL;
	D3DXVECTOR3 Center;
	FLOAT Radius;
	DWORD FVFVertexSize = D3DXGetFVFVertexSize(g_pMesh->GetFVF());
	g_pMesh->GetVertexBuffer(&VertexBuffer);
	VertexBuffer->Lock(0, 0, (VOID**)&Vertices, D3DLOCK_DISCARD);//copiez date in buff de vertex
	D3DXComputeBoundingSphere(Vertices, g_pMesh->GetNumVertices(), FVFVertexSize, &Center, &Radius);
	VertexBuffer->Unlock();//deblocheaza buff de vertexuri
	VertexBuffer->Release();



}

/*void InitDirectShow(HWND hWnd)
{
//Create Filter Graph
HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);

//Create Media Control and Events
hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
hr = pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);

//Load a file
hr = pGraph->RenderFile(L"test.avi", NULL);

//Set window for events
pEvent->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);

//Play media control
pControl->Run();


//	return S_OK;
}*/

//-----------------------------------------------------------------------------
// Name: ShutDown()
// Desc: 
//-----------------------------------------------------------------------------
void ShutDown()
{
	// Release the textures
	for (int i = 0; i < 6; i++)
	{
		g_SkyTextures[i]->Release();
		g_SkyTextures[i] = NULL;
	}

	// Release the vertex buffer
	if (g_pSkyboxVertexBuffer)
	{
		g_pSkyboxVertexBuffer->Release();
		g_pSkyboxVertexBuffer = NULL;
	}

	//Release the mesh
	if (g_pMesh)
	{
		g_pMesh->Release();
		g_pMesh = NULL;
	}

	if (g_pD3DDevice != NULL)
		g_pD3DDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();

	if (pControl)
		pControl->Release();
}

//-----------------------------------------------------------------------------
// Name: ProcessInput()
// Desc: Poll the keyboard using the Win32 function GetKeyboardState().
//       
// Control:
//			Left arrow  = yaw left
//			Right arrow = yaw right
//			Up arrow	= pitch up
//			Down arrow	= pitch down
//			'Z' key		= roll CCW
//			'X' key		= roll CW
//-----------------------------------------------------------------------------
void ProcessInput(float fElapsedTime)
{
	D3DXMATRIX matRotation;
	//unsigned char keys[256];
	//GetKeyboardState(keys);

	if (g_Keystate[DIK_ESCAPE] & 0x80) {
		PostMessage(g_hWnd, WM_DESTROY, 0, 0);
	}

	// Rotate Camera Left (Yaw) 
	if (g_Keystate[DIK_LEFT] & 0x80)
	{
		// Rotate "camera" (view matrix) left
		D3DXMatrixRotationAxis(&matRotation, &g_vecUp, -2.0f * fElapsedTime);
		D3DXVec3TransformNormal(&g_vecLook, &g_vecLook, &matRotation);
		D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &matRotation);
	}

	// Rotate Camera Right (Yaw)
	if (g_Keystate[DIK_RIGHT] & 0x80)
	{
		// Rotate "camera" (view matrix) right
		D3DXMatrixRotationAxis(&matRotation, &g_vecUp, 2.0f * fElapsedTime);
		D3DXVec3TransformNormal(&g_vecLook, &g_vecLook, &matRotation);
		D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &matRotation);
	}

	// Rotate Camera Up (Pitch)
	if (g_Keystate[DIK_UP] & 0x80)
	{
		// Rotate "camera" (view matrix) up
		D3DXMatrixRotationAxis(&matRotation, &g_vecRight, -1.0f * fElapsedTime);
		D3DXVec3TransformNormal(&g_vecLook, &g_vecLook, &matRotation);
		D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &matRotation);
	}

	// Rotate Camera Down (Pitch)
	if (g_Keystate[DIK_DOWN] & 0x80)
	{
		// Rotate "camera" (view matrix) down
		D3DXMatrixRotationAxis(&matRotation, &g_vecRight, 1.0f * fElapsedTime);
		D3DXVec3TransformNormal(&g_vecLook, &g_vecLook, &matRotation);
		D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &matRotation);
	}

	// Rotate Camera CCW (Roll)
	if (g_Keystate[DIK_Z] & 0x80)
	{
		// Rotate "camera" (view matrix) up
		//D3DXMatrixTranslation( &matRotation, &g_vecLook, -1.0f * fElapsedTime);
		D3DXMatrixRotationAxis(&matRotation, &g_vecLook, -1.0f * fElapsedTime);
		D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &matRotation);
		D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &matRotation);
	}

	// Rotate Camera CW (Roll)
	if (g_Keystate[DIK_X] & 0x80)
	{
		// Rotate "camera" (view matrix) down
		D3DXMatrixRotationAxis(&matRotation, &g_vecLook, 1.0f * fElapsedTime);
		D3DXVec3TransformNormal(&g_vecRight, &g_vecRight, &matRotation);
		D3DXVec3TransformNormal(&g_vecUp, &g_vecUp, &matRotation);
	}

	// ---------------
	// Move
	if (g_Keystate[DIK_D] & 0x80)	g_fXaw += 1.0f * fElapsedTime;
	if (g_Keystate[DIK_A] & 0x80)	g_fXaw -= 1.0f * fElapsedTime;
	if (g_Keystate[DIK_W] & 0x80)	g_fZaw += 5.0f * fElapsedTime;
	if (g_Keystate[DIK_S] & 0x80)	g_fZaw -= 20.0f * fElapsedTime;
	if (g_Keystate[DIK_Q] & 0x80)   g_fYaw += 60.0f * fElapsedTime;
	if (g_Keystate[DIK_E] & 0x80)	g_fYaw -= 60.0f * fElapsedTime;

}

//-----------------------------------------------------------------------------
// Name: BuildSkybox()
// Desc: Creates vertex buffer used to hold the skybox mesh vertices.
//		 Loads all 6 textures, 1 texture image per cube face.
//-----------------------------------------------------------------------------
bool BuildSkybox()
{
	// Why did I use an HRESULT instead of a bool or int?  Well since DirectX is
	// written in COM the typical return values are HRESULTs.
	HRESULT hRet;


	// Create our vertex buffer ( 24 vertices (4 verts * 6 faces) )
	hRet = g_pD3DDevice->CreateVertexBuffer(sizeof(TTexVertex) * 24, 0, D3DFVF_XYZ | D3DFVF_TEX1,
		D3DPOOL_MANAGED, &g_pSkyboxVertexBuffer, NULL);
	if (FAILED(hRet))
		return false;

	void *pVertices = NULL;

	// Copy the skybox mesh into the vertex buffer.  I initialized the whole mesh array
	// above in global space.
	g_pSkyboxVertexBuffer->Lock(0, sizeof(TTexVertex) * 24, (void**)&pVertices, 0); //copiaza in buffer de vertexuri
	memcpy(pVertices, g_SkyboxMesh, sizeof(TTexVertex) * 24);
	g_pSkyboxVertexBuffer->Unlock();//release la lock

	// Load Textures.  I created a global array just to keep things simple.  The order of the images
	// is VERY important.  The reason is the skybox mesh (g_SkyboxMesh[]) array was created above
	// in this order. (ie. front, back, left, etc.)
	hRet = D3DXCreateTextureFromFile(g_pD3DDevice, ("Skybox-front.tga"), &g_SkyTextures[0]);
	hRet |= D3DXCreateTextureFromFile(g_pD3DDevice, ("Skybox-back.tga"), &g_SkyTextures[1]);
	hRet |= D3DXCreateTextureFromFile(g_pD3DDevice, ("Skybox-left.tga"), &g_SkyTextures[2]);
	hRet |= D3DXCreateTextureFromFile(g_pD3DDevice, ("Skybox-right.tga"), &g_SkyTextures[3]);
	hRet |= D3DXCreateTextureFromFile(g_pD3DDevice, ("Skybox-top.tga"), &g_SkyTextures[4]);
	hRet |= D3DXCreateTextureFromFile(g_pD3DDevice, ("Skybox-bottom.tga"), &g_SkyTextures[5]);
	if (FAILED(hRet))
		return false;

	// Set up a projection matrix
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f),
		800 / 600, 0.1f, 100.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);


	// What about the ugly seams inbetween the cube face textures?  Well we need to get rid of them
	// somehow.
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	// If we get here then we succeeded!
	return true;
}

//-----------------------------------------------------------------------------
// Name: SetupLights()
// Desc: Sets up the lights and materials for the scene.
//-----------------------------------------------------------------------------
VOID SetupLights()
{
	// Set up a material. The material here just has the diffuse and ambient
	// colors set to yellow. Note that only one material can be used at a time.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 0.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pD3DDevice->SetMaterial(&mtrl);

	// Set up a white, directional light, with an oscillating direction.
	// Note that many lights may be active at a time (but each one slows down
	// the rendering of our scene). However, here we are just using one. Also,
	// we need to set the D3DRS_LIGHTING renderstate to enable lighting
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = D3DXVECTOR3(-320.0f, 0.0f, 100.0f);
	//vecDir = D3DXVECTOR3(1, 1.0f, 1 );
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Finally, turn on some ambient light.
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

//-----------------------------------------------------------------------------
// Name: RenderFrame()
// Desc: 
//-----------------------------------------------------------------------------
void RenderFrame()
{
	D3DXMATRIX matWorld;


	if (NULL == g_pD3DDevice)
		return;

	// Clear the background
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	// Setup the lights and materials
	SetupLights();

	D3DXVec3Normalize(&g_vecLook, &g_vecLook);
	D3DXVec3Cross(&g_vecRight, &g_vecUp, &g_vecLook);
	D3DXVec3Normalize(&g_vecRight, &g_vecRight);
	D3DXVec3Cross(&g_vecUp, &g_vecLook, &g_vecRight);
	D3DXVec3Normalize(&g_vecUp, &g_vecUp);

	// Alter the view matrix so its centered for the skybox
	// Also, since we are rotating the camera, update the Right, Look, and Up vectors of that
	// matrix.
	g_matView._41 = 0.0f;
	g_matView._42 = -0.4f;
	g_matView._43 = 0.0f;
	g_matView._11 = g_vecRight.x;
	g_matView._21 = g_vecRight.y;
	g_matView._31 = g_vecRight.z;

	g_matView._12 = g_vecUp.x;
	g_matView._22 = g_vecUp.y;
	g_matView._32 = g_vecUp.z;

	g_matView._13 = g_vecLook.x;
	g_matView._23 = g_vecLook.y;
	g_matView._33 = g_vecLook.z;


	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_matView);


	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	// Render the sky box
	g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	g_pD3DDevice->SetStreamSource(0, g_pSkyboxVertexBuffer, 0, sizeof(TTexVertex));

	// Set the world matrix to identity for the skybox
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);


	for (ULONG i = 0; i < 6; ++i)
	{
		// Set the texture for this primitive
		g_pD3DDevice->SetTexture(0, g_SkyTextures[i]);

		// Render the face (one strip per face from the vertex buffer)  There are 2 primitives per face.
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);

	} // Next side
	  // -------------------------------------------------------------

	  // -------------------------------------------------------------       
	  // Place and render mesh...
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matMove;
	D3DXMATRIX scalare;
	D3DXMatrixIdentity(&scalare);
	D3DXMatrixScaling(&scalare, 0.5, 0.5, 0.5);

	// Set the world matrix to identity for the teapot
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//D3DXMatrixRotationYawPitchRoll(&matRotation, D3DXToRadian(g_fYaw), D3DXToRadian(g_fPitch), 0.0f);
	D3DXMatrixTranslation(&matTranslation, g_fXaw, 0.0f, g_fZaw);
	matWorld = scalare * matTranslation;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	
	//matWorld = matWorld * scalare;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Must turn lighting back on for the mesh
	// Set up rendering states for the sky box
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);


	for (DWORD i = 0; i<g_dwNumMaterials; i++)
	{
		// Set the material and texture for this subset
		g_pD3DDevice->SetMaterial(&g_pMeshMaterials[i]);
		g_pD3DDevice->SetTexture(0, g_pMeshTextures[i]);

		// Draw the mesh subset
		g_pMesh->DrawSubset(i);
	}
	// -------------------------------------------------------------       


	// --------------
	g_pD3DDevice->EndScene();

	// Present the scene to the front buffer
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//-----------------------------------------------------------------------------
// Name: DetectInput(void)
// Desc: This is the function that gets the latest input data
//-----------------------------------------------------------------------------
VOID DetectInput()
{
	// get access if we don't have it already
	g_pDinKeyboard->Acquire();
	//g_pDinmouse->Acquire();

	// get the input data
	g_pDinKeyboard->GetDeviceState(256, (LPVOID)g_Keystate);
	//g_pDinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&g_pMousestate);


}

//-----------------------------------------------------------------------------
// Name: CleanDInput(void)
// Desc: This is the function that closes DirectInput
//-----------------------------------------------------------------------------
VOID CleanDInput()
{
	g_pDinKeyboard->Unacquire();    // make sure the keyboard is unacquired
	//g_pDinmouse->Unacquire();    // make sure the mouse in unacquired
	g_pDin->Release();    // close DirectInput before exiting
}

//-----------------------------------------------------------------------------
// Name: InitDInput(HINSTANCE hInstance, HWND hWnd)
// Desc: Initializes DirectInput
//-----------------------------------------------------------------------------
HRESULT InitDInput(HINSTANCE hInstance, HWND hWnd)
{
	// create the DirectInput interface
	DirectInput8Create(hInstance,    // the handle to the application
		DIRECTINPUT_VERSION,    // the compatible version
		IID_IDirectInput8,    // the DirectInput interface version
		(void**)&g_pDin,    // the pointer to the interface
		NULL);    // COM stuff, so we'll set it to NULL

				  // create the keyboard device
	g_pDin->CreateDevice(GUID_SysKeyboard,    // the default keyboard ID being used
		&g_pDinKeyboard,    // the pointer to the device interface
		NULL);    // COM stuff, so we'll set it to NULL

				  // create the mouse device
	//g_pDin->CreateDevice(GUID_SysMouse,
	//	&g_pDinmouse,  // the pointer to the device interface
	//	NULL); // COM stuff, so we'll set it to NULL

			   // set the data format to keyboard format
	g_pDinKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// set the data format to mouse format
	//g_pDinmouse->SetDataFormat(&c_dfDIMouse);

	// set the control we will have over the keyboard
	g_pDinKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// set the control we will have over the mouse
	//g_pDinmouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

	return S_OK;
}