/*
 * link_list.h version 2.0
 */

#ifndef C17TESTING_LINK_LIST_V2_H
#define C17TESTING_LINK_LIST_V2_H
#include <memory>
#include <cassert>

#define protected public
namespace expr {

using std::make_unique;
using std::unique_ptr;

template <typename T>
class link_list {
protected:

    struct node_ {
        unique_ptr<node_> next_;
        node_* back_;
        T data_;

        node_(node_* next, node_* back, T data)
                : next_(next), back_(back), data_(data) {}
    };

    struct base_iterator {
        node_* ptr_;
        bool end_;

        base_iterator() {
            ptr_ = nullptr;
            end_ = true;
        }

        base_iterator(node_* ptr, const bool end = false) {
            ptr_ = ptr;
            if(ptr_ == nullptr){
                end_ = true;
            } else {
                end_ = end;
            }
        }

        bool operator==(const base_iterator& other) const {
            return (ptr_ == other.ptr_) && (end_ == other.end_);
        }

        bool operator!=(const base_iterator& other) const {
            return !(*this == other);
        }
    };

    struct base_forward_iterator : base_iterator {
        using base_iterator::ptr_;
        using base_iterator::end_;

        base_forward_iterator() : base_iterator() {};
        base_forward_iterator(node_* ptr, bool end = false) : base_iterator(ptr,end) {}


        base_forward_iterator& operator++() {
            if (ptr_->next_ == nullptr) {
                end_ = true;
            } else {
                ptr_ = ptr_->next_.get();
            }
            return *this;
        }

        base_forward_iterator operator++(int) {
            const base_forward_iterator it(*this);
            ++(*this);
            return it;
        }

        base_forward_iterator& operator--() {
            assert(ptr_->back_ != nullptr);
            ptr_ = ptr_->back_;
            end_ = false;
            return *this;
        }

        base_forward_iterator operator--(int) {
            const base_forward_iterator it(*this);
            --(*this);
            return it;
        }

        base_forward_iterator operator+(const int step) const {
            base_forward_iterator it(*this);
            for (int i = 0; i < step; ++i) {
                ++it;
            }
            return it;
        }

        friend base_forward_iterator operator+(const int step, const base_forward_iterator& it) {
            return it + step;
        }

        base_forward_iterator operator-(const int step) const {
            base_forward_iterator it(*this);
            for (int i = 0; i < step; ++i) {
                --it;
            }
            return it;
        }

        friend base_forward_iterator operator-(const int step, const base_forward_iterator& it) {
            return it - step;
        }

        size_t operator-(const base_forward_iterator& other) const {
            assert(ptr_ <= other.ptr_);
            auto it = other;
            size_t n = 0;
            while (it != *this) {
                --it;
                ++n;
            }
            return n;
        }

    };

    struct base_reverse_iterator : base_iterator {
        using base_iterator::ptr_;
        using base_iterator::end_;

        base_reverse_iterator() : base_iterator() {};
        base_reverse_iterator(node_* ptr, bool end = false) : base_iterator(ptr,end) {}

        //really the --
        base_reverse_iterator& operator++() {
            if (ptr_->back_ == nullptr) {
                end_ = true;
            } else {
                ptr_ = ptr_->back_;
            }
            return *this;
        }

        base_reverse_iterator operator++(int) {
            const base_reverse_iterator it(*this);
            ++(*this);
            return it;
        }

        base_reverse_iterator& operator--() {
            assert(ptr_->next_ != nullptr);
            ptr_ = ptr_->next_.get();
            end_ = false;
            return *this;
        }

        base_reverse_iterator operator--(int) {
            const base_reverse_iterator it(*this);
            ++(*this);
            return it;
        }

        base_reverse_iterator operator+(const int step) const {
            base_reverse_iterator it(*this);
            for (int i = 0; i < step; ++i) {
                ++it;
            }
            return it;
        }

        friend base_reverse_iterator operator+(const int step, const base_reverse_iterator& it) {
            return it + step;
        }

        base_reverse_iterator operator-(const int step) const {
            base_reverse_iterator it(*this);
            for (int i = 0; i < step; ++i) {
                ++it;
            }
            return it;
        }

        friend base_reverse_iterator operator-(const int step, const base_reverse_iterator& it) {
            return it - step;
        }

        size_t operator-(const base_reverse_iterator& other) const {
            assert(ptr_ <= other.ptr_);
            auto it = other;
            size_t n = 0;
            while (it != *this) {
                ++it;
                ++n;
            }
            return n;
        }

    };

public:
    class iterator final  : public base_forward_iterator {
    protected:
        using base_forward_iterator::ptr_;
        using base_forward_iterator::end_;
    public:
        iterator() : base_forward_iterator() {}

        iterator(node_* ptr, bool end) : base_forward_iterator(ptr,end) {}

        iterator(const base_forward_iterator& other) {
            ptr_ = other.ptr_;
            end_ = other.end_;
        }

        T& operator*() {
            assert(ptr_ != nullptr);
            return ptr_->data_;
        }

        T* operator->() {
            assert(ptr_ != nullptr);
            return &(ptr_->data_);
        }
    };

    class const_iterator final : public base_forward_iterator {
    protected:
        using base_forward_iterator::ptr_;
        using base_forward_iterator::end_;
    public:

        const_iterator() : base_forward_iterator() {}

        const_iterator(node_* ptr, const bool end = false) : base_forward_iterator(ptr,end) {}

        const_iterator(const base_forward_iterator& other) {
            ptr_ = other.ptr_;
            end_ = other.end_;
        }

        const T& operator*() const {
            assert(ptr_ != nullptr);
            return ptr_->data_;
        }

        const T* operator->() const {
            assert(ptr_ != nullptr);
            return &(ptr_->data_);
        }
    };

    class reverse_iterator final : public base_reverse_iterator {
    protected:
        using base_reverse_iterator::ptr_;
        using base_reverse_iterator::end_;
    public:
        reverse_iterator() {
            ptr_ = nullptr;
            end_ = false;
        }

        reverse_iterator(node_* ptr, const bool end = false) : base_reverse_iterator(ptr,end) {}

        reverse_iterator(const base_reverse_iterator& other) {
            ptr_ = other.ptr_;
            end_ = other.end_;
        }

        T& operator*() {
            assert(ptr_ != nullptr);
            return ptr_->data_;
        }

        T* operator->() {
            assert(ptr_ != nullptr);
            return &(ptr_->data_);
        }
    };

    class const_reverse_iterator final : public base_reverse_iterator {
    protected:
        using base_reverse_iterator::ptr_;
        using base_reverse_iterator::end_;
    public:

        const_reverse_iterator() : base_reverse_iterator() {}

        const_reverse_iterator(node_* ptr, const bool end = false): base_reverse_iterator(ptr,end) {}

        const_reverse_iterator(const base_reverse_iterator& other) {
            ptr_ = other.ptr_;
            end_ = other.end_;
        }

        T operator*() const {
            assert(ptr_ != nullptr);
            return *ptr_;
        }

        const T* operator->() const {
            assert(ptr_ != nullptr);
            return &(ptr_->data_);
        }
    };

protected:
    iterator atIndex(const size_t index) {
        assert(index < length_);
        auto it = begin();
        return it + index;
    }

    unique_ptr<node_> head_;
    node_* tail_;
    size_t length_;
public:

    link_list() {
        tail_ = nullptr;
        length_ = 0;
    }

    link_list(const link_list& other) {
        tail_ = nullptr;
        length_ = 0;
        head_ = nullptr;
        for (const auto& i : other) {
            push_back(i);
        }
    }

    link_list(link_list&& other) noexcept {
        tail_ = other.tail_;
        head_.reset(other.head_.release());
        length_ = other.length_;
    }

    link_list& operator=(const link_list& other) {
        tail_ = nullptr;
        length_ = 0;
        head_ = nullptr;//this delete the old data
        for (const auto& i : other) {
            push_back(i);
        }
        return *this;
    }

    link_list& operator=(link_list&& other) noexcept {
        tail_ = other.tail_;
        head_ = other.head_.release();
        length_ = other.length_;
        return *this;
    }

    ~link_list() = default;

    void push_back(const T& data) {
        if (head_ == nullptr) {
            head_ = make_unique<node_>(nullptr, nullptr, data);
            tail_ = head_.get();
        } else {
            tail_->next_ = make_unique<node_>(nullptr, tail_, data);
            tail_ = tail_->next_.get();
        }
        ++length_;
    }

    void pop_back() {
        assert(tail_ != nullptr);
        if(tail_->back_ != nullptr) {
            tail_ = tail_->back_;
            tail_->next_.reset();
        } else{
            head_.reset();
            tail_ = nullptr;
        }
        --length_;
    }

    template <typename... Args>
    T& emplace_back(Args ... args) {
        T temp(args...);
        if (head_ == nullptr) {
            head_ = make_unique<node_>(nullptr, nullptr, std::move(temp));
            tail_ = head_.get();
        } else {
            tail_->next_ = make_unique<node_>(nullptr, tail_, std::move(temp));
            tail_ = tail_->next_.get();
        }
        ++length_;
        return back();
    }

    T& back() const {
        assert(tail_ != nullptr);
        return tail_->data_;
    }

    void push_front(const T& data) {
        auto t = head_.release();
        head_ = make_unique<node_>(t, nullptr, std::move(data));
        if (tail_ == nullptr) {
            tail_ = head_.get();
        }
        ++length_;
    }

    void pop_front() {
        auto t = (*head_).next_.release();
        head_.reset(t);
        --length_;
    }

    template <typename... Args>
    T& emplace_front(Args... args) {
        T temp(args...);
        auto t = head_.release();
        head_ = make_unique<node_>(t, nullptr, std::move(temp));
        if (tail_ == nullptr) {
            tail_ = head_.get();
        }
        ++length_;
        return front();

    }

    T& front() const {
        assert(head_ != nullptr);
        return (*head_).data_;
    }

    void insert(const T& data, const size_t index) {
        if (index == 0) {
            push_front(std::move(data));
        } else if (index == length_) {
            push_back(std::move(data));
        } else {
            auto it = atIndex(index);
            --it;
            auto temp = static_cast<base_iterator>(it).ptr_->next_.release();
            static_cast<base_iterator>(it).ptr_->next_ =
                    make_unique<node_>(temp, static_cast<base_iterator>(it).ptr_, std::move(data));
            ++length_;
        }
    }

    template <typename... Args>
    T& emplace(const size_t index, Args... args) {
        T data(args...);
        if (index == 0) {
            push_front(std::move(data));
            return front();
        } else if (index == length_) {
            push_back(std::move(data));
            return back();
        } else {
            auto it = atIndex(index);
            --it;
            auto temp = static_cast<base_iterator>(it).ptr_->next_.release();
            static_cast<base_iterator>(it).ptr_->next_ =
                    make_unique<node_>(temp, static_cast<base_iterator>(it).ptr_, std::move(data));
            ++length_;
            return static_cast<base_iterator>(it).ptr_->next_.get()->data_;
        }
    }

    T& operator[](const size_t index) {
        return static_cast<base_iterator>(atIndex(index)).ptr_->data_;
    }

    T& at(const size_t index) {
        return static_cast<base_iterator>(atIndex(index)).ptr_->data_;
    }

    void clear() {
        head_.reset();
        tail_ = nullptr;
        length_ = 0;
    }

    void erase(const size_t start, const size_t end) {
        assert(start <= end);
        assert(end <= length_);

        if(start == 0 && end == length_){
            clear();
        }

        if (start == 0){
            auto h = atIndex(end);
            static_cast<base_iterator>(h).ptr_->back_->next_.release();
            static_cast<base_iterator>(h).ptr_->back_ = nullptr;
            head_.reset(static_cast<base_iterator>(h).ptr_);
        } else if (end == length_){
            auto h = atIndex(start);
            --h;
            tail_ = static_cast<base_iterator>(h).ptr_;
            tail_->next_.reset();
        } else {
            auto end_it = begin();
            iterator start_it;
            for (int i = 0; i < end; ++i) {
                if(i == start){
                    start_it = end_it;
                }
                ++end_it;
            }
            static_cast<base_iterator>(end_it).ptr_->back_->next_.release();
            static_cast<base_iterator>(end_it).ptr_->back_ = static_cast<base_iterator>(start_it).ptr_->back_;
            --start_it;
            static_cast<base_iterator>(start_it).ptr_->next_.reset(static_cast<base_iterator>(end_it).ptr_);
        }

        length_ -= end - start;

    }

    void rsize(const size_t index) {
        assert(index < length_);
        auto it = atIndex(index);
        --it;
        tail_ = static_cast<base_iterator>(it).ptr_;
        static_cast<base_iterator>(it).ptr_->next_.reset();
        length_ = index;
    }

    size_t size() const {
        return length_;
    }

    iterator begin() {
        return iterator(head_.get());
    }

    iterator end() {
        return iterator(tail_, true);
    }

    const_iterator begin() const {
        return const_iterator(head_.get());
    }

    const_iterator end() const {
        return const_iterator(tail_, true);
    }

    const_iterator cbegin() const {
        return const_iterator(head_.get());
    }

    const_iterator cend() const {
        return const_iterator(tail_, true);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(tail_);
    }

    reverse_iterator rend() {
        return reverse_iterator(head_.get(), true);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(tail_);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(head_.get(), true);
    }
};
}


#endif //C17TESTING_LINK_LIST_V2_H
