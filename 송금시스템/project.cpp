#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>

#include <cstdlib>
#include <ctime>

#define MIN_ACCOUNT_NUMBER 10000000
#define MAX_ACCOUNT_NUMBER 99999999

//클래스안에서 타이머 함수 만들기
class Timer
{
public:
    void Timers_show(int seconds);
    void Timers_noshow(int seconds);
};

class AccountSuper
{
public:
    virtual void AccountInfo(){
        system("cls");
        std::cout<<"Account info"<<std::endl;
        std::cout<<"Name: {name}"<<std::endl;
        std::cout<<"Account Number: {bankbook}"<<std::endl;
        std::cout<<"Money: {money}"<<std::endl;
    }
};

//계정 정보 데이터 저장
class Account : public AccountSuper
{
public:
    std::string name;
    int bankBook;
    int money;

    Account(std::string name, int bankBook, int money){
        this->name = name;
        this->bankBook = bankBook;
        this->money = money;
    }

    void AccountInfo() override{
        system("cls");
        std::cout<<"Your Account info"<<std::endl;
        std::cout<<"Your Name: "<<name<<std::endl;
        std::cout<<"Your Account Number: "<<bankBook<<std::endl;
        std::cout<<"Your Money: "<<money<<std::endl;
    }
};

class DummuYAccount : public AccountSuper   //  테스트용 더미 계정 생성
{
public:
    std::string name;
    int bankBook;
    int money;

    DummuYAccount(std::string name, int bankBook, int money){
        this->name = name;
        this->bankBook = bankBook;
        this->money = money;
    }

    void AccountInfo() override{
        system("cls");
        std::cout<<"Dummy Account info"<<std::endl;
        std::cout<<"Dummy Name: "<<name<<std::endl;
        std::cout<<"Dummy Account Number: "<<bankBook<<std::endl;
        std::cout<<"Dummy Money: "<<money<<std::endl;
    }
};

int main(){
    Timer timer;

    std::string mainInput;
    int consoleAvailable = 1;
    int checkNumber = 0;
    int finalIntergerMoney;

    int randomAccountNumber;

    std::string name;
    std::cout<<"Create your UserId for Bank Manage"<<std::endl;
    std::cin>>name;
    std::cout<<"Setting your Account number..."<<std::endl;

    std::srand(std::time(NULL));    //  계좌 번호 생성
    randomAccountNumber = (rand() % (MIN_ACCOUNT_NUMBER+MIN_ACCOUNT_NUMBER+1));
    randomAccountNumber += MAX_ACCOUNT_NUMBER - MIN_ACCOUNT_NUMBER;
    std::cout<<"Complete make your Account number : "<<randomAccountNumber<<std::endl;

    std::cout<<"Set your money"<<std::endl;
    std::string stringMoney;
    checkNumber = 1;
    while (checkNumber)
    {
        std::cin.ignore();
        std::getline(std::cin, stringMoney);  //  문자열로 숫자 입력받기
        try{    //   문자열을 숫자 변환 시도, 실패시 아래의 catch로 이동
            int intergerMoney = std::stoi(stringMoney);
            finalIntergerMoney = intergerMoney;
            break;
        } catch(const std::invalid_argument){
            std::cout<<"Not a number. please try again"<<std::endl;
            //타이머 입력(3초)
            timer.Timers_show(3);
            system("cls");
        }
    }
    checkNumber = 0;
    Account account(name, randomAccountNumber, finalIntergerMoney);
    
    system("cls");

    std::cout<<"Complete setup!"<<std::endl<<std::endl;
    account.AccountInfo();
    timer.Timers_noshow(5);
    consoleAvailable = 1;

    system("cls");
    
    std::srand(-1);    //  계좌 번호 생성
    randomAccountNumber = (rand() % (MIN_ACCOUNT_NUMBER+MIN_ACCOUNT_NUMBER+1));
    randomAccountNumber += MAX_ACCOUNT_NUMBER - MIN_ACCOUNT_NUMBER;
    DummuYAccount dummyAccount("user-dummy", randomAccountNumber, 0);  //  더미 계정 생성

    while (consoleAvailable == 1)   //  콘솔창 번호 확인(해당하는 숫자가 있으면 break하면서 이동, 없으면 존재하는 번호있을때까지 무한 반복)
    {
        std::ifstream file("welcome.txt");  //  환영 텍스트 콘솔에 출력
        if(file.is_open()){
            std::string readData;
            while (getline(file, readData))
            {
                std::cout<<readData<<std::endl;
            }
            file.close();
            
        } else {
            std::cout<<"NO FILE..."<<std::endl;
        }

        std::cout<<"Please select a number."<<std::endl;
        std::getline(std::cin, mainInput);  //  문자열로 숫자 입력받기
        try{    //   문자열을 숫자 변환 시도, 실패시 아래의 catch로 이동
            int mainInputNumber = std::stoi(mainInput);
            if(mainInputNumber == 1){   //  계좌 확인하기
                account.AccountInfo();
                timer.Timers_noshow(10);
                system("cls");

            } else if(mainInputNumber == 2){    //  돈 송금하기
                system("cls");
                std::cout<<"Enter the amount you want to transfer to the dummy user."<<std::endl;
                int *ptr_money = new int;   //  동적 할당
                checkNumber = 1;
                while (checkNumber)
                {
                    std::getline(std::cin, stringMoney);  //  문자열로 숫자 입력받기
                    try{    //   문자열을 숫자 변환 시도, 실패시 아래의 catch로 이동
                        int finalIntergerMoney = std::stoi(stringMoney);
                        *ptr_money = finalIntergerMoney;
                        break;
                    } catch(const std::invalid_argument){
                        std::cout<<"Not a number. please try again"<<std::endl;
                        //타이머 입력(3초)
                        timer.Timers_show(3);
                        system("cls");
                    }
                }
                checkNumber = 0;
                
                //보내는 기능
                if(account.money > *ptr_money){
                    dummyAccount.money += *ptr_money;
                    account.money -= *ptr_money;
                    std::cout<<"complete send "<<*ptr_money<<std::endl;
                    std::cout<<"your current money have "<<account.money<<std::endl;
                } else {
                    std::cout<<"Not a number. please try again"<<std::endl;
                    //타이머 입력(3초)
                    timer.Timers_noshow(3);
                    system("cls");
                }
                delete ptr_money;
            } else if(mainInputNumber == 3){    //  더미 계정 확인하기
                dummyAccount.AccountInfo();
                timer.Timers_noshow(10);
                system("cls");

            } else if(mainInputNumber == 4){    //  나가기
                break;

            } else {
                std::cout<<"No applicable number. please try again"<<std::endl;
                //타이머 입력(3초)
                timer.Timers_show(3);
                system("cls");
            }
        } catch(const std::invalid_argument){   //  숫자가 아닌 문자가 입력이 되었을때
            std::cout<<"Not a number. please try again"<<std::endl;
            //타이머 입력(3초)
            timer.Timers_show(3);
            system("cls");
        }
    }
    std::cout<<"OFF..."<<std::endl;
    return 0;
}

void Timer::Timers_show(int seconds){
    for (int i = seconds; i > 0; i--){
        std::cout<<"Until you return to the first screen "<<i<<"seconds."<<std::endl;
        Sleep(1000);
    }
}
void Timer::Timers_noshow(int seconds){
    std::cout<<"Until you return to the first screen "<<seconds<<" seconds."<<std::endl;
    for (int i = seconds; i > 0; i--){
        Sleep(1000);
    }
}