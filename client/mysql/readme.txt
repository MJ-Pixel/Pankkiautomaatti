DLLMySQL

bool connectToDb();
- Returns true or false depending on if connection could be made or not

bool login(QString cardid, QString pin);
- Use DLLSarjaPortti::readCard() or insert card's TAG manually (0B0035CD90)

bool withdraw(double amount);
- Returns true or false depending on if the withdraw could be made successfully

bool payment(DLLMySQL::PaymentInfo info);
- Returns true if the depending on if the payment could be made successfully

Struct:
    info.type // int
    info.amount // double
    info.name // QString
    info.iban // QString of 11 characters, for example: "12345678910"
    info.bicc = // QString of 4, for example: "1234"
    info.message = // QString

QVector<QString> specificEvents(QString dateStart, QString dateEnd);
- Give parameters as "YYYY-MM-DD" including the quotes
- If you want to list events from one day, set dateEnd as the following day

QVector<QString> events();
- Returns last 10 events from the user that's logged in

QString balance();
- Returns user's balance
