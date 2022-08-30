#pragma once

#include <QUrl>
#include "../common/HttpAccesser.h"
#include "../common/WebSocketClient.h"

namespace project::Led
{
	inline QString HttpApiHost			   = "http://test_server:8080";
	inline QString WebSocketHost		   = "ws://test_server:8080";
	inline QString HttpApi_Led04_read	   = HttpApiHost + "/led04";
	inline QString HttpApi_Led04_write_on  = HttpApiHost + "/led04/on";
	inline QString HttpApi_Led04_write_off = HttpApiHost + "/led04/off";
	inline QString WebSocket_Led04_read	   = WebSocketHost + "/led04/ws_read";
}

class Led
	: public QObject
{
	Q_OBJECT

  public:
	enum EnumStatus
	{
		on,
		off,
	};

  private:
	QUrl HttpApi_Led04_read		 = QUrl(project::Led::HttpApi_Led04_read);
	QUrl HttpApi_Led04_write_on	 = QUrl(project::Led::HttpApi_Led04_write_on);
	QUrl HttpApi_Led04_write_off = QUrl(project::Led::HttpApi_Led04_write_off);
	QUrl WebSocket_Led04_read	 = QUrl(project::Led::WebSocket_Led04_read);

  private:
	HttpAccesser::HttpHandle handle;
	HttpAccesser access			   = HttpAccesser(&handle);
	WebSocketClient* daemon_status = nullptr;

  private:
	EnumStatus set(EnumStatus);

  signals:
	void signal_OnStatus(Led::EnumStatus);
	void signal_OnStatusError();

  private slots:
	void slot_OnStatus(QString);

  public:
	Led() = default;
	EnumStatus get_status();
	EnumStatus set_on();
	EnumStatus set_off();
	void activate_daemon_status();
	void disActivate_daemon_status();
};

Led::EnumStatus inline Led::set_on()
{
	return this->set(Led::EnumStatus::on);
};

Led::EnumStatus inline Led::set_off()
{
	return this->set(Led::EnumStatus::off);
};
