// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Poolable.h"

//////////////////////////////////////////////////
////////////////////HEADER////////////////////////
//////////////////////////////////////////////////

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int>  = 1>
class ActorPool
{
public:
	static void Init(UWorld* world, TSubclassOf<AActor> obj);
	static void Clear();
	static void SetTemplate(TSubclassOf<AActor> obj);
	static T* Create(FVector const* position, FRotator const* rotation);
	static T* Spawn();
	static T* Spawn(FVector const* position);
	static T* Spawn(FVector const* position, FRotator const* rotation);
	static void Return(T* obj);

	static TSubclassOf<AActor> ObjectTemplate;
	static bool IsInitialized;

private:
	static FName _name;
	static UWorld* _world;
	static TArray<T*> _pool;
};


//////////////////////////////////////////////////
//////////////////////CPP/////////////////////////
//////////////////////////////////////////////////

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
bool ActorPool<T, Ty>::IsInitialized;

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
	Clear();
	_world = world;
	SetTemplate(obj);
	IsInitialized = true;
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::Clear()
{
	IsInitialized = false;
	_pool.Empty();
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::SetTemplate(TSubclassOf<AActor> obj)
{
	ObjectTemplate = obj;
	_name = FName(FString::Format(TEXT("Pool/{0}"), {ObjectTemplate->GetName()}));
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Create(FVector const* position, FRotator const* rotation)
{
	T* spawned = _world->SpawnActor<T>(ObjectTemplate, *position, *rotation);
	return spawned;
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Spawn()
{
	return Spawn(&FVector::ZeroVector, &FRotator::ZeroRotator);
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Spawn(FVector const* position)
{
	return Spawn(position, &FRotator::ZeroRotator);
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Spawn(FVector const* position, FRotator const* rotation)
{
	T* ret;

	APoolable* poolable;
	if (_pool.IsEmpty())
	{
		ret = Create(position, rotation);
		poolable = ret;
		poolable->OnCreated(_name);
	}
	else
	{
		ret = _pool.Pop(false);
		poolable = ret;
	}

	poolable->SetActorLocation(*position);
	poolable->SetActorRotation(*rotation);
	poolable->Spawned();

	return ret;
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::Return(T* obj)
{
	APoolable* poolable = obj;
	poolable->Reset();
	poolable->Returned();
	_pool.Add(obj);
}
