#pragma once

#include <string>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <cstddef>

class CStringList {
private:
    struct Node {
        std::string data;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node(const std::string& value) : data(value) {}
        Node(std::string&& value) : data(std::move(value)) {}
        Node() = default;
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    Node* m_tailSentinel = nullptr;
    size_t m_size = 0;

    void CopyFrom(const CStringList& other) {
        for (const auto& val : other) {
            PushBack(val);
        }
    }

    void MoveFrom(CStringList&& other) noexcept {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_tailSentinel = other.m_tailSentinel;
        m_size = other.m_size;

        other.m_head = other.m_tail = other.m_tailSentinel = nullptr;
        other.m_size = 0;
    }

public:
    CStringList() {
        m_tailSentinel = new Node();
        m_head = m_tailSentinel;
        m_tailSentinel->prev = nullptr;
        m_tailSentinel->next = nullptr;
    }

    CStringList(const CStringList& other) : CStringList() {
        CopyFrom(other);
    }

    CStringList(CStringList&& other) noexcept {
        MoveFrom(std::move(other));
    }

    CStringList& operator=(const CStringList& other) {
        if (this != &other) {
            CStringList temp(other);
            Swap(temp);
        }
        return *this;
    }

    CStringList& operator=(CStringList&& other) noexcept {
        if (this != &other) {
            Clear();
            delete m_tailSentinel;
            MoveFrom(std::move(other));
        }
        return *this;
    }

    ~CStringList() noexcept {
        Clear();
        delete m_tailSentinel;
    }

    void Clear() noexcept {
        Node* current = m_head;
        while (current && current != m_tailSentinel) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        m_head = m_tail = m_tailSentinel;
        if (m_tailSentinel) m_tailSentinel->prev = nullptr;
        m_size = 0;
    }

    void PushBack(const std::string& value) {
        Node* node = new Node(value);
        if (m_tail == nullptr || m_tail == m_tailSentinel) {
            node->next = m_tailSentinel;
            m_tailSentinel->prev = node;
            m_head = m_tail = node;
        }
        else {
            node->prev = m_tail;
            node->next = m_tailSentinel;
            m_tail->next = node;
            m_tailSentinel->prev = node;
            m_tail = node;
        }
        ++m_size;
    }

    void PushBack(std::string&& value) {
        Node* node = new Node(std::move(value));
        if (m_tail == nullptr || m_tail == m_tailSentinel) {
            node->next = m_tailSentinel;
            m_tailSentinel->prev = node;
            m_head = m_tail = node;
        }
        else {
            node->prev = m_tail;
            node->next = m_tailSentinel;
            m_tail->next = node;
            m_tailSentinel->prev = node;
            m_tail = node;
        }
        ++m_size;
    }

    void PushFront(const std::string& value) {
        Node* node = new Node(value);
        if (m_head == m_tailSentinel) {
            node->next = m_tailSentinel;
            m_tailSentinel->prev = node;
            m_head = m_tail = node;
        }
        else {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }
        ++m_size;
    }

    void PushFront(std::string&& value) {
        Node* node = new Node(std::move(value));
        if (m_head == m_tailSentinel) {
            node->next = m_tailSentinel;
            m_tailSentinel->prev = node;
            m_head = m_tail = node;
        }
        else {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }
        ++m_size;
    }

    bool IsEmpty() const noexcept {
        return m_size == 0;
    }

    size_t GetSize() const noexcept {
        return m_size;
    }

    class ConstIterator;

    class Iterator {
        friend class CStringList;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::string;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator() = default;
        explicit Iterator(Node* node) : m_node(node) {}

        reference operator*() const { return m_node->data; }
        pointer operator->() const { return &m_node->data; }

        Iterator& operator++() { m_node = m_node->next; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        Iterator& operator--() { m_node = m_node->prev; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const Iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const Iterator& other) const { return m_node != other.m_node; }

        Node* GetNode() const { return m_node; }

    private:
        Node* m_node = nullptr;
    };

    class ConstIterator {
        friend class CStringList;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const std::string;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        ConstIterator() = default;
        explicit ConstIterator(Node* node) : m_node(node) {}
        ConstIterator(const Iterator& it) : m_node(it.m_node) {}

        reference operator*() const { return m_node->data; }
        pointer operator->() const { return &m_node->data; }

        ConstIterator& operator++() { m_node = m_node->next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }

        ConstIterator& operator--() { m_node = m_node->prev; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

        bool operator==(const ConstIterator& other) const { return m_node == other.m_node; }
        bool operator!=(const ConstIterator& other) const { return m_node != other.m_node; }

        Node* GetNode() const { return m_node; }

    private:
        Node* m_node = nullptr;
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() { return iterator(m_head); }
    iterator end() { return iterator(m_tailSentinel); }
    const_iterator begin() const { return const_iterator(m_head); }
    const_iterator end() const { return const_iterator(m_tailSentinel); }
    const_iterator cbegin() const { return const_iterator(m_head); }
    const_iterator cend() const { return const_iterator(m_tailSentinel); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

    iterator Insert(iterator pos, const std::string& value) {
        Node* posNode = pos.GetNode();
        if (posNode == m_head) {
            PushFront(value);
            return iterator(m_head);
        }
        if (posNode == m_tailSentinel) {
            PushBack(value);
            return iterator(m_tail);
        }

        Node* newNode = new Node(value);
        newNode->next = posNode;
        newNode->prev = posNode->prev;
        posNode->prev->next = newNode;
        posNode->prev = newNode;
        ++m_size;
        return iterator(newNode);
    }

    iterator Erase(iterator pos) {
        Node* node = pos.GetNode();
        if (!node || node == m_tailSentinel) return end();

        Node* next = node->next;

        if (node->prev) {
            node->prev->next = node->next;
        }
        else {
            m_head = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        }

        if (node == m_tail) {
            m_tail = node->prev;
            m_tailSentinel->prev = m_tail;
        }

        delete node;
        --m_size;
        return iterator(next);
    }

    void Swap(CStringList& other) noexcept {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_tailSentinel, other.m_tailSentinel);
        std::swap(m_size, other.m_size);
    }
};
