#pragma once
#include <concepts>

// PURPOSE:
// プレゼンテーション層へデータを渡すための共通インターフェース契約
//　OutPortDTOはフィールドのみのシンプルな構造とする
template <typename T,typename OutPortDTO>
concept OutPortPresenterConcept = requires(T& t,const OutPortDTO& dto)
{
    { t.presentOutPortImpl(dto) }->std::same_as<void>;
};

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template <typename Derived,typename OutPortDTO>
class IOutPortPresenter
{
public:
	void presentOutPort(const OutPortDTO& dto){return static_cast<Derived*>(this)->presentOutPortImpl(dto);}
};
