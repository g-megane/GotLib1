﻿//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<memory>

// シングルトン基底クラス
// このクラスを継承してシングルトンクラスを作成する
namespace got
{
	template <class T>
	class Singleton
	{
	public:
		static T& getInstance()
		{
			static typename T::singleton_pointer_type s_singleton(T::createInstance());
			return getReference(s_singleton);
		}

	private:
		typedef std::unique_ptr<T> singleton_pointer_type;
		// インスタンスの生成
		inline static T *createInstance() { return new T(); }
		// インスタンスの取得
		inline static T &getReference(const singleton_pointer_type &ptr)
		{
			return *ptr;
		}

	protected:
		Singleton() {}

	private:
		// コピーの禁止
		Singleton(const Singleton &) = delete;
		Singleton& operator=(const Singleton &) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton &&) = delete;
	};
}