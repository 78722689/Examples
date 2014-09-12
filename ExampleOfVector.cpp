#include <stdio.h>
#include <vector>
#include <iostream>
#include <new>

int main()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    std::cout << "capacity=" << vec.capacity() << " size=" << vec.size() << " max_size="<<vec.max_size() << std::endl;
    printf("capacity=%d, size=%d, max_size=%d , i=%d\n", vec.capacity(), vec.size(), vec.max_size());
    return 1;
}