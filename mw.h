#ifndef MW_H
#define MW_H

#include <QMainWindow>

namespace Ui {
class MW;
}

class MW : public QMainWindow
{
	Q_OBJECT

public:
	explicit MW(QWidget *parent = 0);
	~MW();

	int randInt(int low, int high);

	void timerEvent(QTimerEvent *te);

	void TimerEventDisp(QTimerEvent *te);
	void TimerEventCount(QTimerEvent *te);

	void SetCountDisp(int count);


private slots:
	void on_QPBClean_clicked();
	void on_QPBRoll_clicked();

private:
	Ui::MW *ui;
	bool RollClick;
	int RollNum;		//Сген. число
	int RollDelta;		//Дельта мин и мах значения рандома
	int RollCount;		//Текушее число сравнивается с RollNum

	int RollCycle;		//3 режим кол-во циклов
	int RollCycleSwitch;//число при котором изменяется скорость

	int TimerDisp;
	int CountDisp;
	bool UpdateDisp;
	int TimerCount;


};

#endif // MW_H
