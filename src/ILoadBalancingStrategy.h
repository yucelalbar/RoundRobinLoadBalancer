#ifndef _ILoadBalancingStrategy_
#define _ILoadBalancingStrategy_

#include <memory>
#include <vector>

template<class T>
class ILoadBalancingStrategy {
public:
    virtual ~ILoadBalancingStrategy() {}
    virtual T* next(const std::vector<std::unique_ptr<T>>& clients) = 0;
};

#endif
