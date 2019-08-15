#pragma once

#include <array>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <vector>

template<typename T>
class dl_list {
public:
    struct chunk {
        chunk()
        {
            value = {};
            next = nullptr;
            prev = nullptr;
        }
        T value;
        std::shared_ptr<chunk> next;
        std::shared_ptr<chunk> prev;
    };
public:
    dl_list() {
        // create head
        head = std::make_shared<chunk>();
        tail = head;
        count = 0;
    }
    void add_front(T &&t)
    {
         std::shared_ptr<chunk> item = std::make_shared<chunk>();
         item->value = t;
         item->prev = head;
         item->next = head->next;

         if(tail == head) {
             head->next = item;
             tail = item;
         } else {
             head->next->prev = item;
             head->next = item;
         }
         count++;
    }
    void add_back(T &&t)
    {
         std::shared_ptr<chunk> item = std::make_shared<chunk>();
         item->value = t;
         item->prev = tail;
         item->next = tail->next;
         tail->next = item;
         tail = tail->next;
         count++;
    }
    bool del_first_item_by_val(T &&t)
    {
        for(auto it = head->next; it; it = it->next) {
            if (it->value == t) {
                if (it == tail) {
                    std::cout << "del last element - " << it->value << std::endl;
                    del_back();
                    return true;
                } else
                if (it == head->next) {
                    std::cout << "del first element - " << it->value << std::endl;
                    del_front();
                    return true;
                } else
                if (it->next == tail) {
                    std::cout << "del prev last element - " << it->value << std::endl;
                    it->prev->next = it->next;
                    tail->prev = it->prev;
                    count--;
                    return true;
                } else {
                    std::cout << "del element in the middle - " << it->value << std::endl;
                    it->prev->next = it->next;
                    it->next->prev = it->prev;
                    count--;
                    return true;
                }
            }
        }
    return false;
}

    void del_front()
    {
        if (!head->next) {
            return;
        }
        if (head->next == tail) {
            tail = head;
            tail->prev = nullptr;
            tail->next = nullptr;
        } else {
            head->next = head->next->next;
            head->next->prev = head;
        }
        count--;
    }
    void del_back()
    {
        tail = tail->prev;
        tail->next = nullptr;
        count--;
    }
    void del_all_items()
    {
        auto item = head;
        while(item = item->next) {
            del_front();
        }
    }
    void set_head(std::shared_ptr<chunk> new_head)
    {
        head = new_head;
    }
    void reset_head()
    {
        head->next = nullptr;
        tail = head;
    }

    void set_tail(const std::shared_ptr<chunk> new_tail)
    {
        tail = new_tail;
        tail->next = nullptr;
    }
    const T get_first_item() const
    {
        if (head->next) {
            return head->next->value;
        } else {
            return {};
        }
    }
    const T get_last_item() const
    {
        return tail->value;
    }
    const std::shared_ptr<chunk> get_head() const
    {
        return head;
    }
    const std::shared_ptr<chunk> get_first_chunk() const
    {
        return head->next;
    }
    const std::shared_ptr<chunk> get_tail() const
    {
        return tail;
    }
    const size_t size() const
    {
        return count;
    }
    void show_all()
    {
        std::cout << "current items:" << std::endl;
        for(auto it = head->next; it; it = it->next) {
            std::cout << it->value << " ";
        }
        std::cout << std::endl;
    }

private:
    size_t count;
    std::shared_ptr<chunk> head;
    std::shared_ptr<chunk> tail;
};


template<typename T1>
class pr_arr_queue {
public:
    pr_arr_queue(size_t v_size = 100)
    {
        vect_ = std::vector<std::shared_ptr<dl_list<T1>>>(v_size);
        for(auto &item: vect_) {
            item = std::make_shared<dl_list<T1>>();
        }
    }
    void add_front(size_t pri, T1 &&t1)
    {
        vect_[pri]->add_front(std::move(t1));
    }
    void add_front(T1 &&t1)
    {
        vect_[vect_.size() - 1]->add_front(std::move(t1));
    }
    bool del_by_val(T1 &&t1)
    {
        for(auto &item : vect_) {
            if (item->del_first_item_by_val(std::move(t1))) {
                return true;
            }
        }
        return false;
    }
    void change_elem_pri(size_t old_pri, size_t new_pri)
    {
        return;
    }
    void change_all_elem_pri(size_t old_pri, size_t new_pri)
    {
        const std::shared_ptr<struct dl_list<T1>::chunk> old_p_fch = vect_[old_pri]->get_first_chunk();
        if (old_p_fch) {
            const std::shared_ptr<struct dl_list<T1>::chunk> new_p_t = vect_[new_pri]->get_tail();

            new_p_t->next = old_p_fch;
            vect_[new_pri]->set_tail(vect_[old_pri]->get_tail());
            vect_[old_pri]->reset_head();
        } else {
            std::cout << "nothing to migrate" << std::endl;
        }

    }
    T1 show_first_val_with_pri(size_t pri)
    {
        return vect_[pri]->get_last_item();
    }
    size_t size(size_t pri)
    {
        return vect_[pri]->size();
    }
    void show_all()
    {
        for(auto &item : vect_) {
            item->show_all();
        }

    }
    void show_all_last_pri()
    {
        vect_[vect_.size() - 1]->show_all();
    }
public:
    std::vector<std::shared_ptr<dl_list<T1>>> vect_;
    dl_list<T1> list_;
};
