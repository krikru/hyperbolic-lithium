#pragma once

#include <memory>
#include "glmesh.h"
#include "glcamera.h"
#include "glimagetexture.h"
#include <glm/gtc/type_ptr.hpp>
#include "gltaskscheduler.h"
#include "glfader.h"
#include "glupdateable.h"
#include "glrenderable.h"

namespace lithium
{
    class Object : public Updateable, public Renderable
    {
    public:
		using TexturePointer = std::shared_ptr<lithium::Texture<unsigned char>>;

		Object(std::shared_ptr<lithium::Mesh> mesh, const std::vector<TexturePointer>& textures);
        Object(const Object& other);
        virtual ~Object() noexcept;

        virtual void draw() const override;

		virtual void shade(lithium::ShaderProgram* shaderProgram) override;

        void setTextures(const std::vector<TexturePointer>& textures)
		{
			_textures = textures;
		}

		lithium::Object* setPosition(const glm::vec3& position)
		{
			_position = position;
			_modelInvalidated = true;
			return this;
		}

		lithium::Object* setPosition(float x, float y, float z)
		{
			return setPosition(glm::vec3{x, y, z});
		}

		void move(const glm::vec3& d)
		{
			_position.x += d.x;
			_position.y += d.y;
			_position.z += d.z;
			_modelInvalidated = true;
		}

		void move(const glm::vec2& d)
		{
			_position.x += d.x;
			_position.y += d.y;
			_modelInvalidated = true;
		}

		const glm::vec3& position() const
		{
			return _position;
		}

		lithium::Object* setRotation(const glm::vec3& rotation)
		{
			_rotation = rotation;
			_modelInvalidated = true;
			return this;
		}

		const glm::vec3& rotation() const
		{
			return _rotation;
		}

		lithium::Object* setScale(const glm::vec3& scale)
		{
			_scale = scale;
			_modelInvalidated = true;
			return this;
		}

		lithium::Object* setScale(float scale)
		{
			return setScale(glm::vec3{scale, scale, scale});
		}

		const glm::vec3 scale() const
		{
			return _scale;
		}

		void setObjectName(const std::string& str)
		{
			_objectName = std::make_shared<std::string>(str);
		}

		std::string objectName() const
		{
			return *_objectName;
		}

		void setMesh(std::shared_ptr<lithium::Mesh> mesh)
		{
			_mesh = mesh;
		}

		virtual lithium::Object* setVisible(bool visible)
		{
			_visible = visible;
			return this;
		}

		bool visible() const
		{
			return _visible;
		}

		lithium::Object* setOpacity(float opacity)
		{
			_color.a = opacity;
			return this;
		}

		lithium::Object* setColor(const glm::vec3 color)
		{
			setColor(glm::vec4{color, _color.a});
			return this;
		}

		lithium::Object* setColor(const glm::vec4 color)
		{
			_color = color;
			return this;
		}

		glm::vec4 color() const
		{
			return _color;
		}

		glm::vec3 rgb() const
		{
			return glm::vec3{_color.x, _color.y, _color.z};
		}

		void copyTranslation(lithium::Object* other)
		{
			for(int y{0}; y < 4; ++y)
			{
				this->_model[y][3] = other->_model[y][3];
				this->_model[3][y] = other->_model[3][y];
			}
		}

		void copyRotation(lithium::Object* other)
		{
			for(int y{0}; y < 3; ++y)
			{
				for(int x{0}; x < 3; ++x)
				{
					this->_model[y][x] = other->_model[y][x];
				}
			}
			this->_modelInvalidated = false;
		}

		void copyModelMatrix(lithium::Object* other)
		{
			for(int y{0}; y < 4; ++y)
			{
				for(int x{0}; x < 4; ++x)
				{
					this->_model[y][x] = other->_model[y][x];
				}
			}
			this->_modelInvalidated = false;
		}

		TexturePointer texture(int textureUnit) const
		{
			return _textures[textureUnit];
		}

		bool hasTexture() const
		{
			return _textures.size() > 0;
		}

		std::shared_ptr<lithium::Mesh> mesh() const
		{
			return _mesh;
		}

		float opacity() const
		{
			return _color.a;
		}

		void setModelInvalidated(bool modelInvalidated)
		{
			_modelInvalidated = modelInvalidated;
		}

		void setModel(const glm::mat4& model)
		{
			_model = model;
			_modelInvalidated = false;
		}

		bool modelInvalidated() const
		{
			return _modelInvalidated;
		}

		virtual lithium::Object* clone() const
		{
			return new lithium::Object(*this);
		}

		glm::mat4 model() const
		{
			return _model;
		}

		virtual void updateModel();

	protected:
        std::shared_ptr<lithium::Mesh> _mesh{nullptr};
		glm::vec3 _position{0.0f};
		glm::vec3 _rotation{0.0f};
		glm::vec3 _scale{1.0f};
		glm::mat4 _model{1.0f};
		bool _visible{true};
		glm::vec4 _color{1.0f};
        std::vector<TexturePointer> _textures;
		std::shared_ptr<std::string> _objectName;
	private:
		bool _modelInvalidated{false};
    };
}