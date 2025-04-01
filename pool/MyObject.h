#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <iosfwd>
#include <string>
#include "pool.h"

class MyObject {
    int id;
    std::string name;
    static Pool pool;

    // Disallow copy, assign, and direct construction by user
    MyObject(const MyObject&) = delete;
    MyObject& operator=(const MyObject&) = delete;
    MyObject(int i, const std::string& nm) : id{i}, name{nm} {}
    static void* operator new(size_t) {
        return pool.allocate();
    }
   
public:
    static MyObject* create(int id, const std::string& name) {
        return new MyObject{id, name};
    }
    static void operator delete(void* p) {
        pool.deallocate(p);
    }
    static void profile() {
        pool.profile();
    }
    friend std::ostream& operator<<(std::ostream&, const MyObject&);
};

#endif