#include "bankui.h"
#include "./ui_bankui.h"

#include "CoinBank.h"
#include "DollarBank.h"

using namespace std;

BankUI::BankUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BankUI)
{
    ui->setupUi(this);
    myBank = new Bank;

    // Hide the "main" screen elements on startup
    ui->comboDepositType->setVisible(false);
    ui->comboWithdrawType->setVisible(false);
    ui->labelDelete->setVisible(false);
    ui->labelDeposit->setVisible(false);
    ui->labelDepositAmount->setVisible(false);
    ui->labelDepositQuantity->setVisible(false);
    ui->labelFunctionsHelp->setVisible(false);
    ui->labelWithdraw->setVisible(false);
    ui->labelWithdrawAmount->setVisible(false);
    ui->labelWithdrawQuantity->setVisible(false);
    ui->lineDepositAmount->setVisible(false);
    ui->lineDepositQuantity->setVisible(false);
    ui->lineWithdrawAmount->setVisible(false);
    ui->lineWithdrawQuantity->setVisible(false);
    ui->pushDelete->setVisible(false);
    ui->pushDepositConfirm->setVisible(false);
    ui->pushWithdrawConfirm->setVisible(false);
    ui->textContents->setVisible(false);
    ui->textLog->setVisible(false);
    ui->labelContents->setVisible(false);
    ui->labelLog->setVisible(false);
    ui->labelBank->setVisible(false);
}

BankUI::~BankUI()
{
    delete ui;
}

void BankUI::on_pushBankType_clicked()
{
    // Hide the "choose bank" screen elements
    ui->comboBankType->setVisible(false);
    ui->labelBankDescriptions->setVisible(false);
    ui->labelBankType->setVisible(false);
    ui->pushBankType->setVisible(false);

    // Show the "main" screen elements
    ui->comboDepositType->setVisible(true);
    ui->comboWithdrawType->setVisible(true);
    ui->labelDelete->setVisible(true);
    ui->labelDeposit->setVisible(true);
    ui->labelDepositAmount->setVisible(true);
    ui->labelFunctionsHelp->setVisible(true);
    ui->labelWithdraw->setVisible(true);
    ui->labelWithdrawAmount->setVisible(true);
    ui->lineDepositAmount->setVisible(true);
    ui->lineWithdrawAmount->setVisible(true);
    ui->pushDelete->setVisible(true);
    ui->pushDepositConfirm->setVisible(true);
    ui->pushWithdrawConfirm->setVisible(true);
    ui->textContents->setVisible(true);
    ui->textLog->setVisible(true);
    ui->labelContents->setVisible(true);
    ui->labelLog->setVisible(true);
    ui->labelBank->setVisible(true);

    // Set the "main" screen ComboBox indexes to 0
    ui->comboDepositType->setCurrentIndex(0);
    ui->comboWithdrawType->setCurrentIndex(0);

    // Create a Bank type based on the QComboBox
    QString s = ui->comboBankType->currentText();
    delete myBank;

    if (s == "Bank"){
        myBank = new Bank;
        ui->labelBank->setText("Your bank can accept both dollars and coins.");
    }

    else if (s == "Coin Bank"){
        myBank = new CoinBank;
        ui->labelBank->setText("Your bank can only accept coins.");
    }

    else if (s == "Dollar Bank"){
        myBank = new DollarBank;
        ui->labelBank->setText("Your bank can only accept dollars.");
    }
}

void BankUI::on_pushDelete_clicked()
{
    // Hide the "main" screen elements
    ui->comboDepositType->setVisible(false);
    ui->comboWithdrawType->setVisible(false);
    ui->labelDelete->setVisible(false);
    ui->labelDeposit->setVisible(false);
    ui->labelDepositAmount->setVisible(false);
    ui->labelDepositQuantity->setVisible(false);
    ui->labelFunctionsHelp->setVisible(false);
    ui->labelWithdraw->setVisible(false);
    ui->labelWithdrawAmount->setVisible(false);
    ui->labelWithdrawQuantity->setVisible(false);
    ui->lineDepositAmount->setVisible(false);
    ui->lineDepositQuantity->setVisible(false);
    ui->lineWithdrawAmount->setVisible(false);
    ui->lineWithdrawQuantity->setVisible(false);
    ui->pushDelete->setVisible(false);
    ui->pushDepositConfirm->setVisible(false);
    ui->pushWithdrawConfirm->setVisible(false);
    ui->textContents->setVisible(false);
    ui->textLog->setVisible(false);
    ui->labelContents->setVisible(false);
    ui->labelLog->setVisible(false);
    ui->labelBank->setVisible(false);

    // Delete old contents and log
    ui->textContents->setText("");
    ui->textLog->setText("");

    // Show the "choose bank" screen elements
    ui->comboBankType->setVisible(true);
    ui->labelBankDescriptions->setVisible(true);
    ui->labelBankType->setVisible(true);
    ui->pushBankType->setVisible(true);

    // Set the "choose bank" screen ComboBox index to 0
    ui->comboBankType->setCurrentIndex(0);

    // Delete the existing bank
    delete myBank;
    myBank = new Bank;
}

void BankUI::on_comboDepositType_activated(int index)
{
    QString s = ui->comboDepositType->currentText();

    // Hide the Quantity section
    if (s == "Direct Amount"){
        ui->labelDepositQuantity->setVisible(false);
        ui->lineDepositQuantity->setVisible(false);
        ui->labelDepositAmount->setText("Amount:");
    }
    // Show the Quantity section
    else if (s == "Quantity"){
        ui->labelDepositQuantity->setVisible(true);
        ui->lineDepositQuantity->setVisible(true);
        ui->labelDepositAmount->setText("Value:");
    }
}

void BankUI::on_comboWithdrawType_activated(int index)
{
    QString s = ui->comboWithdrawType->currentText();

    // Hide the Quantity section
    if (s == "Direct Amount"){
        ui->labelWithdrawQuantity->setVisible(false);
        ui->lineWithdrawQuantity->setVisible(false);
        ui->labelWithdrawAmount->setText("Amount:");
    }
    // Show the Quantity section
    else if (s == "Quantity"){
        ui->labelWithdrawQuantity->setVisible(true);
        ui->lineWithdrawQuantity->setVisible(true);
        ui->labelWithdrawAmount->setText("Value:");
    }
}

void BankUI::on_pushDepositConfirm_clicked()
{
    // Convert all relevant information to strings
    QString s = ui->comboDepositType->currentText();
    QString amountQS = ui->lineDepositAmount->text();
    QString quantityQS = ui->lineDepositQuantity->text();
    string reportC;
    string reportT;

    // Convert inputs to double/int
    double amount = amountQS.toDouble();
    int quantity = quantityQS.toInt();

    // Use the deposit method that corresponds to the ComboBox
    if (s == "Direct Amount") {
        myBank->deposit(amount, reportT);
    }
    else if (s == "Quantity"){
        myBank->deposit(amount, quantity, reportT);
    }

    // Clear the user's input
    ui->lineDepositAmount->clear();
    ui->lineDepositQuantity->clear();

    // Print the changes made
    myBank->print(reportC);
    ui->textContents->setPlainText(QString(reportC.c_str()));
    ui->textLog->insertPlainText(QString(reportT.c_str()));
}


void BankUI::on_pushWithdrawConfirm_clicked()
{
    // Convert all relevant information to strings
    QString s = ui->comboWithdrawType->currentText();
    QString amountQS = ui->lineWithdrawAmount->text();
    QString quantityQS = ui->lineWithdrawQuantity->text();
    string reportC;
    string reportT;

    // Convert inputs to double/int
    double amount = amountQS.toDouble();
    int quantity = quantityQS.toInt();

    // Use the withdraw method that corresponds to the ComboBox
    if (s == "Direct Amount") {
        myBank->withdraw(amount, reportT);
    }
    else if (s == "Quantity"){
        myBank->withdraw(amount, quantity, reportT);
    }

    // Clear the user's input
    ui->lineWithdrawAmount->clear();
    ui->lineWithdrawQuantity->clear();

    // Print the changes made
    myBank->print(reportC);
    ui->textContents->setPlainText(QString(reportC.c_str()));
    ui->textLog->insertPlainText(QString(reportT.c_str()));
}

