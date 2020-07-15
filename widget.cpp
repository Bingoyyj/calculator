#include "widget.h"
#include "ui_widget.h"

#include <QStack>
#include <QQueue>
#include <QChar>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("计算器");

    QFont f("仿宋",16);
    ui->mainLineEdit->setFont(f);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_onebutton_clicked()
{
    expression += "1";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_twobutton_clicked()
{
    expression += "2";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_threebutton_clicked()
{
    expression += "3";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_fourbutton_clicked()
{
    expression += "4";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_fivebutton_clicked()
{
    expression += "5";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_sixbuttton_clicked()
{
    expression += "6";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_sevenbutton_clicked()
{
    expression += "7";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_eightbutton_clicked()
{
    expression += "8";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_ninebutton_clicked()
{
    expression += "9";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_zerobutton_clicked()
{
    expression += "0";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_leftbutton_clicked()
{
    expression += "(";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_rightbutton_clicked()
{
    expression += ")";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_addbutton_clicked()
{
    expression += "+";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_subbutton_clicked()
{
    expression += "-";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_mulbutton_clicked()
{
    expression += "*";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_divbutton_clicked()
{
    expression += "/";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_clearbutton_clicked()
{
    expression.clear();
    ui->mainLineEdit->clear();
}

void Widget::on_delbutton_clicked()
{
    expression.chop(1);
    ui->mainLineEdit->setText(expression);
}

int priority(QChar op){
    if (op=='*' || op=='/')return 2;
    if (op=='+' || op=='-')return 1;
    else return 0;//op为(时
}

void change(QString& input,QQueue<QString> &q){
    QStack<QChar> s;//存放符号
    for(int i=0;i<input.size();i++){
        if(input[i]>='0' && input[i]<='9'){
            if(q.empty() || input[i-1]=='+' || input[i-1]=='-' || input[i-1]=='*' || input[i-1]=='/' || input[i-1]=='(')
                q.push_back(QString(input[i]));//char转string
            else
                q.back()+=input[i];
        }
        else{
            if(s.empty() || input[i]=='(')//栈空或左括号，进栈
                s.push(input[i]);
            else if(input[i]==')'){//弹出括号内所有符号
                while(s.top()!='('){
                    q.push_back(s.top());
                    s.pop();
                }
                s.pop();//弹出左括号
            }
            else{
                while(priority(input[i])<=priority(s.top())){//栈顶运算符大于等于当前运算符时，进队
                    q.push_back(s.top());
                    s.pop();
                    if(s.empty()) break;
                }
                s.push(input[i]);//当前运算符进栈
            }
        }
    }
    while(!s.empty()){
        q.push_back(s.top());
        s.pop();
    }
}

int calculate(QQueue<QString> &q){
    QStack<int> s;
    while(!q.empty()){
        if(q.front()!="+" && q.front()!="-" && q.front()!="*" && q.front()!="/")//若为数字，进栈
            s.push(q.front().toInt());
        else{
            int right=s.top();s.pop();
            int left=s.top();s.pop();
            if(q.front()=="+")
                s.push(left+right);
            else if(q.front()=="-")
                s.push(left-right);
            else if(q.front()=="*")
                s.push(left*right);
            else
                s.push(left/right);
        }
        q.pop_front();
    }
    return s.top();
}

void Widget::on_equalbutton_clicked()
{
    QQueue<QString> q;
    change(expression,q);
    expression=QString::number(calculate(q));
    ui->mainLineEdit->setText(expression);
}
