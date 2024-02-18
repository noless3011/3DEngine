#include "App.h"


App::App() : wnd(800, 600, L"My window") {
	


}


int App::Go() {
	MSG msg = { };
	bool hasMessage = true;
	
	clock = std::make_unique<Clock>();
	Start();
	while (true)
	{
		hasMessage = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
		if (msg.message == WM_QUIT) {
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		Update();
		wnd.Gfx().EndFrame();

	}
	return (int)msg.wParam;
}


Mesh mesh;
MeshRenderer meshRenderer;
void App::Start() {
	std::vector<Vertex> vertices = {
		{0, 0.5, 0},
		{0.5, -0.5, 0},
		{-0.5, -0.5, 0},
		{1, 1, 0}
	};
	std::vector<int> triangles = {
		0, 2, 1, 0, 1, 3
	};
	mesh = Mesh(vertices, triangles);
	meshRenderer = MeshRenderer(mesh);
}


void App::Update() {
	
	wnd.ChangeWindowName(std::to_wstring(clock->Now()).c_str());
	
	
	wnd.Gfx().Draw(meshRenderer);
}