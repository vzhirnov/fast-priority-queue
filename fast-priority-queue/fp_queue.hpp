#pragma once

#include <array>
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
            value = NULL;
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
        head->next = nullptr;
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
             tail = head->next;
             tail->prev = head;
             tail->next = nullptr;
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
                it->prev->next = it->next;
                if(it == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                count--;
                return true;
            }
        }
        return false;
    }
    void del_front()
    {
        if (head == tail) {
            return;
        } else {
            if (head->next == tail) {
                tail = head;
            } else {
                head->next = head->next->next;
            }
        }
        count--;

    }
    void del_back()
    {
         tail = tail->prev;
         tail->next = nullptr;
         count--;
    }
    T get_first_item()
    {
        return head->next->value;
    }
    T get_last_item()
    {
        return tail->value;
    }
    size_t size()
    {
        return count;
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
    void add(size_t pri, T1 &&t1)
    {
        vect_[pri]->add_front(std::move(t1));
    }
    void add(T1 &&t1)
    {
        vect_[vect_.size() - 1]->add_front(std::move(t1));
    }
    bool del(T1 &&t1)
    {
        for(auto &item : vect_) {
            if (item->del_first_item_by_val(std::move(t1))) {
                return true;
            }
        }
        return false;
    }
    T1 show_first_val_with_pri(size_t pri)
    {
        return vect_[pri]->get_last_item();
    }
    size_t size(size_t pri)
    {
        return vect_[pri]->size();
    }
public:
    std::vector<std::shared_ptr<dl_list<T1>>> vect_;
    dl_list<T1> list_;
};
