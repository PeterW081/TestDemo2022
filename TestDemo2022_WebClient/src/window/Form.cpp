#include "Form.h"
#include "ui_Form.h"

namespace Define::Form
{
	// clang-format off
	TupleClass_WidgetStyle_lab_status case_on	  = { "ON",        "background-color: rgb(0, 128, 0);    " };
	TupleClass_WidgetStyle_lab_status case_off	  = { "OFF",       "background-color: rgb(128, 128, 128);" };
	TupleClass_WidgetStyle_lab_status case_error  = { "ERROR",     "background-color: rgb(0, 0, 0);      " };
	TupleClass_WidgetStyle_lab_status case_loding = { "LODING...", "                                     " };
	// clang-format on
}

Form::Form(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Form)
{
	ui->setupUi(this);
	this->init();
	this->init_connect();
	QMetaObject::invokeMethod(
		this, [this]() -> void {
			emit this->signal_refresh();
		},
		Qt::QueuedConnection);
}

Form::~Form()
{
	delete ui;
}

void Form::init()
{
	this->refreshStatus(Define::Form::case_loding);
}

void Form::init_connect()
{
	auto ctrl_led = [this](Led::EnumStatus (Led::*operate)()) -> void {
		this->setDisabled(true);
		//		this->refreshStatus(Define::Form::case_loding);
		static Led led;
		TupleClass_WidgetStyle_lab_status style;
		try
		{
			switch ((led.*operate)())
			{
				case Led::EnumStatus::on:
					style = Define::Form::case_on;
					break;
				case Led::EnumStatus::off:
					style = Define::Form::case_off;
					break;
			}
		}
		catch (...)
		{
			style = Define::Form::case_error;
		}
		this->refreshStatus(style);
		this->setDisabled(false);
	};
	///
	// clang-format off
	this->connect(this, &Form::signal_refresh, this, std::bind(ctrl_led, &Led::get_status ));
	this->connect(this, &Form::signal_led_on , this, std::bind(ctrl_led, &Led::set_on     ));
	this->connect(this, &Form::signal_led_off, this, std::bind(ctrl_led, &Led::set_off    ));
	// clang-format off
	this->connect(this->ui->_btn01_on,   &QPushButton::clicked, this, &Form::signal_led_on  );
	this->connect(this->ui->_btn02_off,  &QPushButton::clicked, this, &Form::signal_led_off );
	this->connect(this->ui->_lab_status, &Label::clicked,       this, &Form::signal_refresh );
	// clang-format on
}

void Form::refreshStatus(TupleClass_WidgetStyle_lab_status style)
{
	this->ui->_lab_status->setText(std::get<TupleIndex_WidgetStyle_lab_status::text>(style));
	this->ui->_lab_status->setStyleSheet(std::get<TupleIndex_WidgetStyle_lab_status::style_sheet>(style));
}

void Form::closeEvent(QCloseEvent* event)
{
	QMetaObject::invokeMethod(
		this, [this]() -> void {
			emit this->signal_led_off();
			QApplication::instance()->quit();
		},
		Qt::QueuedConnection);
}
