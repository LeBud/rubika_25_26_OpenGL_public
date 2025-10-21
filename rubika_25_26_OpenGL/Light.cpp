#include "Light.h"

Light::Light() {
        Position = {0,0,0};
        Ambient = {1,1,1};
        Diffuse = {1,1,1};
        Scalar = {1,1,1};
}

Light::Light(const glm::vec3& position, const glm::vec3& ambient, float ambientIntensity, const glm::vec3& diffuse,
    float diffuseIntensity, const glm::vec3& scalar, float scalarIntensity) {
    Position = position;
    Ambient = ambient * ambientIntensity;
    Diffuse = diffuse * diffuseIntensity;
    Scalar = scalar * scalarIntensity;
}

void Light::Update(float dt) {
    Position = glm::vec3(sin(dt), cos(dt), sin(dt)) * 2.0f;

    glm::vec3 lightColor;
    lightColor.x = (float)sin(dt * 2.0);
    lightColor.y = (float)sin(dt * 0.7);
    lightColor.z = (float)sin(dt * 1.3);
    Diffuse = lightColor * glm::vec3(0.5f);
    Ambient = Diffuse * glm::vec3(0.2f);
}

void Light::Use(Shader& shader) {
    shader.SetVec3("light.position", Position);
    shader.SetVec3("light.ambient", Ambient);
    shader.SetVec3("light.diffuse", Diffuse);
    shader.SetVec3("light.specular", Scalar);
}
