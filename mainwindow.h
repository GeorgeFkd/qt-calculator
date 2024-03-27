#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *expressionLabel;
    enum State{
        NoInput,
        HasPickedATerm
    };
    State currentState;
    int calculateExpression(QString expr);

protected:
    void addToExpression();
    void evaluateExpression();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
