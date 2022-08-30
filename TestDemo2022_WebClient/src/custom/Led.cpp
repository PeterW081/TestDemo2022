#include "Led.h"

Led::EnumStatus extern inline convert_QString_EnumStatus(QString status_string)
{
	Led::EnumStatus status;
	if (status_string == "1")
	{
		status = Led::EnumStatus::on;
		goto mark_if_break;
	}
	if (status_string == "0")
	{
		status = Led::EnumStatus::off;
		goto mark_if_break;
	}
	throw std::exception();
mark_if_break:
	return status;
}

Led::EnumStatus Led::get_status()
{
	QString response = access.request(HttpAccesser::HttpMethod::get, this->HttpApi_Led04_read);
	return convert_QString_EnumStatus(response);
};

Led::EnumStatus Led::set(Led::EnumStatus status)
{
	QString response = "";
	switch (status)
	{
		default:
			break;
		case Led::EnumStatus::on:
			response = access.request(HttpAccesser::HttpMethod::get, this->HttpApi_Led04_write_on);
			break;
		case Led::EnumStatus::off:
			response = access.request(HttpAccesser::HttpMethod::get, this->HttpApi_Led04_write_off);
			break;
	}
	return convert_QString_EnumStatus(response);
};

void Led::slot_OnStatus(QString status)
{
	try
	{
		emit this->signal_OnStatus(convert_QString_EnumStatus(status));
	}
	catch (...)
	{
		emit this->signal_OnStatusError();
	}
}

void Led::activate_daemon_status()
{
	if (this->daemon_status != nullptr && !this->daemon_status->isClose())
	{
		return;
	} else
	{
		this->disActivate_daemon_status();
	}
	this->daemon_status = new WebSocketClient(this, this->WebSocket_Led04_read);
	this->connect(this->daemon_status, &WebSocketClient::signal_onMessage, this, &Led::slot_OnStatus);
};

void Led::disActivate_daemon_status()
{
	if (this->daemon_status != nullptr)
	{
		this->daemon_status->close();
		delete this->daemon_status;
		this->daemon_status = nullptr;
	}
};
