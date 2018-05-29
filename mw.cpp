#include "mw.h"
#include "ui_mw.h"

#include <QTime>
#include <QDebug>
//------------------------------------------------------------------------------
#define QPRINT_VAL(__val) {qDebug()<<#__val<<":"<<__val;}
//------------------------------------------------------------------------------
MW::MW(QWidget *parent) : QMainWindow(parent), ui(new Ui::MW) , RollClick(false)
{
	ui->setupUi(this);

	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	TimerCount = startTimer(10);
	TimerDisp = startTimer(100);

	ui->QLWSelect->addItems(QStringList()<<"Mode0"<<"Mode1"<<"Mode2");
	ui->QLWSelect->setCurrentRow(0);

	//
	int RMin = ui->QLEMin->text().toInt();
	Count = RMin;
	QString text = QString("%1").arg(Count);
	ui->QLInfo->setText(text);

}
//------------------------------------------------------------------------------
MW::~MW()
{
	delete ui;
}
//------------------------------------------------------------------------------
int MW::randInt(int low, int high)
{
	return qrand() % ((high + 1) - low) + low;
}
//------------------------------------------------------------------------------
void MW::timerEvent(QTimerEvent *te)
{
	int tid = te->timerId();
	if(tid == TimerCount) {
		TimerEventCount(te);
	} else if(tid == TimerDisp ) {
		TimerEventDisp(te);
	}
}
//------------------------------------------------------------------------------
void MW::SetCountDisp(int count)
{
	CountDisp = count;
	UpdateDisp = true;
}
//------------------------------------------------------------------------------
void MW::TimerEventDisp(QTimerEvent *te)
{
	Q_UNUSED(te);
	if(UpdateDisp == true) {
		qDebug()<<"UpdateDisp == true";
		ui->QLInfo->setText(QString("%1").arg(CountDisp));
		UpdateDisp = false;
	}
}
//------------------------------------------------------------------------------
void MW::TimerEventCount(QTimerEvent *te)
{
	Q_UNUSED(te);
	int CurrMode = ui->QLWSelect->currentRow();
	if(CurrMode == 0) {
		//Простой режим считает вверх до нахождения числа, при превышении сбрасывается в RMin
		//Skip фрейма
		if(RollClick == true) {

				int RMin = ui->QLEMin->text().toInt();
				int RMax = ui->QLEMax->text().toInt();

				if(Count < RMax) {
					Count++;
				} else {
					Count = RMin;
				}

				QPRINT_VAL(Count);

				SetCountDisp(Count);

				if(RollNum == Count) {
					RollClick = false;
					ui->QPBRoll->setDisabled(false);
				}
		}

	} else if (CurrMode == 1) {
		//Режим пожожий на выше описанный учитывает направление счета
		if(RollClick == true) {

			if(Count < RollNum) {
				Count++;
			} else if(Count > RollNum) {
				Count--;
			}

			SetCountDisp(Count);
			if(RollNum == Count) {
				RollClick = false;
				ui->QPBRoll->setDisabled(false);
			}
		}
		//Режим с затухающей скоростью (не готово).
	} else if(CurrMode == 2) {
		if(RollClick == true) {

			static int speed;
			const int count_max = 20;
			static int count;

			static bool first = true;

			if(first) {
				first = false;
				speed = 10;
				count = 0;
				qDebug()<<"first";
			}

			int RMin = ui->QLEMin->text().toInt();
			int RMax = ui->QLEMax->text().toInt();

			//for(int s=0;s<speed+1;s++) {
				if(Count < RMax) {
					Count++;
				} else {
					Count = RMin;
				}
			//}

			if(count < count_max) {
				count++;
			} else {
				count=0;
				if(speed > 0)
					speed--;
			}

			//QPRINT_VAL(speed);
			QPRINT_VAL(Count);
			QPRINT_VAL(RollNum);

			SetCountDisp(Count);
			if(RollNum == Count && speed == 0) {
				qDebug()<<"RollNum == Count && speed == 0";
				RollClick = false;
				first = true;
				ui->QPBRoll->setDisabled(false);
			}
		}
	}
}
//------------------------------------------------------------------------------
void MW::on_QPBClean_clicked()
{
	int RMin = ui->QLEMin->text().toInt();
	Count = RMin;
	QString text = QString("%1").arg(Count);
	ui->QLInfo->setText(text);
}
//------------------------------------------------------------------------------
void MW::on_QPBRoll_clicked()
{
	int RMin = ui->QLEMin->text().toInt();
	int RMax = ui->QLEMax->text().toInt();
	int randomValue = randInt(RMin,RMax);
	//Count = RMin;
	QPRINT_VAL(randomValue);
	RollNum = randomValue;
	RollClick = true;
	ui->QPBRoll->setDisabled(true);
}
//------------------------------------------------------------------------------
