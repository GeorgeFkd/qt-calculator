#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include "parser.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("My Calculator");
    auto centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    this->currentState = NoInput;
    //here i will draw a layout and put buttons here
    auto* grid = new QGridLayout(this);
    //draw layout
    auto btnPlus = new QPushButton("+");
    auto btnMinus = new QPushButton("-");
    auto btnDiv = new QPushButton("/");
    auto btnMul = new QPushButton("*");
    auto btnLeftPar = new QPushButton("(");
    auto btnRightPar = new QPushButton(")");

    connect(btnPlus,&QPushButton::clicked,this,&MainWindow::addToExpression);
    connect(btnMinus,&QPushButton::clicked,this,&MainWindow::addToExpression);
    connect(btnDiv,&QPushButton::clicked,this,&MainWindow::addToExpression);
    connect(btnMul,&QPushButton::clicked,this,&MainWindow::addToExpression);
    connect(btnLeftPar,&QPushButton::clicked,this,&MainWindow::addToExpression);
    connect(btnRightPar,&QPushButton::clicked,this,&MainWindow::addToExpression);

    auto btnCalc = new QPushButton("Calculate");
    auto btnClear = new QPushButton("Clear");


    //add buttons
    grid->addWidget(btnPlus,1,1);
    grid->addWidget(btnMinus,2,2);
    grid->addWidget(btnDiv,1,2);
    grid->addWidget(btnMul,2,1);
    grid->addWidget(btnLeftPar,2,3);
    grid->addWidget(btnRightPar,1,3);
    grid->addWidget(btnCalc,5,4,2,2);
    grid->addWidget(btnClear,4,4,1,1);

    connect(btnCalc,&QPushButton::clicked,this,&MainWindow::evaluateExpression);
    connect(btnClear,&QPushButton::clicked,this,[this](){
        this->expressionLabel->setText("");
    });
    int rowStartFrom = 2;

    for(int i = 1;i <= 3;i++){
        for(int j = 1;j <= 3;j++){
            int num = (i-1)*3 + j;
            auto btnNum = new QPushButton(QString::number(num));
            grid->addWidget(btnNum,rowStartFrom + i,j);
            connect(btnNum,&QPushButton::clicked,this,&MainWindow::addToExpression);
        }

    }

    expressionLabel = new QLabel("Expression");
    grid->addWidget(expressionLabel,1,4,2,2);

    centralWidget->setLayout(grid);

}

void MainWindow::evaluateExpression(){
    qInfo() << "Evaluating the expression: " << this->expressionLabel->text();
    int res = calculateExpression(this->expressionLabel->text());
    this->expressionLabel->setText(QString("Result: %1").arg(res));
}

int MainWindow::calculateExpression(QString expr){
    auto expression = parse(expr.toStdString());
    return compute(expression);
}

void MainWindow::addToExpression(){
    QObject *s = sender();
    QPushButton *btn = qobject_cast<QPushButton*>(s);
    qInfo() << "Button pressed: " << btn->text();
    if(currentState==NoInput){
        this->expressionLabel->setText(btn->text());
        currentState = HasPickedATerm;
    }else{
        this->expressionLabel->setText(this->expressionLabel->text() + btn->text());
    }


}

MainWindow::~MainWindow() {




    //for each button add an event for clicking on it
}
