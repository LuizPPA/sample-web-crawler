#ifndef RECORD_H
#define RECORD_H

#include<string>
#include<map>

namespace search_engine {
    class Record {

        private:
            std::string domain;
            int visited_pages = 0;
            int total_time = 0;
            bool currently_visiting = false;
            std::map<std::string, int> urls;
            bool valid(std::string url);

        public:
            Record(std::string domain);
            int get_visited_pages();
            int get_total_time();
            bool is_currently_visiting();
            bool has_visited(std::string url);
            bool can_start_visiting(std::string url);
            void start_visiting(std::string url);
            void visit_page(std::string url, int time);
            void finish();
    };
}

#endif