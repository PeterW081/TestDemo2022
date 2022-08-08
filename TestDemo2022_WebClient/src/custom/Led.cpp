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
