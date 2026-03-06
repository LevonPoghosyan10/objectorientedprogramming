#ifndef SOFTACADEMY_VECTOR_HPP
#define SOFTACADEMY_VECTOR_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iostream>

namespace softacademy {

    template <typename T>
    class BuffedVector {
    public:

        BuffedVector() : m_size(0), m_capacity(1) {
            m_data = new T[m_capacity];
        }

        BuffedVector(T* data, int size) {

            m_capacity = 1;
            m_size = size;

            while (m_capacity <= m_size) {
                m_capacity *= 2;
            }

            m_data = new T[m_capacity];

            for (int i = 0; i < size; i++) {
                m_data[i] = data[i];
            }
        }

        BuffedVector(const BuffedVector& other) {
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            m_data = new T[m_capacity];

            for (size_t i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }
        }

        BuffedVector(BuffedVector&& other) noexcept {
            m_data = other.m_data;
            m_capacity = other.m_capacity;
            m_size = other.m_size;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        BuffedVector& operator=(BuffedVector&& other) {
            if (this != &other) {

                delete[] m_data;

                m_data = other.m_data;
                m_capacity = other.m_capacity;
                m_size = other.m_size;

                other.m_data = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }

            return *this;
        }

        const bool comparisonBig(const BuffedVector& other) const {

            int sum1 = 0;
            int sum2 = 0;

            for (size_t i = 0; i < m_size; i++)
                sum1 += m_data[i];

            for (size_t i = 0; i < other.m_size; i++)
                sum2 += other.m_data[i];

            return sum1 > sum2;
        }

        const bool comparisonSmall(const BuffedVector& other) const {

            int sum1 = 0;
            int sum2 = 0;

            for (size_t i = 0; i < m_size; i++)
                sum1 += m_data[i];

            for (size_t i = 0; i < other.m_size; i++)
                sum2 += other.m_data[i];

            return sum1 < sum2;
        }

        void push_back(T value) {

            if (m_size == m_capacity) {

                m_capacity *= 2;

                T* tmp = new T[m_capacity];

                for (size_t i = 0; i < m_size; i++)
                    tmp[i] = m_data[i];

                delete[] m_data;
                m_data = tmp;
            }

            m_data[m_size] = value;
            m_size++;
        }

        void pop_back() {

            if (m_size == 0)
                throw std::out_of_range("out_of_range");

            m_size--;
        }

        size_t size() const {
            return m_size;
        }

        size_t capacity() const {
            return m_capacity;
        }

        bool empty() const {
            return m_size == 0;
        }

        T& front() {

            if (m_size == 0)
                throw std::out_of_range("out_of_range");

            return m_data[0];
        }

        const T& front() const {

            if (m_size == 0)
                throw std::out_of_range("out_of_range");

            return m_data[0];
        }

        T& back() {

            if (m_size == 0)
                throw std::out_of_range("out_of_range");

            return m_data[m_size - 1];
        }

        const T& back() const {

            if (m_size == 0)
                throw std::out_of_range("out_of_range");

            return m_data[m_size - 1];
        }

        void insert(int index, T value) {

            if (index < 0 || index >(int)m_size)
                throw std::out_of_range("Index out of range");

            if (m_size == m_capacity) {

                m_capacity *= 2;

                T* tmp = new T[m_capacity];

                for (size_t i = 0; i < m_size; i++)
                    tmp[i] = m_data[i];

                delete[] m_data;
                m_data = tmp;
            }

            for (int i = m_size; i > index; i--)
                m_data[i] = m_data[i - 1];

            m_data[index] = value;
            m_size++;
        }

        void erase(int index) {

            if (index < 0 || index >= (int)m_size)
                throw std::out_of_range("out_of_range");

            for (int i = index; i < (int)m_size - 1; i++)
                m_data[i] = m_data[i + 1];

            m_size--;
        }

        void clear() {
            m_size = 0;
        }

        void reserve(int wantedcapacity) {

            if (wantedcapacity <= (int)m_capacity)
                return;

            T* tmp = new T[wantedcapacity];

            for (size_t i = 0; i < m_size; i++)
                tmp[i] = m_data[i];

            delete[] m_data;

            m_data = tmp;
            m_capacity = wantedcapacity;
        }

        T& operator[](int index) {

            if (index < 0 || index >= (int)m_size)
                throw std::out_of_range("out_of_range");

            return m_data[index];
        }

        const T& operator[](int index) const {

            if (index < 0 || index >= (int)m_size)
                throw std::out_of_range("out_of_range");

            return m_data[index];
        }

        ~BuffedVector() {
            delete[] m_data;
        }

        friend std::ostream& operator<<(std::ostream& os, const BuffedVector& V) {

            for (size_t i = 0; i < V.m_size; i++)
                os << V.m_data[i] << ' ';

            return os;
        }

    private:

        T* m_data;
        std::size_t m_size;
        std::size_t m_capacity;
    };

}

#endif