#pragma once
#include <concepts>
#include "ADSRParam.hpp"
#include "ADSRGateWayTag.hpp"

using namespace::Domain::ADSR;
using namespace::Application::Ports::GateWay;

// PURPOSE:
// ADSRパラメータをストレージへロード／ストアするための共通インターフェース契約
// WAY:
// 各パラメータをタグ型で識別し、フィールド単位の読み書きも可能にする
template <typename T>
concept ADSRStorageAccessConcept = requires(T& t,ADSRParam& adsr,float data,float& dataref)
{
    { t.loadImpl(adsr) }->std::same_as<bool>;
    { t.loadFieldImpl(Tags::ADSRAttack{},dataref) }->std::same_as<bool>;
    { t.loadFieldImpl(Tags::ADSRDecay{},dataref) }->std::same_as<bool>;
    { t.loadFieldImpl(Tags::ADSRSustain{},dataref) }->std::same_as<bool>;
    { t.loadFieldImpl(Tags::ADSRSustainReset{},dataref) }->std::same_as<bool>;
    { t.loadFieldImpl(Tags::ADSRRelease{},dataref) }->std::same_as<bool>;
    { t.storeImpl(adsr) }->std::same_as<bool>;
    { t.updateFieldImpl(Tags::ADSRAttack{},data) }->std::same_as<bool>;
    { t.updateFieldImpl(Tags::ADSRDecay{},data) }->std::same_as<bool>;
    { t.updateFieldImpl(Tags::ADSRSustain{},data) }->std::same_as<bool>;
    { t.updateFieldImpl(Tags::ADSRSustainReset{},data) }->std::same_as<bool>;
    { t.updateFieldImpl(Tags::ADSRRelease{},data) }->std::same_as<bool>;
};

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template <typename Derived>
class IADSRStorageAccess
{
public:
	bool load(ADSRParam& param){return static_cast<Derived*>(this)->loadImpl(param);}
	bool loadField(Tags::ADSRAttack field, float& data){return static_cast<Derived*>(this)->loadFieldImpl(field,data);}
	bool loadField(Tags::ADSRDecay field, float& data){return static_cast<Derived*>(this)->loadFieldImpl(field,data);}
	bool loadField(Tags::ADSRSustain field, float& data){return static_cast<Derived*>(this)->loadFieldImpl(field,data);}
	bool loadField(Tags::ADSRSustainReset field, float& data){return static_cast<Derived*>(this)->loadFieldImpl(field,data);}
	bool loadField(Tags::ADSRRelease field, float& data){return static_cast<Derived*>(this)->loadFieldImpl(field,data);}
	bool store(const ADSRParam& param){return static_cast<Derived*>(this)->storeImpl(param);}
	bool updateField(Tags::ADSRAttack field,const float data){return static_cast<Derived*>(this)->updateFieldImpl(field,data);}
	bool updateField(Tags::ADSRDecay field,const float data){return static_cast<Derived*>(this)->updateFieldImpl(field,data);}
	bool updateField(Tags::ADSRSustain field,const float data){return static_cast<Derived*>(this)->updateFieldImpl(field,data);}
	bool updateField(Tags::ADSRSustainReset field,const float data){return static_cast<Derived*>(this)->updateFieldImpl(field,data);}
	bool updateField(Tags::ADSRRelease field,const float data){return static_cast<Derived*>(this)->updateFieldImpl(field,data);}
};
