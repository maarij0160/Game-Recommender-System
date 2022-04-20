#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<cmath>

#include <cwchar>
 
#include<iomanip>
#include "words_processing.h"

double GameSimilarityMatrix[86][86];

using namespace std;
using std::setw;
//USED BY TF
vector<long int> countWords() {

	ifstream fin;
    ofstream fout;
  
    fin.open("review words frequency.csv");
    fout.open("total words in reviews per game.csv");
    
    vector<string> record;
    vector<long int> count;
    while (!fin.eof()) {
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
        for(int i=1 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }
        long long int counter=0;
        for(int i=0 ;i < w.size() ; i++){
        	counter+= stoi(w[i],nullptr,10);
        	
        }
    
    fout<<record[0]<<","<<counter<<endl;
    count.push_back(counter);
    }

    fin.close();
    fout.close();
    cout<<"end"<<endl;
	
   return count;

}

void TF(){
	
	ifstream fin;
	ofstream fout;
	
	fin.open("review words frequency.csv");

	fout.open("term frequency.csv");
	
	
	vector<string> record;
	vector<long int>freq=countWords();
    int x=0;
    while (!fin.eof()) {
    	
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
        


        vector<string> w;
        for(int i=1 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }
        

        
        fout<<record[0]<<",";
        double tfreq;
        for(int i=0 ;i < w.size() ; i++){
        	tfreq =0.0;
        	if(stoi(w[i],nullptr,10)!=0){
        	tfreq=(double)stoi(w[i],nullptr,10) / (double)freq[x];
        		
			}
			
        	fout<<tfreq<<",";
        	
        }
     
     fout<<endl;
    x++;

    }

    fin.close();
    fout.close();
    cout<<"end"<<endl;
	
	
}

//USED BY IDF
long long int CountTotal(){
	
	ifstream fin;

	
	fin.open("total words in reviews per game.csv");
	
	vector<string> record;
	vector<string> gamename;
	Gamehashing games;
	
	while(!fin.eof()){
		
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

        string g = record[0];

        vector<string> w;
        for(int i=1 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }
       
       
        for(int i=0 ;i < w.size() ; i++){
           long int hold=stoi(w[i],nullptr,10);
           games.insert(g,hold);
        	
        }
        gamename.push_back(g);
        
	}
	long int count=0;
	
	for(auto i=gamename.begin();i!=gamename.end();i++){
		long long int holder=games.Search(*i);
		count+=holder;
	
	}
	

	return count;
}

void IDF(){
	
	long long int count=CountTotal();
	
	ifstream fin;
    ofstream fout;
  
    fin.open("word list.csv");
    fout.open("inverse doc frequency.csv");
    
    
   
    vector<string> record;
 
    while (!fin.eof()) {
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

       
        string g = record[0];

        vector<string> w;
        for(int i=1 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }
        double invfreq=0.0;
        
        for(int i=0 ;i < w.size() ; i++){
        	int x=(double)stoi(w[i],nullptr,10);
        	int c=(double)count;
        	invfreq=log(c / x);
        	
        }
    
    fout<<record[0]<<","<<invfreq<<endl;
    
    }

    fin.close();
    fout.close();
    cout<<"end"<<endl;
	
	
}

//USED BY TFIDF
vector<string> getinvfreq(){
	
		ifstream fin;

	
	fin.open("inverse doc frequency.csv");
	
	vector<string> record;
    vector<string> data;
	
	while(!fin.eof()){
		
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

        string g = record[0];

        vector<string> w;
        for(int i=1 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }
       
       
        for(int i=0 ;i < w.size() ; i++){
           data.push_back(w[i]);
        	
        }
       
        
	}

   return data;
}

void TFIDF() {

    ifstream fin;

    ofstream fout;

    fin.open("term frequency.csv");
    
    fout.open("TF-IDF.csv");


    vector<string> record;
    vector<string> data=getinvfreq();


    while (!fin.eof()) {

        record.clear();
   

        string line;
        getline(fin, line);
        line.push_back(',');

        string word;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] != ',') {
                word.push_back(line[i]);
            }

            else {
                record.push_back(word);
                word.clear();
            }
        }



        if (record.size() <= 2) continue;
        if (record[0] == "") continue;



        vector<string> w;
        
        for (size_t i = 1; i < record.size(); i++) {
            w.push_back(record[i]);
        }
                
      

        fout << record[0] << ",";


        for (int i = 0; i < w.size()-1; i++) {

           fout<<stod(data[i]) * stod(w[i])<<",";

        }

        fout << endl;


    }

    fin.close();
  
    fout.close();
    cout << "end" << endl;


}



vector<string> get_vec(string s){
	
	ifstream fin;
  
    fin.open("TF-IDF.csv");
    
    
    vector<string> record;
    vector<string> data;
   
    while (!fin.eof()) {
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
        for(int i=1 ; i<record.size() ; i++){
            w.push_back(record[i]);
        }
        
        if(record[0]==s){
        	for(int i=0 ;i < w.size() ; i++){
                //	double h=
                data.push_back(w[i]);
        	
            }
        	break;
		}
        
    }

    fin.close();
   // cout<<"end"<<endl;
	
   return data;
	
}


double dotProduct(string s1,string s2){
	vector<string>v1=get_vec(s1);
	vector<string>v2=get_vec(s2);

   double prod;
    
	for(int i=0; i<v1.size()-1 ;i++){
		
	    prod+=(stod(v1[i]) * stod(v2[i]));

	}

	double p;
	

	return prod;
}

double magnitude(string s1,string s2){
	
	return sqrt(dotProduct(s1,s2));
}





int main(){
	
   
	
	cout<<"COSINE SIMILARITY OF THE GAMES IS :"<<endl;
	cout<<dotProduct("The Witcher 3: Wild Hunt","Half-Life")/(magnitude("The Witcher 3: Wild Hunt","The Witcher 3: Wild Hunt")*magnitude("Half-Life","Half-Life"));
    cout<<endl;
    cout<<dotProduct("Warhammer: Vermintide 2","Half-Life")/(magnitude("Warhammer: Vermintide 2","Warhammer: Vermintide 2")*magnitude("Half-Life","Half-Life"));
}
