//Coded By: Rodrigo Peixoto
//Coded on: 03/06/2023
//Purpose: To read a file and print out the keywords found in a file
//Also to count it so it labels

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Count the number of occurrences of each keyword in the resume tex
vector<int> count_keywords(const string& resume_text, const vector<string>& keywords){
    vector<int> counts(keywords.size());
    string word;

    for (size_t i = 0; i < resume_text.size();i++){
        if(isalnum(resume_text[i])){
            word += tolower(resume_text[i]);
        } else if (!word.empty()){
            if (find(keywords.begin(),keywords.end(),word) != keywords.end()){
                counts[distance(keywords.begin(), find(keywords.begin(), keywords.end(), word))]++;
            }
            word = "";
        }
    }

    if (!word.empty()){
        if (find(keywords.begin(), keywords.end(),word) != keywords.end()){
            counts[distance(keywords.begin(), find(keywords.begin(), keywords.end(), word))]++;
        }
    }
    return counts;
}

int main() {
    //Opens the resume file
    ifstream resume_file("C:/Users/User/Desktop/C++ Code/C++ CODE/Resume Rater/SRC/resume.txt");
    //Prints out if the file is unable to open and stops the program
    if(!resume_file.is_open()){
        cerr << "Error: Could not open the resume file" << endl;
        return 1;
    }
    //Sets the file to a string
    string resume_text((istreambuf_iterator<char>(resume_file)), istreambuf_iterator<char>());
    resume_file.close();

    //Opens the keyword files
    ifstream keywords_file("C:/Users/User/Desktop/C++ Code/C++ CODE/Resume Rater/SRC/keywords.txt");
    //Prints out if the file is unable to open and stops the program
    if(!keywords_file.is_open()){
        cerr << "Error: Could not run keywords file" << endl;
        return 1;
    }
    //Sets a file to the vector string
    vector<string> keywords;
    string keyword;
    while (getline(keywords_file, keyword, ',')) {
        keywords.push_back(keyword);
    }

    // Count the number of occurrences of each keyword in the resume text
    vector<int> keyword_counts(keywords.size(), 0);
    for (int i = 0; i < keywords.size(); i++) {
        string::size_type pos = 0;
        while ((pos = resume_text.find(keywords[i], pos)) != string::npos) {
            keyword_counts[i]++;
            pos += keywords[i].length();
        }
    }

    // Output the keyword counts
    for (size_t i = 0; i < keywords.size(); i++) {
        if (keyword_counts[i] > 0) {
            cout << keywords[i] << ": " << keyword_counts[i] << endl;
        } else {
            cout << keywords[i] << ": 0" << endl;
        }
    }

    return 0;
}
