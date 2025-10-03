#ifndef  _ACCOUNT_H
#define  _ACCOUNT_H

#define MaxAudit  256

enum AccountType {Checking , Saving} ;
enum TxKind {Deposit, Withdrawal, Fee, Interest} ;

struct AccountSettings
{
   AccountType type ;
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

Account(const char* ID, const AccountSettings& settings, long long opening_balance_cents) ;

public:
    //getters
    const char* getID() ;
    AccountType getAccountType() ;
    long long   getBlance_Cents() ;
    int         getNumber_audit() ;
    const TxRecord* getAudit_data() ;

    //operations
    void deposit(long long amount_cents, long long ts, const char* n = nullptr) ;
    void withdraw(long long amount_cents, long long ts, const char* n = nullptr) ;
    void charge_fee(long long fee_cents, long long ts, const char* n = nullptr) ;
    void post_simple_interest(int days, int basis, long long ts, const char* n = nullptr) ;
    void apply(const TxRecord& tx) ;


private:
    const char* id_ ;
    long long blance_cent_ ;
    int auditcount_ ;
    AccountSettings settings_ ;
    TxRecord audit_[MaxAudit] ;

    void record(TxKind kind, long long amount, long long ts, const char* note) ;
    int  check_capacity() ;

};


#endif //_ACCOUNT_H
