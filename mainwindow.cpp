#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){ui->setupUi(this);}
MainWindow::~MainWindow(){delete ui;}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    if(text != "")
    {
        int value = text.toInt();
        m_histogram.push_back(value);
        m_histoArray = m_histogram.data();
        m_size = static_cast<int>(m_histogram.size());
        m_max = histoMaxElement();
        m_maxArea = maxArea(m_histoArray ,0,static_cast<int>(m_histogram.size()-1),m_areaStart, m_areaEnd, m_areaParent) ;

        QString maxArea_Qv =QString::number(m_maxArea); //Qv : Qstring Value
        ui->label_2->setText(maxArea_Qv);
    }
}

int findMin(int *array, int start, int end)
{
    int min = start;

    for( int i=start; i<=end; i++)
    {
        if(array[i]<array[min])
            min = i;
    }
    return min;
}

int MainWindow::maxArea(int *histo, int start, int end,int &maxS, int &maxE,int &maxN)
{
    if(start == end)
    {
        if(maxN *(maxE-maxS+1)<histo[start])
        {
            maxS = start;
            maxE = end;
            maxN = histo[start];
        }
        return histo[start];
    }
    else
    {
        int min_index = findMin(histo,start,end);
        int mid = histo[min_index];
        int leftMax = 0, rightMax=0 ;

        if(min_index-1>=start)
            leftMax = maxArea(histo,start,min_index-1,maxS,maxE,maxN);

        if(min_index+1<=end)
            rightMax = maxArea(histo,min_index+1,end,maxS,maxE,maxN);

        if(max(max(leftMax,rightMax),mid*(end-start+1)) > maxN *(maxE-maxS+1))
        {
            maxS = start;
            maxE = end;
            maxN = mid;
        }
        return max(max(leftMax,rightMax),mid*(end-start+1));
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //cordinate
    int width = 20 ,height = 20 ;
    int x = 5;
    int y = m_max*10 + 100;

    //drawing variables
    QPainter p(this);
    QPainterPath path;
    QPen pen(Qt::black, 2);

    if(m_histoArray)
    {
        for(int i=0; i < m_size; i++)
        {
            height = -10*m_histoArray[i];

            //RoundRect declaration
            path.addRoundedRect(QRectF(x, y, width, height), 0, 0);

            pen.setColor(Qt::black);p.setPen(pen);
            p.fillPath(path, QColor(34, 177, 76)); // border setting
            p.drawPath(path);                      // filler setting

            //indexes
            pen.setColor(Qt::blue);
            QString number = QString::number(m_histoArray[i]);
            p.drawText(x+5,y+15,number);

            //border Graph
            p.drawLine(5,y+2,5,90);
            p.drawLine(5,y+2,x+30,y+2);

            x+=20;
        }

        pen.setColor(Qt::red);p.setPen(pen);
        p.drawRect(20*m_areaStart + 5,y,-20*(m_areaStart - m_areaEnd - 1),-10*m_areaParent);
    }

    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    m_histogram.clear();
    m_histoArray = nullptr;
    m_size = 0;
    m_max = 0;
    m_maxArea = 0;
    m_areaStart=0;
    m_areaEnd=0;
    m_areaParent=0;
    ui->lineEdit->setText("");
    ui->label_2->setText("");
}

int MainWindow::histoMaxElement()
{
    int max_v = 0;
    int size = m_size;
    int *histo = m_histoArray;

    for(int i=0; i<size; i++)
        if(max_v < histo[i])
            max_v = histo[i];

    return max_v;
}
