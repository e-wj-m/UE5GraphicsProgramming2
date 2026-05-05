// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Sphere Collision Component, which will be used as the root component of the projectile.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent")); // The SphereComponent is being created as a default subobject of the projectile, and is being given the name "SphereComponent".
	CollisionComponent->InitSphereRadius(15.0f); // The radius of the sphere is being initialized to 15.0f units, which will determine the size of the collision area for the projectile.
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile")); // The collision profile for the Sphere Collision Component is being set to "Projectile", which means that it will use the predefined collision settings associated with that profile, allowing it to interact with other objects in the game world according to those settings.
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit); // The OnComponentHit event of the Sphere Collision Component is being bound to the OnHit function of the projectile, which means that whenever the projectile collides with another object in the game world, the OnHit function will be called to handle the collision event.
	RootComponent = CollisionComponent; // The Sphere Collision Component is being set as the root component of the projectile, which means that it will be the primary component that defines the position and orientation of the projectile in the game world.

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent")); // The Static Mesh Component is being created as a default subobject of the projectile, and is being given the name "ProjectileMeshComponent". This component will be used to visually represent the projectile in the game world.

	//1. Setup using the imported mesh in the project, which is a sphere mesh.
	 static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Meshes/Projectile/Sphere.Sphere"));

	//2. Setup using the built-in Engine sphere mesh.
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));

	if (ProjectileMeshAsset.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object); // If the mesh asset is successfully found, it is being set as the static mesh for the ProjectileMeshComponent, which will allow it to be rendered in the game world.
	}

	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f)); // The relative scale of the Static Mesh Component is being set to a small value (0.09f) in all three dimensions (X, Y, Z), which will make the visual representation of the projectile smaller in size.
	ProjectileMeshComponent->SetupAttachment(RootComponent); // The Static Mesh Component is being attached to the root component (the Sphere Collision Component) of the projectile, which means that it will move and rotate along with the root component. This allows the visual representation of the projectile to be properly aligned with its collision area.

	//3. Setting up materials from the project. This is entirely done through code as opposed to in the editor itself.
	static ConstructorHelpers::FObjectFinder<UMaterial> ProjectileMaterialAsset(TEXT("/Game/Materials/M_Projectile.M_Projectile"));

	if (ProjectileMaterialAsset.Succeeded()) // If the material asset is successfully found, a dynamic material instance is being created from the material asset and assigned to the ProjectileMaterialInstance variable. This allows for dynamic changes to the material properties at runtime, such as changing colors or other visual effects on the projectile.
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(ProjectileMaterialAsset.Object, ProjectileMeshComponent);
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent")); // The Projectile Movement Component is being created as a default subobject of the projectile, and is being given the name "ProjectileMovementComponent". This component will be responsible for handling the movement and physics of the projectile in the game world.))
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent); // Setting the UpdatedComponent of the Projectile Movement Component to the Collision Component means that the movement and physics calculations performed by the Projectile Movement Component will be applied to the Collision Component, allowing it to move and interact with other objects in the game world based on the defined movement behavior of the projectile.
	ProjectileMovementComponent->InitialSpeed = BulletSpeed; //	Setting the InitialSpeed of the Projectile Movement Component to the value of BulletSpeed means that the projectile will start moving at the specified speed when it is spawned in the game world, allowing for consistent and predictable behavior of the projectile's movement right from the moment it is created.
	ProjectileMovementComponent->MaxSpeed = BulletSpeed; // Setting the InitialSpeed and MaxSpeed of the Projectile Movement Component to the value of BulletSpeed means that the projectile will start moving at the specified speed and will not exceed that speed during its movement, allowing for consistent and predictable behavior of the projectile in the game world.
	ProjectileMovementComponent->bRotationFollowsVelocity = true; // Setting bRotationFollowsVelocity to true means that the projectile will automatically rotate to face the direction it is moving in, which can help improve the visual realism of the projectile's movement.
	ProjectileMovementComponent->bShouldBounce = true; // Setting bShouldBounce to true means that the projectile will simulate bouncing behavior when it collides with surfaces, allowing it to ricochet off walls and other objects in the game world.
	ProjectileMovementComponent->Bounciness = 0.3; // Setting the Bounciness of the Projectile Movement Component to 0.3 means that when the projectile collides with a surface, it will retain 30% of its velocity after the bounce, allowing for a more realistic bouncing behavior where the projectile loses some speed upon impact but still continues to move.
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // Setting the ProjectileGravityScale to 0.0f means that the projectile will not be affected by gravity, allowing it to maintain a straight trajectory without dropping over distance.

	InitialLifeSpan = 5.0f; // Setting the InitialLifeSpan of the projectile to 5.0f means that the projectile will automatically be destroyed after 5 seconds in the game world, preventing it from existing indefinitely and helping to manage resources effectively.
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection) // Memory Address - Passing by reference is more efficient than passing by value for complex data types like FVector, as it avoids the overhead of copying the entire vector each time the function is called. By using a reference, we can directly access and modify the original vector without creating unnecessary copies, which can improve performance, especially if this function is called frequently or if the FVector is large. Additionally, passing by reference allows for modifications to the ShootDirection within the function to be reflected outside the function, which can be useful if we want to update the direction based on certain conditions or calculations.
{
	//1. FVector ShootDirection - Passing by value, not that efficient except for making copies of the vector every time it's called. This is not a problem for this function since it is only called once per projectile, but if this function were to be called multiple times per projectile, it would be more efficient to pass the FVector
	//2. FVector* ShootDirection - Passing by pointer, more efficient as we're using the memory address instead of making copies of the vector each call. However, the pointer MUST be dereferenced, and a check for null pointers should be implemented to avoid potential crashes if a null pointer is passed in.
	//3. FVector& ShootDirection - Passing by reference, also more efficient as we're using the memory address without the need for pointer syntax. This is often the preferred method in C++ for passing complex data types like FVector, as it provides the efficiency of pointers while maintaining safer syntax and avoiding issues with null pointers.
	//4. const FVector& ShootDirection - Pass by Constant Reference, this is the most efficient and safest way to pass the FVector if we do not intend to modify it within the function. It allows us to avoid unnecessary copying while also ensuring that the original vector cannot be modified, which can help prevent bugs and improve code safety.

	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed; // Setting the Velocity of the Projectile Movement Component to the ShootDirection multiplied by the InitialSpeed means that the projectile will start moving in the specified direction at the defined speed, allowing for consistent and predictable behavior of the projectile's movement in the game world.

}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint); // Applying an impulse to the OtherComponent at the location of the hit, with a magnitude based on the projectile's velocity, allows for realistic physics interactions when the projectile collides with other objects in the game world, such as pushing or knocking them back based on the force of the impact.
		Destroy();
	}
}
