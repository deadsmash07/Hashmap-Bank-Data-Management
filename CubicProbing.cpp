#include "CubicProbing.h"
using namespace std;
CubicProbing::CubicProbing(){
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
/*Taking the concept further, cubic probing employs cubic increments to search for open slots. This strategy
adds an extra layer of complexity to the probe sequence, aiming to distribute data evenly and mitigate
clustering issues*/
void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    long long int index=hash(id);
    Account newAccount;
    newAccount.id=id;
    newAccount.balance=count;
    long long int j=1;
    while(bankStorage1d[index].id!="z"){
        index=(index+(j*j*j+j*j+j))%100000;
        j++;
    }
    bankStorage1d[index]=newAccount;

}

std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
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

int CubicProbing::getBalance(std::string id) {
    if(!doesExist(id)){
        return -1;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j+j+j*j*j))%100000;
        j++;
    }
    return bankStorage1d[i].balance;
}

void CubicProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
       if(!doesExist(id)){
        createAccount(id,count);
        return;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j*j+j*j+j))%100000;
        j++;
    }
    bankStorage1d[i].balance+=count;
    return;
}

bool CubicProbing::doesExist(std::string id) {
        long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j*j+j*j+j))%100000;
        j++;
        if(i==index){
            return false;
        }}
        
    return true;
}

bool CubicProbing::deleteAccount(std::string id) {
       if(!doesExist(id)){
        return false;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j*j+j*j+j))%100000;
        j++;
    }
    bankStorage1d[i].id="z";
    return true;
}
int CubicProbing::databaseSize() {
       int count=0;
    for(int i=0 ;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="z"){
            count++;
        }

    }
    return count;
}

int CubicProbing::hash(std::string id) {
    unsigned h = 0x17FFF; // Initialize with 20 bits set to 1

    for (char c : id) {
      
        h ^= static_cast<unsigned>(c);
       
        h *= 0x104C11DB7;
       
        h &= 0x17FFF;
    }

    return static_cast<int>(h);

}
