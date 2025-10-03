#include<iostream>
#include<cstring>
#include "account.h"
#include "calculator.h"



// enum AccountType {Checking , Saving} ;
// enum TxKind {Deposit, Withdrawal, Fee, Interest} ;
// struct AccountSettings
// {
//    AccountType typ ;
//    double apr;
//    long long fee_flat_cents ;
// };
// struct TxRecord
// {
//    TxKind kind ;
//    long long amount_cents ;
//    long long timestamp ;
//    const char* note;
// };


const char *Account::getID()
{
    return id;
}

AccountType Account::getAccountType()
{
    return settings.typ ;
}

long long Account::getBlance_Cents()
{
    return blance_cent;
}

int Account::getNumber_audit()
{
    return auditcount;
}

const TxRecord *Account:: getAudit_data()
{
    return audit_;
}


// void Account::setAudit_count(int *count)
// {
//     if(*count < MaxAudit)
//        auditcount = *count ;      
//     else 
//         std::cout<<"invalid! "   ;
// }
// void Account::setAudit_data(TxRecord audit)
// {
//     //in kind
//     if (audit.kind >=0 && audit.kind < 3 )
//         audit_[auditcount].kind = audit.kind ;
// }





void Account::deposit(long long amount_cents, long long ts, const char *n)
{
    blance_cent = apply_deposit(blance_cent, amount_cents) ;
    audit_ [auditcount].timestamp = ts ;
    audit_ [auditcount].note = n ; 
    auditcount +=1 ;
}

void Account::withdraw(long long amount_cents, long long ts, const char *n)
{
    blance_cent = apply_deposit(blance_cent, amount_cents) ;
    audit_ [auditcount].timestamp = ts ;
    audit_ [auditcount].note  = n ; 
    auditcount++ ;
}



void Account::charge_fee(long long fee_cents, long long ts, const char *n)
{
    blance_cent = apply_fee(blance_cent, fee_cents) ;
    audit_ [auditcount].timestamp = ts ;
    audit_ [auditcount].note  = n ; 
    auditcount++ ;
}

void Account::post_simple_interest(int days, int basis, long long ts, const char* n )
{
    blance_cent += simple_interest(basis, settings.apr, days ) ;
    audit_ [auditcount].timestamp = ts ;
    audit_ [auditcount].note  = n ; 
    auditcount ++ ;
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

Account::Account(const char* ID, const AccountSettings& settings_, long long opening_balance_cents) 
                : id (ID), settings(settings_), blance_cent (opening_balance_cents)
                {
                    
                }
