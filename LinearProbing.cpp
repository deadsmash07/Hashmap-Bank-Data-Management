#include "LinearProbing.h"
using namespace std;
    /*Linear probing is your next tool, allowing you to navigate hash table slots in a linear fashion to find the next
available space when a collision occurs. This strategy emphasizes proximity and aims to avoid gaps in your
hashmap*/
LinearProbing::LinearProbing(){
   
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
void LinearProbing::createAccount(std::string id, int count) {
        /*This function creates a new account with the given
id and initial count value. The id uniquely identifies
the account, and the count parameter represents the
initial balance of the account.*/
    int index=hash(id);
    Account newAccount;
    newAccount.id=id;
    newAccount.balance=count;

    while(bankStorage1d[index].id!="z"){
        index=(index+1)%100000;
    }
    bankStorage1d[index]=newAccount;
    return;
    
}

std::vector<int> LinearProbing::getTopK(int k) {
        /*Retrieves the top k balances values from the
database. Returns a vector containing at most k balances values in decreasing order.
we will copy all the balance information in a new vector and apply mergosort on it.*/
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

int LinearProbing::getBalance(std::string id) {
      /* Returns the current balance of the account identified
by the provided id. In case the id is not present
return -1*/
  int index = hash(id);
    int i = index;
    while(bankStorage1d[i].id != id){
        i = (i+1)%100000;
        if(i == index){
            return -1;
        }
    }
    return bankStorage1d[i].balance;

     // Placeholder return value
}



void LinearProbing::addTransaction(std::string id, int count) {
        /*Adds a transaction of count value to the account
specified by the id. If the account is not already
present, create a new one and then add this transaction. The transaction amount can be positive or
negative, representing deposits or withdrawals, respectively. Transactions will not lead to a negative
balance.
*/  int index=hash(id);
    int i=index;
    while(bankStorage1d[i].id!=id){
        i=(i+1)%100000;
        if(i==index){
          //create account if not present and add the balance
           createAccount(id,count);
          return;
        }
    }
    bankStorage1d[i].balance+=count;
    return;
}

bool LinearProbing::doesExist(std::string id) {
       /*Checks if an account with the given id exists in the
database. Returns true if the account exists, and
false otherwise.*/
    int index=hash(id);
    int i=index;
    while(bankStorage1d[i].id!=id){
        i=(i+1)%100000;
        if(i==index){
            return false;
        }
    }
    return true;
 
}

bool LinearProbing::deleteAccount(std::string id) {
    /*This function deletes the key stored in database. It
will return true after deletion. If the key was not
present, then it should return false*/
    int index=hash(id);
    int i=index;
    while(bankStorage1d[i].id!=id){
        i=(i+1)%100000;
        if(i==index){
            return false;
        }
    }
    bankStorage1d[i].id="z";
    return true;
// Placeholder return value
}
int LinearProbing::databaseSize() {
     /*Returns the total number of accounts currently
stored in the database*/
    //make it efficient
    int count=0;
    for(int i=0 ;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="z"){
            count++;
        }

    }
    return count;
    
         // Placeholder return value
     
}

int LinearProbing::hash(std::string id) {
    unsigned h = 0x17FFF; // Initialize with 20 bits set to 1

    for (char c : id) {
        
        h ^= static_cast<unsigned>(c);
       
        h *= 0x104C11DB7;

        h &= 0x17FFF;
    }

    return static_cast<int>(h);
}

