#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<list>

#include "BST.h"
//#include "porter2_stemmer-master/porter2_stemmer.cpp"
#include "words_processing.h"

using namespace std;

void extract_eng_rev(){
    ifstream fin;
    ofstream fout;

    fin.open("steam_reviews.csv");
    fout.open("english_reviews.csv");

    int len_orig = 0;
    int len = 0;

    vector<string> record;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }
		
        if (record.size() < 6) continue;

        if (record[2] != "" && record[4] == "english" && record[4] != "") {
            fout << record[2].c_str() << ',' << record[4].c_str() << ',' << record[5].c_str() << endl;
            len++;
        }

        len_orig++;
        cout<<len_orig<<" "<<len<<endl;
    }

    fin.close();
    fout.close();

    cout<<"end";
}

void gamelist(){
    ifstream fin;
    ofstream fout;

    fin.open("english_reviews.csv");
    fout.open("game_list.csv");

    int len_orig = 0;
    int len = 0;

    BST<string> games;
    vector<string> record;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }

        if(!games.check(record[0])){
            games.insert(record[0]);
            fout << record[0].c_str() << endl;
            len++;
        }

        len_orig++;
        cout<<len_orig<<" "<<len<<endl;
    }

    fin.close();
    fout.close();

    cout<<"end";
}

string no_grammer(string str){
	string word;
        for (int i = 0; i < str.size(); i++) {
            if (isalnum(str[i]) || str[i] == ' ' || str[i] == '\'') {
                if(isalpha(str[i])) str[i] = tolower(str[i]);

                word.push_back(str[i]);
            }
        }
	
	return  word;
}

void remove_grammer_revs(){
    ifstream fin;
    ofstream fout;

    fin.open("english_reviews.csv");
    fout.open("no_grammer_reviews.csv");

    int len_orig = 0;
    int len = 0;

    vector<string> record;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }

        string rev = no_grammer(record[2]);

        if(rev != ""){
            fout << record[0] << ',' << record[1] << ',' << rev << '\n';
            len++;
        }

        len_orig++;
        cout<<len_orig<<" "<<len<<endl;
    }

    fin.close();
    fout.close();

    cout<<"end";
}

vector<string> tokens(string str){
	vector<string> tok;
	str.push_back(' ');

	string word;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] != ' ') {
                word.push_back(str[i]);
            }

            else {
                tok.push_back(word);
                word.clear();
            }
        }
	
	return  tok;
}

vector<string> no_stop_words(vector<string> w){
    vector<string> no_stop;
    BST<string> words;

    ifstream fin;
    fin.open("stop words.txt");

    while(fin.good()){
        string line;
        getline(fin, line);
        words.insert(line);
    }

    for(int i=0 ; i<w.size() ; i++){
        if(!words.check(w[i])){
            no_stop.push_back(w[i]);
        }
    }

    fin.close();

    return no_stop;
}

//void stemmer(vector<string> &to_stem){
//    for(int i=0 ; i<to_stem.size() ; i++){
//        Porter2Stemmer::trim(to_stem[i]);
//        Porter2Stemmer::stem(to_stem[i]);
//    }
//}
//
//void tokenize_reviews(){
//    ifstream fin;
//    ofstream fout;
//
//    fin.open("no_grammer_reviews.csv");
//    fout.open("tokenized_reviews.csv");
//
//    int len_orig = 0;
//    int len = 0;
//
//    vector<string> record;
//
//    while (fin.good()) {
//        record.clear();
//
//        string line;
//        getline(fin, line);
//        line.push_back(',');
//
//        string word;
//        for (int i = 0; i < line.size(); i++) {
//            if (line[i] != ',') {
//                word.push_back(line[i]);
//            }
//
//            else {
//                record.push_back(word);
//                word.clear();
//            }
//        }
//
//        string to = record[2];
//    
//        vector<string> vs = no_stop_words(tokens(to));
//        stemmer(vs);
//        
//        fout << record[0] << ',' << record[1];
//        
//        for(int i=0 ; i<vs.size() ; i++){
//            if(vs[i] != "") fout << ',' << vs[i];
//		}
//
//        fout << '\n';
//
//        len_orig++;
//        cout<<len_orig<<endl;
//    }
//
//    fin.close();
//    fout.close();
//
//    cout<<"end";
//}

void word_list_count(){
    ifstream fin;
    ofstream fout;

    fin.open("tokenized_reviews.csv");

    int len_orig = 0;
    int len = 0;

    vector<string> record;
    wordtable word_list;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }

        if(record.size() <= 2) continue;

        vector<string> w;
        for(int i=2 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }

        for(int i=0 ; i<w.size() ; i++){
            if(word_list.check(w[i])){
                word_list.inc_count(w[i]);
            }

            else word_list.insert(w[i]);
        }

        len_orig++;
        cout<<len_orig<<endl;
    }

    fin.close();
    cout<<"end"<<endl;

    fout.open("word list.csv");

    word_list.heapify_word();

    for(int i=0 ; i<word_list.word_count() ; i++){
        vector<string> out = word_list.front();
        fout << out[0] << ',' << out[1] << '\n';
        word_list.pop();
    }

    fout.close();
}

list<string> get_word_list(){
    list<string> ret;

    ifstream fin;
    fin.open("word list.csv");

    vector<string> record;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }

        ret.push_back(record[0]);
    }

    fin.close();

    return ret;
}

list<string> get_game_list(){
    list<string> ret;

    ifstream fin;
    fin.open("game_list.csv");

    vector<string> record;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }

        if(record[0] == "") continue;
        ret.push_back(record[0]);
    }

    fin.close();

    return ret;
}

void games_word_count(){
    ifstream fin;
    ofstream fout;

    fin.open("tokenized_reviews.csv");

    int len_orig = 0;
    int len = 0;

    vector<string> record;
    gametable games;

    while (fin.good()) {
        record.clear();

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }

        if(record.size() <= 2) continue;
        if(record[0] == "") continue;

        string g = record[0];

        vector<string> w;
        for(int i=2 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }

        for(int i=0 ;i < w.size() ; i++){
            games.insert(g, w[i]);
        }

        len_orig++;
        cout<<len_orig<<endl;
    }

    fin.close();
    cout<<"end"<<endl;

    fout.open("review words frequency.csv");

    list<string> w = get_word_list();
    list<string> g = get_game_list();

    for(auto it = g.begin() ; it!=g.end() ; it++){
        string game = *it;
        wordtable table = games.search(game);
        fout << game;

        for(auto iter = w.begin() ; iter!=w.end() ; iter++){
            string token = *iter;

            word out = table.search(token);
            fout << ',' << out.count;
        }

        fout << '\n';
    }

    fout.close();
}
