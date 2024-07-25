#include "stdafx.h"
#include "App.h"
#include "Entity.h"

App::App(unsigned int _x, unsigned int _y) {
	width = _x;
	height = _y;
	pWnd = std::make_shared<Window>(width, height, L"My fps game");
}

App::App() {
	height = 600;
	width = 800;
	pWnd = std::make_shared<Window>(width, height, L"My fps game");
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
		pWnd->Gfx().StartFrame();
		Update();
		pWnd->Gfx().EndFrame();
	}

	return (int)msg.wParam;
}

Mesh mesh;
MeshRenderer meshRenderer;
float x, y, z;
Entity entity;
void App::Start() {
	Entity* pEntity = &entity;
	EventAction<MouseEvent> action = [pEntity](MouseEvent e) {
		pEntity->x += e.x;
		pEntity->y += e.y;
		std::wstring x = std::to_wstring(pEntity->x);
		std::wstring y = std::to_wstring(pEntity->y);
		App::GetInstance().getWindow()->ChangeWindowName((x + L" - " + y).c_str());
		return true;
	};
	entity.addEventListener<MouseEvent>(action);
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
}

void App::Update() {
	if (pWnd->Input().IsKeyHold(A)) {
		x += 0.3 * Clock::deltaTime * 2;
	}
	if (pWnd->Input().IsKeyHold(D)) {
		x -= 0.3 * Clock::deltaTime * 2;
	}
	if (pWnd->Input().IsKeyHold(W)) {
		z += 0.3 * Clock::deltaTime * 2;
	}
	if (pWnd->Input().IsKeyHold(S)) {
		z -= 0.3 * Clock::deltaTime * 2;
	}
	if (pWnd->Input().IsKeyHold(Z)) {
		y += 0.3 * Clock::deltaTime * 2;
	}
	if (pWnd->Input().IsKeyHold(X)) {
		y -= 0.3 * Clock::deltaTime * 2;
	}
}

std::shared_ptr<Window> App::getWindow()
{
	return pWnd;
}