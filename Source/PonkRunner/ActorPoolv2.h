// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Poolable.h"

//////////////////////////////////////////////////
////////////////////HEADER////////////////////////
//////////////////////////////////////////////////

template <typename T>
class ActorPoolv2
{
	static_assert(std::is_base_of_v<APoolable, T>, "T must be derived APoolable");
public:
	static void Init(UWorld* world);
	static void Clear();
	static T* Create(TSubclassOf<AActor> objectTemplate, FVector const* position, FRotator const* rotation);
	static T* Spawn(TSubclassOf<AActor> objectTemplate);
	static T* Spawn(TSubclassOf<AActor> objectTemplate, FVector const* position);
	static T* Spawn(TSubclassOf<AActor> objectTemplate, FVector const* position, FRotator const* rotation);
	static void Return(T* obj);
	static bool IsInitialized;

private:
	static FName _name;
	static UWorld* _world;
	static TMap<TSubclassOf<AActor>, TArray<T*>> _mapPool;
};


//////////////////////////////////////////////////
//////////////////////CPP/////////////////////////
//////////////////////////////////////////////////

template<typename T>
bool ActorPoolv2<T>::IsInitialized;

template<typename T>
FName ActorPoolv2<T>::_name;

template<typename T>
UWorld* ActorPoolv2<T>::_world = nullptr;

template<typename T>
TMap<TSubclassOf<AActor>, TArray<T*>> ActorPoolv2<T>::_mapPool;

template<typename T>
void ActorPoolv2<T>::Init(UWorld* world)
{
	Clear();
	_world = world;
	IsInitialized = true;
}

template<typename T>
void ActorPoolv2<T>::Clear()
{
	IsInitialized = false;
	_mapPool.Empty();
}

template<typename T>
T* ActorPoolv2<T>::Create(TSubclassOf<AActor> objectTemplate, FVector const* position, FRotator const* rotation)
{
	T* spawned = _world->SpawnActor<T>(objectTemplate, *position, *rotation);
	return spawned;
}

template<typename T>
T* ActorPoolv2<T>::Spawn(TSubclassOf<AActor> objectTemplate)
{
	return Spawn(objectTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator);
}

template<typename T>
T* ActorPoolv2<T>::Spawn(TSubclassOf<AActor> objectTemplate, FVector const* position)
{
	return Spawn(objectTemplate, position, &FRotator::ZeroRotator);
}

template<typename T>
T* ActorPoolv2<T>::Spawn(TSubclassOf<AActor> objectTemplate, FVector const* position, FRotator const* rotation)
{
	TArray<T*>* arr;

	if (!_mapPool.Contains(objectTemplate))
	{
		arr = &_mapPool.Add(objectTemplate);
	}
	else
	{
		arr = &_mapPool[objectTemplate];
	}

	T* ret;

	if (arr->IsEmpty())
	{
		ret = Create(objectTemplate, position, rotation);
		ret->OnCreated(_name);
	}
	else
	{
		ret = arr->Pop(false);
	}

	ret->SetActorLocation(*position);
	ret->SetActorRotation(*rotation);
	ret->Spawned();

	return ret;
}

template<typename T>
void ActorPoolv2<T>::Return(T* obj)
{
	obj->Reset();
	obj->Returned();
	_mapPool[obj->GetClass()].Add(obj);
}
