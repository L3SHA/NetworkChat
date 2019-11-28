#include "MyClient.h"
#include <QWidget>
#include <QMessageBox>

const QString MyClient::constNameUnknown = QString(".Unknown");

MyClient::MyClient(int desc, MyServer* serv, QObject* parent) :QObject(parent)
{
	//õðàíèèì óêàçàòåëü íà îáúåêò-ñåðâåð
	_serv = serv;
	//êëèåíò íå ïðîøåë àâòîðèçàöèþ
	_isAutched = false;
	_name = constNameUnknown;
	//ðàçìåð ïðèíèìàåìîãî áëîêà 0
	_blockSize = 0;
	//ñîçäàåì ñîêåò
	_sok = new QTcpSocket(this);
	//óñòàíàâëèâàåì äåñêðèïòîð èç incomingConnection()
	_sok->setSocketDescriptor(desc);
	//ïîäêëþ÷àåì ñèãíàëû
	connect(_sok, SIGNAL(connected()), this, SLOT(onConnect()));
	connect(_sok, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
	connect(_sok, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

	qDebug() << "Client connected" << desc;
}

MyClient::~MyClient()
{

}

void MyClient::onConnect()
{
	//never calls, socket already connected to the tcpserver
	//we just binding to this socket here: _sok->setSocketDescriptor(desc);
}

void MyClient::onDisconnect()
{
	qDebug() << "Client disconnected";
	//åñëè àâòîðèçîâàí
	if (_isAutched)
	{
		//óáèðèåì èç èíòåðôåéñà
		emit removeUserFromGui(_name);
		//ñîîáùàåì âñåì, ÷òî êëèåíò âûøåë
		_serv->doSendToAllUserLeft(_name);
		//óáèðàåì èç ñïèñêà
		emit removeUser(this);
	}
	deleteLater();
}

void MyClient::onError(QAbstractSocket::SocketError socketError) const
{
	//w íóæíà äëÿ îáñâîáîæäåíèÿ ïàìÿòè îò QMessageBox (ïîñðåäñòâîì *parent = &w)
	QWidget w;
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(&w, "Error", "The host was not found");
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information(&w, "Error", "The connection was refused by the peer.");
		break;
	default:
		QMessageBox::information(&w, "Error", "The following error occurred: " + _sok->errorString());
	}
	//òóò âûçîâóòñÿ äåñòðóêòîð w è ñîîòâåòñòâåííî QMessageBox (ïî ïðàâèëàì ñ++)
}

void MyClient::onReadyRead()
{
	QDataStream in(_sok);
	//åñëè ñ÷èòûâàåì íîâûé áëîê ïåðâûå 2 áàéòà ýòî åãî ðàçìåð
	if (_blockSize == 0) {
		//åñëè ïðèøëî ìåíüøå 2 áàéò æäåì ïîêà áóäåò 2 áàéòà
		if (_sok->bytesAvailable() < (int)sizeof(quint16))
			return;
		//ñ÷èòûâàåì ðàçìåð (2 áàéòà)
		in >> _blockSize;
		qDebug() << "_blockSize now " << _blockSize;
	}
	//æäåì ïîêà áëîê ïðèéäåò ïîëíîñòüþ
	if (_sok->bytesAvailable() < _blockSize)
		return;
	else
		//ìîæíî ïðèíèìàòü íîâûé áëîê
		_blockSize = 0;
	//3 áàéò - êîìàíäà ñåðâåðó
	quint8 command;
	in >> command;
	qDebug() << "Received command " << command;
	//äëÿ íåàâòîðèçîâàííûé ïîëüçîâàòåëåé ïðèíèìàåòñÿ òîëüêî êîìàíäà "çàïðîñ íà àâòîðèçàöèþ"
	if (!_isAutched && command != comAutchReq)
		return;

	switch (command)
	{
		//çàïðîñ íà àâòîðèçàöèþ
	case comAutchReq:
	{
		//ñ÷èòûâàåì èìÿ
		QString name;
		in >> name;
		//ïðîâåðÿåì åãî
		if (!_serv->isNameValid(name))
		{
			//îòïðàâëÿåì îøèáêó
			doSendCommand(comErrNameInvalid);
			return;
		}
		//ïðîâåðÿåì íå èñïîëüçóåòñÿ ëè èìÿ
		if (_serv->isNameUsed(name))
		{
			//îòïðàâëÿåì îøèáêó
			doSendCommand(comErrNameUsed);
			return;
		}
		//àâòîðèçàöèÿ ïðîéäåíà
		_name = name;
		_isAutched = true;
		//îòïðàâëÿåì íîâîìó êëèåíòó ñïèñîê àêòèâíûõ ïîëüçîâàòåëåé
		doSendUsersOnline();
		//äîáàâëÿåì â èíòåðôåéñ
		emit addUserToGui(name);
		//ñîîáùàåì âñåì ïðî íîâîãî ïîëçîâàòåëÿ
		_serv->doSendToAllUserJoin(_name);
	}
	break;
	//îò òåêóùåãî ïîëüçîâàòåëÿ ïðèøëî ñîîáùåíèå äëÿ âñåõ
	case comMessageToAll:
	{
		QString message;
		in >> message;
		//îòïðàâëÿåì åãî âñåì
		_serv->doSendToAllMessage(message, _name);
		//îáíîâëÿåì ëîã ñîáûòèé
		emit messageToGui(message, _name, QStringList());
	}
	break;
	//îò òåêóùåãî ïîëüçîâàòåëÿ ïðèøëî ñîîáùåíèå äëÿ íåêîòîðûõ ïîëüçîâàòåëåé
	case comMessageToUsers:
	{
		QString users_in;
		in >> users_in;
		QString message;
		in >> message;
		//ðàçáèâàåì ñòðîêó íà èìåíà
		QStringList users = users_in.split(",");
		//îòïðàâëÿåì íóæíûì
		_serv->doSendMessageToUsers(message, users, _name);
		//îáíîâëÿåì èíòåðôåéñ
		emit messageToGui(message, _name, users);
	}
	break;
	}

	//for (long long i = 0; i < 4000000000; ++i){}
}

void MyClient::doSendCommand(quint8 comm) const
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << (quint16)0;
	out << comm;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	_sok->write(block);
	qDebug() << "Send to" << _name << "command:" << comm;
}

void MyClient::doSendUsersOnline() const
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << (quint16)0;
	out << comUsersOnline;
	QStringList l = _serv->getUsersOnline();
	QString s;
	for (int i = 0; i < l.length(); ++i)
		if (l.at(i) != _name)
			s += l.at(i) + (QString)",";
	s.remove(s.length() - 1, 1);
	out << s;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	_sok->write(block);
	qDebug() << "Send user list to" << _name << ":" << s;
}