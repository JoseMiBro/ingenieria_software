#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "vector2d.h"
#include "TextureManager.h"
#include "EntityManager.h"

class Renderer
{

  public:
    Renderer(TextureManager& txtMan, EntityManager& entMan);
    ~Renderer();

    void Init();
    void Terminate();

    void Render(double playTime, double logicTime, double fps, double tick);

  private:
    TextureManager& txtMan;
    EntityManager& entMan;
    
    void RenderSetUp();
    void RenderTexture(vec2 pos, vec2 size, GLuint texId);
    void RenderBackground();
    void RenderBalls();
    void RenderText(double playTime, double logicTime, double fps, double tick);
};

