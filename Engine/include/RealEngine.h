#pragma once

// For use by RealEngine applications (clients)

#include "Core/Application.h"
#include "Core/Assert.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Time.h"
#include "Core/Timestep.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "ImGui/ImGuiLayer.h"
#include <imgui.h>

#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include "Render/Buffer.h"
#include "Render/Framebuffer.h"
#include "Render/OrthographicCamera.h"
#include "Render/PrespectiveCamera.h"
#include "Render/RenderContext.h"
#include "Render/Renderer.h"
#include "Render/RendererAPI.h"
#include "Render/Shader.h"
#include "Render/Texture.h"
#include "Render/VertexArray.h"

#include "Window/Window.h"
#include "Window/WindowProps.h"

#include "Math/Transform.h"
