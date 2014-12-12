/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
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
#include "jsonsnippettranslator.h"

#include <QJsonArray>
#include <QJsonDocument>

#include "snippet.h"
#include "snippetcollection.h"

namespace {

static const QLatin1String TRIGGER("trigger");
static const QLatin1String DESCRIPTION("description");
static const QLatin1String SNIPPET("snippet");
static const QLatin1String CURSOR("cursor");
static const QLatin1String BUILTIN("builtIn");

}

bool JsonSnippetTranslator::processDocument(const QJsonDocument &jsonDocument, JsonCollection<Snippet> *collection)
{
    if (!isValid(jsonDocument, collection->name()))
        return false;

    QJsonArray snippetArray = jsonDocument.object().value(collection->name()).toArray();
    foreach (QJsonValue entry, snippetArray) {
        Snippet snippet = fromJsonObject(entry.toObject());
        collection->insert(snippet);
    }

    return true;
}

QJsonDocument JsonSnippetTranslator::createDocument(JsonCollection<Snippet> *collection)
{
    QJsonArray snippetArray;
    for (int i = 0; i < collection->count(); ++i) {
        Snippet snippet = collection->at(i);

        QJsonObject entry = toJsonObject(snippet);
        snippetArray.append(entry);
    }

    QJsonObject object;
    object.insert(collection->name(), snippetArray);

    QJsonDocument doc(object);
    return doc;
}

Snippet JsonSnippetTranslator::fromJsonObject(const QJsonObject &object)
{
    Snippet snippet;

    snippet.trigger = object.value(TRIGGER).toString();
    snippet.description = object.value(DESCRIPTION).toString();
    snippet.snippet = object.value(SNIPPET).toString();
    snippet.cursorPosition = object.value(CURSOR).toDouble();
    snippet.builtIn = object.value(BUILTIN).toBool();

    return snippet;
}

QJsonObject JsonSnippetTranslator::toJsonObject(const Snippet &snippet)
{
    QJsonObject object;

    object.insert(TRIGGER, snippet.trigger);
    object.insert(DESCRIPTION, snippet.description);
    object.insert(SNIPPET, snippet.snippet);
    object.insert(CURSOR, snippet.cursorPosition);
    object.insert(BUILTIN, snippet.builtIn);

    return object;
}

bool JsonSnippetTranslator::isValid(const QJsonDocument &jsonDocument, const QString &arrayName) const
{
    return !jsonDocument.isEmpty() &&
           jsonDocument.isObject() &&
           jsonDocument.object().contains(arrayName) &&
           jsonDocument.object().value(arrayName).isArray();
}
