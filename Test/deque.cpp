#include <vector>
#include <iostream>
#include "catch.hpp"
#include "deque.h"
#include <deque>
#include <random>  
#include <ctime>  

TEST_CASE( "Deque can be created and deleted", "[deque]" ) {
    Deque<int32_t> d;
    Deque<char>* q = new Deque<char>();
    delete q;
}

TEST_CASE( "All Back functions work properly", "[deque]" ) {
    Deque<int32_t> d;
    for (int32_t i = 0; i < 1024; ++i) d.PushBack(i);
    for (int32_t i = 1023; i >= 0; --i) {
        REQUIRE(d.Back() == i);
        d.PopBack();
        
    }
}

TEST_CASE( "All Front functions work properly", "[deque]" ) {
    Deque<int32_t> d;
    for (int32_t i = 0; i < 1024; ++i) d.PushFront(i);
    for (int32_t i = 1023; i >= 0; --i) {
        REQUIRE(d.Front() == i);
        d.PopFront();
        
    }
}

TEST_CASE( "Mixed Front+Back", "[deque]" ) {
    Deque<int32_t> d;
    for (int32_t i = 512; i < 1024; ++i) d.PushBack(i);
    for (int32_t i = 511; i >= 0; --i) d.PushFront(i);
    for (int32_t i = 1023; i >= 0; --i) {
        REQUIRE(d.Back() == i);
        d.PopBack();
    }
    
     for (int32_t i = 512; i < 1024; ++i) d.PushBack(i);
    for (int32_t i = 511; i >= 0; --i) d.PushFront(i);
    for (int32_t i = 0; i < 1024; ++i) {
        REQUIRE(d.Front() == i);
        d.PopFront();
    }
}

TEST_CASE ( "Long way to future", "[deque]" ) {
    Deque<int32_t> d;
    const size_t shift = 20;
    for (int32_t i = 0; i < 10; ++i) {
        for (int32_t i = 0; i < (1 << shift); ++i) d.PushBack(i);
        for (int32_t i = 0; i < (1 << shift); ++i) d.PopFront();
        for (int32_t i = 0; i < (1 << shift); ++i) d.PushFront(i);
        for (int32_t i = 0; i < (1 << shift); ++i) d.PopBack();
        REQUIRE(d.Size() == 0);
    }
}

TEST_CASE ( "Flow to front", "[deque]" ) {
    Deque<int32_t> d;
    const size_t shift = 20;
    for (int32_t i = 0; i < 100; ++i) {
        for (int32_t i = 0; i < (1 << shift); ++i) d.PushFront(i);
        for (int32_t i = 0; i < (1 << shift); ++i) d.PopBack();
        REQUIRE(d.Size() == 0);
    }
}

TEST_CASE ( "Flow to back", "[deque]" ) {
    Deque<int32_t> d;
    const size_t shift = 20;
    for (int32_t i = 0; i < 100; ++i) {
        for (int32_t i = 0; i < (1 << shift); ++i) d.PushBack(i);
        for (int32_t i = 0; i < (1 << shift); ++i) d.PopFront();
        REQUIRE(d.Size() == 0);
    }
}

TEST_CASE ( "Stress test", "[deque]" ) {
    std::mt19937 gen(time(0)); 
    std::uniform_int_distribution<> dist(0, 1<<30); 
    Deque<int32_t> d;
    std::deque<int32_t> ref;
    
    for (auto i = 0; i < 1000000; ++i) {
        auto number = dist(gen);
        d.PushBack(number);
        ref.push_back(number);
    }
    
    for (auto i = 0; i < 1000000; ++i) {
        auto number = dist(gen);
        switch(number & 3) {
            case 0:
                d.PushBack(number);
                ref.push_back(number);
                break;
            case 1:
                d.PushFront(number);
                ref.push_front(number);
                break;
            case 2:
                d.PopBack();
                ref.pop_back();
                break;
            case 3:
                d.PopFront();
                ref.pop_front();
                break;
        }
    }
    REQUIRE(d.Size() == ref.size());
    for (size_t i = 0; i < d.Size(); ++i) {
        REQUIRE(d[i] == ref[i]);
    }
}
