#pragma once
#include <concepts>

// PURPOSE:
// プレゼンテーション層へスペックデータを渡すための共通インターフェース契約
//　OutPortSpecDTOはフィールドのみのシンプルな構造とする
template <typename T,typename OutPortSpecDTO>
concept OutPortSpecProviderConcept = requires(T& t,const OutPortSpecDTO& spec)
{
    { t.provideSpecImpl(spec) }->std::same_as<void>;
};

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template <typename Derived,typename OutPortSpecDTO>
class IOutPortSpecProvider
{
public:
	void provideSpec(const OutPortSpecDTO& spec){return static_cast<Derived*>(this)->provideSpecImpl(spec);}
};
