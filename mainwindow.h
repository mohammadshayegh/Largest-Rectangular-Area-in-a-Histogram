#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdarg>
#include <QPainter>
#include <QDebug>
#include <vector>
#include <math.h>
#include <vector>

using std::max;
using std::vector;using std::min;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    vector<int> m_histogram;
    int m_size = 0, m_max = 0, m_maxArea = 0;
    int m_areaStart=0, m_areaEnd=0, m_areaParent=0;
    int* m_histoArray = nullptr;

    int histoMaxElement();
    int maxArea(int *histo, int start, int end,int &maxS, int &maxE,int &maxN);
    int* copyInNewArray(const int *histogram, int size);
    void areaElements(int &start, int &end, int &parent);

protected:
    void paintEvent(QPaintEvent *e);

};

#endif // MAINWINDOW_H
