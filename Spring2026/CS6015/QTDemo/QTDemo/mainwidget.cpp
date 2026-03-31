

#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent) : QWidget{parent} {
    firstNameLabel = new QLabel("First Name");
    firstName = new QLineEdit();
    lastNameLabel = new QLabel("Last Name");
    lastName = new QLineEdit();

    submitButton = new QPushButton("Concatenate");

    result = new QLabel("Waiting...");

    main_layout = new QVBoxLayout();

    firstNameLayout = new QHBoxLayout();
    firstNameLayout->addWidget(firstNameLabel);
    firstNameLayout->addWidget(firstName);

    lastNameLayout = new QHBoxLayout();
    lastNameLayout->addWidget(lastNameLabel);
    lastNameLayout->addWidget(lastName);

    main_layout->addLayout(firstNameLayout);
    main_layout->addLayout(lastNameLayout);
    main_layout->addWidget(submitButton);
    main_layout->addWidget(result);

    setLayout(main_layout);

    connect(submitButton, &QPushButton::clicked, this, &mainWidget::concatenate_method);
}

void mainWidget::concatenate_method(){
    result->setText(firstName->text() + " " + lastName->text());
    //OR (keeping both for reference)
    //QString *str = new QString();
    //... lol didn't finish
}
