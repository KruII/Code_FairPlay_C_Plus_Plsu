#include <iostream>
#include<string>
#include<algorithm>

using namespace std;

char kostka[5][5];
string klucz, slowo, haslo;
bool szyfrowanie =false;
char alfabet[25];
int paranumerow1[2],paranumerow2[2];

void TworzenieAlfabetu(){
    for (int i = 0; i < 25; i++){
        if(65+i<74){
            alfabet[i]=65+i;}
        else{
            alfabet[i]=66+i;}
            
    }
}

string ZmianaLiterNaDuze(string napis){
    for(int i = 0; i < napis.size(); i++){
        napis[i] = toupper(napis[i]);
        if (napis[i]>90 || napis[i]<65){
            napis.erase(i, 1);
            napis[i] = toupper(napis[i]);}
        if (napis[i]==74){
            napis[i]-=1;}
    }
    return napis;
}

void TworzenieKostki(){
    for (int i = 0; i < klucz.size(); i++){
        for (int j = 0; j < klucz.size(); j++){
            if (klucz[i]==klucz[j] && i!=j){
                klucz.erase(j, 1);}
        }
    }
    string pomocniczy=klucz;
    sort(pomocniczy.begin(), pomocniczy.end(), greater<char>());
    string alfabet1;
    for (int j = 0; j < 25; j++){
        alfabet1.push_back(alfabet[j]);}
    for (int i = 0; i < pomocniczy.size(); i++){
        for (int j = 0; j < alfabet1.size(); j++){
           if (pomocniczy[i]==alfabet[j]){
               alfabet1.erase(j,1);}
        }   
    }
    klucz.append(alfabet1);
    cout<<"KOSTKA:"<<endl;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            kostka[j][i]=klucz[j+5*i];
            cout<<kostka[j][i]<<" | ";}
        cout<<endl;}
}
void Szukanie(int numerek){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (kostka[j][i]==slowo[numerek]){
                    paranumerow1[numerek%2]=i;
                    paranumerow2[numerek%2]=j;
            }     
        }    
    }
}

void Szyfrowanie(){
    if (slowo.size()%2!=0)
    {
        slowo.push_back('A');
    }
    
    for (int b = 0; b < slowo.size(); b+=2){
        Szukanie(b);
        Szukanie(b+1);
        
        if (paranumerow1[0]!=paranumerow1[1] && paranumerow2[0]!=paranumerow2[1]){
            haslo.push_back(kostka[paranumerow2[1]][paranumerow1[0]]);
            haslo.push_back(kostka[paranumerow2[0]][paranumerow1[1]]);
        }
        else if (paranumerow1[0]==paranumerow1[1] && paranumerow2[0]==paranumerow2[1]){
            haslo.push_back(kostka[paranumerow2[0]][paranumerow1[0]]);
            haslo.push_back(kostka[paranumerow2[1]][paranumerow1[1]]);
        }
        else{
            if (paranumerow1[0]==paranumerow1[1]){
                for (int i = 0; i < 2; i++){
                    if (paranumerow2[i]<5){
                        paranumerow2[i]++;}
                    else{
                        paranumerow2[i]=0;}
                }
            }else{
                for (int i = 0; i < 2; i++){
                    if (paranumerow1[i]<5){
                        paranumerow1[i]++;}
                    else{
                        paranumerow1[i]=0;}
                }
            }
            haslo.push_back(kostka[paranumerow2[0]][paranumerow1[0]]);
            haslo.push_back(kostka[paranumerow2[1]][paranumerow1[1]]);
        }
    }
}

void DeSzyfrowanie(){
    if (slowo.size()%2!=0)
    {
        slowo.push_back('A');
    }
    
    for (int b = 0; b < slowo.size(); b+=2){
        Szukanie(b);
        Szukanie(b+1);
        
        if (paranumerow1[0]!=paranumerow1[1] && paranumerow2[0]!=paranumerow2[1]){
            haslo.push_back(kostka[paranumerow2[1]][paranumerow1[0]]);
            haslo.push_back(kostka[paranumerow2[0]][paranumerow1[1]]);
        }
        else if (paranumerow1[0]==paranumerow1[1] && paranumerow2[0]==paranumerow2[1]){
            haslo.push_back(kostka[paranumerow2[0]][paranumerow1[0]]);
            haslo.push_back(kostka[paranumerow2[1]][paranumerow1[1]]);
        }
        else{
            if (paranumerow1[0]==paranumerow1[1]){
                for (int i = 0; i < 2; i++){
                    if (paranumerow2[i]>0){
                        paranumerow2[i]--;}
                    else{
                        paranumerow2[i]=5;}
                }
            }else{
                for (int i = 0; i < 2; i++){
                    if (paranumerow1[i]>0){
                        paranumerow1[i]--;}
                    else{
                        paranumerow1[i]=5;}
                }
            }
            haslo.push_back(kostka[paranumerow2[0]][paranumerow1[0]]);
            haslo.push_back(kostka[paranumerow2[1]][paranumerow1[1]]);
        }
    }
}

int main(){
    TworzenieAlfabetu();
    cout<<"Podaj klucz: ";
    getline(cin,klucz);
    klucz = ZmianaLiterNaDuze(klucz);
    TworzenieKostki();
    cout<<"Podaj haslo: ";
    getline(cin,slowo);
    slowo = ZmianaLiterNaDuze(slowo);
    cout<<"Czy zaszyfrowac(0)/zdeszyfrowac(1): ";
    cin>>szyfrowanie;
    if (!szyfrowanie){
        Szyfrowanie();}
    else{
        DeSzyfrowanie();}
    cout<<haslo;
};