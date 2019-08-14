#include <iostream>

#include "fp_queue.hpp"

int main()
{

    pr_arr_queue<int> test(100);

    test.add(0, 0);
    test.add(1, 1);

    test.add(99, 99);
    test.add(99, 100);
    test.add(99, 101);

    std::cout << "size: " << test.size(99) << std::endl;
    if (test.del(99)) {
        test.del(100);
        test.del(101);
        std::cout << "deleted" << std::endl;
    }
    std::cout << "size: " << test.size(99) << std::endl;
    std::cout << "show_first_val_with_pri: " << test.show_first_val_with_pri(99) << std::endl;

    return 0;
}
