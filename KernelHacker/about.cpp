//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "about.hpp"
#include "ui_about.h"

About::About(QWidget *parent) : QWidget(parent), ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
