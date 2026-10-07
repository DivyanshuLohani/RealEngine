#pragma once

#include <glm/glm.hpp>

namespace RealEngine {

glm::mat4 CreateTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

}
