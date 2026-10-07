#include "Engine/Math/Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RealEngine {

glm::mat4 CreateTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
    glm::mat4 transform(1.0f);

    transform = glm::translate(transform, position);

    transform = glm::rotate(transform, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

    transform = glm::rotate(transform, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

    transform = glm::rotate(transform, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    transform = glm::scale(transform, scale);

    return transform;
}

} // namespace RealEngine
