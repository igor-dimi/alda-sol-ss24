#include <iostream>

struct UniquePtr {
    int *ptr;
    // RAII - constructor taking integer pointer parameter
    UniquePtr(int* adr) : ptr(adr) {std::cout << "Constr: " << ptr << std::endl;}

    // copy constructor is deleted:
    UniquePtr(const UniquePtr &) = delete;

    // move constructor
    UniquePtr(UniquePtr&& other)
    {
        std::cout << "Move: " << other.ptr << std::endl;
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    ~UniquePtr()
    {
        if (ptr == nullptr) {
            std::cout << "Empty" << std::endl;
        } else {
            std::cout << "Destroy " << ptr << 
             " pointing to value " << *ptr << std::endl;
            delete ptr;
        }
    }
};

int main()
{
    UniquePtr up(new int(1));
    std::cout << "pointer: " << up.ptr << std::endl;
    std::cout << "value: " << *up.ptr << std::endl;

    // copy constructor is deleted
    // UniquePtr up2(up);
    // std::cout << "value: " << *up2.ptr << std::endl;

    /* code */

    {
        UniquePtr up1(new int(123));
        auto up2(std::move(up1));
        std::cout << "up1.ptr: " << up1.ptr << std::endl; 
        std::cout << "up2.ptr: " << up2.ptr << std::endl;
        std::cout << "*up2.ptr: " << *up2.ptr << std::endl;
        std::cout << "printing nullptr: " << nullptr << std::endl;

        auto *raw_ptr = up2.ptr;

        std::cout << "*raw_ptr: " << *raw_ptr << std::endl;
        
    }
    return 0;
}
