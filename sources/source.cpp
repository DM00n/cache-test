// Copyright 2019 DM00n <teamvortex@yandex.ru>

#include <header.hpp>

typedef std::chrono::high_resolution_clock Clock;

Cache::Cache(unsigned buf) {
    _array = new int[buf / sizeof(int)];
    _length = buf / sizeof(int);
}

Cache::~Cache() {
    delete[] _array;
}

void Cache::warm() {
    int g = 0;
    while (g < 100) {
        for (unsigned i = 0; i < _length; i++) {
            _array[i] = 0;
        }
        g++;
    }
}

void Cache::fill_direct() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (unsigned i = 0; i < _length; i++) {
        _array[i] = mersenne() % 100 + 1;
    }
}

void Cache::fill_reverse() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (unsigned i = 0; i < _length; i++) {
        _array[_length - i - 1] = mersenne() % 100 + 1;
    }
}

void Cache::fill_random(std::vector<int> pos_vec) {
    while (!pos_vec.empty()) {
        std::random_device rd;
        std::mt19937 mersenne(rd());
        int pos = pos_vec[pos_vec.size() - 1];
        _array[pos] = mersenne() % 100 + 1;
        pos_vec.pop_back();
    }
}

void Cache::experiment_d(int num) {
    auto t1 = Clock::now();
    for (unsigned j = 0; j < 10; j++) {
        fill_direct();
    }
    auto t2 = Clock::now();
    make_report("\"direct\"", num, std::chrono::duration_cast
                    <std::chrono::nanoseconds>(t2 - t1).count());
}

void Cache::experiment_rev(int num) {
    auto t1 = Clock::now();
    for (unsigned j = 0; j < 10; j++) {
        fill_reverse();
    }
    auto t2 = Clock::now();
    make_report("\"reverse\"", num, std::chrono::duration_cast
            <std::chrono::nanoseconds>(t2 - t1).count());
}

void Cache::experiment_rand(int num) {
    std::vector<int> pos_vec(_length);
    for (unsigned i = 0; i < pos_vec.size(); ++i) {
        pos_vec[i] = i;
    }
    std::random_device rd;
    std::shuffle(std::begin(pos_vec), std::end(pos_vec), rd);
    auto t1 = Clock::now();
    for (unsigned j = 0; j < 10; j++) {
        fill_random(pos_vec);
    }
    auto t2 = Clock::now();
    make_report("\"random\"", num, std::chrono::duration_cast
            <std::chrono::nanoseconds>(t2 - t1).count());
}

void Cache::make_report(const std::string &dir, int num, int dur) {
    std::string str1, exps, expt1, expt2,
                expt3, duration, buf_size, number, OMEGASTRING;
    str1 = "investigation:\n"
           "\ttravel_variant: ";
    exps = "\nexperiments:\n";
    expt1 = "\t- experiment:\n\t\tnumber: ";
    expt2 = "\n\t\tinput_data:\n\t\t\tbuffer_size: ";
    expt3 = "\n\t\tresults:\n\t\t\tduration: ";
    number = std::to_string(num + 1);
    duration = "\"" + std::to_string(dur) + "ns\"\n\n";
    int size_of_arr = _length * sizeof(int);
    int measure = 0;
    while (size_of_arr >= 1024) {
        size_of_arr /= 1024;
        measure++;
    }
    switch (measure) {
        case 0 : {
            buf_size = "\"" + std::to_string(size_of_arr) + "b\"";
            break;
        }
        case 1 : {
            buf_size = "\"" + std::to_string(size_of_arr) + "Kb\"";
            break;
        }
        case 2 : {
            buf_size = "\"" + std::to_string(size_of_arr) + "Mb\"";
            break;
        }
        case 3 : {
            buf_size = "\"" + std::to_string(size_of_arr) + "Gb\"";
            break;
        }
        case 4 : {
            buf_size = "\"" + std::to_string(size_of_arr) + "Tb\"";
            break;
        }
    }
    if (num == 0) OMEGASTRING = str1 + dir + exps + expt1
            + number + expt2 + buf_size + expt3 + duration;
    else
        OMEGASTRING = expt1 + number + expt2 + buf_size + expt3 + duration;
    std::ofstream out;
    out.open(R"(C:\Users\Rex\Documents\GitHub\cache_test)", std::ios::app);
    if (!out) std::cout << "error opening file";
    else
        out << OMEGASTRING;
    OMEGASTRING.clear();
    out.close();
}

