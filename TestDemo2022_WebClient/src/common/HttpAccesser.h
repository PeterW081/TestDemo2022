#pragma once

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

namespace Class::HttpAccesser
{
	enum HttpMethod
	{
		get = 0,
	};
	struct HttpRequest
	{
		HttpMethod method;
		QUrl path;
	};
	struct HttpResponse
	{
		int status = -1;
		QByteArray body;
	};
}

class HttpAccesser
	: public QObject
{
	Q_OBJECT

  public:
	using HttpHandle   = QNetworkAccessManager;
	using HttpMethod   = Class::HttpAccesser::HttpMethod;
	using HttpRequest  = Class::HttpAccesser::HttpRequest;
	using HttpResponse = Class::HttpAccesser::HttpResponse;

  public:
	explicit HttpAccesser(HttpHandle* handle);
	HttpAccesser(QObject* parent, HttpHandle* handle);

  public:
	QString request(HttpMethod method, QUrl const& path) const;

  private:
	HttpHandle* handle;
	int request(HttpRequest* request, HttpResponse* response) const;

  protected:
	auto const& get_handle() { return handle; };
};
