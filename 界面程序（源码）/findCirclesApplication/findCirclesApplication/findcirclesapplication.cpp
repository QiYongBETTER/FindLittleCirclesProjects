#include "findcirclesapplication.h"

findCirclesApplication::findCirclesApplication(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//��ʼ��
	imgNum = 0;

	//СԲ�ߵ����� ��ʼ��Ϊ0
	nLittleCircle = 0;

	//��ֵ ��ֵ����ֵ ��Ĭ��ֵ
	nThreshold = 135;
	stringstream sThreshold;
	sThreshold << nThreshold;
	ui.editThresholdValue->setText(sThreshold.str().c_str());  
	//�����ڴ���ֵ�����ؽԸ�ֵΪ0 ��Ĭ��ֵ
	nPixelThreshold = 160;
	stringstream sPixelThreshold;
	sPixelThreshold << nPixelThreshold;
	ui.editPixelThreshold->setText(sPixelThreshold.str().c_str());


}

findCirclesApplication::~findCirclesApplication()
{

}

void findCirclesApplication::on_bthSetPath_clicked()
{
	//����ͼ�����һ��Ŀ¼
	QString imgPath = QFileDialog::getExistingDirectory(this, GBK::ToUnicode("����ͼ���·��"), "D:/ImgFiles/", QFileDialog::Option::ShowDirsOnly);
	QDir dir(imgPath);
	QStringList nameFilters;
	nameFilters << "*.jpg";
	dir.setNameFilters(nameFilters);
	dir.setSorting(QDir::Name);

	//��ȡ·����ͼ�����б�
	imgNameList = dir.entryList();
	QString tem = imgPath;
	tem = tem + "/";
	for (int i = 0; i < imgNameList.size();i++)
	{
		imgNameList[i].prepend(tem);
	}
	std::stringstream str;
	str << imgNameList.size();
	ui.editTotalNum->setText(str.str().c_str());

	ui.btnReadImg->setEnabled(true);
}

void findCirclesApplication::on_btnReadImg_clicked()
{
	pixmap = new QPixmap(imgNameList[imgNum]);
	ui.ImgLabel ->setPixmap(*pixmap);
	imgWidth = pixmap->width();
	imgHeight = pixmap->height();

	drawImg = cv::imread(imgNameList[imgNum].toStdString(), CV_LOAD_IMAGE_COLOR);
	cvtColor(drawImg, grayImg, CV_BGR2GRAY);

	stringstream PicNum;
	int PicNumber = imgNum + 1;
	PicNum << PicNumber;
	ui.editImgNum->setText(PicNum.str().c_str());

	ui.btnNextImg->setEnabled(true);
	ui.btnToDetectSampleImgs->setEnabled(true);

}

void findCirclesApplication::on_btnNextImg_clicked()
{
	//�����ʾ�����lineEdit����
	ui.editResult->clear();

	imgNum++;
	pixmap = new QPixmap(imgNameList[imgNum]);
	ui.ImgLabel->setPixmap(*pixmap);
	imgWidth = pixmap->width();
	imgHeight = pixmap->height();

	drawImg = cv::imread(imgNameList[imgNum].toStdString(), CV_LOAD_IMAGE_COLOR);
	cvtColor(drawImg, grayImg, CV_BGR2GRAY);

	stringstream NextImg;
	int imgNumber = imgNum + 1;
	NextImg << imgNumber;
	ui.editImgNum->setText(NextImg.str().c_str());

	imgNum++;
	//�ж�ͼƬ�Ƿ����
	if (imgNum==imgNameList.size())
	{
		ui.btnNextImg->setEnabled(false);
	}
	imgNum--;
}

void findCirclesApplication::on_btnSetThresholdValue_clicked()
{
	QString mString = ui.editThresholdValue->text();
	nThreshold = mString.toInt();
}

void findCirclesApplication::on_btnPixelThreshold_clicked()
{
	QString mString = ui.editPixelThreshold->text();
	nPixelThreshold = mString.toInt();
}



void findCirclesApplication::on_btnToDetectSampleImgs_clicked()
{
	//�Դ���ͼƬ���б��ݵ�һ��Mat��
	Mat img;
	grayImg.copyTo(img);
	//��ͼ�н����Ĳ�����ȫ����ֵΪ0 Ҳ���Ǵ�Բ�ߵĵط�ȫ�����¸�ֵΪ0
	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++)
		{
			int value = img.at<uchar>(i, j);
			if (value>=nPixelThreshold)
			{
				img.at<uchar>(i, j) = 0;
			}
		}
	}
	//��ֵ�� ֮���Դ������ֵ��ֵΪ255 Ҳ����СԲ�ߴ����ĵط�
	Mat img_threshold;
	threshold(img, img_threshold,nThreshold, 255, CV_THRESH_BINARY);
	//imwrite("./PicsDetected/1/img_threshold.bmp", img_threshold);

	//���µ�ͼƬ�����������
	vector<vector<cv::Point>> contoursOrigin;
	vector<cv::Vec4i> hierarchy;
	findContours(img_threshold, contoursOrigin, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	if (!contoursOrigin.size())
	{
		return;
	}
	else
	{
		//�����������������1��������ΪСԲ��
		for (int i = 0; i < contoursOrigin.size(); i++)
		{
			if (contoursOrigin[i].size() >= 1&&contoursOrigin[i].size()<=5)
			{
				nLittleCircle++;
			}
			else
			{
				continue;
			}
		}
	}

	//����ʾ�����lineEdit����ʾ�����

	stringstream result;
	result << nLittleCircle;
	ui.editResult->setText(result.str().c_str());

	nLittleCircle = 0;
    

}

void findCirclesApplication::on_btnExit_clicked()
{

	exit(0);

}