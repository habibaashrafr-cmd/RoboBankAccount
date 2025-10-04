#include<iostream>
#include<cstring>
#include "account.h"
#include "calculator.h"



const char *Account::getID()
{
    return id_;
}

AccountType Account::getAccountType()
{
    return settings_.type ;
}

long long Account::getBlance_Cents()
{
    return blance_cent_;
}

int Account::getNumber_audit()
{
    return auditcount_;
}

const TxRecord *Account:: getAudit_data()
{
    return audit_;
}


void Account::deposit(long long amount_cents, long long ts, const char *n)
{
        record(Deposit, amount_cents, ts, n) ;    
        blance_cent_ = apply_deposit(blance_cent_, audit_[auditcount_-1].amount_cents) ;
}

void Account::withdraw(long long amount_cents, long long ts, const char *n)
{
        record(Withdrawal, amount_cents, ts, n) ;
        blance_cent_ = apply_withdrawal(blance_cent_, audit_ [auditcount_-1].amount_cents) ;
}



void Account::charge_fee(long long fee_cents, long long ts, const char *n)
{
        record(Fee, fee_cents, ts, n) ;    
        blance_cent_ = apply_fee(blance_cent_, audit_ [auditcount_-1].amount_cents) ;
}

void Account::post_simple_interest(int days, int basis, long long ts, const char* n )
{
        record(Interest, basis, ts, n) ;    
        blance_cent_ += simple_interest(blance_cent_, settings_.apr, days ) ;
}


void Account::apply(const TxRecord& tx) 
{
    switch (tx.kind)
    {
        case Deposit :
            deposit(tx.amount_cents, tx.timestamp, tx.note) ;
            break ;

        case Withdrawal :    
            withdraw(tx.amount_cents, tx.timestamp, tx.note) ;
            break ;
        
        case Fee :
            charge_fee(tx.amount_cents, tx.timestamp, tx.note) ;
            break ;

        default :
              std::cout<<"You have entered incorrect data! " << std::endl ;   
              break ;
    }       

}

void Account::record(TxKind kind, long long amount, long long ts, const char *note)
{
    if (auditcount_ < MaxAudit)
    {
        audit_ [auditcount_].amount_cents = amount ;
        audit_ [auditcount_].timestamp = ts ;
        audit_ [auditcount_].note  = note ; 
        auditcount_++ ;
    }
    else 
    {
        auditcount_ = 0 ;
        audit_ [auditcount_].amount_cents = amount ;
        audit_ [auditcount_].timestamp = ts ;
        audit_ [auditcount_].note  = note ; 
    }
}

// int Account::check_capacity() 
// {
//     if (auditcount_ < MaxAudit )
//        return 0 ;

//     return (auditcount_ = 0) ;    
// }


Account::Account(const char* ID, const AccountSettings& settings, long long opening_balance_cents)
                : id_(ID), settings_(settings), blance_cent_ (opening_balance_cents) {}
