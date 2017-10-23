//
// Created by ekuehler on 10/18/17.
//

#ifndef C17TESTING_LINK_LIST_H
#define C17TESTING_LINK_LIST_H

#include <cassert>

namespace eLib {

    template<typename T>
    class link_list {
    protected:

        struct _node final {
            _node() = default;

            _node(T data, _node *next, _node *back) {
                _data = data;
                _next = next;
                _back = back;
            }

            T _data;
            _node *_next;
            _node *_back;
        };

    protected:

        class base_iterator {
        public:
            _node *_ptr;
            bool isEnd;

            base_iterator() {
                _ptr = nullptr;
                isEnd = false;
            }

            explicit base_iterator(_node *ptr) {
                if (ptr != nullptr) {
                    _ptr = ptr;
                    isEnd = false;
                } else {
                    isEnd = true;
                    _ptr = nullptr;
                }
            }

            explicit base_iterator(bool x, _node *ptr) {
                isEnd = x;
                _ptr = ptr;
            }

            bool operator==(const base_iterator &other) {
                return (_ptr == other._ptr) and (isEnd == other.isEnd);
            }

            bool operator!=(const base_iterator &other) {
                return !(*this == other);
            }

            base_iterator &operator++() {
                if (_ptr->_next != nullptr) {
                    _ptr = _ptr->_next;
                } else {
                    isEnd = true;
                }
                return *this;
            }

            base_iterator operator++(int) {
                auto it = *this;
                if (_ptr->_next != nullptr) {
                    _ptr = _ptr->_next;
                } else {
                    isEnd = true;
                }
                return it;
            }

            base_iterator &operator--() {
                assert(_ptr->_back != nullptr);
                auto it = *this;
                _ptr = _ptr->_back;
                if (isEnd) isEnd = false;
                return *this;
            }

            base_iterator operator--(int) {
                assert(_ptr->_back != nullptr);
                auto it = *this;
                _ptr = _ptr->_back;
                if (isEnd) isEnd = false;
                return it;
            }

            friend base_iterator operator+(const base_iterator &lhs, std::size_t rhs) {
                base_iterator it;
                for (int i = 0; i < rhs; i++) {
                    lhs++;
                }
                return it;
            }

            friend base_iterator operator+(std::size_t lhs, const base_iterator &rhs) {
                base_iterator it;
                for (int i = 0; i < lhs; i++) {
                    rhs++;
                }
                return it;
            }

            friend base_iterator operator-(const base_iterator &lhs, std::size_t rhs) {
                base_iterator it;
                for (int i = 0; i < rhs; ++i) {
                    lhs--;
                }
                return it;
            }
        };

        class base_reverse_iterator{
        public:
            _node *_ptr;
            bool isEnd;

            base_reverse_iterator() {
                _ptr = nullptr;
                isEnd = false;
            }

            explicit base_reverse_iterator(_node *ptr) {
                if (ptr != nullptr) {
                    _ptr = ptr;
                    isEnd = false;
                } else {
                    isEnd = true;
                    _ptr = nullptr;
                }
            }

            explicit base_reverse_iterator(bool x, _node *ptr) {
                isEnd = x;
                _ptr = ptr;
            }

            bool operator==(const base_reverse_iterator &other) {
                return (_ptr == other._ptr) and (isEnd == other.isEnd);
            }

            bool operator!=(const base_reverse_iterator &other) {
                return !(*this == other);
            }

            base_reverse_iterator &operator++() {
                if(_ptr->_back != nullptr) {
                    auto it = *this;
                    _ptr = _ptr->_back;
                } else {
                    isEnd = true;
                }
                return *this;
            }

            base_reverse_iterator operator++(int) {
                auto it = *this;
                if(_ptr->_back != nullptr) {
                    _ptr = _ptr->_back;
                } else {
                    isEnd = true;
                }
                return it;
            }

            base_reverse_iterator &operator--() {
                assert(_ptr->_next != nullptr);
                _ptr = _ptr->_next;
                if(isEnd) isEnd = true;
                return *this;
            }

            base_reverse_iterator operator--(int) {
                assert(_ptr->_next != nullptr);
                auto it = *this;
                _ptr = _ptr->_next;
                if(isEnd) isEnd = true;
                return it;
            }

            friend base_reverse_iterator operator+(const base_reverse_iterator &lhs, std::size_t rhs) {
                base_reverse_iterator it;
                for (int i = 0; i < rhs; i++) {
                    lhs++;
                }
                return it;
            }

            friend base_reverse_iterator operator+(std::size_t lhs, const base_reverse_iterator &rhs) {
                base_reverse_iterator it;
                for (int i = 0; i < lhs; i++) {
                    rhs++;
                }
                return it;
            }

            friend base_reverse_iterator operator-(const base_reverse_iterator &lhs, std::size_t rhs) {
                base_reverse_iterator it;
                for (int i = 0; i < rhs; ++i) {
                    lhs--;
                }
                return it;
            }
        };

    public:
        //iterator for the link_list
        class iterator final : public base_iterator {
        protected:
            using base_iterator::isEnd;
            using base_iterator::base_iterator;
        public:
            using base_iterator::_ptr;

            T &operator*() {
                assert(_ptr != nullptr);
                return _ptr->_data;
            }

        };

        //const iterator for the link_list
        class const_iterator final : public base_iterator {
        protected:
            using base_iterator::_ptr;
            using base_iterator::isEnd;
        public:
            using base_iterator::base_iterator;

            const T &operator*() const {
                assert(_ptr != nullptr);
                return _ptr->_data;
            }
        };


        //reverse_iterator for the link_list
        class reverse_iterator final : public base_reverse_iterator{
        protected:
            using base_reverse_iterator::isEnd;
            using base_reverse_iterator::base_reverse_iterator;
        public:
            using base_reverse_iterator::_ptr;

            T &operator*() {
                assert(_ptr != nullptr);
                return _ptr->_data;
            }
        };

        class const_reverse_iterator final : public base_reverse_iterator{
        protected:
            using base_reverse_iterator::_ptr;
            using base_reverse_iterator::isEnd;
        public:
            using base_reverse_iterator::base_reverse_iterator;

            const T &operator*() const {
                assert(_ptr != nullptr);
                return _ptr->_data;
            }
        };

    protected:

        const_iterator _atIndex(std::size_t index) const {
            auto it = cbegin();
            std::size_t n = 0;
            while (n < index) {
                n++;
                it++;
            }
            return it;
        }

//this needs to be better
        void distroyFrom(base_iterator start, base_iterator anEnd) {

            if (_head == nullptr and _end == nullptr) {
                return;
            }
            if (start == begin()) {
                if (anEnd == end()) {
                    auto i = begin();
                    while (i._ptr->_next != nullptr) {
                        i++;
                        delete i._ptr->_back;
                    }
                    delete anEnd._ptr;
                    _end = _head = nullptr;
                } else {
                    for (auto i = start; i != anEnd;) {
                        i++;
                        delete i._ptr->_back;
                    }
                    _head = anEnd._ptr;
                }
            } else if (anEnd == end()) {
                _end = start._ptr->_back;
                start._ptr->_back->_next = nullptr;
                for (auto i = start; i._ptr->_next != anEnd._ptr;) {
                    i++;
                    delete i._ptr->_back;
                }
                delete anEnd._ptr;
            } else {
                start._ptr->_back->_next = anEnd._ptr;
                anEnd._ptr->_back = start._ptr->_back;
                for (auto i = start; i._ptr->_next != anEnd._ptr;) {
                    i++;
                    delete i._ptr->_back;
                }
            }
        }

        _node *_head;
        _node *_end;
        std::size_t _length;
    public:
        link_list() {
            _head = _end = nullptr;
            _length = 0;
        }

        link_list(const link_list &other) {
            _length = 0;
            _end = _head = nullptr;
            for (const auto &i : other) {
                push_back(i);
            }
        }

        link_list(link_list &&other) noexcept {
            _length = other._length;
            _head = other._head;
            _end = other._end;
            other._end = nullptr;
            other._head = nullptr;
        }

        link_list &operator=(const link_list &other) {
            if (_head == nullptr) {
                _length = 0;
                _end = _head = nullptr;
            } else {
                distroyFrom(begin(), end());
            }
            for (const auto &i : other) {
                push_back(i);
            }
            return *this;
        }

        link_list &operator=(link_list &&other) noexcept {
            _length = other._length;
            _head = other._head;
            _end = other._end;
            other._end = nullptr;
            other._head = nullptr;
            return *this;
        }

        ~link_list() {
            distroyFrom(begin(), end());
        }

        void push_back(const T &i) {
            if (_head != nullptr) {
                auto node = new _node(i, nullptr, _end);
                _end->_next = node;
                _end = node;
            } else {
                auto node = new _node(i, nullptr, nullptr);
                _head = _end = node;
            }
            _length++;
        }

        template<typename... Args>
        T &emplace_back(Args... args) {
            push_back(T(args...));
            return back();
        }

        void pop_back() {
            assert(_end != nullptr);
            if (_end->_back != nullptr) {
                _end = _end->_back;
                delete _end->_next;
                _end->_next = nullptr;
            } else {
                delete _end;
                _head = _end = nullptr;
            }
            _length--;
        }

        void push_front(const T &i) {
            if (_head != nullptr) {
                auto node = new _node(i, _head, nullptr);
                _head->_back = node;
                _head = node;
            } else {
                auto node = new _node(i, nullptr, nullptr);
                _head = _end = node;
            }
            _length++;
        }

        template<typename... Args>
        T &emplace_front(Args... args) {
            push_front(T(args...));
            return front();

        }

        void pop_front() {
            assert(_head != nullptr);
            if (_head->_next != nullptr) {
                _head = _head->_next;
                delete _head->_back;
                _head->_back = nullptr;
            } else {
                delete _head;
                _head = _end = nullptr;
            }
            _length--;
        }

        T& front() {
            assert(_head != nullptr);
            return _head->_data;
        }

        T& back() {
            assert(_end != nullptr);
            return _end->_data;
        }

        void clear() {
            distroyFrom(begin(), end());
            _length = 0;
        }

        void insert(const T &i, std::size_t index) {
            if (_head == nullptr) {
                assert(index == 0);
                push_back(i);
            } else {
                auto it = _atIndex(index);
                if (it != begin() and it != end()) {
                    auto node = new _node{i, it._ptr, it._ptr->_back};
                    _length++;
                    node->_back->_next = node;
                    node->_next->_back = node;
                } else if (it == end()) {
                    push_back(i);
                } else {
                    push_front(i);
                }
            }
        }

        template<typename... Args>
        void emplace(std::size_t index, Args... args) {
            if (_head == nullptr) {
                assert(index == 0);
                push_back(T(args...));
            } else {
                auto it = _atIndex(index);
                if (it != begin() and it != end()) {
                    auto node = new _node{T(args...), it._ptr, it._ptr->_back};
                    _length++;
                    node->_back->_next = node;
                    node->_next->_back = node;
                } else if (it == end()) {
                    push_back(T(args...));
                } else {
                    push_front(T(args...));
                }
            }
        }


        void erase(std::size_t start, std::size_t end) {
            assert(start < end);
            auto b = _atIndex(start);
            auto e = _atIndex(end);
            distroyFrom(b, e);
            _length -= end - start;
        }

        void rsize(std::size_t start) {
            auto b = _atIndex(start);
            distroyFrom(b, end());
            _length -= start;
        }

        T& at(std::size_t index) {
            assert(index < size());
            return _atIndex(index)._ptr->_data;
        }

        T at(std::size_t index) const {
            assert(index < size());
            return *_atIndex(index);
        }

        T& operator[](std::size_t index) {
            assert(index < size());
            return _atIndex(index)._ptr->_data;
        }

        T operator[](std::size_t index) const {
            assert(index < size());
            return *_atIndex(index);
        }

        std::size_t size() const {
            return _length;
        }

        iterator begin() {
            return iterator(_head);
        }

        iterator end() {
            //this is fine
            return iterator(true, _end);
        }

        const_iterator begin() const {
            return const_iterator(_head);
        }

        const_iterator end() const {
            //this is fine
            return const_iterator(true, _end);
        }

        const_iterator cbegin() const {
            return const_iterator(_head);
        }

        const_iterator cend() const {
            //this is fine
            return const_iterator(true, _end);
        }

        reverse_iterator rbegin(){
            return reverse_iterator(_end);
        }

        reverse_iterator rend(){
            //this is fine
            return reverse_iterator(true,_head);
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(_end);
        }

        const_reverse_iterator crend() const {
            //this is fine
            return const_reverse_iterator(true,_head);
        }

    };
}

#endif //C17TESTING_LINK_LIST_H
