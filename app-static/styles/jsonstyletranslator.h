/*
 * Copyright 2014 Christian Loose <christian.loose@hamburg.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef JSONSTYLETRANSLATOR_H
#define JSONSTYLETRANSLATOR_H

#include "json/jsontranslator.h"
#include <QJsonObject>
class QJsonDocument;
struct Style;


class JsonStyleTranslator : public JsonTranslator<Style>
{
public:
    bool processDocument(const QJsonDocument &jsonDocument, JsonCollection<Style> *collection) Q_DECL_OVERRIDE;
    QJsonDocument createDocument(JsonCollection<Style> *collection) Q_DECL_OVERRIDE;

private:
    Style fromJsonObject(const QJsonObject &object);
    QJsonObject toJsonObject(const Style &style);

    bool isValid(const QJsonDocument &jsonDocument, const QString &arrayName) const;
};

#endif // JSONSTYLETRANSLATOR_H

