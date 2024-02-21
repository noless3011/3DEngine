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

Matrix mymatrix;
Vector scale;
Mesh mesh;
MeshRenderer meshRenderer;
void App::Start() {
	std::vector<Vertex> vertices = {
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
		0, 2, 1, //face front
		0, 3, 2,
		2, 3, 4, //face top
		2, 4, 5,
		1, 2, 5, //face right
		1, 5, 6,
		0, 7, 4, //face left
		0, 4, 3,
		5, 4, 7, //face back
		5, 7, 6,
		0, 6, 7, //face bottom
		0, 1, 6
	};
	mesh = Mesh(vertices, triangles);
	meshRenderer = MeshRenderer(mesh);
	
	

	mymatrix = {

	};
	
	scale = {
		DirectX::XMVectorSet(1, 1, 1, 1)

	};

	mymatrix = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationY(13.65) *
			DirectX::XMMatrixRotationX(8.65) *
			DirectX::XMMatrixTranslation(0, 0, 3) *
			DirectX::XMMatrixPerspectiveFovLH(1.57f, 1.33f, 0.1, 1000)
		)
	};

	wnd.Gfx().globalBuffers().AddGlobalBuffer(mymatrix, "MyMatrix");

	wnd.Gfx().globalBuffers().AddGlobalBuffer(scale, "Scale");
}


void App::Update() {
	
	wnd.ChangeWindowName(std::to_wstring(clock->Now()).c_str());
	
	scale = {
		DirectX::XMVectorSet(sin(clock->Now()), 1, 1, 1)
	};

	//wnd.Gfx().globalBuffers().ChangeGlobalBuffer(mymatrix, "MyMatrix");
	wnd.Gfx().globalBuffers().ChangeGlobalBuffer(scale, "Scale");
	//wnd.Gfx().DrawTest(clock->Now());
	wnd.Gfx().Draw(meshRenderer);
}