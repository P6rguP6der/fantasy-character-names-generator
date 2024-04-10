
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

#define ARR_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

#define DEFAULT_NAMES_LENGTH 10

const std::string signatures[] = {
	// C - consonant
	// V - vowel
	// A - apostrophe
	// D - dash

	"CVC",
	"CACVCV",
	"CACVVCV",
	"CVCDCVCV",
	"CVC CVCV",
	"CVCV",
	"CVVCV",
	"CVCVC",
	"CVCCVC",
	"CVCV CVC",

	// TODO: add some more
};


inline char random_letter(std::string type) {
	std::string vowels = "aeiou";
	std::string consonants = "bcdfghjklmnpqrstvwxyz"; // Let's consider the "y" as consonant
	std::string letters;

	if (type == "vowel") {
		letters = vowels;
	} else if (type == "consonant") {
		letters = consonants;
	} else {
		letters = vowels + consonants;
	}

	char rand_item = letters[rand() % letters.length()];

	return rand_item;
}


inline char random_vowel() {
	return random_letter("vowel");
}


inline char random_consonant() {
	return random_letter("consonant");
}


void capitalize_string(std::string& s) {
	int len = s.length();
	for (int i; i < len; ++i) {
		if (i == 0) {
			s[i] = toupper(s[i]);
		} else if (i >= 2 && s[i - 1] == '\'') {
			s[i] = toupper(s[i]);
			s[i - 2] = toupper(s[i - 2]);
		} else if (i >= 2 && (s[i - 1] == '-' || s[i - 1] == ' ')) {
			s[i] = toupper(s[i]);
		}
	}
}


std::string generate_name(std::string signature) {
	std::string result = "";

	int len = signature.length();
	for (int i = 0; i < len; ++i) {
		char curr_char = signature[i];

		if (curr_char == 'V') {
			result += random_vowel();
		} else if (curr_char == 'C') {
			result += random_consonant();
		} else if (curr_char == 'A') {
			result += "'";
		} else if (curr_char == 'D') {
			result += "-";
		} else {
			result += curr_char;
		}
	}

	capitalize_string(result);

	return result;
}


int main(int argc, char **argv) {
	srand(time(NULL));

	int sig_length = ARR_SIZE(signatures);
	int names_length = DEFAULT_NAMES_LENGTH;

	if (argc > 1) {
		names_length = atoi(argv[1]);
	}

	if (names_length <= 0) {
		names_length = DEFAULT_NAMES_LENGTH;
	}

	for (int i = 0; i < names_length; ++i) {
		int rand_num = rand() % sig_length;
		std::string rand_signature = signatures[rand_num];

		std::cout << generate_name(rand_signature) << std::endl;
	}

	return 0;
}

