#ifndef INDEXER_H
#define INDEXER_H

#include<map>
#include<string>

#include"./index-cell.hpp"

#define COLLECTION_PATH "./output/collection.jl"
#define INDEX_PATH "./output/index.idx"
#define BRIEFING_PATH "./output/briefing.doc.idx"
#define TEMP_OUTPUT_FOLDER "./output/"
#define MAX_DOCUMENTS_PER_BATCH 4096

namespace search_engine {

    class Indexer {
        private:
            std::map<std::string, IndexCell*>* dictionary;
            void add_to_dictionary(std::string word, int document, int position);
            void load_index(std::ifstream& index_file);
            void build_brief(std::ifstream& collection_file);

        public:
            Indexer();
            ~Indexer();
            void index();
            void index(const char* collection_path);
            void build_index(std::ifstream& collection_file, std::ofstream& collection_briefing_file, int pages_to_index, int iteration);
            void merge(int indexes_number);
            void save_index(int iteration);
            void build_brief();
            void build_brief(const char* collection_path);
            void load_index(std::string file_path);
            void load_index(const char* file_path);
            void report();
    };

}

#endif