#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    m_isLoggedIn = false;
    m_jwtToken = "";
    m_username = "";
    m_password = "";
}

QString MainController::getUsername()
{
    return QString("tulm");
}

void MainController::userLogin(const QString& u, const QString& p)
{
    if (u.isNull() || p.isNull() || p.isEmpty() || u.isEmpty())
    {
        return;
    }
    doAuthenticate(u, p);
}

bool MainController::isUserLoggedIn()
{
    return m_isLoggedIn;
}

// SLOTS: authenticating
void MainController::doAuthenticate(const QString &u, const QString &p)
{
    // Encrypting password before request
    m_username = u;
    m_password = QString(QCryptographicHash::hash(p.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    // Build JSON request body
    QJsonObject bodyJsonObj;
    bodyJsonObj.insert("username", u);
    bodyJsonObj.insert("password", m_password);
    QJsonDocument bodyJsonDoc(bodyJsonObj);

    // Building request
    QNetworkRequest request;
    request.setUrl(QUrl(AUTHEN_URL));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *restClient = new QNetworkAccessManager(this);
    connect(restClient, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthenticateDone(QNetworkReply*)), Qt::UniqueConnection);
    restClient->post(request, bodyJsonDoc.toJson());
}

// SLOTS: when authenticate done
void MainController::onAuthenticateDone(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // Cannot error to service api
    if (!(statusCode.isValid() && reply->canReadLine()))
    {
        emit login(-1, "Cannot connect to server");
        reply->deleteLater();
        return;
    }

    if(statusCode.isValid() && statusCode.value<int>() == 400)
    {
        emit login(0, "Login fail");
    }
    else if(statusCode.value<int>() == 200)
    {
        QByteArray resData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(resData);
        QJsonObject jsonObject = jsonDoc.object();
        this->m_jwtToken = jsonObject["token"].toString();
        emit login(1, this->m_jwtToken);
    }
    reply->deleteLater();
}
