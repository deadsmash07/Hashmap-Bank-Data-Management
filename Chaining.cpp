#include "Chaining.h"
using namespace std;

Chaining::Chaining(){
    bankStorage2d.resize(100000);
    vector<Account> newAccount;
    Account newAccount1;
    newAccount1.id="z";
    newAccount1.balance=0;
    for(int i=0 ;i<bankStorage2d.size();i++){
        bankStorage2d[i]=newAccount;
    } 
} 

void Chaining::M(std::vector<int> &v, int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
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
void Chaining::MS(std::vector<int> &v, int l, int r){
    if (l<r){
        int m = (l+r)/2;
        MS(v, l, m);
        MS(v, m+1, r);
        M(v, l, m, r);
    }
}
void Chaining::createAccount(std::string id, int count) {
    /*This function creates a new account with the given
id and initial count value. The id uniquely identifies
the account, and the count parameter represents the
initial balance of the account.*/
    int index= hash(id);
    Account newAccount;
    newAccount.id=id;
    newAccount.balance=count;
    bankStorage2d[index].push_back(newAccount);
}

std::vector<int> Chaining::getTopK(int k) {
    /*Retrieves the top k balances values from the
database. Returns a vector containing at most k balances values in decreasing order.
we will copy all the balance information in a new vector and apply mergosort on it.*/
        std::vector<int> topK;
        std::vector<int>TopK1;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0;j<bankStorage2d[i].size();j++){
            topK.push_back(bankStorage2d[i][j].balance);
        }
    }
    MS(topK,0,topK.size()-1);
    if(topK.size()<k){
        for(int i=0;i<topK.size();i++){
            TopK1.push_back(topK[topK.size()-1-i]);
        }
    }
    else{
        for(int i=0;i<k;i++){
            TopK1.push_back(topK[topK.size()-1-i]);
        }
    }
    return TopK1;
    


   // return std::vector<int>(); // Placeholder return value
}

int Chaining::getBalance(std::string id) {
    /* Returns the current balance of the account identified
by the provided id. In case the id is not present
return -1*/
    int index=hash(id);
    for(int i=0; i<bankStorage2d[index].size(); i++){
        if(bankStorage2d[index][i].id==id){
            return bankStorage2d[index][i].balance;
        }
    }

    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    /*Adds a transaction of count value to the account
specified by the id. If the account is not already
present, create a new one and then add this transaction. The transaction amount can be positive or
negative, representing deposits or withdrawals, respectively. Transactions will not lead to a negative
balance.
*/
    int index=hash(id);
    for(int i=0; i<bankStorage2d[index].size(); i++){
        if(bankStorage2d[index][i].id==id){
            bankStorage2d[index][i].balance+=count;
            return;
        }

    }
    createAccount(id, count);

}

bool Chaining::doesExist(std::string id) {
    /*Checks if an account with the given id exists in the
database. Returns true if the account exists, and
false otherwise.*/
   int index=hash(id);
   for (int i=0; i<bankStorage2d[index].size();i++){
    if (bankStorage2d[index][i].id==id){
        return true;
    }
   }
    return false; // Placeholder return value
     
}

bool Chaining::deleteAccount(std::string id) {
    /*This function deletes the key stored in database. It
will return true after deletion. If the key was not
present, then it should return false*/
    int index=hash(id);
    for(int i=0;i<bankStorage2d[index].size();i++){
        if (bankStorage2d[index][i].id==id){
            bankStorage2d[index].erase(bankStorage2d[index].begin()+i);
            return true;
        }
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    /*Returns the total number of accounts currently
stored in the database*/
    int count=0;
    for(int i=0;i<bankStorage2d.size();i++){
        count+=bankStorage2d[i].size();
    }
    return count; // Placeholder return value
}
int Chaining::hash(std::string id) {
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