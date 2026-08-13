#pragma once
#include "ADSRParam.hpp"
#include "SharedADSRParamPod.hpp"
#include "IADSRStorageAccess.hpp"
#include "SharedMemoryAccessor.hpp"

using namespace Domain::ADSR;

namespace Infrastructure::SharedMemory
{
	// PURPOSE:
	// 共有メモリに配置されるADSRパラメータの取得/更新を実行するクラス
	// WAY:
	// タグで取得/更新するフィールドの識別を可能とする
	// sharedMemoryInitializationをコンストラクタから分離する意図は
	// 起動直後に共有メモリの値を参照すると処理が停止するため
	//　CONSTRAINT：
	// sharedMemoryInitializationは起動後少なくとも10ms経過した後に実行すること
	class SharedADSRStorage : public IADSRStorageAccess<SharedADSRStorage>
	{
	public:
		SharedADSRStorage(SharedMemoryAccessor& accessor)
			: m_Accessor(accessor) {}

		bool loadImpl(ADSRParam& param);
		bool loadFieldImpl(Tags::ADSRAttack,float& data);
		bool loadFieldImpl(Tags::ADSRDecay,float& data);
		bool loadFieldImpl(Tags::ADSRSustain,float& data);
		bool loadFieldImpl(Tags::ADSRSustainReset,float& data);
		bool loadFieldImpl(Tags::ADSRRelease,float& data);
		bool storeImpl(const ADSRParam& param);
		bool updateFieldImpl(Tags::ADSRAttack,const float data);
		bool updateFieldImpl(Tags::ADSRDecay,const float data);
		bool updateFieldImpl(Tags::ADSRSustain,const float data);
		bool updateFieldImpl(Tags::ADSRSustainReset,const float data);
		bool updateFieldImpl(Tags::ADSRRelease,const float data);
		bool sharedMemoryInitialization();
	private:
		ADSRParam m_AdsrCache{};
		SharedMemoryAccessor& m_Accessor;

	};
}

#include "SharedADSRStorage_Impl.hpp"
