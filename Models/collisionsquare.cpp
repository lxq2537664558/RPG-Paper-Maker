/*
    RPG Paper Maker Copyright (C) 2017 Marie Laporte

    This file is part of RPG Paper Maker.

    RPG Paper Maker is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    RPG Paper Maker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "collisionsquare.h"
#include "wanok.h"

const QString CollisionSquare::JSON_RECT = "rec";
const QString CollisionSquare::JSON_LEFT = "l";
const QString CollisionSquare::JSON_RIGHT = "r";
const QString CollisionSquare::JSON_TOP = "t";
const QString CollisionSquare::JSON_BOT = "b";

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

CollisionSquare::CollisionSquare() :
    m_rect(new QRect(0, 0, Wanok::BASIC_SQUARE_SIZE, Wanok::BASIC_SQUARE_SIZE)),
    m_left(true),
    m_right(true),
    m_top(true),
    m_bot(true)
{

}

CollisionSquare::~CollisionSquare() {
    delete m_rect;
}

QRect* CollisionSquare::rect() const {
    return m_rect;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

// -------------------------------------------------------
//
//  READ / WRITE
//
// -------------------------------------------------------

void CollisionSquare::read(const QJsonObject &json) {
    QJsonArray tab = json[JSON_RECT].toArray();
    m_rect->setX(tab.at(0).toInt());
    m_rect->setY(tab.at(1).toInt());
    m_rect->setWidth(tab.at(2).toInt());
    m_rect->setHeight(tab.at(3).toInt());

    m_left = json[JSON_LEFT].toBool();
    m_right = json[JSON_RIGHT].toBool();
    m_top = json[JSON_TOP].toBool();
    m_bot = json[JSON_BOT].toBool();
}

void CollisionSquare::write(QJsonObject &json) const {
    QJsonArray tab;
    tab.append(m_rect->x());
    tab.append(m_rect->y());
    tab.append(m_rect->width());
    tab.append(m_rect->height());
    json[JSON_RECT] = tab;

    json[JSON_LEFT] = m_left;
    json[JSON_RIGHT] = m_right;
    json[JSON_TOP] = m_top;
    json[JSON_BOT] = m_bot;
}
