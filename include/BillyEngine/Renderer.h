#pragma once

#include "Color.h"
#include "Utils.h"

BE_HEADER_START

struct Renderer;

BE_PUBLIC void RendererSetClearColor(Renderer*, const Color*);
BE_PUBLIC void RendererSetWireframeView(Renderer*, bool);

BE_HEADER_END