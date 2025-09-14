#pragma once

struct SDL_Window;
typedef struct SDL_GLContextState* SDL_GLContext;
struct ImGuiIO;

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	void Show();
private:
	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;
	ImGuiIO* m_IO;
};