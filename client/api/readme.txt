Dokumentaatio JsonAPI/JsonRequestController
# Abstraktio HTTP-pyyntöjen lähettämiseen palvelimen rajapinnalle
# Objekti luokasta on paketoitu DataRequestControlleriin, joten suora käyttö ei ole tarpeellista.

Rajapinta:
	request(int id, int type, QString endPoint, QString apiKey, QString params)
	- id: 		pyynnön id, jonka perusteella se käsitellään
	- type:		1 = GET, 2 = POST
	- endPoint:	url-osoite johon pyyntö lähetetään
	- apiKey:	avain tunnistautumista varten, sijaitsee pyynnön headerissa(ApiKey)
	- params:	pyynnön sisältö, GET: suoraan osoitteeseen ?param=content, POST: pyynnön sisältöön

Signaalit:
	requestError(int code, QString msg)
	- code:		virhekoodi
	- msg:		QNetworkAccessManagerin virheilmoitus

	requestComplete(int id, QString response)
	- id:		pyynnön id
	- response:	vastauksen sisältö tekstinä

* Julkisia slotteja ei ole.

Dokumentaatio JsonAPI/DataRequestController

TULOSSA