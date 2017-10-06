#pragma once

#include <QWidget>
#include "ui_about_popup.h"

class about_popup : public QWidget
{
	Q_OBJECT

public:
	about_popup(QWidget *parent = Q_NULLPTR);
	~about_popup();

private:
	Ui::about_popup ui;
};
