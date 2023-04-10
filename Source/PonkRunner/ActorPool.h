// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Poolable.h"

//////////////////////////////////////////////////
////////////////////HEADER////////////////////////
//////////////////////////////////////////////////

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int>  = 0>
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
	// _pool.Reset();
	Clear();
	_world = world;
	SetTemplate(obj);
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> E0>
void ActorPool<T, E0>::Clear()
{
	_pool.Reset();
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
void ActorPool<T, Ty>::SetTemplate(TSubclassOf<AActor> obj)
{
	ObjectTemplate = obj;
	_name = FName(ObjectTemplate->GetName());
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Create(FVector const* position, FRotator const* rotation)
{
	AActor* spawned = _world->SpawnActor(ObjectTemplate, position, rotation);
	T* ret = Cast<T>(spawned);
	return ret;
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> Ty>
T* ActorPool<T, Ty>::Spawn()
{
	return Spawn(&FVector::ZeroVector, &FRotator::ZeroRotator);
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> E0>
T* ActorPool<T, E0>::Spawn(FVector const* position)
{
	return Spawn(position, &FRotator::ZeroRotator);
}

template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int> E0>
T* ActorPool<T, E0>::Spawn(FVector const* position, FRotator const* rotation)
{
	const int size = _pool.Num();

	T* ret;

	if (size <= 0)
	{
		ret = Create(position, rotation);
		ret->SetFolderPath(_name);
		// LOG("Created");
	}
	else
	{
		ret = _pool.Pop();
		// LOG("Popped");
	}

	APoolable* poolable = ret;
	poolable->SetActorLocation(*position);
	poolable->SetActorRotation(*rotation);
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
	// LOG("Returned");
}
