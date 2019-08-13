#include <iostream>

#include "fp_queue.hpp"

int main()
{

    d_list<int> test;
    test.add_front(3);
//    test.add_front(2);
//    test.add_front(1);

    test.del_front();
    std::cout << "first: " << test.get_first_item() << std::endl;
    std::cout << "last: " << test.get_last_item() << std::endl;

    return 0;
}
