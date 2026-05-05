// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/FPSGameHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class GRAPHICSPROGRAMMING2_API SFPSSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFPSSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AFPSGameHUD>, FPSGameHUD)
	SLATE_ARGUMENT(int, MyInt)
	SLATE_END_ARGS()

	TWeakObjectPtr<class AFPSGameHUD> FPSGameHUD;
	int MyInt;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnResumeClicked() const;
	FReply OnIntClicked() const;
	FReply OnQuitClicked() const;


	/* ----------Smart Pointers!! Yay!---------
	
	Unique Pointers: UniquePtr<T> = UniquePtr<int> score - > score is a unique pointer to an int. Only one unique pointer can point to a given object. When the unique pointer goes out of scope, the object it points to is automatically deleted.
		- Sole Owner of the object it's pointing towards
		- Cannot be copied, but can be moved (transferring ownership)
		- Automatically deletes the object when it goes out of scope, removing the need for manual deletion to prevent memory leaks
	
	Shared Pointers: SharedPtr<T> = SharedPtr<int> PlayerHealth -> PlayerHealth is a shared pointer to an int. Multiple shared pointers can point to the same object, and the object will only be deleted when the last shared pointer pointing to it is destroyed or reset.
		- Multiple ownership of the object it's pointing towards
		- Can be copied and moved/shared among multiple SharedPtr instances
		- Automatically deletes the object when the last SharedPtr pointing to it is destroyed or reset, using reference counting to manage the object's lifetime
		- UI Widgets, Game Objects shared across different systems, and any resource that needs to be shared across multiple parts of the codebase are good candidates for shared pointers.

	Weak Pointers: WeakPtr<T> = WeakPtr<int> EnemyCount -> EnemyCount is a weak pointer to an int. A weak pointer does not own the object it points to and does not contribute to the reference count. It can be used to observe an object without preventing its deletion, and it can be converted to a shared pointer if the object still exists.
		- Non-owning reference to an object managed by SharedPtr
		- Doesn't affect the Pointer/Reference count of the object. Or, creates the pointer without responsibility for the lifetime of the object.
		- Can be used to check if the object still exists without preventing its deletion
		- Useful for avoiding circular references that can lead to memory leaks, as it allows you to reference an object without increasing its reference count, thus not preventing its destruction when all SharedPtr instances are destroyed.
		- Good for Observer design patterns, Caches, and any situation where you want to reference an object without taking ownership or affecting its lifetime.

	Soft Object Pointers: SoftObjectPtr<T> = SoftObjectPtr<UTexture> MassiveTextureThatHasNoRightToBeThisBig -> MassiveTextureThatHasNoRightToBeThisBig is a soft object pointer to a UTexture. A soft object pointer is a reference to an asset that may not be loaded in memory. It can be used to reference assets without loading them until they are needed, which can help reduce memory usage and improve performance.
		- Reference to an asset that may not be loaded in memory
		- Can be used to reference assets without loading them until they are needed, helping to reduce memory usage and improve performance
		- Can be resolved to a hard pointer (T*) when the asset is loaded, allowing you to access the asset's properties and functions once it's available
		- Useful for managing large assets or resources that may not always be needed, such as textures, meshes, or audio files, allowing you to load them on demand rather than keeping them in memory at all times.
		- Load assets on demand, manage memory more efficiently, and improve performance by avoiding unnecessary loading of assets until they are actually needed in the game.
		- Good for spawning projectiles and initializing memory to ensure the proper textures appear on the projectiles, and for any situation where you want to reference an asset without loading it until it's necessary.

	
	
	
	
	
	
	
	*/






};
