#pragma once
namespace Core
{
	// PURPOSE:
	// クラス関用のデリゲート
	// HOW:
	// ディスパッチャクラス等のハンドラの抽象化に利用する
	// WHY:
	// 組み込み向けに軽量なデリゲートとして最低限の実装としている
	// SCOPE:
	// クラス関数以外には対応していない
	// 利用例：
	// using Handler = Core::Delegate<void>;
	// Handler delegate;
	// delegate = Handler::bind<Composition::ADSRViewController_t,&Composition::ADSRViewController_t::onUpButton>(&handler);
    template <typename Ret, typename... Args>
    class Delegate
	{
    public:
        using Stub = Ret(*)(void*, Args...);

        Delegate() = default;

        template <typename T, Ret(T::*method)(Args...)>
        static Delegate bind(T* instance) {
            Delegate d;
            d.instance_ = instance;
            d.stub_ = [](void* inst, Args... args) -> Ret {
                return (static_cast<T*>(inst)->*method)(args...);
            };
            return d;
        }

        Ret operator()(Args... args) const {
            return stub_(instance_, args...);
        }

        explicit operator bool() const { return stub_ != nullptr; }

    private:
        void* instance_ = nullptr;
        Stub stub_ = nullptr;
    };
}

