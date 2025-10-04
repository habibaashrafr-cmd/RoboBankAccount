#include<iostream>
#include "account.h"


int main()
{
    
    int type, kind, days ; //checking = 0 , saving = 1 , Apply prebuilt records =2
    long long  amount, ts ;
    char continu_ ;
    AccountSettings settings ;
    settings = {Checking, 0.0} ;
    std::cout<<"fee_flat_cents " ;
    std::cin >>settings.fee_flat_cents ;
    Account A {"habiba", settings, 300} ;
    while (1)
    {
        std::cout<<"chose what want to do : " << std::endl ;
        std::cout<<"1.Checking account with fee : "<< std::endl;
        std::cout<<"2.withdrawal : "<< std::endl;
        std::cout<<"3. Apply prebuilt records : "<< std::endl; 
        std::cin>> type ;
        switch (type)
        {
        //1.Checking account with fee    
        case  0 :
        while (1)
        {
            std::cout<<"chose the transaction you want to do :  " ;
            std::cout<<"1.Deposit : " <<std::endl;
            std::cout<<"2.withdrawal : " <<std::endl;
            std::cout<<"3.interest : " <<std::endl; 
            std::cin >> kind ;
            switch (kind)
            {
            case 1 :
                std::cout<<"Enter the amount : " ;
                std::cin >> amount;
                std::cout<<"Enter the timesimple : " ;
                std::cin >> ts;
                A.deposit(amount, ts) ;
                break;
            
            case 2 :
                std::cout<<"Enter the amount : " ;
                std::cin >> amount;
                std::cout<<"Enter the timesimple : " ;
                std::cin >> ts;
                A.withdraw(amount, ts) ; 
                break; 
            case 3 :
                std::cout<<"Enter the fee_cents : " ;
                std::cin >> amount;
                std::cout<<"Enter the timesimple : " ;
                std::cin >> ts;
                A.charge_fee(amount, ts) ;  
                break;
                 
            default:
                std::cout<<" this invalid input " << std::endl ;
                break;
            }
        std::cout<< "Balanc = " << A.getBlance_Cents() << std::endl ;  
        std::cout<<"Audit size = " << A.getNumber_audit() << std::endl ; 
            
        std::cout<<"if you want to do more iteraction in this account  press y, if not press any key ";
        std::cin >> continu_;
        if(continu_=='y'||continu_=='Y')
        {
           continue;    
        }
        else
            break;   

        }
        std::cout<< "Balanc = " << A.getBlance_Cents() << std::endl ;  
        std::cout<<"Audit size = " << A.getNumber_audit() << std::endl ; 
        break;
        //2.Savings interest
        case 1 :{
            settings = {Saving, 0, 0} ;
            std::cout<<"enter the apr  " ;
            std::cin>>settings.apr ;
            Account S{"ali", settings, 500000} ;
            std::cout<< "enter number of days :" ;
            std::cin >> days ;
            S.post_simple_interest(days, 365, ts) ;
           std::cout<< "Balanc = " << S.getBlance_Cents() << std::endl ; 
           std::cout<<"Last audit entry = {" << S.getAudit_data()->kind <<", " << S.getAudit_data()->amount_cents <<", "
                <<", "<<S.getAudit_data()->timestamp <<" }"<< std::endl ; 

            break; }
     //3. Apply prebuilt records    
        case 2 :
        {
           int x ;
           TxRecord t1 {Deposit, amount, ts, "deposit"} ;
           TxRecord t2 {Withdrawal, amount, ts, "withdrawal"} ;
           TxRecord t3 {Fee, amount, ts, "apply fee"} ;
           std::cout<<"enter you want to apply : " ;
           std::cout<<"1.Deposit : "<<std::endl;
           std::cout<<"2.withdrawal : "<<std::endl;
           std::cout<<"3.fee : "<<std::endl; 
           std::cin >> x ;
        switch (x)
        {
        case 1 :
            A.apply(t1) ;
            break;
         case 2 :
            A.apply(t2) ;
            break;
         case 3 :
            A.apply(t3) ;
            break;        
        }
        std::cout<< "Balanc = " << A.getBlance_Cents() << std::endl ;  
        std::cout<<"Audit size = " << A.getNumber_audit() << std::endl ; 
        break; }
    }
        std::cout<<"if you want to continue  press y, if not press any key ";
        std::cin >> continu_;
        if(continu_=='y' || continu_=='Y')
        {
           continue;    
        }
        else
            break;   

    }   

    return 0;
}