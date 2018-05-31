#include "mw.h"
#include "ui_mw.h"

#include <QTime>
#include <QDebug>
#include "rand_alg.h"
//------------------------------------------------------------------------------
#define QPRINT_VAL(__val) {qDebug()<<#__val<<":"<<__val;}
//------------------------------------------------------------------------------
MW::MW(QWidget *parent) : QMainWindow(parent), ui(new Ui::MW) , RollClick(false)
{
	ui->setupUi(this);

	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	TimerCount = startTimer(50);
	TimerDisp = startTimer(100);

	ui->QLWSelect->addItems(QStringList()<<"Mode0"<<"Mode1"<<"Mode2");
	ui->QLWSelect->setCurrentRow(2);

	//
	int RMin = ui->QLEMin->text().toInt();
	RollCount = RMin;
	QString text = QString("%1").arg(RollCount);
	ui->QLInfo->setText(text);


	RandAlg_TestLoop();
}
//------------------------------------------------------------------------------
MW::~MW()
{
	delete ui;
}
//------------------------------------------------------------------------------
int MW::randInt(int low, int high)
{
	return rand() % ((high + 1) - low) + low;
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

				if(RollCount < RMax) {
					RollCount++;
				} else {
					RollCount = RMin;
				}

				QPRINT_VAL(RollCount);

				SetCountDisp(RollCount);

				if(RollNum == RollCount) {
					RollClick = false;
					ui->QPBRoll->setDisabled(false);
				}
		}

	} else if (CurrMode == 1) {
		//Режим пожожий на выше описанный учитывает направление счета
		if(RollClick == true) {

			if(RollCount < RollNum) {
				RollCount++;
			} else if(RollCount > RollNum) {
				RollCount--;
			}

			SetCountDisp(RollCount);
			if(RollNum == RollCount) {
				RollClick = false;
				ui->QPBRoll->setDisabled(false);
			}
		}
		//Режим с затухающей скоростью (не готово).
	} else if(CurrMode == 2) {
		if(RollClick == true) {

			int RMin = ui->QLEMin->text().toInt();
			int RMax = ui->QLEMax->text().toInt();


			//SetCountDisp(RollCount / );

			static int id_tmp = 0;
			static int id = 0;

			if(id >= id_tmp) {

				id = 0;
				int rand = RandAlg_Step(RandAlg_Get(),&id_tmp);
				SetCountDisp(rand);

				printf("Rand:%i id:%i\n",rand,id_tmp);
				fflush(stdout);
			} else {
				id++;
			}

			if(id_tmp < 0) {

				RollClick = false;
				ui->QPBRoll->setDisabled(false);
			}
		}
	}
}
//------------------------------------------------------------------------------
void MW::on_QPBClean_clicked()
{
	int RMin = ui->QLEMin->text().toInt();
	RollCount = RMin;
	QString text = QString("%1").arg(RollCount);
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
	RollDelta = RMax - RMin;
	RollCycle = 5;

	RollCount = RollDelta * RollCycle + RollNum;

	RollCycleSwitch = RollCount / 2;

	RandAlg_TestInit();
	RandAlg* ra = RandAlg_Get();
	RandAlg_SetMinMax(ra,RMin,RMax);

	ui->QPBRoll->setDisabled(true);
}
//------------------------------------------------------------------------------
