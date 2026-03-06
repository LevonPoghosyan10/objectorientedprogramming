#ifndef SOFTACADEMY_SHAPES_HPP
#define SOFTACADEMY_SHAPES_HPP

#include <cstddef>
#include <stdexcept>
#include <cmath>

namespace softacademy {

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Radius can't be negative!");
        }
        m_radius = radius;
    };
        
        

    double radius() const noexcept {
        return m_radius;
    };

    double area() const override {
        return m_radius * m_radius * 3.1415;
    };
    double perimeter() const override {
        return m_radius * 2 * 3.1415;
    };

private:
    double m_radius;
};

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("There are no negative sides in a rectangle!");
        }
        m_width = width;
        m_height = height;
    };

    double width() const noexcept {
        return m_width;
    };
    double height() const noexcept {
        return m_height;
    };

    double area() const override {
        return m_height * m_width;
    };
    double perimeter() const override {
        return 2 * (m_width + m_height);
    };

private:
    double m_width;
    double m_height;
};

class Triangle final : public Shape {
public:
    Triangle(double a, double b, double c) {
        if(valid_triangle(a, b, c)){
            m_a = a;
            m_b = b;
            m_c = c;
        }
    };

    double a() const noexcept {
        return m_a;
    };
    double b() const noexcept {
        return m_b;
    };
    double c() const noexcept {
        return m_c;
    };

    double area() const override {
        double s = (m_a + m_b + m_c) / 2;
        return sqrt(s * (s - m_a) * (s - m_b) * (s - m_c));
        };
    double perimeter() const override {
        return m_a + m_b + m_c;
    };

private:
    double m_a;
    double m_b;
    double m_c;

private:
    bool valid_triangle(double a, double b, double c) const noexcept {
        return(a + b > c && a + c > b && b + c > a);  
    };
};

} // namespace softacademy

#endif // SOFTACADEMY_SHAPES_HPP
