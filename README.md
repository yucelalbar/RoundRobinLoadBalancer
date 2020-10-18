# RoundRobinLoadBalancer
A Round-Robin Load  Balancing Implementation with C++. 

# Details
It's a header-only project that has implementation of round-robin load balancing strategy. ILoadBalancingStrategy is an interface and other types of strategies can be implemented.

# Usage
A class named "Scheduler" keeps "Client" objects to make round-robin scheduling. "acquireClient" method is used to acquire next Client object. 

# Example

    /*Create strategy*/
    auto strategy = std::make_shared<RoundRobinLoadBalancingStrategy<Client>>();
    /*Create Scheduler*/
    auto scheduler = std::make_shared<Scheduler<Client>>(std::move(strategy));
    /*Add Client(s) to scheduler*/
    scheduler->addClient(std::make_shared<Client>());
    scheduler->addClient(std::make_shared<Client>());

    for(auto i = 0; i<10; ++i) {
        /*Acquire next client object*/
        auto client = scheduler->acquireClient();
        if(client != nullptr) {
            /*Send packet*/
            client->send();
        }
    }

