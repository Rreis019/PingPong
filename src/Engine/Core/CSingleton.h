#pragma once
template <typename T>
class CSingleton
{
public:
    static T& Get()
    {
        static T instance;
        return instance;
    }
protected:
    CSingleton() {}
    ~CSingleton() {}
public:
    CSingleton(CSingleton const&) = delete;
    CSingleton& operator=(CSingleton const&) = delete;
};