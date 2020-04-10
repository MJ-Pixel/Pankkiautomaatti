Page changes:
	Big pages:
		MainScreen(); //opens up the main the main screen
		LoginScreen(); //opens up the login screen
	
	Small pages:
		PaymentScreen(); //opens up the payment screen
		BalanceScreen(); //opens up the Balance screen
		WithdrawScreen(); //Opens up the withdraw scre

Buttons:
	EnablePayment();
	DisablePayment(); 
	EnableBalance();
	DisableBalance();
	EnableWithdraw();
	DisableWithdraw();  //all of theese enables or disables respective buttons.

	ButtonMadness(); //checks if 4 numbers have been put to password line edit and auto log in attempts if they have

	button presses:
		on_main_payment_button_clicked(); //runs PaymentScreen(), ClearPayment(), ClearWithdraw(), EnableBalance(), EnableWithdraw(), DisablePayment() funktions.
		on_payment_confirm_button_clicked(); //opens a message box asks for confirmation (and writes the info given in there), if pressed no allows you to continue, if pressed yes, moves to MainScreen();
		on_main_balance_button_clicked(); //runs BalanceScreen(), ClearPayment(), ClearWithdraw(), DisableBalance(), EnableWithdraw(), EnablePayment() funktions.
		on_main_withdraw_button_clicked();//runs WithdrawScreen(), ClearPayment(), ClearWithdraw(), EnableBalance(), DisableWithdraw(), EnablePayment() funktions.
		on_withdraw_confirm_button_clicked(); //opens a message box asks for confirmation (and writes the info given in there), if pressed no allows you to continue, if pressed yes, moves to MainScreen();
		on_login_login_button_clicked(); //(has no physical button) checks if login_password_line == 1234, if yes turns login=true, and runs LoginCheck()
		on_main_transaction_button_clicked(); /Currently does nothing
		on_login_mix_button_clicked(); //runs NumpadRandom() once, enables off button disables on button, turns on randomiser boolean
		on_login_reset_button_clicked(); //runs ResetNumpad(), enables on button, disables off button, turns randomiser boolean off.
		on_login_numpad_button(1-9)_clicked(); //puts a respective number into login_password_line, runs ButtonMadness(), checks if randomiser boolean is on, if on runs NumpadRandom().
		on_login_empty_button_clicked(); //Clears login_password_line

Other:

	int randInt(int low, int high); //gets a random number between low and high
	SetBalance(); //Sets balance value to balance screen and withdraw screen from variable balanceAmmount
	LoginCheck(); //checks if boolean login is true, if true runs MainScreen(), otherwise runs ErrorMessage()
	ResetNumpad(); //Resets a numpad into orignal positions
	NumpadRandom(); //randomises numpad
	ClearPayment(); //Clears the line edits in payment screen
	ClearWithdraw(); //Clears the line edits in withdraw screen
	ErrorMessage(); //gives a "Wrong Password!" message box
		