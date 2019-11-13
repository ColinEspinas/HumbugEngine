#pragma once
#include "HumbugEngine/Utils/GameHeader.h"
#include "HumbugEngine/Components/Camera.h"
#include "HumbugEngine/Core/Input.h"
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Objects/Portal.h"
#include "HumbugEngine/Objects/Player.h"
#include "HumbugEngine/Core/Timer.h"
#include "HumbugEngine/Core/Scene.h"
#include "HumbugEngine/Core/Sky.h"
#include "HumbugEngine/Core/Lighting.h"
#include "HumbugEngine/FreeCamera.h"
#include <GL/glew.h>
#include <windows.h>
#include <memory>
#include <vector>

class Engine {
public:
  Engine();
  ~Engine();

  int Run();
  void Update();
  void Render(const Camera& cam, GLuint curFBO, const Portal* skipPortal);
  void LoadScene(int ix);

  LRESULT WindowProc(HWND hCurWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  const Player& GetPlayer() const { return *player; }
  float NearestPortalDist() const;

private:
  void CreateGLWindow();
  void InitGLObjects();
  void DestroyGLObjects();
  void SetupInputs();
  void ConfineCursor();
  void ToggleFullscreen();

  HDC   hDC;           // device context
  HGLRC hRC;				   // opengl context
  HWND  hWnd;				   // window
  HINSTANCE hInstance; // process id

  LONG iWidth;         // window width
  LONG iHeight;        // window height
  bool isFullscreen;   // fullscreen state

  bool shouldConfineCursor;
  bool shouldDrawColliders;

  Camera main_cam;
  Input input;
  Timer timer;

  Lighting lighting;

  std::vector<std::shared_ptr<Object>> vObjects;
  std::shared_ptr<Sky> sky;

  std::shared_ptr<FreeCamera> freeCamera;
  std::shared_ptr<Player> player;
  std::shared_ptr<Playable> curFocus;

  GLint occlusionCullingSupported;

  std::vector<std::shared_ptr<Scene>> vScenes;
  std::shared_ptr<Scene> curScene;
};
