#ifndef  _ACCOUNT_H
#define _ACCOUNT_H

#define MaxAudit  256

enum AccountType {Checking , Saving} ;
enum TxKind {Deposit, Withdrawal, Fee, Interest} ;

struct AccountSettings
{
   AccountType typ ;
   double apr ;
   long long fee_flat_cents ;
};

struct TxRecord
{
   TxKind kind ;
   long long amount_cents ;
   long long timestamp ;
   const char* note = nullptr;
};

class Account
{
private:
    const char* id ;
    long long blance_cent ;
    int auditcount ;
    AccountSettings settings ;
    TxRecord audit_[MaxAudit] ;

public:
    //getters
    const char* getID() ;
    AccountType getAccountType() ;
    long long   getBlance_Cents() ;
    int         getNumber_audit() ;
    const TxRecord* getAudit_data() ;
    
    //setter
    void setAudit_count(int *count);
    void setAudit_data(TxRecord audit);
    
    //operations
    void deposit(long long amount_cents, long long ts, const char* n = nullptr) ;
    void withdraw(long long amount_cents, long long ts, const char* n = nullptr) ;
    void charge_fee(long long fee_cents, long long ts, const char* n = nullptr) ;
    void post_simple_interest(int days, int basis, long long ts, const char* n = nullptr) ;
    void apply(const TxRecord& tx) ;


/// @brief 
/// @param ID 
/// @param settings_ 
/// @param opening_balance_cents 
Account(const char* ID, const AccountSettings& settings_, long long opening_balance_cents) ;

    
};

/// @brief 
/// @param ID 
/// @param settings_ 
/// @param opening_balance_cents 
//Account::Account(const char* ID, const AccountSettings& settings_, long long opening_balance_cents) ;

// Account::~Account()
// {
// }


#endif //_ACCOUNT_H
