// Copyright 2019 DM00n <teamvortex@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

class Cache {
public:
    Cache(unsigned buf);

    void warm();

    void experiment_d(int num);

    void experiment_rev(int num);

    void experiment_rand(int num);

    ~Cache();

    void fill_direct();

    void fill_reverse();

    void fill_random(std::vector<int> pos_vec);

    void make_report(const std::string &dir, int num, int dur);

private:
    int *_array;
    unsigned _length;
};

#endif // INCLUDE_HEADER_HPP_
