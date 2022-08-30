#include "WebSocketClient.h"

#include <QEventLoop>
#include <QTimer>
#include <functional>

namespace CppDefine
{
	extern inline const int http_request_waiting_time = 16 * 1000;
};

WebSocketClient::WebSocketClient(QObject* parent, QUrl const& path)
	: QObject(parent)
{
	this->connect(&this->websocket, &QWebSocket::disconnected, this, &WebSocketClient::signal_onClose);
	this->connect(&this->websocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::signal_onMessage);
	///
	websocket.open(path);
	QEventLoop blocker;
	QTimer::singleShot(CppDefine::http_request_waiting_time, &this->websocket, std::bind(&QWebSocket::close, &this->websocket, QWebSocketProtocol::CloseCodeNormal, QString()));
	this->connect(&this->websocket, &QWebSocket::connected, &blocker, &QEventLoop::quit);
	this->connect(&this->websocket, &QWebSocket::disconnected, &blocker, &QEventLoop::quit);
	blocker.exec();
}

void WebSocketClient::close()
{
	this->websocket.close();
}

bool WebSocketClient::isValid()
{
	return this->websocket.isValid();
}

bool WebSocketClient::isClose()
{
	return this->websocket.state() == QAbstractSocket::SocketState::UnconnectedState;
}
