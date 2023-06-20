#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


namespace ariel {
class MagicalContainer {
private:
    std::vector<int> numbers;

public:
    void addElement(int num);

    void removeElement(int num);

    int size() const;

    // Ascending Iterator
    class AscendingIterator {
    private:
        const MagicalContainer& container;
        size_t index;

    public:
        AscendingIterator(const MagicalContainer& cntr) : container(cntr), index(0) {}

        const int& operator*() const {
            return container.numbers[index];
        }

        //++i
        AscendingIterator& operator++() {
            if(index >= container.numbers.size()){
                throw std::runtime_error("Index out of range");
            }
            ++index;
            return *this;
        }

        // i++;
        // Usually iterators are passed by value and not by const& as they are small.
        const AscendingIterator operator++(int) {
            AscendingIterator tmp= *this;
            if(index >= container.numbers.size()){
                throw std::runtime_error("Index out of range");
            }
            ++index;
            return tmp;
        }

        bool operator==(const AscendingIterator& cntr) const {
            return index == cntr.index;
        }

        bool operator!=(const AscendingIterator& cntr) const {
            return !(*this == cntr);
        }

        AscendingIterator& operator=(const AscendingIterator& cntr) {
            if (this != &cntr) {
                throw std::runtime_error("The pointer not goood");
            }
            else{
                index = cntr.index;
            }
            return *this;
        }

        bool operator<(const AscendingIterator& cntr) const {
            return this->container.numbers[index] < cntr.container.numbers[cntr.index];
        }

        bool operator>(const AscendingIterator& cntr) const {
            return this->container.numbers[index] > cntr.container.numbers[cntr.index];
        }

        AscendingIterator begin() const {
            return *this;
        }

        AscendingIterator end() const {
            //helped from chatGPT - creat new AscendingIterator, 
            // and because it's pass by referece, our AscendingIterator and the new one have the same container address
            AscendingIterator iter(container);
            iter.index = container.numbers.size();
            return iter;
        }
    };//end AscendingIterator


    // SideCross Iterator
    class SideCrossIterator {
    private:
        MagicalContainer& container;
        //index that go to both begining and end
        size_t index;
        //return true if "index" is related to begin index, amd false if it's related to the end
        bool isBegin;
        //count how much time we move
        size_t count;


    public:
        SideCrossIterator(MagicalContainer& cntr) : 
        container(cntr), index(0), count(0), isBegin(true) {
        }

        const int& operator*() const {

            if (isBegin){
                return container.numbers[index];
            }
            else{
                return container.numbers[container.numbers.size() - index];
            }
        }

        SideCrossIterator& operator++() {
            if(count >= container.numbers.size()){
                throw std::runtime_error("index out of range");
            }
            if (isBegin){
                index += 1;
                isBegin = false;
            }
            else{
                isBegin = true;
            }
            count +=1;
            return *this;
        }

        SideCrossIterator& operator=(const SideCrossIterator& cntr) {
            if (this != &cntr) {
                throw std::runtime_error("The pointer not goood");
                
            }
            else{
                container = cntr.container;
                isBegin = cntr.isBegin;
                index = cntr.index;
                count = cntr.count;
            }
            return *this;
        }

        bool operator==(const SideCrossIterator& cntr) const {
            //If they move same times they are equals
            return count == cntr.count;
        }

        bool operator!=(const SideCrossIterator& cntr) const {
            return !(*this == cntr);
        }

        bool operator>(const SideCrossIterator& cntr) const {
            return this->container.numbers[index] > cntr.container.numbers[cntr.index];
        }

        bool operator<(const SideCrossIterator& cntr) const {
            return this->container.numbers[index] < cntr.container.numbers[cntr.index];
        }

        SideCrossIterator begin() const {
            return *this;
        }

        SideCrossIterator end() const {
            //helped from chatGPT (like Accending iterator)
            SideCrossIterator iter(container);
            iter.count = container.numbers.size();   
            return iter;
        }
    };//end SideCrossIterator

    // Prime Iterator
    class PrimeIterator {
    private:
        MagicalContainer& container;
        size_t index;

        bool isPrime(int num) const {
            if (num <= 1)
                return false;

            int sqrtNum = static_cast<int>(std::sqrt(num));
            for (int i = 2; i <= sqrtNum; ++i) {
                if (num % i == 0)
                    return false;
            }
            return true;
        }

    public:
        PrimeIterator(MagicalContainer& cntr) : container(cntr), index(0) {
            while (index < container.size() && !isPrime(container.numbers[index])) {
            ++index;
        }

        }

        const int& operator*() const {
            return container.numbers[index];
        }

        PrimeIterator& operator++() {
            ++index;
            if(index >= container.numbers.size()){
                throw std::runtime_error("Index out of range");
            }
            while (index < container.numbers.size() && !isPrime(container.numbers[index])) {
                ++index;
            }
            return *this;
        }

        bool operator==(const PrimeIterator& cntr) const {
            return index == cntr.index;
        }

        bool operator!=(const PrimeIterator& cntr) const {
            return !(*this == cntr);
        }

        PrimeIterator& operator=(const PrimeIterator& cntr) {
            if (this != &cntr) {
                throw std::runtime_error("The pointer not goood");
                
            }
            else{
                container = cntr.container;
                index = cntr.index;            
            }
            return *this;
        }

        bool operator>(const PrimeIterator& cntr) const {
            return this->container.numbers[index] > cntr.container.numbers[cntr.index];
        }

        bool operator<(const PrimeIterator& cntr) const {
            return this->container.numbers[index] < cntr.container.numbers[cntr.index];
        }

        PrimeIterator begin () const {
            return *this;
        }

        PrimeIterator end() const {
            PrimeIterator iter(container);
            iter.index = container.numbers.size();
            return iter;
        }
    };//end PrimeIterator
};//end MagicalContainer
};//end ariel namespace