#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>

#include <QtWidgets>

class mainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mainWidget(QWidget *parent = nullptr);

private:
    QLabel *firstNameLabel;
    QLineEdit *firstName;

    QHBoxLayout *firstNameLayout;

    QLabel *lastNameLabel;
    QLineEdit *lastName;

    QHBoxLayout *lastNameLayout;

    QPushButton *submitButton;

    QLabel *result;
    QVBoxLayout *main_layout;


public slots:
    void concatenate_method();
};

#endif // MAINWIDGET_H
