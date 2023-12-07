#include "Comp.h"
using namespace std;
Comp::Comp(){
    Account newAccount;
    newAccount.id="z";
    
    for(int i=0 ;i<100000;i++){
        bankStorage1d.push_back(newAccount);
}
}


void M(vector<int> &v, int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1], R[n2];
    for (i=0; i<n1; i++){
        L[i] = v[l+i];
    }
    for (j=0; j<n2; j++){
        R[j] = v[m+1+j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i<n1 && j<n2){
        if (L[i] <= R[j]){
            v[k] = L[i];
            i++;
        }
        else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i<n1){
        v[k] = L[i];
        i++;
        k++;
    }
    while (j<n2){
        v[k] = R[j];
        j++;
        k++;
    }
}
void MS(vector<int> &v, int l, int r){
    if (l<r){
        int m = (l+r)/2;
        MS(v, l, m);
        MS(v, m+1, r);
        M(v, l, m, r);
    }
}
void Comp::createAccount(std::string id, int count) {
    long long int index=hash(id);
    Account newAccount;
    newAccount.id=id;
    newAccount.balance=count;
    long long int j=1;
    //have to use efficient quadratic probing
    while(bankStorage1d[index].id!="z"){
        index=(index+((j*j+j)/2))%100000;
        j++; 
    }
    bankStorage1d[index]=newAccount;}

std::vector<int> Comp::getTopK(int k) {
       vector<int>TopK;
    vector<int>TopK1;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="z"){
            TopK.push_back(bankStorage1d[i].balance);
        }
    }
    MS(TopK,0,TopK.size()-1);
    if(TopK.size()<k){
        for(int i=0;i<TopK.size();i++){
            TopK1.push_back(TopK[TopK.size()-1-i]);
        }
    }
    else{
        for(int i=0;i<k;i++){
            TopK1.push_back(TopK[TopK.size()-1-i]);
        }
    }
    return TopK1;
}

int Comp::getBalance(std::string id) {
    if(!doesExist(id)){
        return -1;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+((j*j+j)/2))%100000;
        j++;
    }
    return bankStorage1d[i].balance;

}

void Comp::addTransaction(std::string id, int count) {
     if(!doesExist(id)){
        createAccount(id,count);
        return;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+((j*j+j)/2))%100000;
        j++;
    }
    bankStorage1d[i].balance+=count;
    return;
}

bool Comp::doesExist(std::string id) {
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+((j*j+j)/2))%100000;
        j++;
        if(i==index){
            return false;
        }}
        
    return true;

}

bool Comp::deleteAccount(std::string id) {
    if(!doesExist(id)){
        return false;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+((j*j+j)/2))%100000;
        j++;
    }
    bankStorage1d[i].id="z";
    return true;
}
int Comp::databaseSize() {
    int count=0;
    for(int i=0 ;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="z"){
            count++;
        }

    }
    return count;
}

int Comp::hash(std::string id) {
    unsigned h = 0x17FFF; // Initialize with 20 bits set to 1

    for (char c : id) {
        // XOR the current hash value with the character code of the character c
        h ^= static_cast<unsigned>(c);
        // Multiply the result by the constant 0x104C11DB7 (273 * 2^19 + 1)
        h *= 0x104C11DB7;
        // Apply a 20-bit mask to truncate to 20 bits
        h &= 0x17FFF;//covers 90111 cases of account id
    }

    return static_cast<int>(h);
}


// Feel free to add any other helper functions you need
// Good Luck!