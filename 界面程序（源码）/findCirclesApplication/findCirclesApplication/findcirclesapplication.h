#ifndef FINDCIRCLESAPPLICATION_H
#define FINDCIRCLESAPPLICATION_H

#include <QtWidgets/QMainWindow>
#include "ui_findcirclesapplication.h"

//qt header files
#include<QDialog>
#include <QFileDialog>
#include<QString>
#include<QPixmap>

//����ͷ�ļ�
#include "GBK.h"
#include <sstream>
#include "findCircles.h"

class findCirclesApplication : public QMainWindow
{
	Q_OBJECT

public:
	findCirclesApplication(QWidget *parent = 0);
	~findCirclesApplication();

private:
	Ui::findCirclesApplicationClass ui;

private slots:
//���ö�ȡͼƬ·��
void on_bthSetPath_clicked();
//��ȡ��ǰͼƬ
void on_btnReadImg_clicked();

//��һ��ͼƬ
void on_btnNextImg_clicked();

//������ֵ
void on_btnSetThresholdValue_clicked();

//���ͼƬ
void on_btnToDetectSampleImgs_clicked();

//��������ֵ
void on_btnPixelThreshold_clicked();

//�˳�
void on_btnExit_clicked();


public:
	//�����ͼ�����б�
	QStringList imgNameList;
	//���ڴ洢��ǰ��ʾͼ������
	int imgNum;
	//�洢��ǰ��ʾͼ��pixmap
	QPixmap *pixmap;
    //��ǰͼ��Ŀ��
	int imgWidth;
	int imgHeight;
	//�洢��ǰ�����ͼ���Mat
	Mat drawImg;//��ͨ��
	Mat grayImg;//��ͨ��ͼ��

	//�������ֵ ��ֵ����ֵ
	int nThreshold;

	//������ֵ �����ڴ���ֵ�����ؽԸ�ֵΪ0;
	int nPixelThreshold;

	//ͳ��СԲ�ߵ�����
	int nLittleCircle;

};

#endif // FINDCIRCLESAPPLICATION_H
