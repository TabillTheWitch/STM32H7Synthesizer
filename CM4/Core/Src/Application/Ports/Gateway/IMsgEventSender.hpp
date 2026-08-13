#pragma once
#include <concepts>
#include "MsgEventId.hpp"

using namespace Domain::Event;

// PURPOSE:
// 別コアへメッセージイベントを送信するための共通インターフェース契約
template <typename T>
concept MsgEventSenderConcept = requires(T& t,MsgEventId& eventid)
{
    { t.msgSend(eventid) }->std::same_as<bool>;
};

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template <typename Derived>
class IMsgEventSender
{
public:
	bool msgSend(MsgEventId& eventid){return static_cast<Derived*>(this)->msgSendImpl(eventid);}

};
