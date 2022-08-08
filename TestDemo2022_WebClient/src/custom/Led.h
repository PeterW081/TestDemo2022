#pragma once

#include <QUrl>
#include "../common/HttpAccesser.h"

namespace project::Led
{
	inline QString HttpApiHost			   = "http://192.168.1.1:8080";
	inline QString HttpApi_Led04_read	   = HttpApiHost + "/led04";
	inline QString HttpApi_Led04_write_on  = HttpApiHost + "/led04/on";
	inline QString HttpApi_Led04_write_off = HttpApiHost + "/led04/off";
}

class Led
{
  private:
	QUrl HttpApi_Led04_read		 = QUrl(project::Led::HttpApi_Led04_read);
	QUrl HttpApi_Led04_write_on	 = QUrl(project::Led::HttpApi_Led04_write_on);
	QUrl HttpApi_Led04_write_off = QUrl(project::Led::HttpApi_Led04_write_off);

  private:
	HttpAccesser::HttpHandle handle;
	HttpAccesser access = HttpAccesser(&handle);

  public:
	enum EnumStatus
	{
		on,
		off,
	};

  private:
	EnumStatus set(EnumStatus);

  public:
	Led() = default;
	EnumStatus get_status();
	EnumStatus set_on();
	EnumStatus set_off();
};

Led::EnumStatus inline Led::set_on()
{
	return this->set(Led::EnumStatus::on);
};

Led::EnumStatus inline Led::set_off()
{
	return this->set(Led::EnumStatus::off);
};
