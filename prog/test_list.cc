#include "list.hpp"
#include <iostream>
#include <memory>
#include <cassert>
#include <sstream>

int main()
{
    // {
    //     using namespace std;
    //     List::Item it;
    //     cout << it.get_value() << endl;
    //     List::Item it2{3};
    //     cout << "it2: " << it2.get_value() << endl;
    //     cout << "it2.next: " << it2.next.get() << endl;
    //     List::Item* ip = new List::Item(3);
    //     cout << "ip->getvalue(): " << ip->get_value() << endl;
    //     cout << "ip->next.get(): " << ip->next.get() << endl;
    //     auto ip2 = make_unique<List::Item>(4);
    //     cout << "ip2->getvalue(): " << ip2->get_value() << endl;
    //     cout << "ip2->next.get(): " << ip2->next.get() << endl;
    // }

    // {
    //     using namespace std;
    //     List l;
    //     cout << l.empty() << endl;
    //     cout << "size: " << l.size() << endl;
    //     cout << "l: " << l << endl;

    //     l.push_front(3);
    //     l.push_front(4);
    //     l.push_front(-2);
    //     l.push_front(10);

    //     cout << "l: " << l << endl;

    //     l.pop_front();
    //     l.pop_front();

    //     cout << "l: " << l << endl;
    // }

    // {
    //     using namespace std;
    //     List l;
    //     cout << l.empty() << endl;
    //     l.push_front(1);
    //     cout << l.empty() << endl;
    // }

    // {
    //     using namespace std;
    //     cout << endl << "testing size: " << endl;
    //     List l;
    //     l.push_front(1);
    //     cout << l.size() << endl;
    //     l.push_front(2);
    //     cout << l.size() << endl;
    // }

    {
        using namespace std;
        cout << endl << "testing push_front(): " << endl;
        List l;

        for (int i = 0; i < 10; i++) {
            l.push_front(i);
        }
   
        cout << l << endl;
    }

    // {
    //     using namespace std;
    //     cout << endl << "testing pop_front(): " << endl;
    //     List l;
    //     l.push_front(1);
    //     cout << "l: " << endl;
    //     {
    //         auto ip = l.pop_front();
    //         cout << "l: " << endl;
    //         assert(ip->get_value() == 1);
    //     }

    //     {
    //         // auto ip = l.pop_front();
    //         // assert(!ip);
    //     }
    // }

    // {
    //     using namespace std;
    //     cout << endl << "testing foreach: " << endl;
    //     {
    //         List l;
    //         l.push_front(1);
    //         l.push_front(2);
    //         l.push_front(-3);
    //         cout << "l: " << l << endl;
    //         l.foreach([] (const List::Value& val) {std::cout << val << " ";});
    //         cout << endl;
    //     }
    // }

    // {
    //     using namespace std;
    //     cout << endl << "testing push_back(): " << endl;
    //     {
    //         List l;
    //         l.push_front(1);
    //         l.push_front(2);
    //         cout << l << endl;
    //         l.push_back(3);
    //         cout << l << endl;
    //     }
    //     cout << "push_back() and push_back_item() are not yet implemented!" << endl;
    // }

    // // {
    // //     using namespace std;
    // //     cout << endl << "testing move_into_if" << endl;
    // //     {
    // //         List l;
    // //         for (int i = 0; i < 10; i++) l.push_back(i);
    // //         cout << "l: " << l << endl;
    // //         List l_even;
    // //         l.move_into_if(l_even, 
    // //             [] (const List::Value& val) {return val % 2 == 0;});
    // //         cout << "l_even: " << l_even << endl;
    // //     }
    // // }

    // {
    //    using namespace std;
    //    cout << endl << "testing is_sorted():" << endl;
    //    List l;
    //    l.push_front(2);
    //    assert(l.is_sorted());
    //    cout << "l: " << l << "is sorted? " << l.is_sorted() << endl;
    //    l.push_front(1);
    //    cout << "l: " << l << "is sorted? " << l.is_sorted() << endl;
    //    assert(l.is_sorted());
    //    l.push_front(3);
    //    cout << "l: " << l << "is sorted? " << l.is_sorted() << endl;
    //    assert(!l.is_sorted());
    // }

    // {
    //     using namespace std;
    //     cout << endl << "testing list traversal with while: " << endl;
    //     List l;
    //     l.push_front(3);
    //     l.push_front(-1);
    //     l.push_front(4);
    //     l.push_front(-5);
    //     l.push_front(10);
    //     l.traverse();
    //     cout << endl;
    // }

    // {
    //     using namespace std;
    //     cout << endl << "testing automatic destruction: " << endl;
    //     {
    //         auto head = std::make_unique<List::Item>(1);
    //         head->next = std::make_unique<List::Item>(3);
    //         head->next->next = std::make_unique<List::Item>(-2);
    //     }

    // }

    // {
    //     using namespace std;
    //     cout << endl << "testing deletion with pop front: " << endl;
    //     List l; 
    //     l.push_front(3);
    //     l.push_front(-1);
    //     l.push_front(4);
    //     l.push_front(-5);
    //     l.push_front(10);
    //     cout << "l: " << l << endl;
    //     l.pop_front(); 
    //     cout << "l: " << l << endl;
    // }

    {
        using namespace std;
        cout << endl << "testing destructor" << endl;
        List l; 
        l.push_front(3);
        l.push_front(-1);
        l.push_front(4);
        l.push_front(-5);
        l.push_front(10);
        cout << "l: " << l << endl;
        l.pop_front(); 
        cout << "l: " << l << endl;
    }

    {
        using namespace std;
        cout << endl << "testing push_back(): " << endl;
        List l;
        l.push_front(3);
        l.push_front(-2);
        l.push_back(1);
        l.push_back(5);
        cout << "l: " << l << endl;

        List l2;
        l2.push_back(3);
        l2.push_back(10);
        cout << "l2: " << l2 << endl;

        List l3;
        for (int i = 0; i < 10; i++) l3.push_back(i);
        cout << "l3: " << l3 << endl;

    }

    {
        using namespace std;
        cout << endl << "testing concat: " << endl;
        List l1;
        l1.push_back(3);
        l1.push_back(-2);
        l1.push_back(4);
        cout << "l1: " << l1 << endl;

        List l2;
        l2.push_back(7);
        l2.push_back(5);
        l2.push_back(9);
        cout << "l2: " << l2 << endl;

        l1.concat(l2);
        cout << "after concat: " << endl;
        cout << "l1: " << l1 << endl;
        cout << "l2: " << l2 << endl;

        List l5;
        l5.push_back(20);
        cout << "concatenating to l1 again: " << endl;
        l1.concat(l5);
        cout << "l1: " << l1 << endl;
        cout << "l5: " << l5 << endl;

        List l3;
        l1.concat(l3);
        cout << "after concat with an empty list: " << endl;
        cout << "l1: " << l1 << endl;


        List l4;
        l4.concat(l1);
        cout << "concatenating to an empty list: " << endl;
        cout << "l4: " << l4 << endl;
        cout << "l1: " << l1 << endl;


    }

    {
        using namespace std;
        cout << endl << "testing move_into_if(): " << endl;

        List l, l3;

        for (int i = 0; i < 10; i++) l.push_back(i); // l == [0, 1, ... , 9]

        // is_even is a lambda expresion
        // auto is_even = [] (const List::Value& val) {return val % 2 == 0; };
        auto is_greater_than_3 = [] (const List::Value& val) {return (val > 7);};

        l.move_into_if(l3, is_greater_than_3);

        cout << "l: " << l << endl;
        cout << "l3: " << l3 << endl;

        // List l3;

        // l.move_into_if(l3, is_greater_than_3);

        // cout << "l: " << l << endl;
        // cout << "l3: " << l3 << endl;

        List l4, l5;

        l4.move_into_if(l5, is_greater_than_3);
        cout << "l4: " << l4 << endl;
        cout << "l5: " << l5 << endl;
    }

    {
        using namespace std;
        cout << endl << "test stringstream: " << endl;
        List l1;
        l1.push_back(1);
        l1.push_back(2);

        stringstream ss;
        ss << l1;
        cout << "ss: " << ss.str() << endl;

        stringstream ss2;
        ss2 << l1;
        cout << "ss2: " << ss.str() << endl;
    }

    {
        using namespace std;
        cout << endl << "test sort: " << endl;
        List l;
        l.push_back(3);
        l.push_back(1);
        l.push_back(2);
        l.push_back(4);
        l.push_back(10);
        l.push_back(-3);
        l.push_back(20);
        l.push_back(9);
        std::cout << "l: " << l << std::endl;
        int k = l.sort();
        std::cout << "sorted l: " << l << std::endl; // gibt "[1, 2, 3, 4]" aus.
        std::cout << "k: " << k << std::endl;

    }


    return 0;
}