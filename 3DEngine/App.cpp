#include "App.h"



App::App(unsigned int _x, unsigned int _y) : wnd(_x, _y, L"My window") {
	width = _x;
	height = _y;
}

App::App() : wnd(800, 600, L"My window") {
	height = 600;
	width = 800;
}


int App::Go() {
	MSG msg = { };
	bool hasMessage = true;
	
	Start();
	while (true)
	{
		hasMessage = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
		if (msg.message == WM_QUIT) {
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		Clock::CalculateDeltaTime();
		wnd.Gfx().StartFrame();
		Update();
		wnd.Gfx().EndFrame();

	}
	
	return (int)msg.wParam;
}

Matrix mymatrix;
Vector scale;
Mesh mesh;
MeshRenderer meshRenderer;
float currentVAngle = 0;
float currentHAngle = 0;
float currentDist = 3;
void App::Start() {
	std::vector<Vector3> vertices = {
		{0, 0, 0},
		{1, 0, 0},
		{1, 1, 0},
		{0, 1, 0},
		{0, 1, 1},
		{1, 1, 1},
		{1, 0, 1},
		{0, 0, 1}
	};

	

	std::vector<int> triangles = {
		0, 1, 2, //face front
		0, 2, 3,
		2, 4, 3, //face top
		2, 5, 4,
		1, 5, 2, //face right
		1, 6, 5,
		0, 4, 7, //face left
		0, 3, 4,
		5, 7, 4, //face back
		5, 6, 7,
		0, 7, 6, //face bottom
		0, 6, 1
	};
	mesh = Mesh(vertices, triangles);
	meshRenderer = MeshRenderer(mesh);
	
	

	mymatrix = {

	};
	
	scale = {
		DirectX::XMVectorSet(1, 1, 1, 1)

	};


	wnd.Gfx().globalBuffersSystem().AddGlobalBuffer(mymatrix, "MyMatrix");

	wnd.Gfx().globalBuffers().AddGlobalBuffer(scale, "Scale");
}


void App::Update() {
	
	scale = {
		DirectX::XMVectorSet(sin(Clock::GetClock().Now()), 1, 1, 1)
	};
	if (wnd.Input().IsKeyHold(A)) {
		currentVAngle += 0.3 * Clock::deltaTime * 2;
	}
	if (wnd.Input().IsKeyHold(D)) {
		currentVAngle -= 0.3 * Clock::deltaTime * 2;
	}
	if (wnd.Input().IsKeyHold(W)) {
		currentHAngle += 0.3 * Clock::deltaTime * 2;
	}
	if (wnd.Input().IsKeyHold(S)) {
		currentHAngle -= 0.3 * Clock::deltaTime * 2;
	}
	if (wnd.Input().IsKeyHold(Z)) {
		currentDist += 0.3 * Clock::deltaTime * 2;
	}
	if (wnd.Input().IsKeyHold(X)) {
		currentDist -= 0.3 * Clock::deltaTime * 2;
	}
	

	std::wstringstream windowname;
	windowname << std::to_wstring(wnd.Input().GetAxis(MouseX)) << L" ----- " << std::to_wstring(wnd.Input().GetAxis(MouseY));
	wnd.ChangeWindowName(windowname.str().c_str());
	mymatrix = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationY(currentVAngle) *
			DirectX::XMMatrixRotationX(currentHAngle) *
			DirectX::XMMatrixTranslation(0, 0, currentDist) *
			DirectX::XMMatrixPerspectiveFovLH(1.57f, 1.33f, 0.1, 1000)
		)
	};
	wnd.Gfx().globalBuffersSystem().ChangeGlobalBuffer(mymatrix, "MyMatrix");
	wnd.Gfx().globalBuffers().ChangeGlobalBuffer(scale, "Scale");
	wnd.Gfx().Draw(meshRenderer);
}