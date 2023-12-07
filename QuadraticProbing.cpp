#include "QuadraticProbing.h"
/*The quadratic probing strategy introduces a more sophisticated approach by using quadratic increments to
find the next available slot. This technique strikes a balance between proximity and distribution, providing
an alternative to linear probing that is more likely to avoid clustering.*/
using namespace std;
QuadraticProbing::QuadraticProbing(){

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
void QuadraticProbing::createAccount(std::string id, int count) {
    long long int index=hash(id);
    Account newAccount;
    newAccount.id=id;
    newAccount.balance=count;
    long long int j=1;
    //have to use efficient quadratic probing
    while(bankStorage1d[index].id!="z"){
        index=(index+(j*j+j))%100000;
        j++; 
    }
    bankStorage1d[index]=newAccount;
    database_size++;
}

std::vector<int> QuadraticProbing::getTopK(int k) {
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


    //return std::vector<int>(); // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {
         /* Returns the current balance of the account identified
by the provided id. In case the id is not present
return -1*/
    if(!doesExist(id)){
        return -1;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j+j))%100000;
        j++;
    }
    return bankStorage1d[i].balance;



    
    //dont get stuck in an infinite loop

    // Placeholder return value
}

void QuadraticProbing::addTransaction(std::string id, int count) {
           /*Adds a transaction of count value to the account
specified by the id. If the account is not already
present, create a new one and then add this transaction. The transaction amount can be positive or
negative, representing deposits or withdrawals, respectively. Transactions will not lead to a negative
balance.
*/   if(!doesExist(id)){
        createAccount(id,count);
        return;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j+j))%100000;
        j++;
    }
    bankStorage1d[i].balance+=count;
    return;

}

bool QuadraticProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
     /*Checks if an account with the given id exists in the
database. Returns true if the account exists, and
false otherwise.*/
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j+j))%100000;
        j++;
        if(i==index){
            return false;
        }}
        
    return true;


     // Placeholder return value
}

bool QuadraticProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
        /*This function deletes the key stored in database. It
will return true after deletion. If the key was not
present, then it should return false*/
    if(!doesExist(id)){
        return false;
    }
    long long int index=hash(id);
    long long int i=index;
    long long int j=1;
    while(bankStorage1d[i].id!=id){
        i=(i+(j*j+j))%100000;
        j++;
    }
    bankStorage1d[i].id="z";
    database_size--;
    return true;
     // Placeholder return value
}
int QuadraticProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    /*Returns the total number of accounts currently*/
     // Placeholder return value
    // int count=0;
    // for(int i=0 ;i<bankStorage1d.size();i++){
    //     if(bankStorage1d[i].id!="z"){
    //         count++;
    //     }

    // }
    // return count;
    return database_size;

}

int QuadraticProbing::hash(std::string id) {
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

