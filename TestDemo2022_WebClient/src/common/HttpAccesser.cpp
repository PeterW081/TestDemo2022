#include "HttpAccesser.h"

#include <QException>
#include <QEventLoop>
#include <QTimer>

namespace CppDefine
{
	extern inline const int http_request_waiting_time = 16 * 1000;
};

HttpAccesser::HttpAccesser(HttpHandle* manager)
	: QObject(manager != nullptr ? manager->parent() : nullptr)
	, handle(manager)
{
}

QString HttpAccesser::request(HttpMethod method, QUrl const& path) const
{
	/// func_head
	HttpRequest request;
	HttpResponse response;

	/// request
	request.method = method;
	request.path   = path;

	/// request -> response
	this->request(&request, &response);
	if (response.status != 200)
	{
		throw QException();
	}

	/// func_tail
	return response.body;
}

int HttpAccesser::request(HttpRequest* request, HttpResponse* response) const
{
	QNetworkRequest request_qt;
	QNetworkReply* response_qt = nullptr;

	/// request_qt.path
	QUrl path = request->path;
	request_qt.setUrl(path);

	/// response_qt
	switch (request->method)
	{
		case HttpMethod::get:
			response_qt = this->handle->get(request_qt);
			break;
		default:
			return -1;
	}

	/// response_qt, finish or timeout,
	QEventLoop blocker;
	QTimer::singleShot(CppDefine::http_request_waiting_time, &blocker, &QEventLoop::quit);
	this->connect(response_qt, &QNetworkReply::finished, &blocker, &QEventLoop::quit);
	blocker.exec(); // block until finish
	if (!response_qt->isFinished())
	{
		response_qt->abort();
		response_qt->deleteLater();
		return -1;
	}
	if (response_qt->error() != QNetworkReply::NoError)
	{
		qDebug() << "reply error: " << response_qt->error();
	}

	/// response
	response->status = response_qt->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	response->body	 = response_qt->readAll();

	/// return
	return response->status;
}
