#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    std::string query;
    bool all = false;

    for(int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        query = arg;
    }

    if(query.size() < 1) {
        fprintf(stderr, "Syntax: acronym [letters]\n");
        return 0;
    }

    std::ifstream f("data/acronym_words");
    if(!f) {
        return 0;
    }

    int letterIndices[27];
    int letterCounts[26];
    for(int i = 0; i < 26; ++i) {
        letterIndices[i] = -1;
        letterCounts[i] = 0;
    }

    std::vector<std::string> words;
    std::string word;
    while(std::getline(f, word)) {
        int length = (int)word.size();
        if(length < 1) {
            continue;
        }
        char initial = word[0];
        if((initial < 'a') || (initial > 'z')) {
            continue;
        }

        int letterIndex = initial - 'a';
        if(letterIndices[letterIndex] == -1) {
            letterIndices[letterIndex] = (int)words.size();
        }

        words.push_back(word);
    }

    letterIndices[26] = (int)words.size(); // hacky!
    for(int i = 0; i < 26; ++i) {
        letterCounts[i] = letterIndices[i+1] - letterIndices[i];
        if(letterCounts[i] < 1) {
            return 0;
        }
    }

    // for(int i = 0; i < 26; ++i) {
    //     printf("letter %c starts on line %d (total: %d, first word %s)\n", i + 'a', letterIndices[i], letterCounts[i], words[letterIndices[i]].c_str());
    // }

    srand((unsigned int)time(NULL));

    std::string output;
    int queryLen = (int)query.size();
    for(int i = 0; i < queryLen; ++i) {
        int letter = tolower(query[i]) - 'a';
        int randomIndex = letterIndices[letter] + (rand() % letterCounts[letter]);
        output += words[randomIndex] + " ";
    }
    printf("%s\n", output.c_str());
    return 0;
}
