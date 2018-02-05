#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    memset(bStage,false,sizeof(bStage));
    ui->setupUi(this);
    QWidget *temp;
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            temp=new QWidget(ui->stage);
            temp->setGeometry(j*16+1,i*16+1,15,15);
            temp->setStyleSheet("background:#FFF");
            stage[i][j]=temp;
        }
    }
    for(int i=0; i<=4; i++)
    {
        stage[0][i]->setStyleSheet("background:#2a386c");
        bStage[0][i]=true;
    }
    snakeHead[0] = 0;
    snakeHead[1] = 4;
    snakeLast[0] = 0;
    snakeLast[1] = 0;
    canGrow = false;
    headDir = dirRight;
    lastDir = dirRight;
    ChangedHeadDir = dirRight;
    timer=new QTimer();
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(game_event()));
    change_point();
    stage[point[0]][point[1]]->setStyleSheet("background:#222222");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::game_event()
{
    if (ChangedHeadDir != headDir)
    {
        headDir = ChangedHeadDir;
        dirCLL.enqueue(DirChanging(snakeHead[0], snakeHead[1], headDir));
    }
    if (!dirCLL.isEmpty())
    {
        if (dirCLL.head().x == snakeLast[0] && dirCLL.head().y == snakeLast[1])
        {
            lastDir = dirCLL.head().dir;
            dirCLL.dequeue();
        }
    }
    if (move_is_OK())
    {
        if (canGrow)
            canGrow = false;
        else
        {
            stage[snakeLast[0]][snakeLast[1]]->setStyleSheet("background:#fff");
            switch (lastDir)
            {
                case dirRight:
                    ++snakeLast[1];
                    break;
                case dirUp:
                    --snakeLast[0];
                    break;
                case dirDown:
                    ++snakeLast[0];
                    break;
                case dirLeft:
                    --snakeLast[1];
                    break;
            }
        }
        switch (headDir)
        {
            case dirRight:
                ++snakeHead[1];
                break;
            case dirUp:
                --snakeHead[0];
                break;
            case dirDown:
                ++snakeHead[0];
                break;
            case dirLeft:
                --snakeHead[1];
                break;
        }
        stage[snakeHead[0]][snakeHead[1]]->setStyleSheet("background:#2a386c");
        if (snakeHead[0] == point[0] && snakeHead[1] == point[1])
        {
            change_point();
            stage[point[0]][point[1]]->setStyleSheet("background:#222222");
            canGrow = true;
        }
    }
    else
    {
        QMessageBox::information(this,"Game Over","GG");
        timer->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
            if (headDir!=dirDown)
                ChangedHeadDir=dirUp;
            break;
        case Qt::Key_S:
            if (headDir!=dirUp)
                ChangedHeadDir=dirDown;
            break;
        case Qt::Key_A:
            if (headDir!=dirRight)
                ChangedHeadDir=dirLeft;
            break;
        case Qt::Key_D:
            if (headDir!=dirLeft)
                ChangedHeadDir=dirRight;
            break;
    }
}

bool MainWindow::move_is_OK()
{
    int nextHead[2];
    nextHead[0] = snakeHead[0];
    nextHead[1] = snakeHead[1];
    bStage[snakeLast[0]][snakeLast[1]] = false;
    switch (headDir)
    {
        case dirRight:
            ++nextHead[1];
            break;
        case dirUp:
            --nextHead[0];
            break;
        case dirDown:
            ++nextHead[0];
            break;
        case dirLeft:
            --nextHead[1];
            break;
    }
    if (bStage[nextHead[0]][nextHead[1]] == true || nextHead[0] < 0 || nextHead[0] >19 || nextHead[1] < 0 || nextHead[1] >19)
        return false;
    else
    {
        bStage[nextHead[0]][nextHead[1]] = true;
        return true;
    }
}

void MainWindow::change_point()
{
    do
    {
        point[0]=qrand()%20;
        point[1]=qrand()%20;
    }while(bStage[point[0]][point[1]]);
}

void MainWindow::on_pushButton_clicked()
{
    memset(bStage,false,sizeof(bStage));
    timer->start(100);
    snakeHead[0] = 0;
    snakeHead[1] = 4;
    snakeLast[0] = 0;
    snakeLast[1] = 0;
    canGrow = false;
    headDir = dirRight;
    lastDir = dirRight;
    ChangedHeadDir = dirRight;
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            stage[i][j]->setStyleSheet("background:#FFF");
        }
    }
    for(int i=0; i<=4; i++)
    {
        stage[0][i]->setStyleSheet("background:#2a386c");
        bStage[0][i]=true;
    }
    change_point();
    stage[point[0]][point[1]]->setStyleSheet("background:#222222");
    dirCLL.clear();
}
