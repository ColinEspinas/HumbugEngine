#include "HumbugEngine/Objects/Portal.h"
#include "HumbugEngine/Core/Engine.h"
#include <cassert>
#include <iostream>

Portal::Portal() : front(this), back(this) {
  m_portalFrame = AquireMesh("double_quad.obj");
  m_shader = AquireShader("portal");
  m_errShader = AquireShader("pink");
}

void Portal::Draw(const Camera& cam, GLuint curFBO) {
  assert(m_euler.x == 0.0f);
  assert(m_euler.z == 0.0f);

  //Draw pink to indicate end of render chain
  if (GH_REC_LEVEL <= 0) {
    DrawPink(cam);
    return;
  }

  //Find normal relative to camera
  Vector3 normal = Forward();
  const Vector3 camPos = cam.worldView.Inverse().Translation();
  const bool frontDirection = (camPos - m_pos).Dot(normal) > 0;
  const Warp* warp = (frontDirection ? &front : &back);
  if (frontDirection) {
    normal = -normal;
  }

  //Extra clipping to prevent artifacts
  const float extra_clip = GH_MIN(GH_ENGINE->NearestPortalDist() * 0.5f, 0.1f);

  //Create new portal camera
  Camera portalCam = cam;
  portalCam.ClipOblique(m_pos - normal*extra_clip, -normal);
  portalCam.worldView *= warp->delta;
  portalCam.width = GH_FBO_SIZE;
  portalCam.height = GH_FBO_SIZE;

  //Render portal's view from new camera
  m_frameBuf[GH_REC_LEVEL - 1].Render(portalCam, curFBO, warp->toPortal);
  cam.UseViewport();

  //Now we can render the portal texture to the screen
  const Matrix4 mv = LocalToWorld();
  const Matrix4 mvp = cam.Matrix() * mv;
  shader->Use();
  m_frameBuf[GH_REC_LEVEL - 1].Use();
  m_shader->SetMVP(mvp.m, mv.m);
  m_portalFrame->Draw();
}

void Portal::DrawPink(const Camera& cam) {
  const Matrix4 mv = LocalToWorld();
  const Matrix4 mvp = cam.Matrix() * mv;
  m_errShader->Use();
  m_errShader->SetMVP(mvp.m, mv.m);
  m_portalFrame->Draw();

#ifdef _DEBUG
  DebugDraw(cam, LocalToWorld());
#endif
}

Vector3 Portal::GetBump(const Vector3& a) const {
  const Vector3 n = Forward();
  return n * ((a - m_pos).Dot(n) > 0 ? 1.0f : -1.0f);
}

const Portal::Warp* Portal::Intersects(const Vector3& a, const Vector3& b, const Vector3& bump) const {
  const Vector3 n = Forward();
  const Vector3 p = m_pos + bump;
  const float da = n.Dot(a - p);
  const float db = n.Dot(b - p);
  if (da * db > 0.0f) {
    return nullptr;
  }
  const Matrix4 m = LocalToWorld();
  const Vector3 d = a + (b - a) * (da / (da - db)) - p;
  const Vector3 x = (m * Vector4(1, 0, 0, 0)).XYZ();
  if (std::abs(d.Dot(x)) >= x.Dot(x)) {
    return nullptr;
  }
  const Vector3 y = (m * Vector4(0, 1, 0, 0)).XYZ();
  if (std::abs(d.Dot(y)) >= y.Dot(y)) {
    return nullptr;
  }
  return (da > 0.0f ? &front : &back);
}

float Portal::DistTo(const Vector3& pt) const {
  //Get world delta
  const Matrix4 localToWorld = LocalToWorld();
  const Vector3 v = pt - localToWorld.Translation();

  //Get axes
  const Vector3 x = localToWorld.XAxis();
  const Vector3 y = localToWorld.YAxis();

  //Find closest point
  const float px = GH_CLAMP(v.Dot(x) / x.MagSq(), -1.0f, 1.0f);
  const float py = GH_CLAMP(v.Dot(y) / y.MagSq(), -1.0f, 1.0f);
  const Vector3 closest = x*px + y*py;

  //Calculate distance to closest point
  return (v - closest).Mag();
}

void Portal::Connect(std::shared_ptr<Portal>& a, std::shared_ptr<Portal>& b) {
  Connect(a->front, b->back);
  Connect(b->front, a->back);
}

void Portal::Connect(Warp& a, Warp& b) {
  a.toPortal = b.fromPortal;
  b.toPortal = a.fromPortal;
  a.delta = a.fromPortal->LocalToWorld() * b.fromPortal->WorldToLocal();
  b.delta = b.fromPortal->LocalToWorld() * a.fromPortal->WorldToLocal();
  a.deltaInv = b.delta;
  b.deltaInv = a.delta;
}

void Portal::DebugDraw(const Camera & cam, const Matrix4 & objMat)
{
	glDepthFunc(GL_ALWAYS);
	glUseProgram(0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 1.0f);

	Matrix4 mat;
	// TODO: fill 'mat' with positions
	
	const Matrix4 m = cam.Matrix() * objMat * mat;
	
	for (int ii = 0; ii < 4; ii++)
		glVertex4f(m.m[0 + ii * 4], m.m[1 + ii * 4], m.m[2 + ii * 4], m.m[3 + ii * 4]);

	glEnd();
	glDepthFunc(GL_LESS);
}
