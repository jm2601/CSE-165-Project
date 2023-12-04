#ifndef BANKUI_H
#define BANKUI_H

#include "CoinBank.h"
#include "DollarBank.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BankUI;
}
QT_END_NAMESPACE

class BankUI : public QMainWindow
{
    Q_OBJECT

public:
    BankUI(QWidget *parent = nullptr);
    ~BankUI();

private slots:
    void on_pushBankType_clicked();

    void on_pushDelete_clicked();

    void on_comboDepositType_activated(int index);

    void on_comboWithdrawType_activated(int index);

    void on_pushDepositConfirm_clicked();

    void on_pushWithdrawConfirm_clicked();

private:
    Ui::BankUI *ui;
    Bank *myBank;
};
#endif // BANKUI_H
