// Copyright 2019 DM00n <teamvortex@yandex.ru>
#include <iostream>
#include "header.hpp"

#define l0 131072
#define l1 262144
#define l2 524288
#define l3 1048576
#define l4 2097152
#define l5 4194304
#define l6 8388608
#define l7 9437184
#define max 6*1024*1024

std::map<int, int> number_of_experiments() {
    std::map<int, int> experiments;
    int count = 0, n = -2;
    experiments[count] = l1 / 2;
    count++;
    while (pow(2, n) * 1024*1024 < (3 * max / 2)) {
        experiments[count] = pow(2, n) * 1024*1024;
        count++;
        n++;
    }
    //++n;
    experiments[count] = 3 * max / 2;
    return experiments;
}
void research_d(unsigned arr[]) {
    int size = sizeof(arr);
    for (unsigned i = 0; i < size; ++i) {
        Cache instance(arr[i]);
        instance.warm();
        instance.experiment_d(i);
    }
}

void research_rev(unsigned arr[]) {
    int size = sizeof(arr);
    for (unsigned i = 0; i < size; ++i) {
        Cache instance(arr[i]);
        instance.warm();
        instance.experiment_rev(i);
    }
}

void research_rand(unsigned arr[]) {
    int size = sizeof(arr);
    for (unsigned i = 0; i < size; ++i) {
        Cache instance(arr[i]);
        instance.warm();
        instance.experiment_rand(i);
    }
}

int main() {
    std::map check_cache = number_of_experiments();
    unsigned exp[] = {l0, l1, l2, l3, l4, l5, l6, l7};
    research_d(exp);
    research_rev(exp);
    research_rand(exp);
    return 0;
}
