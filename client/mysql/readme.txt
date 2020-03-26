DLLMySql.dll

static QSqlDatabase& connectToDb();
- Checks that connection can be opened

static QSqlDatabase& login(int cardid, QString pin);
- Takes card's/user's ID and PIN-code and checks if there are corresponding data on the "kirjautuminen" table

static QSqlDatabase& withdraw(int cardid, double amount);
- Takes card's/user's ID and the amount to be withdrawn from the bank account, reads from database if there
are enough funds to complete the withdraw and updates the new balance if a withdraw is made.
