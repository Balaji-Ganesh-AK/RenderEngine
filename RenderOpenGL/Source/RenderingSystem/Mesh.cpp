#include "Mesh.h"


namespace KREngine
{
	void FMesh::SetTransform(const FTransform& transform)
	{
		Transform = transform;
	}

	void FMesh::SetLocation(const FVector& location)
	{
		Transform.SetLocation( location );
	}

	void FMesh::SetRotation(const FRotation& rotation)
	{
		Transform.SetRotation( rotation );
	}

	void FMesh::SetScale(const FVector& scale)
	{
		Transform.SetScale( scale );
	}

	void FMesh::SetTransform(FTransform& transform)
	{
		Transform = transform;
	}

	void FMesh::SetLocation(FVector& location)
	{
		Transform.SetLocation( location );
	}

	void FMesh::SetRotation(FRotation& rotation)
	{
		Transform.SetRotation( rotation );
	}

	void FMesh::SetScale(FVector& scale)
	{	Transform.SetScale( scale );
	}

	FTransform& FMesh::GetTransform()
	{
		return Transform;
	}

	FVector& FMesh::GetLocation()
	{
		return Transform.GetLocation();
	}

	FVector& FMesh::GetRotation()
	{
		return Transform.GetRotation();
	}

	FVector& FMesh::GetScale()
	{
		return Transform.GetScale();
	}
}
