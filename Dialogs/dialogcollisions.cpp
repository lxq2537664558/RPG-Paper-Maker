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

#include "dialogcollisions.h"
#include "ui_dialogcollisions.h"
#include "wanok.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogCollisions::DialogCollisions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCollisions)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());

    initializeTilesets();
    initializeCharacters();
    initializeAutotiles();
    initializeWalls();
}

DialogCollisions::~DialogCollisions()
{
    delete ui;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogCollisions::disablePanelListEdition(PanelSuperList* panel) {
    panel->showEditName(false);
    panel->showButtonMax(false);
    panel->list()->setHasContextMenu(false);
    panel->list()->setCanDragAndDrop(false);
}

// -------------------------------------------------------

void DialogCollisions::initializeTilesets() {

    // Initialize name & pictures
    ui->panelSuperListTilesets->list()->initializeNewItemInstance(
                new SystemTileset);
    ui->panelSuperListTilesets->initializeModel(Wanok::get()->project()
                                                ->gameDatas()->tilesetsDatas()
                                                ->model());
    connect(ui->panelSuperListTilesets->list()->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)), this,
            SLOT(on_tilesetSelected(QModelIndex,QModelIndex)));
    ui->widgetTilesetPictureSettings->setKind(PictureKind::Tilesets);
    disablePanelListEdition(ui->panelSuperListTilesets);

    // Select the first tileset
    QModelIndex index = ui->panelSuperListTilesets->list()->getModel()
            ->index(0,0);
    ui->panelSuperListTilesets->list()->setIndex(0);
    on_tilesetSelected(index,index);
}

// -------------------------------------------------------

void DialogCollisions::updateTileset(SystemTileset* tileset) {
    SystemPicture* picture = tileset->picture();
    ui->widgetTilesetPictureSettings->setSquares(picture->collisions());
    ui->widgetTilesetPictureSettings->updateImage(picture);
}

// -------------------------------------------------------

void DialogCollisions::initializeCharacters() {

    // Initialize name & pictures
    ui->panelSuperListCharacters->list()->initializeNewItemInstance(
                new SystemPicture);
    ui->panelSuperListCharacters->initializeModel(Wanok::get()->project()
                                              ->picturesDatas()
                                              ->model(PictureKind::Characters));
    connect(ui->panelSuperListCharacters->list()->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)), this,
            SLOT(on_characterSelected(QModelIndex,QModelIndex)));
    ui->widgetCharacterPraticable->setKind(PictureKind::Characters);
    ui->widgetCharacterPraticable->deleteDirectionTab();
    ui->widgetCharacterPraticable->showRepeat();
    disablePanelListEdition(ui->panelSuperListCharacters);

    // Select the first tileset
    QModelIndex index = ui->panelSuperListCharacters->list()->getModel()
            ->index(0,0);
    ui->panelSuperListCharacters->list()->setIndex(0);
    on_characterSelected(index,index);
}

// -------------------------------------------------------

void DialogCollisions::updateCharacter(SystemPicture* picture) {
    ui->widgetCharacterPraticable->setSquares(picture->collisions());
    ui->widgetCharacterPraticable->updateImage(picture);
    ui->widgetCharacterPraticable->disableNone(picture->id() == -1);
}

// -------------------------------------------------------

void DialogCollisions::initializeAutotiles() {

    // Initialize name & pictures
    ui->panelSuperListAutotiles->list()->initializeNewItemInstance(
                new SystemAutotile);
    ui->panelSuperListAutotiles->initializeModel(Wanok::get()->project()
                                                 ->specialElementsDatas()
                                                 ->modelAutotiles());
    connect(ui->panelSuperListAutotiles->list()->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)), this,
            SLOT(on_autotileSelected(QModelIndex,QModelIndex)));
    ui->widgetAutotilePictureSettings->setKind(PictureKind::Autotiles);
    disablePanelListEdition(ui->panelSuperListAutotiles);

    // Select the first tileset
    QModelIndex index = ui->panelSuperListAutotiles->list()->getModel()
            ->index(0,0);
    ui->panelSuperListAutotiles->list()->setIndex(0);
    on_autotileSelected(index,index);
}

// -------------------------------------------------------

void DialogCollisions::updateAutotile(SystemAutotile* autotile) {
    SystemPicture* picture = autotile->picture();
    ui->widgetAutotilePictureSettings->setSquares(picture->collisions());
    ui->widgetAutotilePictureSettings->updateImageAutotile(picture);
}

// -------------------------------------------------------

void DialogCollisions::initializeWalls() {

    // Initialize name & pictures
    ui->panelSuperListWalls->list()->initializeNewItemInstance(
                new SystemSpriteWall);
    ui->panelSuperListWalls->initializeModel(Wanok::get()->project()
                                             ->specialElementsDatas()
                                             ->modelSpriteWalls());
    connect(ui->panelSuperListWalls->list()->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)), this,
            SLOT(on_wallSelected(QModelIndex,QModelIndex)));
    ui->widgetWallPraticable->setKind(PictureKind::Walls);
    ui->widgetWallPraticable->deleteDirectionTab();
    disablePanelListEdition(ui->panelSuperListWalls);

    // Select the first tileset
    QModelIndex index = ui->panelSuperListWalls->list()->getModel()
            ->index(0,0);
    ui->panelSuperListWalls->list()->setIndex(0);
    on_wallSelected(index,index);
}

// -------------------------------------------------------

void DialogCollisions::updateWall(SystemSpriteWall *wall) {
    SystemPicture* picture = wall->picture();
    ui->widgetWallPraticable->setSquares(picture->collisions());
    ui->widgetWallPraticable->updateImage(picture);
    ui->widgetWallPraticable->disableNone(picture->id() == -1);
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogCollisions::on_tilesetSelected(QModelIndex index, QModelIndex) {
    QStandardItem* selected = ui->panelSuperListTilesets->list()->getModel()
            ->itemFromIndex(index);
    if (selected != nullptr)
        updateTileset((SystemTileset*)selected->data().value<quintptr>());
}

// -------------------------------------------------------

void DialogCollisions::on_characterSelected(QModelIndex index, QModelIndex) {
    QStandardItem* selected = ui->panelSuperListCharacters->list()->getModel()
            ->itemFromIndex(index);
    if (selected != nullptr)
        updateCharacter((SystemPicture*)selected->data().value<quintptr>());
}

// -------------------------------------------------------

void DialogCollisions::on_autotileSelected(QModelIndex index, QModelIndex) {
    QStandardItem* selected = ui->panelSuperListAutotiles->list()->getModel()
            ->itemFromIndex(index);
    if (selected != nullptr)
        updateAutotile((SystemAutotile*)selected->data().value<quintptr>());
}

// -------------------------------------------------------

void DialogCollisions::on_wallSelected(QModelIndex index, QModelIndex) {
    QStandardItem* selected = ui->panelSuperListWalls->list()->getModel()
            ->itemFromIndex(index);
    if (selected != nullptr)
        updateWall((SystemSpriteWall*)selected->data().value<quintptr>());
}
