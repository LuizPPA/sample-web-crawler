#include<iostream>

#include "./include/crawler.hpp"
#include "./include/indexer.hpp"
#include "./include/search.hpp"
#include "./include/log-utils.hpp"

#define PAGES_TO_COLLECT 100000

void query_interface(char const* index_path, char const* collection_briefing_path) {
    std::string query_string;

    std::cout << "=============== Query interface (Ctrl+D to exit) ===============\n\n";
    std::cout << "query: " << BOLDYELLOW;
    while(std::getline(std::cin, query_string, '\n')){
        std::cout << RESET << '\n';
        search_engine::Search::execute_query(query_string, index_path, collection_briefing_path);
        std::cout << "query: " << BOLDYELLOW;
    }
    std::cout << RESET << '\n';
}

void query(char const* index_path, char const* collection_briefing_path, char const* rank_path){
    std::cout << BOLDGREEN << "Loading.";
    search_engine::Search::init_rank_weights(rank_path);
    std::cout << ".." << RESET << "\n\n";
    query_interface(index_path, collection_briefing_path);
}

void query(char const* index_path, char const* collection_briefing_path){
    std::cout << BOLDGREEN << "Loading..." << RESET << "\n\n";
    query_interface(index_path, collection_briefing_path);
}

void run(search_engine::Crawler* crawler, search_engine::Indexer* indexer, int argc, char* const argv[]){
    int i = 1;
    while(i < argc){
        if(argv[i][0] == '-'){
            int op = (int)argv[i][1];
            switch(op){
                case 'c':
                    if(argc > i + 1 && argv[i+1][0] != '-'){
                        crawler->crawl(argv[i+1], PAGES_TO_COLLECT);
                        crawler->join_tasks();
                        crawler->report();
                        i++;
                    }
                    else {
                        std::cout << "Seed not provided\n";
                    }
                    break;

                case 'i':
                    if(argc > i + 1 && argv[i+1][0] != '-'){
                        indexer->index(argv[i+1]);
                        i++;
                    }
                    else {
                        indexer->index();
                    }
                    break;

                case 'b':
                    if(argc > i + 1 && argv[i+1][0] != '-'){
                        indexer->build_brief(argv[i+1]);
                        i++;
                    }
                    else {
                        indexer->build_brief();
                    }
                    break;

                case 'l':
                    if(argc > i + 1 && argv[i+1][0] != '-'){
                        indexer->load_index(argv[i+1]);
                        indexer->report();
                        i++;
                    }
                    else {
                        indexer->load_index(INDEX_PATH);
                        indexer->report();
                    }
                    break;

                case 'q':
                    if(argc > i + 3 && argv[i+1][0] != '-' && argv[i+2][0] != '-' && argv[i+3][0] != '-'){   
                        query(argv[i+1], argv[i+2], argv[i+3]);
                        i += 3;
                    }
                    else if(argc > i + 2 && argv[i+1][0] != '-' && argv[i+2][0] != '-'){   
                        query(argv[i+1], argv[i+2]);
                        i += 2;
                    }
                    else if(argc > i + 2 && argv[i+1][0] != '-'){
                        query(argv[i+1], BRIEFING_PATH);
                        i++;
                    }
                    else{
                        query(INDEX_PATH, BRIEFING_PATH);
                    }
                    break;
                
                default:
                    std::cout << "Unkown option \"" << argv[i] << "\"\n";
                    break;
            }
        }
        else{
            std::cout << "Unkown option \"" << argv[i] << "\"\n";
        }
        i++;
    }
}

int main(int argc, char* const argv[]){
    if(argc < 2){
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    search_engine::Crawler* crawler = new search_engine::Crawler();
    search_engine::Indexer* indexer = new search_engine::Indexer();

    run(crawler, indexer, argc, argv);

    delete crawler;
    delete indexer;
    return 0;
}