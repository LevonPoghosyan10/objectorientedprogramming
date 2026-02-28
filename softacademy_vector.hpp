#ifndef SOFTACADEMY_VECTOR_HPP
#define SOFTACADEMY_VECTOR_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace softacademy {

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type  = std::size_t;

    Vector() noexcept;
    explicit Vector(size_type count);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    ~Vector();

    size_type size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_type new_cap);
    void shrink_to_fit();

    T& operator[](size_type index) noexcept;
    const T& operator[](size_type index) const noexcept;
    T& at(size_type index);
    const T& at(size_type index) const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    T* data() noexcept;
    const T* data() const noexcept;

    void clear() noexcept;
    void push_back(const T& value);
    void push_back(T&& value);

    template <typename... Args>
    T& emplace_back(Args&&... args);

    void pop_back();
    void resize(size_type new_size);
    void resize(size_type new_size, const T& value);

    void swap(Vector& other) noexcept;

private:
    T* data_;
    size_type size_;
    size_type capacity_;

    void grow_if_needed();
    void reallocate(size_type new_capacity);
    void destroy_range(size_type from, size_type to) noexcept;
};

} // namespace softacademy

#endif
