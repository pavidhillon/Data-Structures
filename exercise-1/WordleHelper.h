#ifndef WORDLE_HELPER_H
#define WORDLE_HELPER_H

#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

class WordleHelper{
 
    std::vector<std::string> allowed;
    std::vector<std::string> answers;

    std::vector<std::string> green;
    std::vector<std::string> yellow;
    std::vector<std::string> gray;

    bool contains(std::string word, char c){
        for (int i = 0; i < word.length(); i++){
            if (word[i] == c){
                return true;
            }
        }

        return false;
    }

 bool satisfyGreen(std::string word, std::string green){
        for (int i = 0; i < green.length(); i++){
            if (green[i] != '_'){
                if (green[i] != word[i]){
                    return false;
                }
            }
        }
        return true;
    }

    bool satisfyYellow(std::string word, std::string yellow) {
        for (int i = 0; i < yellow.size(); ++i) {
            bool discovered = false;
            if (yellow[i] != '_') {
                for (int j = 0; j < word.size(); ++j){
                    if (word[j] == yellow[i] && j !=i){
                        discovered = true;
                        break;
                    }
                }
                if (!discovered){
                    return false;
                }
            }
        }
        return true;
    }

    bool satisfyGray(std::string word, std::string gray){
        for (int i = 0; i < gray.size(); ++i) {
            if (gray[i] != '_'){
                if (contains(word,gray[i])){
                    return false;
                }
            }
        }
        return true;
    }

public:
    WordleHelper(){
        std::string answersFile = "answers.txt";
        std::string allowedFile = "allowed.txt";

        std::fstream newfile;

        newfile.open(answersFile, std::ios::in);
        if (newfile.is_open()){
            std::string tp;
            
            while(getline(newfile, tp)){
                answers.push_back(tp);
            }
            newfile.close();
        }
        else {
            throw std::logic_error("Cant read file " + answersFile + ".");
        }

        newfile.open(allowedFile, std::ios::in);
        if (newfile.is_open()){
            std::string tp;
            
            while(getline(newfile, tp)){
                allowed.push_back(tp);
            }
            newfile.close();
        }
        else {
            throw std::logic_error("Cant read file " + allowedFile + ".");
        }
    }

    void addGreen(std::string feedback){
        if (feedback.size() != 5){
            throw std::logic_error("Green feedback must be exactly 5 characters");
        }
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c != '_' && (c < 'a' || c > 'z');
        })){
            throw std::logic_error("Green feedback must contain only lowercase letters or underscores");
        }

        green.push_back(feedback);
    }

    void addYellow(std::string feedback){
        if (feedback.size() != 5){
            throw std::logic_error("Yellow feedback must be exactly 5 characters");
        }
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c != '_' && (c < 'a' || c > 'z');
        })){
            throw std::logic_error("Yellow feedback must contain only lowercase letters or underscores");
        }

        yellow.push_back(feedback);
    }

    void addGray(std::string feedback){
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c < 'a' && c > 'z';
        })){
            throw std::logic_error("Yellow feedback must contain only lowercase letters");
        }

        gray.push_back(feedback);
    }

    std::vector<std::string>possibleSolutions(){
        std::vector<std::string> result;
        std::string Greennow = green[green.size()-1];
        std::string Yellownow = yellow[yellow.size()-1];
        std::string Graynow = gray[gray.size()-1];

        for(int i = 0; i < answers.size(); i++){
            if(satisfyGreen(answers[i], Greennow)
                && satisfyYellow(answers[i], Yellownow)
                && satisfyGray(answers[i], Graynow))
                result.push_back(answers[i]);
            }
        return result;
    }

    std::vector<std::string> suggest(){
        // Optionally, your code here...
        return {"bring", "words", "close"};
    }

    ~WordleHelper(){

    }

    friend struct WordleTester;

};

#endif