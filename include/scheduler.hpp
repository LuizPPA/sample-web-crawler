#ifndef SCHEDULER_H
#define SCHEDULER_H

#include<queue>
#include<mutex>

namespace search_engine {

    class Scheduler {
        private:
            std::queue<std::string> schedule;
            std::mutex m;

        public:
            Scheduler();
            int size();
            bool empty();
            void push(std::string url);
            std::string pop();
    };
}

#endif