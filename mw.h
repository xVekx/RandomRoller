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
	int RollNum;

	int Count;

	int TimerDisp;
	int CountDisp;
	bool UpdateDisp;

	int TimerCount;
};

#endif // MW_H
