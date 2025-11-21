#include <Aqua/Core/Texture.hpp>
#include <Aqua/Core/Types.hpp>
#include <memory>
#include <glad/glad.h>
#include <Aqua/Core/Shader.hpp>

namespace Aqua {
class Render {
public:
	Render(std::shared_ptr<Shader> shader);
	~Render();

	void DrawSprite(std::shared_ptr<Texture> texture, vec2 pos, vec2 scale, float rotation, vec3 color);
private:
	std::shared_ptr<Shader> shader;
	GLuint quadVAO;

};
}
