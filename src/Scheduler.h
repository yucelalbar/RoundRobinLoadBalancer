#ifndef _Scheduler_
#define _Scheduler_

#include <algorithm>
#include "ILoadBalancingStrategy.h"

template <class T>
class Scheduler {
public:
    Scheduler(std::unique_ptr<ILoadBalancingStrategy<T>> strategy)
                        : m_strategy(std::move(strategy))
    {
    }

    void addClient(std::unique_ptr<T> client)
    {
        m_clients.emplace_back(std::move(client));
    }
    void removeClient(const std::unique_ptr<T>& client)
    {
        const auto& it = std::find(m_clients.begin(), m_clients.end(), client);
        if(it != m_clients.end()) {
            m_clients.erase(it);
        }
    }
    void removeAllConnectionClients()
    {
        m_clients.clear();
    }

    std::vector<std::unique_ptr<T>>& getClients()
    {
        return m_clients;
    }

    const bool isClientListEmpty() const
    {
        return m_clients.empty();
    }

    T* acquireClient()
    {
        return m_strategy->next(m_clients);
    }

private:
   std::unique_ptr<ILoadBalancingStrategy<T>> m_strategy;
   std::vector<std::unique_ptr<T>> m_clients;
};

#endif