#pragma once

#include <array>
#include <list>
#include <memory>
#include <numeric>


template<typename T>
class d_list {
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
    d_list() {
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
             tail = tail->next;
             tail->prev = item;
         } else {
             head->next->prev = item;
             head->next = item;
         }

    }
    void add_back(T &&t)
    {
         std::shared_ptr<chunk> item = std::make_shared<chunk>();
         item->value = t;
         item->prev = tail;
         item->next = tail->next;
         tail->next = item;
         tail = tail->next;

    }
    void del_item_by_val(T t)
    {
        for(auto it = head->next; it; it = it->next) {
            if (it->value == t) {
                it->prev->next = it->next;
                if(it == tail) {
                    tail = tail->prev;
                }
            }
        }
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

    }
    void del_back()
    {
         tail = tail->prev;
         tail->next = nullptr;
    }
    T get_first_item()
    {
        return head->next->value;
    }
    T get_last_item()
    {
        return tail->value;
    }

private:
    size_t count;
    std::shared_ptr<chunk> head;
    std::shared_ptr<chunk> tail;


};
