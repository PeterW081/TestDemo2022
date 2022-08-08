#pragma once

#include <QLabel>

class Label : public QLabel
{
	Q_OBJECT

  public:
	explicit Label(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

  signals:
	void clicked();

  protected:
	void mouseReleaseEvent(QMouseEvent* ev);
};
