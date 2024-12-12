#include<iostream>
#include<string>
#include<math.h>
#include<cstdlib>
#include<ctime>
using namespace std;
enum enQuetionslevel{easylevel=1,medlevel=2,Hardlevel=3,mix=4};
enum enOperationType{Add=1,sub=2,mult=3,Div=4,mixop=5};
struct stquestion
 {
    int Number1=0;
    int number2=0;
    enOperationType operationtype;
    enQuetionslevel Questionlevel;
    int correctanswer=0;
    int playeranswer=0;
    bool Answerresult=false;

};
struct stQizz
{
    stquestion Questionlist[100];
    short numberofQuestion;
    enQuetionslevel Questionlevel;
    enOperationType optype;
    short NumberOfWrongAnswers=0;
    short NumberOfRightAnswer=0;
    bool ispass=false;

};
void ResetScreen()
 {   
      system("cls");
           system("color 0F");
 }

short ReadHowManyQuestions()
{
 short NumberOfQuestions;
 do
 {
    cout <<"How Many Questions do you want to answer?";
    cin>>NumberOfQuestions;
 } while (NumberOfQuestions<1||NumberOfQuestions>10);
 return NumberOfQuestions;
}
enQuetionslevel ReadQuestionLevel()
{
    short Questionlevel=0;
    cout<<"Enter Question Level {1} Easy,{2} Med,{3} Hard ,{4} Mex?";
    cin>>Questionlevel;
    return (enQuetionslevel) Questionlevel;
}
enOperationType ReadOperationType()
{
    short OPType=0;
    do
    { 
        cout<<"Enter Operation Type {1}Add, {2} Sub, {3} Mult, {4} div ,{5} mix?";
        cin>>OPType;
    } while (OPType<1||OPType>5);
    return (enOperationType) OPType;
}
int RandNumber(int from ,int to)
{
    int Randnum=rand()%(to -from + 1)+from;
    return Randnum;
}
enOperationType GeTRandnumOperationType()
{
    int op=RandNumber(1,4);
    return (enOperationType) op;
}
int SimpleCalculater(int NUmber1,int Number2,enOperationType optype)
{
    switch (optype)
    {
    case enOperationType::Add:
       return NUmber1+Number2;
    case enOperationType::sub:
       return NUmber1-Number2;
    case enOperationType::Div:
       return NUmber1/Number2;
    case enOperationType::mult:
       return NUmber1*Number2;
    default:
    return NUmber1+Number2;         

    }
}
stquestion GenerateQuestion(enQuetionslevel questionlevel,enOperationType optype)
{
    stquestion Question;
    if (questionlevel==enQuetionslevel::mix)
    {
       questionlevel=(enQuetionslevel) RandNumber(1,3);
    }
    if (optype==enOperationType::mixop)
       {
         optype=GeTRandnumOperationType();
       }
       Question.operationtype=optype;
      switch (questionlevel)
      {
      case enQuetionslevel::easylevel:
      Question.Number1=RandNumber(1,10);
      Question.number2=RandNumber(1,10);
      Question.correctanswer=SimpleCalculater(Question.Number1,Question.number2,Question.operationtype);
      Question.Questionlevel=questionlevel;
      return Question;

      case enQuetionslevel::medlevel:
      Question.Number1=RandNumber(10,50);
      Question.number2=RandNumber(10,50);
      Question.correctanswer=SimpleCalculater(Question.Number1,Question.number2,Question.operationtype);
      Question.Questionlevel=questionlevel;
      return Question;

      case enQuetionslevel::Hardlevel:
      Question.Number1=RandNumber(50,100);
      Question.number2=RandNumber(50,100);
      Question.correctanswer=SimpleCalculater(Question.Number1,Question.number2,Question.operationtype);
      Question.Questionlevel=questionlevel;
      return Question;
      } 
      return Question;
}
void GenerateQuizzQuestions(stQizz &quizz)
{
  for (short i = 0; i < quizz.numberofQuestion; i++)
  {
    quizz.Questionlist[i]=GenerateQuestion(quizz.Questionlevel,quizz.optype);

  }
  
}
string GetOperationTypeSymbol(enOperationType optye)
{
    switch (optye)
    {
    case enOperationType::Add:
      return "+";
    case enOperationType::sub:
      return "-";
    case enOperationType::mult:
      return "x ";
    case enOperationType::Div:
      return "/";
      default :
        return "mix";  
        
    }
}
void PrintQuestion(stQizz QUizz ,short QuestionNumber)
{
    cout<<"\nQuestion["<<QuestionNumber+1<<"/"<<QUizz.numberofQuestion<<"]\n\n";
    cout<<QUizz.Questionlist[QuestionNumber].Number1<<endl;
    cout<<QUizz.Questionlist[QuestionNumber].number2<<" ";
    cout<<GetOperationTypeSymbol(QUizz.Questionlist[QuestionNumber].operationtype);
    cout<<"___________________________________"<<endl;
}
int ReadQuestionAnswer()
{
    int Answer=0;
    cin>>Answer;
    return Answer;
}
void SetScreenColor(bool Right)
 { 
    if (Right)     
        system("color 2F"); //turn screen to Greenelse 
        else  
            {
                 system("color 4F"); //turn screen to Red   
                   cout     <<     "\a";  
            }
 }   
void CorrectTheQuestionAnswer(stQizz & Quizz,short QuestionNumber)
{
    if (Quizz.Questionlist[QuestionNumber].playeranswer!=Quizz.Questionlist[QuestionNumber].correctanswer)

    {
        Quizz.NumberOfWrongAnswers++;
        cout<<"wrong Answer:-(\n";
        cout<<"The right Answer is :";
        cout<<Quizz.Questionlist[QuestionNumber].correctanswer;
    }
    else
    {
        Quizz.Questionlist[QuestionNumber].Answerresult=true;
        Quizz.NumberOfRightAnswer++;
        cout <<"right answer:-)\n"<<endl;
        SetScreenColor(Quizz.Questionlist[QuestionNumber].Answerresult);

    }
    
    
    
    
}

void AskandCorrectQuestionListAnswers(stQizz &Quizz)
{
  for (short i = 0; i < Quizz.numberofQuestion; i++)
  {
    PrintQuestion(Quizz,i);
    Quizz.Questionlist[i].playeranswer=ReadQuestionAnswer();
    CorrectTheQuestionAnswer(Quizz,i);
  }
  Quizz.ispass=(Quizz.NumberOfRightAnswer>=Quizz.NumberOfWrongAnswers);
  
}
string GetFinalResultsText(bool pass)
{
    if (pass)
    {
        return "pass:-)";
    }
    else
    return "fail:-(";
}
string getQuestionLevelText(enQuetionslevel Question)
{
    string arrQuestionLevelText[4]={"Easy","med","Hard","mix"};
    return arrQuestionLevelText[Question-1];
}
void printQuizzResult(stQizz Quizz)
{
    cout<<"\n__________________________________\n\n";
    cout<<"final Result is "<<GetFinalResultsText(Quizz.ispass);
    cout<<"\n____________________\n\n";
    cout<<"number of Questions   : "<<Quizz.numberofQuestion<<endl;
    cout<<"Questions level       : "<<getQuestionLevelText(Quizz.Questionlevel);
    cout <<"optype               : "<<GetOperationTypeSymbol(Quizz.optype)<<endl;
    cout<<"Number of Right Answer: "<<Quizz.NumberOfRightAnswer<<endl;
    cout<<"Number of Wrong Answer: "<<Quizz.NumberOfWrongAnswers<<endl;
    cout<<"_____________________________________\n";
}
void playMathgame()
{
    stQizz Quizz;
    Quizz.numberofQuestion=ReadHowManyQuestions();
    Quizz.Questionlevel=ReadQuestionLevel();
    Quizz.optype=ReadOperationType();
    GenerateQuizzQuestions(Quizz);
    AskandCorrectQuestionListAnswers(Quizz);
   printQuizzResult(Quizz);

}
void startGame()
{
    char Playagain='y';
    do
    {
        ResetScreen();
        playMathgame();
        cout<<endl<<"Do You Want To Play Again? Y/N";
        cin>>Playagain;
    } while (Playagain=='y'||Playagain=='Y');
    
}


int main()
{
   srand ((unsigned)time(NULL));
   startGame();       
}