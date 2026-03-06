#ifndef SOFTACADEMY_LIST_HPP
#define SOFTACADEMY_LIST_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iostream>

namespace softacademy {

    template <typename T>
    class LinkedList {
    public:

        LinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

        LinkedList(const LinkedList& other) : m_head(nullptr), m_tail(nullptr), m_size(0) {
            for (Node* curr = other.m_head; curr; curr = curr->next)
                push_back(curr->value);
        }

        LinkedList(LinkedList&& other) noexcept
            : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        LinkedList& operator=(const LinkedList& other) {
            if (this != &other) {
                clear();
                for (Node* curr = other.m_head; curr; curr = curr->next)
                    push_back(curr->value);
            }
            return *this;
        }

        LinkedList& operator=(LinkedList&& other) noexcept {
            if (this != &other) {
                clear();
                m_head = other.m_head;
                m_tail = other.m_tail;
                m_size = other.m_size;
                other.m_head = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        ~LinkedList() { clear(); }

        size_t size() const { return m_size; }
        bool empty() const { return m_size == 0; }

        T& front() {
            if (empty()) throw std::out_of_range("List is empty");
            return m_head->value;
        }

        const T& front() const {
            if (empty()) throw std::out_of_range("List is empty");
            return m_head->value;
        }

        T& back() {
            if (empty()) throw std::out_of_range("List is empty");
            return m_tail->value;
        }

        const T& back() const {
            if (empty()) throw std::out_of_range("List is empty");
            return m_tail->value;
        }

        void clear() {
            Node* curr = m_head;
            while (curr) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
            m_head = m_tail = nullptr;
            m_size = 0;
        }

        void push_front(const T& value) {
            Node* newNode = new Node(value, nullptr, m_head);
            if (m_head) m_head->prev = newNode;
            m_head = newNode;
            if (!m_tail) m_tail = newNode;
            ++m_size;
        }

        void push_front(T&& value) {
            Node* newNode = new Node(std::move(value), nullptr, m_head);
            if (m_head) m_head->prev = newNode;
            m_head = newNode;
            if (!m_tail) m_tail = newNode;
            ++m_size;
        }

        void push_back(const T& value) {
            Node* newNode = new Node(value, m_tail, nullptr);
            if (m_tail) m_tail->next = newNode;
            m_tail = newNode;
            if (!m_head) m_head = newNode;
            ++m_size;
        }

        void push_back(T&& value) {
            Node* newNode = new Node(std::move(value), m_tail, nullptr);
            if (m_tail) m_tail->next = newNode;
            m_tail = newNode;
            if (!m_head) m_head = newNode;
            ++m_size;
        }

        template <typename... Args>
        void emplace_front(Args&&... args) {
            Node* newNode = new Node(T(std::forward<Args>(args)...), nullptr, m_head);
            if (m_head) m_head->prev = newNode;
            m_head = newNode;
            if (!m_tail) m_tail = newNode;
            ++m_size;
        }

        template <typename... Args>
        void emplace_back(Args&&... args) {
            Node* newNode = new Node(T(std::forward<Args>(args)...), m_tail, nullptr);
            if (m_tail) m_tail->next = newNode;
            m_tail = newNode;
            if (!m_head) m_head = newNode;
            ++m_size;
        }

        void pop_front() {
            if (empty()) return;
            Node* temp = m_head;
            m_head = m_head->next;
            if (m_head) m_head->prev = nullptr;
            else m_tail = nullptr;
            delete temp;
            --m_size;
        }

        void pop_back() {
            if (empty()) return;
            Node* temp = m_tail;
            m_tail = m_tail->prev;
            if (m_tail) m_tail->next = nullptr;
            else m_head = nullptr;
            delete temp;
            --m_size;
        }

        void swap(LinkedList& other) noexcept {
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
            std::swap(m_size, other.m_size);
        }

        friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
            Node* curr = list.m_head;
            while (curr) {
                os << curr->value << " ";
                curr = curr->next;
            }
            return os;
        }

    private:
        struct Node {
            T value;
            Node* prev;
            Node* next;
            Node(const T& v, Node* p = nullptr, Node* n = nullptr)
                : value(v), prev(p), next(n) {}
            Node(T&& v, Node* p = nullptr, Node* n = nullptr)
                : value(std::move(v)), prev(p), next(n) {}
        };

        Node* m_head;
        Node* m_tail;
        size_t m_size;
    };

} // namespace softacademy

#endif