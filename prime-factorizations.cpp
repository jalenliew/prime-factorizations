#include <iostream>
#include <map>
#include <iomanip>

int getHighestNumberFactors(int num) {
    int count = 0;
    do {
        num = num >> 1;
        count++;
    } while (num > 1);
    return count;
}

void getPrimeFactors(std::map<int, int> primeNumbers, int num, int* &primeFactors, int size) {
    int index = 0;
    for (auto it = ++primeNumbers.begin(); it != primeNumbers.end();) {
        int primeNumber = it->first;

        if (num % primeNumber == 0) {
            num /= primeNumber;
            primeFactors[index] = primeNumber;
            index++;
        } else {
            it++;
        }
    }
    if (index == 0) {
        primeFactors[0] = 0;
    }
}

void bubbleSort(int* &arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void print(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            std::cout << '0';
        } else {
            std::cout << arr[i];
        }
        if (i + 1 < size) {
            std::cout << " * ";
        }
    }
}

int main() {
    int n;
    std::map<int, int> primeNumbers = {{1, 0}};

    std::cout << "Find Prime Factorizations up to: ";
    std::cin >> n;
    if (n < 1) {
        std::cout << "This is not designed to handle values smaller than 1";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        int size = getHighestNumberFactors(i);
        int* primeFactors = new int[size]();

        getPrimeFactors(primeNumbers, i, primeFactors, size);
        bubbleSort(primeFactors, size);

        if (primeFactors[0] == 0) {
            primeNumbers.at(1)++;
            primeNumbers.insert(std::make_pair(i, 0));


            std::cout << i << " is a Prime Number" << std::endl;
        } else {
            primeNumbers.at(primeFactors[0])++;

            std::cout << i << " = ";
            print(primeFactors, size);
            std::cout << std::endl;
        }

        delete primeFactors;
        primeFactors = nullptr;
    }

    for (auto it = primeNumbers.begin(); it != primeNumbers.end(); it++) {
        if (it->first == 1) {
            std::cout << "Prime";
        } else {
            std::cout << it->first;
        }
        std::cout << " Instances: " << it->second << "| Percentage: " << std::fixed << std::setprecision(2) << ((static_cast<float>(it->second) / static_cast<float>(n)) * 100) << '%' << std::endl;
    }

    return 0;
}
