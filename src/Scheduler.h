#ifndef _Scheduler_
#define _Scheduler_

#include <algorithm>
#include "ILoadBalancingStrategy.h"

template <class T>
class Scheduler {
public:
    Scheduler(std::shared_ptr<ILoadBalancingStrategy<T>> strategy)
                        : m_strategy(std::move(strategy)) { }

    inline void addClient(std::shared_ptr<T> client) {
        m_clients.emplace_back(std::move(client));
    }
    inline void removeClient(std::shared_ptr<T> client) {
        const auto& it = std::find(m_clients.begin(), m_clients.end(), client);
        if(it != m_clients.end()) {
            m_clients.erase(it);
        }
    }
    inline void removeAllConnectionClients() {
        m_clients.clear();
    }

    inline std::vector<std::shared_ptr<T>>& getClients() {
        return m_clients;
    }

    inline const bool isClientListEmpty() const {
        return m_clients.empty();
    }

    inline std::shared_ptr<T> acquireClient() {
        return m_strategy->next(m_clients);
    }

private:
   std::shared_ptr<ILoadBalancingStrategy<T>> m_strategy;
   std::vector<std::shared_ptr<T>> m_clients;
};

#endif