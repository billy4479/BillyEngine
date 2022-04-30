#pragma once

#include "Color.h"
#include "Utils.h"

BE_HEADER_START

struct Renderer;

BE_API void RendererSetClearColor(Renderer*, const Color*);
BE_API void RendererSetWireframeView(Renderer*, bool);

BE_HEADER_END