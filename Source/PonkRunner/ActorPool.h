// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Poolable.h"
#include "PonkRunner.h"

//////////////////////////////////////////////////
////////////////////HEADER////////////////////////
//////////////////////////////////////////////////

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int>  = 0>
class ActorPool
{
public:
	static void Init(UWorld* world, TSubclassOf<AActor> obj);
	static void SetTemplate(TSubclassOf<AActor> obj);
	static T* Create();
	static T* Get();
	static void Return(T* obj);

	static TSubclassOf<AActor> ObjectTemplate;

private:
	static FName _name;
	static UWorld* _world;
	static TArray<T*> _pool;
};


//	linker will not work when put in another .cpp file, but this works

//////////////////////////////////////////////////
//////////////////////CPP/////////////////////////
//////////////////////////////////////////////////

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
FName ActorPool<T, Ty>::_name;

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
UWorld* ActorPool<T, Ty>::_world = nullptr;

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
TArray<T*> ActorPool<T, Ty>::_pool;

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
TSubclassOf<AActor> ActorPool<T, Ty>::ObjectTemplate;

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::Init(UWorld* world, TSubclassOf<AActor> obj)
{
	_pool.Reset();
	_world = world;
	SetTemplate(obj);
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::SetTemplate(TSubclassOf<AActor> obj)
{
	ObjectTemplate = obj;
	_name = FName(ObjectTemplate->GetName());
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Create()
{
	AActor* spawned = _world->SpawnActor(ObjectTemplate);
	T* ret = Cast<T>(spawned);
	return ret;
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Get()
{
	const int size = _pool.Num();

	T* ret;

	if (size <= 0)
	{
		ret = Create();
		ret->SetFolderPath(_name);
		LOG("Created");
	}
	else
	{
		ret = _pool.Pop();
		LOG("Popped");
	}

	APoolable* poolable = ret;
	poolable->SetActive(true);

	return ret;
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::Return(T* obj)
{
	APoolable* poolable = obj;
	poolable->Reset();
	poolable->SetActive(false);
	_pool.Add(obj);
	LOG("Returned");
}