//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <QWidget>

namespace Ui {
    class About;
}

class About : public QWidget
{
        Q_OBJECT
        
    public:
        explicit About(QWidget *parent = 0);
        ~About();
        
    private:
        Ui::About *ui;
};

#endif // ABOUT_HPP
