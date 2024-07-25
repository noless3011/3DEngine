#pragma once
enum KEYCODE {
	Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M
};
class EventContext {
public:
	virtual ~EventContext() = default;
};

class KeyEvent : public EventContext {
public:
	KeyEvent(KEYCODE keyPressed);
	KEYCODE keyPressed;
};

class MouseEvent : public EventContext {
public:
	MouseEvent(int x, int y) : x(x), y(y) {};
	int x, y;
};
