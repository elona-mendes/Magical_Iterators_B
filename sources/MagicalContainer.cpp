#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

void MagicalContainer::addElement(int num) {
    numbers.push_back(num);
    std::sort(numbers.begin(), numbers.end());
}

void MagicalContainer::removeElement(int num) {
    //was helped from chatGPT
    bool isIn = false;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == num) {
            numbers.erase(it);
            isIn = true;
            break;
        }
    }
    if(!isIn){
        throw std::runtime_error("The element is not in the container");
    }
}

int MagicalContainer::size() const {
    return numbers.size();
}