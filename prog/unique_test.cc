#include <memory>
#include <string>
#include <iostream>
#include <utility>

int main()
{
   
    auto sp = std::make_unique<std::string>("data");
    std::cout << "sp pointer value: " << sp.get() << std::endl;
    std::cout << "sp value: " <<  *sp << std::endl;
    std::cout << "*sp.get(): " << *sp.get() << std::endl;
    sp.get()->append(" item");
    std::cout << "*sp: " << *sp << std::endl;
    sp->append(" another data");
    std::cout << "*sp: " << *sp << std::endl;
    // std::cout << "sp value value: " << sp->get_value() << std::endl;


    auto sp02 = new std::string{"hey"};
    std::cout << *sp02 << std::endl;

    std::unique_ptr<int> up; 
    std::cout << "up (empty unique pointer): " << (bool) up << std::endl;
    std::unique_ptr<int> up2(new int{3});
    std::cout << "up2 (empty unique pointer): " << (bool) up2 << std::endl;

    {
        using namespace std;
        // copying unique pointers is not allowed
        auto up1 = std::make_unique<int>(123);
        // auto up2 = up1; (ERROR)

        auto up2(std::move(up1));
        cout << "up1: " << (bool) up1 << endl;
        cout << "up2: " << (bool) up2 << endl;
    }
    return 0;
}
