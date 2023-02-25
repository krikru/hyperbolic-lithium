#pragma once

#include "glabstractbb.h"

namespace lithium
{
    class AABB : public AbstractBB
    {
    public:
        AABB(const glm::vec3 &position, const glm::vec3 &a, const glm::vec3 &b)
            : AbstractBB{position}, _a{a}, _b{b},
              _dimensions{abs(b - a)}, _center{position + a + _dimensions * 0.5f}
        {
        }

        AABB(const AABB &other)
            : AbstractBB{other}, _a{other._a}, _b{other._b},
              _dimensions{other._dimensions}, _center{other._center}
        {
        }

        virtual ~AABB() noexcept
        {
        }

        void setA(const glm::vec3 &a)
        {
            _a = a;
        }

        void setB(const glm::vec3 &b)
        {
            _b = b;
        }

        glm::vec3 a() const
        {
            return _a;
        }

        glm::vec3 b() const
        {
            return _b;
        }

        glm::vec3 center() const
        {
            return _center;
        }

        float dimX() const
        {
            return _dimensions.x;
        }

        float dimY() const
        {
            return _dimensions.y;
        }

        float dimZ() const
        {
            return _dimensions.z;
        }

        glm::vec3 dimensions() const
        {
            return _dimensions;
        }

    private:
        glm::vec3 _a;
        glm::vec3 _b;
        glm::vec3 _dimensions;
        glm::vec3 _center;
    };
}