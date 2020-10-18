#include "RoundRobinLoadBalancingStrategy.h"
#include "Scheduler.h"
#include "Client.h"

int main() {
    /*Create strategy*/
    auto strategy = std::make_shared<RoundRobinLoadBalancingStrategy<Client>>();
    /*Create Scheduler*/
    auto scheduler = std::make_shared<Scheduler<Client>>(std::move(strategy));
    /*Add Client(s) to scheduler*/
    scheduler->addClient(std::make_shared<Client>());
    scheduler->addClient(std::make_shared<Client>());

    for(auto i = 0; i<10; ++i) {
        auto client = scheduler->acquireClient();
        if(client != nullptr) {
            client->send();
        }
    }
    return 0;
}