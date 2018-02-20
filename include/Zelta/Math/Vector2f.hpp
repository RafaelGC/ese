/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector2f.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 12:14 PM
 */

#ifndef ZELTALIB_VECTOR2F_HPP
#define ZELTALIB_VECTOR2F_HPP

#include <Zelta/Math/Vector3f.hpp>
#include <SFML/System/Vector2.hpp>

#ifndef M_PI
# define M_PI           3.14159265358979323846
#endif

namespace zt {
    /**
     * @brief Utility class for 2-dimensional vectors.
     */
    class Vector2f {
        public:
        Vector2f();
        Vector2f(float x, float y);
        Vector2f(const sf::Vector2f& v);

        float getX() const;
        float getY() const;

        float length() const;

        // MODIFIERS //
        
        void setX(float x);
        void setY(float y);
        void set(float x, float y);

        /**
         * @brief Normalizes the vector.
         * @see If you don't want to modify this vector but get 
         * a new one use normalized().
         */
        void normalize();

        /**
         * @brief Adds the other vector to this one.
         * @param other
         * @return Returns this vector.
         */
        Vector2f& add(const Vector2f& other);
        
        /**
         * @brief Multiply the vector by a scalar.
         * @param other
         * @return Returns this vector.
         */
        Vector2f& multiply(float num);
        
        /**
         * @brief Multiply the vector by two scalars.
         * @param x
         * @param y
         * @return Returns this vector.
         */
        Vector2f& multiply(float x, float y);

        /**
         * @brief Rotates de vector.
         * @param angle
         * @return Returns this vector.
         */
        Vector2f& rotate(float angle);

        // NOT MODIFIERS //
        /**
         * @brief Returns the normalized vector.
         * @warning This method does not modify the original vector.
         * @return Normalized vector.
         */
        Vector2f normalized() const;

        /**
         * @brief Returns the cross product.
         * @param other Other vector.
         * @return Cross product (3d vector). 
         */
        Vector3f cross(const Vector2f& other) const;

        /**
         * @brief Returns the dot product.
         * @param other Other vector.
         * @return Dot product.
         */
        float dot(const Vector2f& other) const;

        /**
         * @brief Adds this vector to other and returns the result.
         * @param other Other vector.
         * @return Returns the sum.
         */
        Vector2f plus(const Vector2f& other) const;
        
        /**
         * @brief Substracts other vector to thisand returns the result.
         * @param other Other vector.
         * @return Returns the substraction.
         */
        Vector2f minus(const Vector2f& other) const;

        /**
         * @brief Multiply the vector by a scalar.
         * @param other
         * @return Returns the new scaled vector.
         */
        Vector2f multiplied(float s) const;
        
        /**
         * @brief Multiply the vector by two scalars.
         * @param x
         * @param y
         * @return Returns the new scaled vector.
         */
        Vector2f multiplied(float x, float y) const;

        /**
         * @brief Returns a new rotated vector.
         * @param angle Angle
         * @return Rotated vector.
         */
        Vector2f rotated(float angle) const;
        
        /**
         * @return Returns the angle of the vector.
         */
        float getAngle() const;
        
        /**
         * Calcula el vector que va desde this hasta other.
         * Este método es azúcar sintáctico para: other.minus(*this).
         * @param Vector destino.
         * @return Vector que tiene origen en this y termina en other.
         */
        /**
         * Returns the vector from <<this>> to <<other>>.
         * Its the same that other.minus(*this).
         * @param other Other vector.
         * @return New vector.
         */
        Vector2f to(const Vector2f& other) const;
        
        /**
         * Converts this vector to a sf::Vector2f.
         * @return SFML vector.
         */
        sf::Vector2f toSfml() const;

        private:
        float x, y;
    };
}
#endif /* VECTOR2F_HPP */

