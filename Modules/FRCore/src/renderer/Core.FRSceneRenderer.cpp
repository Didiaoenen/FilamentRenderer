#include "Core.FRSceneRenderer.h"
#include <FRRendererWarp.h>

FR::FRSceneRenderer::FRSceneRenderer()
	: FRCompositeRenderer()
{
	mRenderer->SetClearOptions({ .clearColor = {0.1,0.1,0.1,1.0}, .clear = true });
}
