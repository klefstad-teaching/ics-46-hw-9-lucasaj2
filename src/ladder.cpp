#include "ladder.h"

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void error(std::string word1, std::string word2, std::string msg) {
	std::cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
	int len1 = str1.size(), len2 = str2.size();
	if (std::abslen1-len2) > d) return false;

	int str1_index = 0, int str2_index = 0, edits = 0;

	while (str1_index < len1 && str2_index < len2) {
		if (str1[str1_index] != str2[str2_index]) {
			++edits;
			if (++edits > d) return false;
			if (len1 > len2) ++str1_index;
			else if (len1 < len2) ++str2_index;
			else ++str1_index, ++str2_index;
		} else
			++str1_index, ++str2_index;
	}

	return edits + (len1 - str1_index) + (len2 - str2_index) <= d;
	
}

bool is_adjacent(const string& word1, const string& word2) {
	return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const set<std::string>& word_list) {
	if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must be different");
        return {};
    }
	
	std::queue<std::vector<std::string>> ladder_queue;
	ladder_queue.push([begin_word]);
	std::set<std::string> visited;
	visited.insert(begin_word);

	while(!ladder_queue.empty()) {
		std::vector<std::string> ladder = ladder_queue.front();
		ladder_queue.pop();
		std::string last_word = ladder.empty() ? "" : ladder.back();

		for (std::string word : word_list) {
			if (is_adjacent(last_word, word) && !visited.count(word) {
				visited.insert(word);
				std::vector<std::string> new_ladder = ladder;
				new_ladder.push_back(word);
				
				if (word == end_word) 
					return new_ladder;
				
				ladder_queue.push(new_ladder);
				visited.insert(word);
			}
		}
	error(begin_word, end_word, "No ladder found");
	return {};
}

void load_words(set<std::string> & word_list, const sd::string& file_name) {
	ifstream file(file_name);

	string word;
    while (file >> word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		word_list.insert(word);
	}
	file.close();
}

void print_word_ladder(const vector<std::string>& ladder) {
	if (ladder.empty()) {
        std::cout << "No word ladder found." << std::endl;
        return;
    }
	for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " -> ";
    }
    std::cout << std::endl;
}

void verify_word_ladder() {
	set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}





