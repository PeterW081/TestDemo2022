#pragma once

#include <QWidget>
#include "../custom/Led.h"

namespace Ui
{
	class Form;
}

namespace Define::Form
{
	// clang-format off
	using TupleClass_WidgetStyle_lab_status = std::tuple<QString, QString>;
	enum  TupleIndex_WidgetStyle_lab_status
	{
		text,
		style_sheet,
	};
	// clang-format on
}

class Form : public QWidget
{
	Q_OBJECT

  public:
	explicit Form(QWidget* parent = nullptr);
	~Form();

  private:
	Ui::Form* ui;

  signals:
	void signal_led_on();
	void signal_led_off();
	void signal_refresh();

  private:
	Led* led;

  private:
	virtual void closeEvent(QCloseEvent*);

  private:
	using TupleClass_WidgetStyle_lab_status = Define::Form::TupleClass_WidgetStyle_lab_status;
	using TupleIndex_WidgetStyle_lab_status = Define::Form::TupleIndex_WidgetStyle_lab_status;
	void init();
	void init_connect();
	void refreshStatus(TupleClass_WidgetStyle_lab_status);
};
