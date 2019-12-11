#pragma once
#include "HumbugEngine/GameHeader.h"
#include "HumbugEngine/Camera.h"
#include "HumbugEngine/Input.h"
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Portal.h"
#include "HumbugEngine/Player.h"
#include "HumbugEngine/Timer.h"
#include "HumbugEngine/Scene.h"
#include "HumbugEngine/Sky.h"
#include "HumbugEngine/Lighting.h"
#include "HumbugEngine/FreeCamera.h"
#include "HumbugEngine/UIQuad.h"
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

  Lighting lighting = Lighting(vLights);

  std::vector<std::shared_ptr<Object>> vObjects;
  std::vector<std::shared_ptr<Portal>> vPortals;
  std::vector<std::shared_ptr<Light>> vLights;
  std::vector<std::shared_ptr<UIQuad>> vUIQuads;

  std::shared_ptr<Sky> sky;

  std::shared_ptr<FreeCamera> freeCamera;
  std::shared_ptr<Player> player;
  std::shared_ptr<Playable> curFocus;

  GLint occlusionCullingSupported;

  std::vector<std::shared_ptr<Scene>> vScenes;
  std::shared_ptr<Scene> curScene;
};
