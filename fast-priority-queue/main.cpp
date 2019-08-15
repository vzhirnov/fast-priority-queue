#include <iostream>

#include "fp_queue.hpp"

int main()
{


//    dl_list<int> test;
//    test.add_front(1);
//    test.add_front(2);
//    test.add_front(3);
//    test.add_front(4);
//    test.add_front(5);
//    test.del_all_items();
//    std::cout << "front: " << test.get_first_item() << std::endl;

    pr_arr_queue<int> test(5);
    test.add_front(0, 0);
    test.add_front(0, 1);
    test.add_front(0, 2);
    test.add_front(0, 3);
    test.add_front(1, 4);
    test.add_front(1, 5);
//    test.show_all_last_pri();

    test.change_all_elem_pri(0, 1);
//    test.del(0);
//    test.del(3);
//    test.del(2);
//    test.del(1);

//    test.show_all();
    test.add_front(0, 11);
//    test.add_front(0, 22);
//    test.add_front(0, 33);
    test.show_all();
//    std::cout << "size: " << test.size(99) << std::endl;
//    std::cout << "show_first_val_with_pri: " << test.show_first_val_with_pri(99) << std::endl;

    return 0;
}
