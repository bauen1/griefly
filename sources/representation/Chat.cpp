#include "Chat.h"

#include "Text.h"
#include "core/Constheader.h"
#include "Screen.h"
#include "core/Helpers.h"
#include "core/Game.h"

#include <QUuid>
#include <QTextCursor>

Chat::Chat(GameInterface* game)
{
    game_ = game;
}

void Chat::PostSimpleText(const QString& str, quint32 tile_id)
{
    if (!game_->GetMap().IsTileVisible(tile_id))
    {
        return;
    }

    GetRepresentation().AddToNewFrame(
        Representation::ChatMessage{str.toHtmlEscaped()});
}

void Chat::PostHtmlText(const QString& str, quint32 tile_id)
{
    if (!game_->GetMap().IsTileVisible(tile_id))
    {
        return;
    }

    GetRepresentation().AddToNewFrame(
        Representation::ChatMessage{str});
}

void Chat::PostDamage(const QString& by, const QString& who, const QString& object, quint32 tile_id)
{
    if (!game_->GetMap().IsTileVisible(tile_id))
    {
        return;
    }

    QString q_by = by.toHtmlEscaped();
    QString q_who = who.toHtmlEscaped();
    QString q_object = object.toHtmlEscaped();

    GetRepresentation().AddToNewFrame(Representation::ChatMessage{
        QString("<font color=\"red\">%1 is attacked by %2 with %3</font>")
            .arg(q_by).arg(q_who).arg(q_object)});
}

void Chat::PostWords(const QString& who, const QString& text, quint32 tile_id)
{
    if (!game_->GetMap().IsTileVisible(tile_id))
    {
        return;
    }

    QString q_who = who.toHtmlEscaped();
    QString q_text = text.toHtmlEscaped();

    if (q_text.size() > 0)
    {
        q_text[0] = q_text[0].toUpper();
    }

    GetRepresentation().AddToNewFrame(Representation::ChatMessage{
        QString("<b>%1</b> <i>says</i>, <span>\"%2\"</span>").arg(q_who).arg(q_text)});
}

void Chat::PostTextFor(const QString& str, IdPtr<kv::MapObject> owner)
{
    if (game_->GetMob() == owner)
    {
        PostText(str);
    }
}

void Chat::PostHtmlFor(const QString& str, IdPtr<kv::MapObject> owner)
{
    if (game_->GetMob() == owner)
    {
        GetRepresentation().AddToNewFrame(Representation::ChatMessage{str});
    }
}

void Chat::PostText(const QString& str)
{
    QString loc = str.toHtmlEscaped();
    loc.replace('\n', "<br>");
    GetRepresentation().AddToNewFrame(Representation::ChatMessage{loc});
}

void Chat::PostOOCText(const QString &who, const QString& text)
{
    QString q_who = who.toHtmlEscaped();
    QString q_text = text.toHtmlEscaped();

    GetRepresentation().AddToNewFrame(Representation::ChatMessage{
        QString("<font color=\"blue\"><b>%1</b>: <span>%2</span></font>")
            .arg(q_who).arg(q_text)});
}
