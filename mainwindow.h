#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QQueue>
#include <QTime>
#include <QKeyEvent>
#include <QDebug>
#include "dirchanging.h"
#include "direction.h"
#include <QMessageBox>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void game_event();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QWidget *stage[20][20];
    bool bStage[20][20];
    int snakeHead[2];
    int snakeLast[2];
    int point[2];
    bool canGrow;
    Direction headDir;
    Direction ChangedHeadDir;
    Direction lastDir;
    QTimer *timer;
    QQueue<DirChanging> dirCLL;
    void keyPressEvent(QKeyEvent *event);
    bool move_is_OK();
    void change_point();
};

#endif // MAINWINDOW_H
