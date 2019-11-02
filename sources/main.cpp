// Copyright 2019 DM00n <teamvortex@yandex.ru>
#include <iostream>
#include "header.hpp"

#define e0 131072
#define e1 262144
#define e2 524288
#define e3 1048576
#define e4 2097152
#define e5 4194304
#define e6 8388608
#define e7 9437184

void research_d(unsigned arr[]) {
    int size = sizeof(arr);
    for (unsigned i = 0; i < size; i++) {
        Cache instance(arr[i]);
        instance.warm();
        instance.experiment_d(i);
    }
}

void research_rev(unsigned arr[]) {
    int size = sizeof(arr);
    for (unsigned i = 0; i < size; i++) {
        Cache instance(arr[i]);
        instance.warm();
        instance.experiment_rev(i);
    }
}

void research_rand(unsigned arr[]) {
    int size = sizeof(arr);
    for (unsigned i = 0; i < size; i++) {
        Cache instance(arr[i]);
        instance.warm();
        instance.experiment_rand(i);
    }
}

int main() {
    unsigned exp[] = {e0, e1, e2, e3, e4, e5, e6, e7};
    research_d(exp);
    research_rev(exp);
    research_rand(exp);
    return 0;
}
