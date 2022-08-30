#pragma once

#include <QWebSocket>

class WebSocketClient
	: public QObject
{
	Q_OBJECT
  private:
	QWebSocket websocket;

  signals:
	void signal_onClose();
	void signal_onMessage(const QString& message);

  public:
	WebSocketClient(QObject* parent, QUrl const& path);
	void close();
	bool isClose();
	bool isValid();
};
